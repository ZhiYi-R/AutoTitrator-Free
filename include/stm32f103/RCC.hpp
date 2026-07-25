#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::RCC {

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000083;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadHSION() noexcept -> ValueType { return Reg::Read<F_HSION>(); }
    static void WriteHSION(ValueType value) noexcept { Reg::Write<F_HSION>(value); }
    static auto ReadHSIRDY() noexcept -> ValueType { return Reg::Read<F_HSIRDY>(); }
    static auto ReadHSITRIM() noexcept -> ValueType { return Reg::Read<F_HSITRIM>(); }
    static void WriteHSITRIM(ValueType value) noexcept { Reg::Write<F_HSITRIM>(value); }
    static auto ReadHSICAL() noexcept -> ValueType { return Reg::Read<F_HSICAL>(); }
    static auto ReadHSEON() noexcept -> ValueType { return Reg::Read<F_HSEON>(); }
    static void WriteHSEON(ValueType value) noexcept { Reg::Write<F_HSEON>(value); }
    static auto ReadHSERDY() noexcept -> ValueType { return Reg::Read<F_HSERDY>(); }
    static auto ReadHSEBYP() noexcept -> ValueType { return Reg::Read<F_HSEBYP>(); }
    static void WriteHSEBYP(ValueType value) noexcept { Reg::Write<F_HSEBYP>(value); }
    static auto ReadCSSON() noexcept -> ValueType { return Reg::Read<F_CSSON>(); }
    static void WriteCSSON(ValueType value) noexcept { Reg::Write<F_CSSON>(value); }
    static auto ReadPLLON() noexcept -> ValueType { return Reg::Read<F_PLLON>(); }
    static void WritePLLON(ValueType value) noexcept { Reg::Write<F_PLLON>(value); }
    static auto ReadPLLRDY() noexcept -> ValueType { return Reg::Read<F_PLLRDY>(); }

private:
    static constexpr std::uintptr_t Address = 0x40021000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HSION = CortexM3::Field<ValueType, 0, 1>;
    using F_HSIRDY = CortexM3::Field<ValueType, 1, 1>;
    using F_HSITRIM = CortexM3::Field<ValueType, 3, 5>;
    using F_HSICAL = CortexM3::Field<ValueType, 8, 8>;
    using F_HSEON = CortexM3::Field<ValueType, 16, 1>;
    using F_HSERDY = CortexM3::Field<ValueType, 17, 1>;
    using F_HSEBYP = CortexM3::Field<ValueType, 18, 1>;
    using F_CSSON = CortexM3::Field<ValueType, 19, 1>;
    using F_PLLON = CortexM3::Field<ValueType, 24, 1>;
    using F_PLLRDY = CortexM3::Field<ValueType, 25, 1>;
};

class CFGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSW() noexcept -> ValueType { return Reg::Read<F_SW>(); }
    static void WriteSW(ValueType value) noexcept { Reg::Write<F_SW>(value); }
    static auto ReadSWS() noexcept -> ValueType { return Reg::Read<F_SWS>(); }
    static auto ReadHPRE() noexcept -> ValueType { return Reg::Read<F_HPRE>(); }
    static void WriteHPRE(ValueType value) noexcept { Reg::Write<F_HPRE>(value); }
    static auto ReadPPRE1() noexcept -> ValueType { return Reg::Read<F_PPRE1>(); }
    static void WritePPRE1(ValueType value) noexcept { Reg::Write<F_PPRE1>(value); }
    static auto ReadPPRE2() noexcept -> ValueType { return Reg::Read<F_PPRE2>(); }
    static void WritePPRE2(ValueType value) noexcept { Reg::Write<F_PPRE2>(value); }
    static auto ReadADCPRE() noexcept -> ValueType { return Reg::Read<F_ADCPRE>(); }
    static void WriteADCPRE(ValueType value) noexcept { Reg::Write<F_ADCPRE>(value); }
    static auto ReadPLLSRC() noexcept -> ValueType { return Reg::Read<F_PLLSRC>(); }
    static void WritePLLSRC(ValueType value) noexcept { Reg::Write<F_PLLSRC>(value); }
    static auto ReadPLLXTPRE() noexcept -> ValueType { return Reg::Read<F_PLLXTPRE>(); }
    static void WritePLLXTPRE(ValueType value) noexcept { Reg::Write<F_PLLXTPRE>(value); }
    static auto ReadPLLMUL() noexcept -> ValueType { return Reg::Read<F_PLLMUL>(); }
    static void WritePLLMUL(ValueType value) noexcept { Reg::Write<F_PLLMUL>(value); }
    static auto ReadOTGFSPRE() noexcept -> ValueType { return Reg::Read<F_OTGFSPRE>(); }
    static void WriteOTGFSPRE(ValueType value) noexcept { Reg::Write<F_OTGFSPRE>(value); }
    static auto ReadMCO() noexcept -> ValueType { return Reg::Read<F_MCO>(); }
    static void WriteMCO(ValueType value) noexcept { Reg::Write<F_MCO>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SW = CortexM3::Field<ValueType, 0, 2>;
    using F_SWS = CortexM3::Field<ValueType, 2, 2>;
    using F_HPRE = CortexM3::Field<ValueType, 4, 4>;
    using F_PPRE1 = CortexM3::Field<ValueType, 8, 3>;
    using F_PPRE2 = CortexM3::Field<ValueType, 11, 3>;
    using F_ADCPRE = CortexM3::Field<ValueType, 14, 2>;
    using F_PLLSRC = CortexM3::Field<ValueType, 16, 1>;
    using F_PLLXTPRE = CortexM3::Field<ValueType, 17, 1>;
    using F_PLLMUL = CortexM3::Field<ValueType, 18, 4>;
    using F_OTGFSPRE = CortexM3::Field<ValueType, 22, 1>;
    using F_MCO = CortexM3::Field<ValueType, 24, 3>;
};

class CIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLSIRDYF() noexcept -> ValueType { return Reg::Read<F_LSIRDYF>(); }
    static auto ReadLSERDYF() noexcept -> ValueType { return Reg::Read<F_LSERDYF>(); }
    static auto ReadHSIRDYF() noexcept -> ValueType { return Reg::Read<F_HSIRDYF>(); }
    static auto ReadHSERDYF() noexcept -> ValueType { return Reg::Read<F_HSERDYF>(); }
    static auto ReadPLLRDYF() noexcept -> ValueType { return Reg::Read<F_PLLRDYF>(); }
    static auto ReadCSSF() noexcept -> ValueType { return Reg::Read<F_CSSF>(); }
    static auto ReadLSIRDYIE() noexcept -> ValueType { return Reg::Read<F_LSIRDYIE>(); }
    static void WriteLSIRDYIE(ValueType value) noexcept { Reg::Write<F_LSIRDYIE>(value); }
    static auto ReadLSERDYIE() noexcept -> ValueType { return Reg::Read<F_LSERDYIE>(); }
    static void WriteLSERDYIE(ValueType value) noexcept { Reg::Write<F_LSERDYIE>(value); }
    static auto ReadHSIRDYIE() noexcept -> ValueType { return Reg::Read<F_HSIRDYIE>(); }
    static void WriteHSIRDYIE(ValueType value) noexcept { Reg::Write<F_HSIRDYIE>(value); }
    static auto ReadHSERDYIE() noexcept -> ValueType { return Reg::Read<F_HSERDYIE>(); }
    static void WriteHSERDYIE(ValueType value) noexcept { Reg::Write<F_HSERDYIE>(value); }
    static auto ReadPLLRDYIE() noexcept -> ValueType { return Reg::Read<F_PLLRDYIE>(); }
    static void WritePLLRDYIE(ValueType value) noexcept { Reg::Write<F_PLLRDYIE>(value); }
    static void WriteLSIRDYC(ValueType value) noexcept { Reg::Write<F_LSIRDYC>(value); }
    static void WriteLSERDYC(ValueType value) noexcept { Reg::Write<F_LSERDYC>(value); }
    static void WriteHSIRDYC(ValueType value) noexcept { Reg::Write<F_HSIRDYC>(value); }
    static void WriteHSERDYC(ValueType value) noexcept { Reg::Write<F_HSERDYC>(value); }
    static void WritePLLRDYC(ValueType value) noexcept { Reg::Write<F_PLLRDYC>(value); }
    static void WriteCSSC(ValueType value) noexcept { Reg::Write<F_CSSC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LSIRDYF = CortexM3::Field<ValueType, 0, 1>;
    using F_LSERDYF = CortexM3::Field<ValueType, 1, 1>;
    using F_HSIRDYF = CortexM3::Field<ValueType, 2, 1>;
    using F_HSERDYF = CortexM3::Field<ValueType, 3, 1>;
    using F_PLLRDYF = CortexM3::Field<ValueType, 4, 1>;
    using F_CSSF = CortexM3::Field<ValueType, 7, 1>;
    using F_LSIRDYIE = CortexM3::Field<ValueType, 8, 1>;
    using F_LSERDYIE = CortexM3::Field<ValueType, 9, 1>;
    using F_HSIRDYIE = CortexM3::Field<ValueType, 10, 1>;
    using F_HSERDYIE = CortexM3::Field<ValueType, 11, 1>;
    using F_PLLRDYIE = CortexM3::Field<ValueType, 12, 1>;
    using F_LSIRDYC = CortexM3::Field<ValueType, 16, 1>;
    using F_LSERDYC = CortexM3::Field<ValueType, 17, 1>;
    using F_HSIRDYC = CortexM3::Field<ValueType, 18, 1>;
    using F_HSERDYC = CortexM3::Field<ValueType, 19, 1>;
    using F_PLLRDYC = CortexM3::Field<ValueType, 20, 1>;
    using F_CSSC = CortexM3::Field<ValueType, 23, 1>;
};

class APB2RSTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadAFIORST() noexcept -> ValueType { return Reg::Read<F_AFIORST>(); }
    static void WriteAFIORST(ValueType value) noexcept { Reg::Write<F_AFIORST>(value); }
    static auto ReadIOPARST() noexcept -> ValueType { return Reg::Read<F_IOPARST>(); }
    static void WriteIOPARST(ValueType value) noexcept { Reg::Write<F_IOPARST>(value); }
    static auto ReadIOPBRST() noexcept -> ValueType { return Reg::Read<F_IOPBRST>(); }
    static void WriteIOPBRST(ValueType value) noexcept { Reg::Write<F_IOPBRST>(value); }
    static auto ReadIOPCRST() noexcept -> ValueType { return Reg::Read<F_IOPCRST>(); }
    static void WriteIOPCRST(ValueType value) noexcept { Reg::Write<F_IOPCRST>(value); }
    static auto ReadIOPDRST() noexcept -> ValueType { return Reg::Read<F_IOPDRST>(); }
    static void WriteIOPDRST(ValueType value) noexcept { Reg::Write<F_IOPDRST>(value); }
    static auto ReadIOPERST() noexcept -> ValueType { return Reg::Read<F_IOPERST>(); }
    static void WriteIOPERST(ValueType value) noexcept { Reg::Write<F_IOPERST>(value); }
    static auto ReadIOPFRST() noexcept -> ValueType { return Reg::Read<F_IOPFRST>(); }
    static void WriteIOPFRST(ValueType value) noexcept { Reg::Write<F_IOPFRST>(value); }
    static auto ReadIOPGRST() noexcept -> ValueType { return Reg::Read<F_IOPGRST>(); }
    static void WriteIOPGRST(ValueType value) noexcept { Reg::Write<F_IOPGRST>(value); }
    static auto ReadADC1RST() noexcept -> ValueType { return Reg::Read<F_ADC1RST>(); }
    static void WriteADC1RST(ValueType value) noexcept { Reg::Write<F_ADC1RST>(value); }
    static auto ReadADC2RST() noexcept -> ValueType { return Reg::Read<F_ADC2RST>(); }
    static void WriteADC2RST(ValueType value) noexcept { Reg::Write<F_ADC2RST>(value); }
    static auto ReadTIM1RST() noexcept -> ValueType { return Reg::Read<F_TIM1RST>(); }
    static void WriteTIM1RST(ValueType value) noexcept { Reg::Write<F_TIM1RST>(value); }
    static auto ReadSPI1RST() noexcept -> ValueType { return Reg::Read<F_SPI1RST>(); }
    static void WriteSPI1RST(ValueType value) noexcept { Reg::Write<F_SPI1RST>(value); }
    static auto ReadTIM8RST() noexcept -> ValueType { return Reg::Read<F_TIM8RST>(); }
    static void WriteTIM8RST(ValueType value) noexcept { Reg::Write<F_TIM8RST>(value); }
    static auto ReadUSART1RST() noexcept -> ValueType { return Reg::Read<F_USART1RST>(); }
    static void WriteUSART1RST(ValueType value) noexcept { Reg::Write<F_USART1RST>(value); }
    static auto ReadADC3RST() noexcept -> ValueType { return Reg::Read<F_ADC3RST>(); }
    static void WriteADC3RST(ValueType value) noexcept { Reg::Write<F_ADC3RST>(value); }
    static auto ReadTIM9RST() noexcept -> ValueType { return Reg::Read<F_TIM9RST>(); }
    static void WriteTIM9RST(ValueType value) noexcept { Reg::Write<F_TIM9RST>(value); }
    static auto ReadTIM10RST() noexcept -> ValueType { return Reg::Read<F_TIM10RST>(); }
    static void WriteTIM10RST(ValueType value) noexcept { Reg::Write<F_TIM10RST>(value); }
    static auto ReadTIM11RST() noexcept -> ValueType { return Reg::Read<F_TIM11RST>(); }
    static void WriteTIM11RST(ValueType value) noexcept { Reg::Write<F_TIM11RST>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002100c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_AFIORST = CortexM3::Field<ValueType, 0, 1>;
    using F_IOPARST = CortexM3::Field<ValueType, 2, 1>;
    using F_IOPBRST = CortexM3::Field<ValueType, 3, 1>;
    using F_IOPCRST = CortexM3::Field<ValueType, 4, 1>;
    using F_IOPDRST = CortexM3::Field<ValueType, 5, 1>;
    using F_IOPERST = CortexM3::Field<ValueType, 6, 1>;
    using F_IOPFRST = CortexM3::Field<ValueType, 7, 1>;
    using F_IOPGRST = CortexM3::Field<ValueType, 8, 1>;
    using F_ADC1RST = CortexM3::Field<ValueType, 9, 1>;
    using F_ADC2RST = CortexM3::Field<ValueType, 10, 1>;
    using F_TIM1RST = CortexM3::Field<ValueType, 11, 1>;
    using F_SPI1RST = CortexM3::Field<ValueType, 12, 1>;
    using F_TIM8RST = CortexM3::Field<ValueType, 13, 1>;
    using F_USART1RST = CortexM3::Field<ValueType, 14, 1>;
    using F_ADC3RST = CortexM3::Field<ValueType, 15, 1>;
    using F_TIM9RST = CortexM3::Field<ValueType, 19, 1>;
    using F_TIM10RST = CortexM3::Field<ValueType, 20, 1>;
    using F_TIM11RST = CortexM3::Field<ValueType, 21, 1>;
};

class APB1RSTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIM2RST() noexcept -> ValueType { return Reg::Read<F_TIM2RST>(); }
    static void WriteTIM2RST(ValueType value) noexcept { Reg::Write<F_TIM2RST>(value); }
    static auto ReadTIM3RST() noexcept -> ValueType { return Reg::Read<F_TIM3RST>(); }
    static void WriteTIM3RST(ValueType value) noexcept { Reg::Write<F_TIM3RST>(value); }
    static auto ReadTIM4RST() noexcept -> ValueType { return Reg::Read<F_TIM4RST>(); }
    static void WriteTIM4RST(ValueType value) noexcept { Reg::Write<F_TIM4RST>(value); }
    static auto ReadTIM5RST() noexcept -> ValueType { return Reg::Read<F_TIM5RST>(); }
    static void WriteTIM5RST(ValueType value) noexcept { Reg::Write<F_TIM5RST>(value); }
    static auto ReadTIM6RST() noexcept -> ValueType { return Reg::Read<F_TIM6RST>(); }
    static void WriteTIM6RST(ValueType value) noexcept { Reg::Write<F_TIM6RST>(value); }
    static auto ReadTIM7RST() noexcept -> ValueType { return Reg::Read<F_TIM7RST>(); }
    static void WriteTIM7RST(ValueType value) noexcept { Reg::Write<F_TIM7RST>(value); }
    static auto ReadTIM12RST() noexcept -> ValueType { return Reg::Read<F_TIM12RST>(); }
    static void WriteTIM12RST(ValueType value) noexcept { Reg::Write<F_TIM12RST>(value); }
    static auto ReadTIM13RST() noexcept -> ValueType { return Reg::Read<F_TIM13RST>(); }
    static void WriteTIM13RST(ValueType value) noexcept { Reg::Write<F_TIM13RST>(value); }
    static auto ReadTIM14RST() noexcept -> ValueType { return Reg::Read<F_TIM14RST>(); }
    static void WriteTIM14RST(ValueType value) noexcept { Reg::Write<F_TIM14RST>(value); }
    static auto ReadWWDGRST() noexcept -> ValueType { return Reg::Read<F_WWDGRST>(); }
    static void WriteWWDGRST(ValueType value) noexcept { Reg::Write<F_WWDGRST>(value); }
    static auto ReadSPI2RST() noexcept -> ValueType { return Reg::Read<F_SPI2RST>(); }
    static void WriteSPI2RST(ValueType value) noexcept { Reg::Write<F_SPI2RST>(value); }
    static auto ReadSPI3RST() noexcept -> ValueType { return Reg::Read<F_SPI3RST>(); }
    static void WriteSPI3RST(ValueType value) noexcept { Reg::Write<F_SPI3RST>(value); }
    static auto ReadUSART2RST() noexcept -> ValueType { return Reg::Read<F_USART2RST>(); }
    static void WriteUSART2RST(ValueType value) noexcept { Reg::Write<F_USART2RST>(value); }
    static auto ReadUSART3RST() noexcept -> ValueType { return Reg::Read<F_USART3RST>(); }
    static void WriteUSART3RST(ValueType value) noexcept { Reg::Write<F_USART3RST>(value); }
    static auto ReadUART4RST() noexcept -> ValueType { return Reg::Read<F_UART4RST>(); }
    static void WriteUART4RST(ValueType value) noexcept { Reg::Write<F_UART4RST>(value); }
    static auto ReadUART5RST() noexcept -> ValueType { return Reg::Read<F_UART5RST>(); }
    static void WriteUART5RST(ValueType value) noexcept { Reg::Write<F_UART5RST>(value); }
    static auto ReadI2C1RST() noexcept -> ValueType { return Reg::Read<F_I2C1RST>(); }
    static void WriteI2C1RST(ValueType value) noexcept { Reg::Write<F_I2C1RST>(value); }
    static auto ReadI2C2RST() noexcept -> ValueType { return Reg::Read<F_I2C2RST>(); }
    static void WriteI2C2RST(ValueType value) noexcept { Reg::Write<F_I2C2RST>(value); }
    static auto ReadUSBRST() noexcept -> ValueType { return Reg::Read<F_USBRST>(); }
    static void WriteUSBRST(ValueType value) noexcept { Reg::Write<F_USBRST>(value); }
    static auto ReadCANRST() noexcept -> ValueType { return Reg::Read<F_CANRST>(); }
    static void WriteCANRST(ValueType value) noexcept { Reg::Write<F_CANRST>(value); }
    static auto ReadBKPRST() noexcept -> ValueType { return Reg::Read<F_BKPRST>(); }
    static void WriteBKPRST(ValueType value) noexcept { Reg::Write<F_BKPRST>(value); }
    static auto ReadPWRRST() noexcept -> ValueType { return Reg::Read<F_PWRRST>(); }
    static void WritePWRRST(ValueType value) noexcept { Reg::Write<F_PWRRST>(value); }
    static auto ReadDACRST() noexcept -> ValueType { return Reg::Read<F_DACRST>(); }
    static void WriteDACRST(ValueType value) noexcept { Reg::Write<F_DACRST>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIM2RST = CortexM3::Field<ValueType, 0, 1>;
    using F_TIM3RST = CortexM3::Field<ValueType, 1, 1>;
    using F_TIM4RST = CortexM3::Field<ValueType, 2, 1>;
    using F_TIM5RST = CortexM3::Field<ValueType, 3, 1>;
    using F_TIM6RST = CortexM3::Field<ValueType, 4, 1>;
    using F_TIM7RST = CortexM3::Field<ValueType, 5, 1>;
    using F_TIM12RST = CortexM3::Field<ValueType, 6, 1>;
    using F_TIM13RST = CortexM3::Field<ValueType, 7, 1>;
    using F_TIM14RST = CortexM3::Field<ValueType, 8, 1>;
    using F_WWDGRST = CortexM3::Field<ValueType, 11, 1>;
    using F_SPI2RST = CortexM3::Field<ValueType, 14, 1>;
    using F_SPI3RST = CortexM3::Field<ValueType, 15, 1>;
    using F_USART2RST = CortexM3::Field<ValueType, 17, 1>;
    using F_USART3RST = CortexM3::Field<ValueType, 18, 1>;
    using F_UART4RST = CortexM3::Field<ValueType, 19, 1>;
    using F_UART5RST = CortexM3::Field<ValueType, 20, 1>;
    using F_I2C1RST = CortexM3::Field<ValueType, 21, 1>;
    using F_I2C2RST = CortexM3::Field<ValueType, 22, 1>;
    using F_USBRST = CortexM3::Field<ValueType, 23, 1>;
    using F_CANRST = CortexM3::Field<ValueType, 25, 1>;
    using F_BKPRST = CortexM3::Field<ValueType, 27, 1>;
    using F_PWRRST = CortexM3::Field<ValueType, 28, 1>;
    using F_DACRST = CortexM3::Field<ValueType, 29, 1>;
};

class AHBENR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000014;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDMA1EN() noexcept -> ValueType { return Reg::Read<F_DMA1EN>(); }
    static void WriteDMA1EN(ValueType value) noexcept { Reg::Write<F_DMA1EN>(value); }
    static auto ReadDMA2EN() noexcept -> ValueType { return Reg::Read<F_DMA2EN>(); }
    static void WriteDMA2EN(ValueType value) noexcept { Reg::Write<F_DMA2EN>(value); }
    static auto ReadSRAMEN() noexcept -> ValueType { return Reg::Read<F_SRAMEN>(); }
    static void WriteSRAMEN(ValueType value) noexcept { Reg::Write<F_SRAMEN>(value); }
    static auto ReadFLITFEN() noexcept -> ValueType { return Reg::Read<F_FLITFEN>(); }
    static void WriteFLITFEN(ValueType value) noexcept { Reg::Write<F_FLITFEN>(value); }
    static auto ReadCRCEN() noexcept -> ValueType { return Reg::Read<F_CRCEN>(); }
    static void WriteCRCEN(ValueType value) noexcept { Reg::Write<F_CRCEN>(value); }
    static auto ReadFSMCEN() noexcept -> ValueType { return Reg::Read<F_FSMCEN>(); }
    static void WriteFSMCEN(ValueType value) noexcept { Reg::Write<F_FSMCEN>(value); }
    static auto ReadSDIOEN() noexcept -> ValueType { return Reg::Read<F_SDIOEN>(); }
    static void WriteSDIOEN(ValueType value) noexcept { Reg::Write<F_SDIOEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DMA1EN = CortexM3::Field<ValueType, 0, 1>;
    using F_DMA2EN = CortexM3::Field<ValueType, 1, 1>;
    using F_SRAMEN = CortexM3::Field<ValueType, 2, 1>;
    using F_FLITFEN = CortexM3::Field<ValueType, 4, 1>;
    using F_CRCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_FSMCEN = CortexM3::Field<ValueType, 8, 1>;
    using F_SDIOEN = CortexM3::Field<ValueType, 10, 1>;
};

class APB2ENR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadAFIOEN() noexcept -> ValueType { return Reg::Read<F_AFIOEN>(); }
    static void WriteAFIOEN(ValueType value) noexcept { Reg::Write<F_AFIOEN>(value); }
    static auto ReadIOPAEN() noexcept -> ValueType { return Reg::Read<F_IOPAEN>(); }
    static void WriteIOPAEN(ValueType value) noexcept { Reg::Write<F_IOPAEN>(value); }
    static auto ReadIOPBEN() noexcept -> ValueType { return Reg::Read<F_IOPBEN>(); }
    static void WriteIOPBEN(ValueType value) noexcept { Reg::Write<F_IOPBEN>(value); }
    static auto ReadIOPCEN() noexcept -> ValueType { return Reg::Read<F_IOPCEN>(); }
    static void WriteIOPCEN(ValueType value) noexcept { Reg::Write<F_IOPCEN>(value); }
    static auto ReadIOPDEN() noexcept -> ValueType { return Reg::Read<F_IOPDEN>(); }
    static void WriteIOPDEN(ValueType value) noexcept { Reg::Write<F_IOPDEN>(value); }
    static auto ReadIOPEEN() noexcept -> ValueType { return Reg::Read<F_IOPEEN>(); }
    static void WriteIOPEEN(ValueType value) noexcept { Reg::Write<F_IOPEEN>(value); }
    static auto ReadIOPFEN() noexcept -> ValueType { return Reg::Read<F_IOPFEN>(); }
    static void WriteIOPFEN(ValueType value) noexcept { Reg::Write<F_IOPFEN>(value); }
    static auto ReadIOPGEN() noexcept -> ValueType { return Reg::Read<F_IOPGEN>(); }
    static void WriteIOPGEN(ValueType value) noexcept { Reg::Write<F_IOPGEN>(value); }
    static auto ReadADC1EN() noexcept -> ValueType { return Reg::Read<F_ADC1EN>(); }
    static void WriteADC1EN(ValueType value) noexcept { Reg::Write<F_ADC1EN>(value); }
    static auto ReadADC2EN() noexcept -> ValueType { return Reg::Read<F_ADC2EN>(); }
    static void WriteADC2EN(ValueType value) noexcept { Reg::Write<F_ADC2EN>(value); }
    static auto ReadTIM1EN() noexcept -> ValueType { return Reg::Read<F_TIM1EN>(); }
    static void WriteTIM1EN(ValueType value) noexcept { Reg::Write<F_TIM1EN>(value); }
    static auto ReadSPI1EN() noexcept -> ValueType { return Reg::Read<F_SPI1EN>(); }
    static void WriteSPI1EN(ValueType value) noexcept { Reg::Write<F_SPI1EN>(value); }
    static auto ReadTIM8EN() noexcept -> ValueType { return Reg::Read<F_TIM8EN>(); }
    static void WriteTIM8EN(ValueType value) noexcept { Reg::Write<F_TIM8EN>(value); }
    static auto ReadUSART1EN() noexcept -> ValueType { return Reg::Read<F_USART1EN>(); }
    static void WriteUSART1EN(ValueType value) noexcept { Reg::Write<F_USART1EN>(value); }
    static auto ReadADC3EN() noexcept -> ValueType { return Reg::Read<F_ADC3EN>(); }
    static void WriteADC3EN(ValueType value) noexcept { Reg::Write<F_ADC3EN>(value); }
    static auto ReadTIM9EN() noexcept -> ValueType { return Reg::Read<F_TIM9EN>(); }
    static void WriteTIM9EN(ValueType value) noexcept { Reg::Write<F_TIM9EN>(value); }
    static auto ReadTIM10EN() noexcept -> ValueType { return Reg::Read<F_TIM10EN>(); }
    static void WriteTIM10EN(ValueType value) noexcept { Reg::Write<F_TIM10EN>(value); }
    static auto ReadTIM11EN() noexcept -> ValueType { return Reg::Read<F_TIM11EN>(); }
    static void WriteTIM11EN(ValueType value) noexcept { Reg::Write<F_TIM11EN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_AFIOEN = CortexM3::Field<ValueType, 0, 1>;
    using F_IOPAEN = CortexM3::Field<ValueType, 2, 1>;
    using F_IOPBEN = CortexM3::Field<ValueType, 3, 1>;
    using F_IOPCEN = CortexM3::Field<ValueType, 4, 1>;
    using F_IOPDEN = CortexM3::Field<ValueType, 5, 1>;
    using F_IOPEEN = CortexM3::Field<ValueType, 6, 1>;
    using F_IOPFEN = CortexM3::Field<ValueType, 7, 1>;
    using F_IOPGEN = CortexM3::Field<ValueType, 8, 1>;
    using F_ADC1EN = CortexM3::Field<ValueType, 9, 1>;
    using F_ADC2EN = CortexM3::Field<ValueType, 10, 1>;
    using F_TIM1EN = CortexM3::Field<ValueType, 11, 1>;
    using F_SPI1EN = CortexM3::Field<ValueType, 12, 1>;
    using F_TIM8EN = CortexM3::Field<ValueType, 13, 1>;
    using F_USART1EN = CortexM3::Field<ValueType, 14, 1>;
    using F_ADC3EN = CortexM3::Field<ValueType, 15, 1>;
    using F_TIM9EN = CortexM3::Field<ValueType, 19, 1>;
    using F_TIM10EN = CortexM3::Field<ValueType, 20, 1>;
    using F_TIM11EN = CortexM3::Field<ValueType, 21, 1>;
};

class APB1ENR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIM2EN() noexcept -> ValueType { return Reg::Read<F_TIM2EN>(); }
    static void WriteTIM2EN(ValueType value) noexcept { Reg::Write<F_TIM2EN>(value); }
    static auto ReadTIM3EN() noexcept -> ValueType { return Reg::Read<F_TIM3EN>(); }
    static void WriteTIM3EN(ValueType value) noexcept { Reg::Write<F_TIM3EN>(value); }
    static auto ReadTIM4EN() noexcept -> ValueType { return Reg::Read<F_TIM4EN>(); }
    static void WriteTIM4EN(ValueType value) noexcept { Reg::Write<F_TIM4EN>(value); }
    static auto ReadTIM5EN() noexcept -> ValueType { return Reg::Read<F_TIM5EN>(); }
    static void WriteTIM5EN(ValueType value) noexcept { Reg::Write<F_TIM5EN>(value); }
    static auto ReadTIM6EN() noexcept -> ValueType { return Reg::Read<F_TIM6EN>(); }
    static void WriteTIM6EN(ValueType value) noexcept { Reg::Write<F_TIM6EN>(value); }
    static auto ReadTIM7EN() noexcept -> ValueType { return Reg::Read<F_TIM7EN>(); }
    static void WriteTIM7EN(ValueType value) noexcept { Reg::Write<F_TIM7EN>(value); }
    static auto ReadTIM12EN() noexcept -> ValueType { return Reg::Read<F_TIM12EN>(); }
    static void WriteTIM12EN(ValueType value) noexcept { Reg::Write<F_TIM12EN>(value); }
    static auto ReadTIM13EN() noexcept -> ValueType { return Reg::Read<F_TIM13EN>(); }
    static void WriteTIM13EN(ValueType value) noexcept { Reg::Write<F_TIM13EN>(value); }
    static auto ReadTIM14EN() noexcept -> ValueType { return Reg::Read<F_TIM14EN>(); }
    static void WriteTIM14EN(ValueType value) noexcept { Reg::Write<F_TIM14EN>(value); }
    static auto ReadWWDGEN() noexcept -> ValueType { return Reg::Read<F_WWDGEN>(); }
    static void WriteWWDGEN(ValueType value) noexcept { Reg::Write<F_WWDGEN>(value); }
    static auto ReadSPI2EN() noexcept -> ValueType { return Reg::Read<F_SPI2EN>(); }
    static void WriteSPI2EN(ValueType value) noexcept { Reg::Write<F_SPI2EN>(value); }
    static auto ReadSPI3EN() noexcept -> ValueType { return Reg::Read<F_SPI3EN>(); }
    static void WriteSPI3EN(ValueType value) noexcept { Reg::Write<F_SPI3EN>(value); }
    static auto ReadUSART2EN() noexcept -> ValueType { return Reg::Read<F_USART2EN>(); }
    static void WriteUSART2EN(ValueType value) noexcept { Reg::Write<F_USART2EN>(value); }
    static auto ReadUSART3EN() noexcept -> ValueType { return Reg::Read<F_USART3EN>(); }
    static void WriteUSART3EN(ValueType value) noexcept { Reg::Write<F_USART3EN>(value); }
    static auto ReadUART4EN() noexcept -> ValueType { return Reg::Read<F_UART4EN>(); }
    static void WriteUART4EN(ValueType value) noexcept { Reg::Write<F_UART4EN>(value); }
    static auto ReadUART5EN() noexcept -> ValueType { return Reg::Read<F_UART5EN>(); }
    static void WriteUART5EN(ValueType value) noexcept { Reg::Write<F_UART5EN>(value); }
    static auto ReadI2C1EN() noexcept -> ValueType { return Reg::Read<F_I2C1EN>(); }
    static void WriteI2C1EN(ValueType value) noexcept { Reg::Write<F_I2C1EN>(value); }
    static auto ReadI2C2EN() noexcept -> ValueType { return Reg::Read<F_I2C2EN>(); }
    static void WriteI2C2EN(ValueType value) noexcept { Reg::Write<F_I2C2EN>(value); }
    static auto ReadUSBEN() noexcept -> ValueType { return Reg::Read<F_USBEN>(); }
    static void WriteUSBEN(ValueType value) noexcept { Reg::Write<F_USBEN>(value); }
    static auto ReadCANEN() noexcept -> ValueType { return Reg::Read<F_CANEN>(); }
    static void WriteCANEN(ValueType value) noexcept { Reg::Write<F_CANEN>(value); }
    static auto ReadBKPEN() noexcept -> ValueType { return Reg::Read<F_BKPEN>(); }
    static void WriteBKPEN(ValueType value) noexcept { Reg::Write<F_BKPEN>(value); }
    static auto ReadPWREN() noexcept -> ValueType { return Reg::Read<F_PWREN>(); }
    static void WritePWREN(ValueType value) noexcept { Reg::Write<F_PWREN>(value); }
    static auto ReadDACEN() noexcept -> ValueType { return Reg::Read<F_DACEN>(); }
    static void WriteDACEN(ValueType value) noexcept { Reg::Write<F_DACEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002101c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIM2EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TIM3EN = CortexM3::Field<ValueType, 1, 1>;
    using F_TIM4EN = CortexM3::Field<ValueType, 2, 1>;
    using F_TIM5EN = CortexM3::Field<ValueType, 3, 1>;
    using F_TIM6EN = CortexM3::Field<ValueType, 4, 1>;
    using F_TIM7EN = CortexM3::Field<ValueType, 5, 1>;
    using F_TIM12EN = CortexM3::Field<ValueType, 6, 1>;
    using F_TIM13EN = CortexM3::Field<ValueType, 7, 1>;
    using F_TIM14EN = CortexM3::Field<ValueType, 8, 1>;
    using F_WWDGEN = CortexM3::Field<ValueType, 11, 1>;
    using F_SPI2EN = CortexM3::Field<ValueType, 14, 1>;
    using F_SPI3EN = CortexM3::Field<ValueType, 15, 1>;
    using F_USART2EN = CortexM3::Field<ValueType, 17, 1>;
    using F_USART3EN = CortexM3::Field<ValueType, 18, 1>;
    using F_UART4EN = CortexM3::Field<ValueType, 19, 1>;
    using F_UART5EN = CortexM3::Field<ValueType, 20, 1>;
    using F_I2C1EN = CortexM3::Field<ValueType, 21, 1>;
    using F_I2C2EN = CortexM3::Field<ValueType, 22, 1>;
    using F_USBEN = CortexM3::Field<ValueType, 23, 1>;
    using F_CANEN = CortexM3::Field<ValueType, 25, 1>;
    using F_BKPEN = CortexM3::Field<ValueType, 27, 1>;
    using F_PWREN = CortexM3::Field<ValueType, 28, 1>;
    using F_DACEN = CortexM3::Field<ValueType, 29, 1>;
};

class BDCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLSEON() noexcept -> ValueType { return Reg::Read<F_LSEON>(); }
    static void WriteLSEON(ValueType value) noexcept { Reg::Write<F_LSEON>(value); }
    static auto ReadLSERDY() noexcept -> ValueType { return Reg::Read<F_LSERDY>(); }
    static auto ReadLSEBYP() noexcept -> ValueType { return Reg::Read<F_LSEBYP>(); }
    static void WriteLSEBYP(ValueType value) noexcept { Reg::Write<F_LSEBYP>(value); }
    static auto ReadRTCSEL() noexcept -> ValueType { return Reg::Read<F_RTCSEL>(); }
    static void WriteRTCSEL(ValueType value) noexcept { Reg::Write<F_RTCSEL>(value); }
    static auto ReadRTCEN() noexcept -> ValueType { return Reg::Read<F_RTCEN>(); }
    static void WriteRTCEN(ValueType value) noexcept { Reg::Write<F_RTCEN>(value); }
    static auto ReadBDRST() noexcept -> ValueType { return Reg::Read<F_BDRST>(); }
    static void WriteBDRST(ValueType value) noexcept { Reg::Write<F_BDRST>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021020;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LSEON = CortexM3::Field<ValueType, 0, 1>;
    using F_LSERDY = CortexM3::Field<ValueType, 1, 1>;
    using F_LSEBYP = CortexM3::Field<ValueType, 2, 1>;
    using F_RTCSEL = CortexM3::Field<ValueType, 8, 2>;
    using F_RTCEN = CortexM3::Field<ValueType, 15, 1>;
    using F_BDRST = CortexM3::Field<ValueType, 16, 1>;
};

class CSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0C000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLSION() noexcept -> ValueType { return Reg::Read<F_LSION>(); }
    static void WriteLSION(ValueType value) noexcept { Reg::Write<F_LSION>(value); }
    static auto ReadLSIRDY() noexcept -> ValueType { return Reg::Read<F_LSIRDY>(); }
    static auto ReadRMVF() noexcept -> ValueType { return Reg::Read<F_RMVF>(); }
    static void WriteRMVF(ValueType value) noexcept { Reg::Write<F_RMVF>(value); }
    static auto ReadPINRSTF() noexcept -> ValueType { return Reg::Read<F_PINRSTF>(); }
    static void WritePINRSTF(ValueType value) noexcept { Reg::Write<F_PINRSTF>(value); }
    static auto ReadPORRSTF() noexcept -> ValueType { return Reg::Read<F_PORRSTF>(); }
    static void WritePORRSTF(ValueType value) noexcept { Reg::Write<F_PORRSTF>(value); }
    static auto ReadSFTRSTF() noexcept -> ValueType { return Reg::Read<F_SFTRSTF>(); }
    static void WriteSFTRSTF(ValueType value) noexcept { Reg::Write<F_SFTRSTF>(value); }
    static auto ReadIWDGRSTF() noexcept -> ValueType { return Reg::Read<F_IWDGRSTF>(); }
    static void WriteIWDGRSTF(ValueType value) noexcept { Reg::Write<F_IWDGRSTF>(value); }
    static auto ReadWWDGRSTF() noexcept -> ValueType { return Reg::Read<F_WWDGRSTF>(); }
    static void WriteWWDGRSTF(ValueType value) noexcept { Reg::Write<F_WWDGRSTF>(value); }
    static auto ReadLPWRRSTF() noexcept -> ValueType { return Reg::Read<F_LPWRRSTF>(); }
    static void WriteLPWRRSTF(ValueType value) noexcept { Reg::Write<F_LPWRRSTF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40021024;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LSION = CortexM3::Field<ValueType, 0, 1>;
    using F_LSIRDY = CortexM3::Field<ValueType, 1, 1>;
    using F_RMVF = CortexM3::Field<ValueType, 24, 1>;
    using F_PINRSTF = CortexM3::Field<ValueType, 26, 1>;
    using F_PORRSTF = CortexM3::Field<ValueType, 27, 1>;
    using F_SFTRSTF = CortexM3::Field<ValueType, 28, 1>;
    using F_IWDGRSTF = CortexM3::Field<ValueType, 29, 1>;
    using F_WWDGRSTF = CortexM3::Field<ValueType, 30, 1>;
    using F_LPWRRSTF = CortexM3::Field<ValueType, 31, 1>;
};

} // namespace STM32F103::RCC
