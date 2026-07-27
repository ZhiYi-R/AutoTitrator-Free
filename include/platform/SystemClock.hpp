/**
 * @file    SystemClock.hpp
 * @brief   系统时钟配置（HSE 8MHz → PLL ×9 → SYSCLK 72MHz）
 */

#pragma once

#include <stm32f103/FLASH.hpp>
#include <stm32f103/RCC.hpp>

namespace Platform {

/**
 * @brief 系统时钟配置
 *
 * HSE 8MHz → PLL ×9 → SYSCLK 72MHz
 * AHB=72MHz, APB1=36MHz, APB2=72MHz, ADC=12MHz, Flash latency=2
 */
class SystemClock {
public:
    /**
     * @brief 初始化系统时钟（一次性，复位后调用）
     */
    static void initialize() noexcept {
        using namespace STM32F103;

        /** 启用 HSE */
        RCC::CR::WriteHSEON(1);
        while (RCC::CR::ReadHSERDY() == 0) {
            /** 等待 HSE 就绪 */
        }

        /** Flash latency = 2 (72MHz) + 预取使能 */
        FLASH::ACR::WriteLATENCY(2);
        FLASH::ACR::WritePRFTBE(1);
        while (FLASH::ACR::ReadPRFTBE() == 0) {
            /** 等待预取缓冲使能 */
        }

        /** 总线分频：AHB=/1, APB1=/2, APB2=/1, ADC=APB2/6 */
        RCC::CFGR::WriteHPRE(0);     /** AHB = SYSCLK */
        RCC::CFGR::WritePPRE1(4);    /** APB1 = AHB/2 (0b100) */
        RCC::CFGR::WritePPRE2(0);    /** APB2 = AHB */
        RCC::CFGR::WriteADCPRE(3);   /** ADC = APB2/6 (0b11) */

        /** PLL: HSE /1 → ×9 */
        RCC::CFGR::WritePLLSRC(1);   /** PLL source = HSE */
        RCC::CFGR::WritePLLXTPRE(0); /** HSE before PLL = /1 */
        RCC::CFGR::WritePLLMUL(7);   /** PLL ×9 (0b0111) */

        /** 启用 PLL */
        RCC::CR::WritePLLON(1);
        while (RCC::CR::ReadPLLRDY() == 0) {
            /** 等待 PLL 就绪 */
        }

        /** 切换系统时钟到 PLL */
        RCC::CFGR::WriteSW(2); /** SW = PLL (0b10) */
        while (RCC::CFGR::ReadSWS() != 2) {
            /** 等待切换完成 */
        }

        /** 启用 CSS（HSE 失效时自动切回 HSI 并触发 NMI） */
        RCC::CR::WriteCSSON(1);
    }

    SystemClock() = delete;
};

} // namespace Platform
