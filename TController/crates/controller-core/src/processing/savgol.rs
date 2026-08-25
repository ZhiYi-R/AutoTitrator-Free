//! Savitzky-Golay 平滑（对称窗口，离线用）— Python `savgol_filter` 的移植。

/// 最小二乘系数：`coeffs = solve(AᵀA, Aᵀ)[0]`，A 为范德蒙德矩阵（升幂）。
///
/// 即 X = (AᵀA)⁻¹·Aᵀ 的第 0 行（长度 = window）。实现上先解
/// `AᵀA·y = e₀`，再由 `coeffs[i] = Σ_j y[j]·x_i^j` 展开回长度 window。
pub fn savgol_coeffs(window: usize, order: usize) -> Result<Vec<f64>, String> {
    if window.is_multiple_of(2) {
        return Err(format!("window 必须为奇数，得到 {window}"));
    }
    let half = window / 2;
    let m = order + 1;

    // A[i][j] = x_i^j, x_i ∈ [-half, half]
    let mut ata = vec![vec![0.0; m]; m];
    let mut xs = Vec::with_capacity(window);
    for i in -(half as i32)..=(half as i32) {
        let x = i as f64;
        xs.push(x);
        let row: Vec<f64> = (0..m).map(|j| x.powi(j as i32)).collect();
        for a in 0..m {
            for b in 0..m {
                ata[a][b] += row[a] * row[b];
            }
        }
    }
    // 解 AᵀA·y = e₀
    let mut rhs = vec![0.0; m];
    rhs[0] = 1.0;
    let y = solve_linear(&mut ata, rhs).ok_or("savgol: 奇异法方程矩阵")?;
    // coeffs[i] = Σ_j y[j]·x_i^j = (X 的第 0 行)
    Ok(xs
        .iter()
        .map(|&x| (0..m).map(|j| y[j] * x.powi(j as i32)).sum::<f64>())
        .collect())
}

/// 对信号做边缘填充后按系数卷积（等价 `np.convolve(padded, coeffs[::-1], 'valid')`）。
pub fn savgol_filter(signal: &[f64], window: usize, order: usize) -> Result<Vec<f64>, String> {
    if signal.is_empty() {
        return Ok(Vec::new());
    }
    let coeffs = savgol_coeffs(window, order)?;
    let half = window / 2;

    let mut padded = Vec::with_capacity(signal.len() + 2 * half);
    padded.extend(std::iter::repeat_n(signal[0], half));
    padded.extend_from_slice(signal);
    padded.extend(std::iter::repeat_n(*signal.last().unwrap(), half));

    // valid 卷积（核已反转）= 与 coeffs 的互相关
    Ok((0..signal.len())
        .map(|i| (0..window).map(|k| coeffs[k] * padded[i + k]).sum::<f64>())
        .collect())
}

/// 高斯消元（部分主元）解小型稠密线性方程组。
fn solve_linear(a: &mut [Vec<f64>], mut b: Vec<f64>) -> Option<Vec<f64>> {
    let n = a.len();
    for col in 0..n {
        // 选主元
        let pivot =
            (col..n).max_by(|&i, &j| a[i][col].abs().partial_cmp(&a[j][col].abs()).unwrap())?;
        if a[pivot][col].abs() < 1e-12 {
            return None;
        }
        a.swap(col, pivot);
        b.swap(col, pivot);

        let div = a[col][col];
        for j in col..n {
            a[col][j] /= div;
        }
        b[col] /= div;

        for i in (col + 1)..n {
            let factor = a[i][col];
            if factor == 0.0 {
                continue;
            }
            for j in col..n {
                a[i][j] -= factor * a[col][j];
            }
            b[i] -= factor * b[col];
        }
    }
    // 回代
    for i in (0..n).rev() {
        for j in (i + 1)..n {
            b[i] -= a[i][j] * b[j];
        }
    }
    Some(b)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn constant_signal_is_unchanged() {
        let y = vec![5.0; 20];
        let out = savgol_filter(&y, 5, 2).unwrap();
        for v in out {
            approx::assert_relative_eq!(v, 5.0, epsilon = 1e-9);
        }
    }

    #[test]
    fn linear_signal_is_unchanged_for_order_2() {
        let y: Vec<f64> = (0..20).map(|i| i as f64 * 0.5 + 1.0).collect();
        let out = savgol_filter(&y, 7, 2).unwrap();
        // edge 填充 + valid 卷积下，边缘半窗口有多项式拟合偏差
        // （Python np.pad('edge') 版本同样如此）；内部点应精确还原线性信号。
        for (i, v) in out.iter().enumerate().skip(3).take(y.len() - 6) {
            approx::assert_relative_eq!(*v, y[i], epsilon = 1e-9);
        }
        assert!(out.iter().all(|v| v.is_finite()));
    }

    #[test]
    fn even_window_is_rejected() {
        assert!(savgol_coeffs(4, 2).is_err());
    }
}
