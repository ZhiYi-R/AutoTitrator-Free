//! AMPD（自动多尺度峰值检测）— Python `_ampd_peak_idx` 向量化版本的逐位移植。
//!
//! 逐尺度即时归约而不物化稠密 `L×N` 局部极大矩阵；严格比较、首个 argmin/argmax
//! 与 Python/NumPy 一致。

/// 返回最显著 AMPD 峰索引，无峰返回 `None`。
pub fn ampd_peak_idx(signal: &[f64]) -> Option<usize> {
    let n = signal.len();
    if n < 12 {
        return None;
    }
    let l = n / 2 - 1;
    if l < 2 {
        return None;
    }

    // 尺度 k 的局部极大判定：sig[i] 严格大于两侧 sig[i±k]（i ∈ [k, N-k)）。
    let row = |k: usize, i: usize| signal[i] > signal[i - k] && signal[i] > signal[i + k];

    // gamma[k-1] 为尺度 k 的极大计数；sigma 是信号最稳定呈峰的尺度（首个最小值）。
    let gamma: Vec<i64> = (1..=l)
        .map(|k| (k..n - k).filter(|&i| row(k, i)).count() as i64)
        .collect();
    let sigma = gamma
        .iter()
        .enumerate()
        .min_by(|a, b| a.1.partial_cmp(b.1).unwrap())
        .map(|(idx, _)| idx)?;

    let mut score = vec![0i64; n];
    // Python: for k in range(sigma + 1, L + 1)；sigma 是 0 基 gamma 索引，
    // 故实际起始尺度 k = sigma + 1。
    for k in (sigma + 1)..=l {
        for i in k..n - k {
            if row(k, i) {
                score[i] += 1;
            }
        }
    }
    let best = score
        .iter()
        .enumerate()
        .max_by(|a, b| a.1.partial_cmp(b.1).unwrap())
        .map(|(idx, _)| idx)?;
    (score[best] > 0).then_some(best)
}

#[cfg(test)]
mod tests {
    use super::*;

    /// 稠密 O(N²) 参照实现（Python 测试 `_ampd_reference` 的移植，作 oracle）。
    fn ampd_dense_reference(signal: &[f64]) -> Option<usize> {
        let n = signal.len();
        if n < 12 {
            return None;
        }
        let l = n / 2 - 1;
        if l < 2 {
            return None;
        }
        let mut lms = vec![vec![0i64; n]; l];
        for k in 1..=l {
            for i in k..n - k {
                if signal[i] > signal[i - k] && signal[i] > signal[i + k] {
                    lms[k - 1][i] = 1;
                }
            }
        }
        let row_sums: Vec<i64> = lms.iter().map(|r| r.iter().sum()).collect();
        let sigma = row_sums
            .iter()
            .enumerate()
            .min_by(|a, b| a.1.partial_cmp(b.1).unwrap())
            .map(|(idx, _)| idx)?;
        let mut score = vec![0i64; n];
        for row in &lms[sigma..] {
            for (i, &v) in row.iter().enumerate() {
                score[i] += v;
            }
        }
        let best = score
            .iter()
            .enumerate()
            .max_by(|a, b| a.1.partial_cmp(b.1).unwrap())
            .map(|(idx, _)| idx)?;
        (score[best] > 0).then_some(best)
    }

    /// 与 Python 测试同源的确定性伪随机（xorshift64*，足够做 oracle 对照）。
    struct Rng(u64);
    impl Rng {
        fn next_f64(&mut self) -> f64 {
            // xorshift64*
            let mut x = self.0;
            x ^= x >> 12;
            x ^= x << 25;
            x ^= x >> 27;
            self.0 = x;
            let v = x.wrapping_mul(0x2545F4914F6CDD1D);
            (v >> 11) as f64 / (1u64 << 53) as f64
        }
        fn normal(&mut self) -> f64 {
            // Box-Muller
            let u1 = self.next_f64().max(1e-12);
            let u2 = self.next_f64();
            (-2.0 * u1.ln()).sqrt() * (std::f64::consts::TAU * u2).cos()
        }
    }

    #[test]
    fn reduction_matches_dense_reference() {
        let mut cases: Vec<Vec<f64>> = vec![
            vec![0.0; 40],
            vec![1.0; 40],
            (0..40).map(|i| i as f64).collect(),
            (0..40).rev().map(|i| i as f64).collect(),
            vec![1.0, 2.0, 1.0],
            (0..12).map(|i| i as f64 / 11.0).collect(),
        ];
        let mut rng = Rng(20260821);
        for &length in &[13usize, 25, 64, 137] {
            cases.push((0..length).map(|_| rng.normal()).collect());
            let peak: Vec<f64> = (0..length)
                .map(|i| {
                    let c = 0.6 * length as f64;
                    (-((i as f64 - c).powi(2)) / (2.0 * (length as f64 / 12.0).powi(2))).exp()
                })
                .collect();
            cases.push(peak.iter().map(|&p| p + 0.05 * rng.normal()).collect());
        }
        for case in &cases {
            assert_eq!(
                ampd_peak_idx(case),
                ampd_dense_reference(case),
                "case len={}",
                case.len()
            );
        }
    }

    #[test]
    fn short_signals_return_none() {
        assert_eq!(ampd_peak_idx(&[1.0, 2.0, 1.0]), None);
        assert_eq!(ampd_peak_idx(&[0.0; 11]), None);
    }
}
