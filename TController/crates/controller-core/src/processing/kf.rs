//! 终点融合 Kalman 滤波器 — Python `EndpointFusionKF` 的移植。
//!
//! 两状态线性 KF：状态 = [终点体积, 光谱延迟]。
//! 电位观测 H=[1,0]；光谱观测 H=[1,1]（光谱终点 = 终点 + 延迟）。

use std::collections::HashSet;

use serde::Serialize;

/// 观测模态。
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, Serialize)]
#[serde(rename_all = "lowercase")]
pub enum ObservationKind {
    Potential,
    Spectral,
}

impl ObservationKind {
    pub fn as_str(self) -> &'static str {
        match self {
            ObservationKind::Potential => "potential",
            ObservationKind::Spectral => "spectral",
        }
    }
}

/// NIS 门限：每次观测的新息为标量，卡方门 1 自由度，6.635 是 chi2(1) 的 99 分位。
/// （旧值 9.21 是 chi2(2) 分位，属自由度错配。）
pub const DEFAULT_NIS_GATE: f64 = 6.635;

/// `observe` 的结果快照（Python `_snapshot` 字段一一对应）。
#[derive(Debug, Clone, PartialEq, Serialize)]
pub struct KfSnapshot {
    pub initialized: bool,
    pub endpoint_volume: Option<f64>,
    pub spectral_delay: Option<f64>,
    pub endpoint_std: Option<f64>,
    pub innovation: Option<f64>,
    pub innovation_covariance: Option<f64>,
    pub nis: Option<f64>,
    pub accepted: bool,
    pub kind: Option<String>,
    pub consistent: bool,
    pub reason: String,
}

impl Default for KfSnapshot {
    fn default() -> Self {
        Self {
            initialized: false,
            endpoint_volume: None,
            spectral_delay: None,
            endpoint_std: None,
            innovation: None,
            innovation_covariance: None,
            nis: None,
            accepted: false,
            kind: None,
            consistent: false,
            reason: "no_observation".into(),
        }
    }
}

/// 两状态 KF。
#[derive(Debug, Clone)]
pub struct EndpointFusionKf {
    pub potential_var: f64,
    pub spectral_var: f64,
    pub delay_var: f64,
    pub process_var: f64,
    pub delay_prior: f64,
    pub nis_gate: f64,

    x: [f64; 2],
    p: [[f64; 2]; 2],
    initialized: bool,
    observed_potential: bool,
    observed_spectral: bool,
    tokens: HashSet<String>,
    last: KfSnapshot,
}

impl Default for EndpointFusionKf {
    fn default() -> Self {
        Self::new()
    }
}

impl EndpointFusionKf {
    pub fn new() -> Self {
        Self::with_params(
            0.012, // potential_std
            0.025, // spectral_std
            0.08,  // delay_std
            0.004, // process_std
            0.02,  // delay_prior
            DEFAULT_NIS_GATE,
        )
    }

    #[allow(clippy::too_many_arguments)]
    pub fn with_params(
        potential_std: f64,
        spectral_std: f64,
        delay_std: f64,
        process_std: f64,
        delay_prior: f64,
        nis_gate: f64,
    ) -> Self {
        let mut kf = Self {
            potential_var: (potential_std * potential_std).max(1e-8),
            spectral_var: (spectral_std * spectral_std).max(1e-8),
            delay_var: (delay_std * delay_std).max(1e-8),
            process_var: (process_std * process_std).max(1e-10),
            delay_prior,
            nis_gate: nis_gate.max(1.0),
            x: [0.0; 2],
            p: [[1e6, 0.0], [0.0, 1e6]],
            initialized: false,
            observed_potential: false,
            observed_spectral: false,
            tokens: HashSet::new(),
            last: KfSnapshot::default(),
        };
        kf.reset();
        kf
    }

    pub fn reset(&mut self) {
        self.x = [0.0; 2];
        self.p = [[1e6, 0.0], [0.0, 1e6]];
        self.initialized = false;
        self.observed_potential = false;
        self.observed_spectral = false;
        self.tokens.clear();
        self.last = KfSnapshot::default();
    }

    fn prediction(&self) -> ([f64; 2], [[f64; 2]; 2]) {
        if !self.initialized {
            return (self.x, self.p);
        }
        let mut p = self.p;
        p[0][0] += self.process_var;
        p[1][1] += self.process_var;
        (self.x, p)
    }

    fn consistent(&self) -> bool {
        self.observed_potential && self.observed_spectral
    }

    fn make_snapshot(
        &self,
        kind: ObservationKind,
        innovation: f64,
        innovation_covariance: f64,
        nis: f64,
        accepted: bool,
        reason: &str,
    ) -> KfSnapshot {
        KfSnapshot {
            initialized: self.initialized,
            endpoint_volume: Some(self.x[0]),
            spectral_delay: Some(self.x[1]),
            endpoint_std: Some(self.p[0][0].max(0.0).sqrt()),
            innovation: Some(innovation),
            innovation_covariance: Some(innovation_covariance),
            nis: Some(nis),
            accepted,
            kind: Some(kind.as_str().to_string()),
            consistent: self.consistent(),
            reason: reason.to_string(),
        }
    }

    /// 消费一条终点观测；token 重复时幂等返回上次快照。
    pub fn observe(
        &mut self,
        kind: ObservationKind,
        volume: f64,
        token: Option<&str>,
    ) -> KfSnapshot {
        let token_owned = token
            .map(str::to_string)
            .unwrap_or_else(|| default_token(kind, volume));
        if self.tokens.contains(&token_owned) {
            return self.last.clone();
        }
        let z = volume;
        if !z.is_finite() {
            let mut snap = self.last.clone();
            snap.kind = Some(kind.as_str().to_string());
            snap.accepted = false;
            snap.reason = "nonfinite_observation".into();
            self.last = snap;
            return self.last.clone();
        }

        if !self.initialized {
            match kind {
                ObservationKind::Potential => {
                    self.x = [z, 0.0];
                    self.p = [[self.potential_var, 0.0], [0.0, self.delay_var]];
                    self.observed_potential = true;
                }
                ObservationKind::Spectral => {
                    self.x = [z - self.delay_prior, self.delay_prior];
                    self.p = [
                        [self.spectral_var + self.delay_var, 0.0],
                        [0.0, self.delay_var],
                    ];
                    self.observed_spectral = true;
                }
            }
            self.initialized = true;
            self.tokens.insert(token_owned);
            self.last = self.make_snapshot(kind, 0.0, self.p[0][0], 0.0, true, "initialized");
            return self.last.clone();
        }

        let (x_prior, p_prior) = self.prediction();
        let (h, r) = match kind {
            ObservationKind::Potential => ([1.0, 0.0], self.potential_var),
            ObservationKind::Spectral => ([1.0, 1.0], self.spectral_var),
        };
        let h_x = h[0] * x_prior[0] + h[1] * x_prior[1];
        let innovation = z - h_x;
        // S = h·P·hᵀ + R，按 NumPy (h@P)@h 的左结合顺序展开
        let hp = [
            h[0] * p_prior[0][0] + h[1] * p_prior[1][0],
            h[0] * p_prior[0][1] + h[1] * p_prior[1][1],
        ];
        let s = hp[0] * h[0] + hp[1] * h[1] + r;
        let s = s.max(1e-10);
        let nis = innovation * innovation / s;
        let accepted = nis <= self.nis_gate;

        if accepted {
            // K = P·hᵀ / S（P 对称，P·h = [P00·h0 + P01·h1, P10·h0 + P11·h1]）
            let k = [
                (p_prior[0][0] * h[0] + p_prior[0][1] * h[1]) / s,
                (p_prior[1][0] * h[0] + p_prior[1][1] * h[1]) / s,
            ];
            self.x = [
                x_prior[0] + k[0] * innovation,
                x_prior[1] + k[1] * innovation,
            ];
            // P = (I − K⊗h)·P
            let p00 = (1.0 - k[0] * h[0]) * p_prior[0][0] - k[0] * h[1] * p_prior[1][0];
            let p01 = (1.0 - k[0] * h[0]) * p_prior[0][1] - k[0] * h[1] * p_prior[1][1];
            let p10 = -k[1] * h[0] * p_prior[0][0] + (1.0 - k[1] * h[1]) * p_prior[1][0];
            let p11 = -k[1] * h[0] * p_prior[0][1] + (1.0 - k[1] * h[1]) * p_prior[1][1];
            // P ← 0.5·(P + Pᵀ)：对角不变，非对角取平均
            self.p = [[p00, 0.5 * (p01 + p10)], [0.5 * (p10 + p01), p11]];
            match kind {
                ObservationKind::Potential => self.observed_potential = true,
                ObservationKind::Spectral => self.observed_spectral = true,
            }
            self.tokens.insert(token_owned);
        } else {
            self.x = x_prior;
            self.p = p_prior;
        }
        self.last = self.make_snapshot(
            kind,
            innovation,
            s,
            nis,
            accepted,
            if accepted { "accepted" } else { "nis_gate" },
        );
        self.last.clone()
    }

    pub fn snapshot(&self) -> KfSnapshot {
        self.last.clone()
    }

    /// 双模态均已接受观测且最近一次观测通过门控。
    pub fn can_fuse(&self) -> bool {
        self.consistent() && self.last.accepted
    }

    /// 融合后的终点体积（未融合时无意义）。
    pub fn endpoint_volume(&self) -> f64 {
        self.x[0]
    }
}

fn default_token(kind: ObservationKind, volume: f64) -> String {
    // Python 默认 token = (kind, round(volume, 9))；格式化保留 9 位小数等价。
    format!("{}:{:.9}", kind.as_str(), volume)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn gate_and_repeated_observation_are_stable() {
        let mut kf = EndpointFusionKf::with_params(0.01, 0.01, 0.08, 0.004, 0.02, 3.84);
        let initial = kf.observe(ObservationKind::Potential, 1.0, Some("potential-1"));
        assert!(initial.accepted);
        let accepted = kf.observe(ObservationKind::Spectral, 1.03, Some("spectral-1"));
        assert!(accepted.accepted);
        assert!(accepted.consistent);
        let repeated = kf.observe(ObservationKind::Spectral, 1.03, Some("spectral-1"));
        assert_eq!(repeated, accepted);
        let rejected = kf.observe(ObservationKind::Potential, 2.0, Some("potential-2"));
        assert!(!rejected.accepted);
        assert_eq!(rejected.reason, "nis_gate");
        assert!(rejected.endpoint_std.unwrap().is_finite());
    }

    #[test]
    fn reset_lets_a_revised_endpoint_pair_refuse() {
        // 复刻 Paper/ExpData 回归：被顶替的光谱终点必须能重新融合，
        // 而不是被去重 token 挡住。
        let mut kf = EndpointFusionKf::with_params(0.01, 0.01, 0.08, 0.004, 0.02, DEFAULT_NIS_GATE);
        kf.observe(ObservationKind::Potential, 2.1475, Some("potential@2.1475"));
        let stale = kf.observe(ObservationKind::Spectral, 1.1805, Some("spectral@1.1805"));
        assert!(!stale.accepted);
        assert_eq!(stale.reason, "nis_gate");
        assert!(!kf.can_fuse());

        kf.reset();
        kf.observe(ObservationKind::Potential, 2.1475, Some("potential@2.1475"));
        let revised = kf.observe(ObservationKind::Spectral, 2.1489, Some("spectral@2.1489"));
        assert!(revised.accepted);
        assert!(revised.consistent);
        assert!(kf.can_fuse());
    }

    #[test]
    fn nonfinite_observation_is_rejected_not_corrupting() {
        let mut kf = EndpointFusionKf::new();
        let snap = kf.observe(ObservationKind::Potential, f64::NAN, None);
        assert!(!snap.accepted);
        assert_eq!(snap.reason, "nonfinite_observation");
        assert!(!kf.initialized);
    }
}
