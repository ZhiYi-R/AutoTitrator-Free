//! 一阶因果指数移动平均。

/// 因果 EWMA（Python `_EWMA` / `_ScalarEWMA`）。
#[derive(Debug, Clone, Copy)]
pub struct Ewma {
    alpha: f64,
    value: Option<f64>,
}

impl Ewma {
    pub fn new(alpha: f64) -> Self {
        Self {
            alpha: alpha.clamp(0.0, 1.0),
            value: None,
        }
    }

    pub fn push(&mut self, x: f64) -> f64 {
        self.value = Some(match self.value {
            None => x,
            Some(v) => self.alpha * x + (1.0 - self.alpha) * v,
        });
        self.value.unwrap()
    }

    /// 当前水平；未初始化返回 0.0（Python `hold()`）。
    pub fn hold(&self) -> f64 {
        self.value.unwrap_or(0.0)
    }

    pub fn value(&self) -> Option<f64> {
        self.value
    }

    pub fn reset(&mut self) {
        self.value = None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn first_sample_initializes() {
        let mut e = Ewma::new(0.15);
        assert_eq!(e.push(1.0), 1.0);
        // 0.15·2 + 0.85·1 = 1.15
        approx::assert_relative_eq!(e.push(2.0), 1.15);
        assert_eq!(e.hold(), 1.15);
    }
}
