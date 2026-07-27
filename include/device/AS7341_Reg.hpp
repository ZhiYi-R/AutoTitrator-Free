/**
 * @file    AS7341_Reg.hpp
 * @brief   AS7341 光谱传感器寄存器定义与 SMUX 配置表
 */

#pragma once

#include <cstdint>

namespace Device::AS7341_Reg {

/**
 * @brief AS7341 寄存器地址
 */
enum class Reg : uint8_t {
    ADDR = 0x39,    /** 7 位 I2C 地址 */
    ADDR_W = 0x72,  /** 写地址（8 位） */
    ADDR_R = 0x73,  /** 读地址（8 位） */

    CONFIG = 0x70,
    STAT = 0x71,
    EDGE = 0x72,
    GPIO = 0x73,
    LED = 0x74,
    ENABLE = 0x80,
    ATIME = 0x81,
    WTIME = 0x83,
    SP_TH_L_LSB = 0x84,
    SP_TH_L_MSB = 0x85,
    SP_TH_H_LSB = 0x86,
    SP_TH_H_MSB = 0x87,
    AUXID = 0x90,
    REVID = 0x91,
    ID = 0x92,
    STATUS_1 = 0x93,
    ASTATUS = 0x94,
    CH0_DATA_L = 0x95,
    CH0_DATA_H = 0x96,
    CH1_DATA_L = 0x97,
    CH1_DATA_H = 0x98,
    CH2_DATA_L = 0x99,
    CH2_DATA_H = 0x9A,
    CH3_DATA_L = 0x9B,
    CH3_DATA_H = 0x9C,
    CH4_DATA_L = 0x9D,
    CH4_DATA_H = 0x9E,
    CH5_DATA_L = 0x9F,
    CH5_DATA_H = 0xA0,
    STATUS_2 = 0xA3,
    STATUS_3 = 0xA4,
    STATUS_5 = 0xA6,
    STATUS_6 = 0xA7,
    CFG_0 = 0xA9,
    CFG_1 = 0xAA,
    CFG_3 = 0xAC,
    CFG_6 = 0xAF,
    CFG_8 = 0xB1,
    CFG_9 = 0xB2,
    CFG_10 = 0xB3,
    CFG_12 = 0xB5,
    PERS = 0xBD,
    GPIO_2 = 0xBE,
    ASTEP_L = 0xCA,
    ASTEP_H = 0xCB,
    INTENAB = 0xF9,
    CONTROL = 0xFA,
    FIFO_MAP = 0xFC,
    FIFO_LVL = 0xFD,
    FDATA_L = 0xFE,
    FDATA_H = 0xFF,
};

/**
 * @brief 到 uint8_t 的隐式转换
 * @param r 寄存器枚举值
 * @return 寄存器地址
 */
inline constexpr uint8_t operator+(Reg r) noexcept {
    return static_cast<uint8_t>(r);
}

/**
 * @brief ADC 增益预设
 */
enum class AGain : uint8_t {
    X0_5 = 0,
    X1 = 1,
    X2 = 2,
    X4 = 3,
    X8 = 4,
    X16 = 5,
    X32 = 6,
    X64 = 7,
    X128 = 8,
    X256 = 9,
    X512 = 10,
};

/**
 * @brief 一次 AS7341 全扫描的完整光谱测量结果
 *
 * 两 phase 扫描：F1F4(Clear+NIR) → F5F8(Clear+NIR)
 * Clear 和 nm910 取两次平均值
 */
struct SpectralData {
    uint16_t nm415; /** F1 (405-425nm, 中心 415nm) */
    uint16_t nm445; /** F2 (435-455nm, 中心 445nm) */
    uint16_t nm480; /** F3 (470-490nm, 中心 480nm) */
    uint16_t nm515; /** F4 (505-525nm, 中心 515nm) */
    uint16_t nm555; /** F5 (545-565nm, 中心 555nm) */
    uint16_t nm590; /** F6 (580-600nm, 中心 590nm) */
    uint16_t nm630; /** F7 (620-640nm, 中心 630nm) */
    uint16_t nm680; /** F8 (670-690nm, 中心 680nm) */
    uint16_t Clear; /** 宽谱可见光通道（两次平均） */
    uint16_t nm910; /** NIR (~910nm, 两次平均) */
};

/** F1-F4 + Clear + NIR 的 SMUX 配置 */
inline constexpr uint8_t SMUX_F1F4[20]{
    0x30, 0x01, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00,
    0x50, 0x00, 0x00, 0x00, 0x20, 0x04, 0x00, 0x30,
    0x01, 0x50, 0x00, 0x06,
};

/** F5-F8 + Clear + NIR 的 SMUX 配置 */
inline constexpr uint8_t SMUX_F5F8[20]{
    0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x10, 0x03,
    0x50, 0x10, 0x03, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x50, 0x00, 0x06,
};

} // namespace Device::AS7341_Reg
