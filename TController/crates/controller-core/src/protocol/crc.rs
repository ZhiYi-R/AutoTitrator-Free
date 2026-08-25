//! CRC-8（Maxim-Dallas 变体，多项式 0x31）— 与固件 `CommandDispatcher` 一致。

#[inline]
fn crc8_update(crc: u8, data: u8) -> u8 {
    let mut crc = crc ^ data;
    for _ in 0..8 {
        crc = if crc & 0x80 != 0 {
            (crc << 1) ^ 0x31
        } else {
            crc << 1
        };
    }
    crc
}

/// 计算字节流的 CRC-8（初值 0）。
pub fn crc8(data: &[u8]) -> u8 {
    let mut crc: u8 = 0;
    for &b in data {
        crc = crc8_update(crc, b);
    }
    crc
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn matches_python_reference_vectors() {
        // 与 Python `_crc8` 实测一致的参照向量
        assert_eq!(crc8(&[]), 0x00);
        assert_eq!(crc8(&[0x00, 0x01]), 0x31);
        let mut v = vec![0x20];
        v.extend_from_slice(&(0u8..11).collect::<Vec<u8>>());
        assert_eq!(crc8(&v), 0xCA);
    }
}
