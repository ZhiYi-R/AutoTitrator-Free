//! 谱散度函数 — JS 散度（有界）、旧版交叉熵与 KL（`cross_entropy_excess`）。

/// 数值下限（Python `_EPS`）。
pub const EPS: f64 = 1e-12;
/// JS 实测舍入下界（Python `_JS_FLOOR`）：
/// float64 上真实 8 通道帧的 JS 舍入下界约 5e-17，平台期约 2e-12，终点事件约 2e-7。
/// js_speed 除以体积步长平方（约 4e7 倍放大），低于此下界的 JS 绝不能归一化。
pub const JS_FLOOR: f64 = 1e-14;

/// NumPy `np.sum` 的成对求和逐位复刻（loops_utils.h `pairwise_sum`）：
/// n<8 顺序累加；n≤128 用 8 累加器树；更大者对半递归。
/// 与 NumPy 的求和舍入完全一致，是两实现数值一致的前提。
pub fn np_sum(a: &[f64]) -> f64 {
    const PW_BLOCKSIZE: usize = 128;
    let n = a.len();
    if n < 8 {
        let mut res = 0.0;
        for &x in a {
            res += x;
        }
        return res;
    }
    if n <= PW_BLOCKSIZE {
        let mut r = [0.0f64; 8];
        r.copy_from_slice(&a[..8]);
        let mut i = 8;
        let limit = n - (n % 8);
        while i < limit {
            for j in 0..8 {
                r[j] += a[i + j];
            }
            i += 8;
        }
        let mut res = ((r[0] + r[1]) + (r[2] + r[3])) + ((r[4] + r[5]) + (r[6] + r[7]));
        while i < n {
            res += a[i];
            i += 1;
        }
        return res;
    }
    // n > 128：对半递归
    let n2 = n / 2;
    np_sum(&a[..n - n2]) + np_sum(&a[n - n2..])
}

/// 帧级检查+归一化（Python `_finite_vector`）：非负、有限、和为 1。
/// 返回 `Err(原因)` 供诊断字段使用，与 Python 的 reason 字符串一致。
pub fn finite_vector(values: &[f64]) -> Result<Vec<f64>, &'static str> {
    if values.is_empty() {
        return Err("spectrum_empty");
    }
    if !values.iter().all(|v| v.is_finite()) {
        return Err("spectrum_nonfinite");
    }
    let clipped: Vec<f64> = values.iter().map(|v| v.max(0.0)).collect();
    let total = np_sum(&clipped);
    if total <= EPS {
        return Err("spectrum_zero");
    }
    Ok(clipped.into_iter().map(|v| v / total).collect())
}

/// 加性平滑归一化（Python `normalize_spectrum`，ε=1e-9）。
pub fn normalize_spectrum(values: &[f64]) -> Result<Vec<f64>, String> {
    if values.is_empty() || !values.iter().all(|v| v.is_finite()) {
        return Err("spectrum must be a non-empty finite array".into());
    }
    let smoothed: Vec<f64> = values.iter().map(|v| v.max(0.0) + 1e-9).collect();
    let sum = np_sum(&smoothed);
    Ok(smoothed.into_iter().map(|v| v / sum).collect())
}

/// 自然对数底的 Jensen-Shannon 散度（对称，值域 [0, ln2]）。
///
/// 元素级运算与两段求和的分组顺序均与 NumPy 版一致（0.5·Σp + 0.5·Σq）。
pub fn js_divergence(p: &[f64], q: &[f64]) -> f64 {
    let p = normalize_spectrum(p).expect("js_divergence: invalid p");
    let q = normalize_spectrum(q).expect("js_divergence: invalid q");
    let p_part: Vec<f64> = p
        .iter()
        .zip(&q)
        .map(|(&pi, &qi)| pi * (pi / (0.5 * (pi + qi))).ln())
        .collect();
    let q_part: Vec<f64> = q
        .iter()
        .zip(&p)
        .map(|(&qi, &pi)| qi * (qi / (0.5 * (pi + qi))).ln())
        .collect();
    let value = 0.5 * np_sum(&p_part) + 0.5 * np_sum(&q_part);
    value.clamp(0.0, std::f64::consts::LN_2)
}

/// 旧版方向性交叉熵（保留供旧脚本读取，勿用于驱动阈值状态机）。
pub fn cross_entropy(p: &[f64], q: &[f64]) -> f64 {
    let p = normalize_spectrum(p).expect("cross_entropy: invalid p");
    let q = normalize_spectrum(q).expect("cross_entropy: invalid q");
    let part: Vec<f64> = p
        .iter()
        .zip(&q)
        .map(|(&pi, &qi)| pi * qi.max(1e-12).ln())
        .collect();
    -np_sum(&part)
}

/// 去自身下界的交叉熵 = KL(p‖q)：恒等分布为 0，可与退出阈值比较。
///
/// `cross_entropy(p,p)` 是 p 的熵（~ln n），不是 0，直接驱动状态机会永远出不去
/// IN_CHANGE；减去下界后才是可用的 KL。
pub fn cross_entropy_excess(p: &[f64], q: &[f64]) -> f64 {
    let p = normalize_spectrum(p).expect("cross_entropy_excess: invalid p");
    let q = normalize_spectrum(q).expect("cross_entropy_excess: invalid q");
    let delta: Vec<f64> = p
        .iter()
        .zip(&q)
        .map(|(&pi, &qi)| pi * (pi.max(1e-12).ln() - qi.max(1e-12).ln()))
        .collect();
    np_sum(&delta).max(0.0)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn js_is_symmetric_bounded_and_gain_invariant() {
        let p = [1.0, 2.0, 4.0, 8.0];
        let q = [2.0, 3.0, 5.0, 7.0];
        let pq = js_divergence(&p, &q);
        let qp = js_divergence(&q, &p);
        approx::assert_relative_eq!(pq, qp);
        assert!((0.0..=std::f64::consts::LN_2).contains(&pq));
        let scaled = [17.0, 34.0, 68.0, 136.0];
        let scaled_q = [34.0, 51.0, 85.0, 119.0];
        // Python np.isclose 默认 rtol=1e-5；放大 17 倍引入 ~1e-9 相对舍入差
        approx::assert_relative_eq!(pq, js_divergence(&scaled, &scaled_q), max_relative = 1e-6);
    }

    #[test]
    fn identical_distributions_have_zero_js_and_excess() {
        let v = [1.0, 2.0, 3.0, 4.0];
        approx::assert_relative_eq!(js_divergence(&v, &v), 0.0, epsilon = 1e-15);
        approx::assert_relative_eq!(cross_entropy_excess(&v, &v), 0.0, epsilon = 1e-12);
    }

    #[test]
    fn finite_vector_reports_reasons() {
        assert_eq!(finite_vector(&[]), Err("spectrum_empty"));
        assert_eq!(
            finite_vector(&[1.0, f64::NAN, 1.0]),
            Err("spectrum_nonfinite")
        );
        assert_eq!(finite_vector(&[0.0, 0.0]), Err("spectrum_zero"));
        let n = finite_vector(&[1.0, 3.0]).unwrap();
        approx::assert_relative_eq!(n[1], 0.75);
    }

    #[test]
    fn cross_entropy_floor_is_entropy_not_zero() {
        let identical = [1.0, 2.0, 3.0, 4.0];
        assert!(cross_entropy(&identical, &identical) > 1.0);
        assert!(cross_entropy_excess(&identical, &[4.0, 3.0, 2.0, 1.0]) > 0.0);
    }
}
