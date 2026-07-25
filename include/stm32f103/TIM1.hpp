#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::TIM1 {

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCKD() noexcept -> ValueType { return Reg::Read<F_CKD>(); }
    static void WriteCKD(ValueType value) noexcept { Reg::Write<F_CKD>(value); }
    static auto ReadARPE() noexcept -> ValueType { return Reg::Read<F_ARPE>(); }
    static void WriteARPE(ValueType value) noexcept { Reg::Write<F_ARPE>(value); }
    static auto ReadCMS() noexcept -> ValueType { return Reg::Read<F_CMS>(); }
    static void WriteCMS(ValueType value) noexcept { Reg::Write<F_CMS>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadOPM() noexcept -> ValueType { return Reg::Read<F_OPM>(); }
    static void WriteOPM(ValueType value) noexcept { Reg::Write<F_OPM>(value); }
    static auto ReadURS() noexcept -> ValueType { return Reg::Read<F_URS>(); }
    static void WriteURS(ValueType value) noexcept { Reg::Write<F_URS>(value); }
    static auto ReadUDIS() noexcept -> ValueType { return Reg::Read<F_UDIS>(); }
    static void WriteUDIS(ValueType value) noexcept { Reg::Write<F_UDIS>(value); }
    static auto ReadCEN() noexcept -> ValueType { return Reg::Read<F_CEN>(); }
    static void WriteCEN(ValueType value) noexcept { Reg::Write<F_CEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CKD = CortexM3::Field<ValueType, 8, 2>;
    using F_ARPE = CortexM3::Field<ValueType, 7, 1>;
    using F_CMS = CortexM3::Field<ValueType, 5, 2>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_OPM = CortexM3::Field<ValueType, 3, 1>;
    using F_URS = CortexM3::Field<ValueType, 2, 1>;
    using F_UDIS = CortexM3::Field<ValueType, 1, 1>;
    using F_CEN = CortexM3::Field<ValueType, 0, 1>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadOIS4() noexcept -> ValueType { return Reg::Read<F_OIS4>(); }
    static void WriteOIS4(ValueType value) noexcept { Reg::Write<F_OIS4>(value); }
    static auto ReadOIS3N() noexcept -> ValueType { return Reg::Read<F_OIS3N>(); }
    static void WriteOIS3N(ValueType value) noexcept { Reg::Write<F_OIS3N>(value); }
    static auto ReadOIS3() noexcept -> ValueType { return Reg::Read<F_OIS3>(); }
    static void WriteOIS3(ValueType value) noexcept { Reg::Write<F_OIS3>(value); }
    static auto ReadOIS2N() noexcept -> ValueType { return Reg::Read<F_OIS2N>(); }
    static void WriteOIS2N(ValueType value) noexcept { Reg::Write<F_OIS2N>(value); }
    static auto ReadOIS2() noexcept -> ValueType { return Reg::Read<F_OIS2>(); }
    static void WriteOIS2(ValueType value) noexcept { Reg::Write<F_OIS2>(value); }
    static auto ReadOIS1N() noexcept -> ValueType { return Reg::Read<F_OIS1N>(); }
    static void WriteOIS1N(ValueType value) noexcept { Reg::Write<F_OIS1N>(value); }
    static auto ReadOIS1() noexcept -> ValueType { return Reg::Read<F_OIS1>(); }
    static void WriteOIS1(ValueType value) noexcept { Reg::Write<F_OIS1>(value); }
    static auto ReadTI1S() noexcept -> ValueType { return Reg::Read<F_TI1S>(); }
    static void WriteTI1S(ValueType value) noexcept { Reg::Write<F_TI1S>(value); }
    static auto ReadMMS() noexcept -> ValueType { return Reg::Read<F_MMS>(); }
    static void WriteMMS(ValueType value) noexcept { Reg::Write<F_MMS>(value); }
    static auto ReadCCDS() noexcept -> ValueType { return Reg::Read<F_CCDS>(); }
    static void WriteCCDS(ValueType value) noexcept { Reg::Write<F_CCDS>(value); }
    static auto ReadCCUS() noexcept -> ValueType { return Reg::Read<F_CCUS>(); }
    static void WriteCCUS(ValueType value) noexcept { Reg::Write<F_CCUS>(value); }
    static auto ReadCCPC() noexcept -> ValueType { return Reg::Read<F_CCPC>(); }
    static void WriteCCPC(ValueType value) noexcept { Reg::Write<F_CCPC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c04;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OIS4 = CortexM3::Field<ValueType, 14, 1>;
    using F_OIS3N = CortexM3::Field<ValueType, 13, 1>;
    using F_OIS3 = CortexM3::Field<ValueType, 12, 1>;
    using F_OIS2N = CortexM3::Field<ValueType, 11, 1>;
    using F_OIS2 = CortexM3::Field<ValueType, 10, 1>;
    using F_OIS1N = CortexM3::Field<ValueType, 9, 1>;
    using F_OIS1 = CortexM3::Field<ValueType, 8, 1>;
    using F_TI1S = CortexM3::Field<ValueType, 7, 1>;
    using F_MMS = CortexM3::Field<ValueType, 4, 3>;
    using F_CCDS = CortexM3::Field<ValueType, 3, 1>;
    using F_CCUS = CortexM3::Field<ValueType, 2, 1>;
    using F_CCPC = CortexM3::Field<ValueType, 0, 1>;
};

class SMCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadETP() noexcept -> ValueType { return Reg::Read<F_ETP>(); }
    static void WriteETP(ValueType value) noexcept { Reg::Write<F_ETP>(value); }
    static auto ReadECE() noexcept -> ValueType { return Reg::Read<F_ECE>(); }
    static void WriteECE(ValueType value) noexcept { Reg::Write<F_ECE>(value); }
    static auto ReadETPS() noexcept -> ValueType { return Reg::Read<F_ETPS>(); }
    static void WriteETPS(ValueType value) noexcept { Reg::Write<F_ETPS>(value); }
    static auto ReadETF() noexcept -> ValueType { return Reg::Read<F_ETF>(); }
    static void WriteETF(ValueType value) noexcept { Reg::Write<F_ETF>(value); }
    static auto ReadMSM() noexcept -> ValueType { return Reg::Read<F_MSM>(); }
    static void WriteMSM(ValueType value) noexcept { Reg::Write<F_MSM>(value); }
    static auto ReadTS() noexcept -> ValueType { return Reg::Read<F_TS>(); }
    static void WriteTS(ValueType value) noexcept { Reg::Write<F_TS>(value); }
    static auto ReadSMS() noexcept -> ValueType { return Reg::Read<F_SMS>(); }
    static void WriteSMS(ValueType value) noexcept { Reg::Write<F_SMS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ETP = CortexM3::Field<ValueType, 15, 1>;
    using F_ECE = CortexM3::Field<ValueType, 14, 1>;
    using F_ETPS = CortexM3::Field<ValueType, 12, 2>;
    using F_ETF = CortexM3::Field<ValueType, 8, 4>;
    using F_MSM = CortexM3::Field<ValueType, 7, 1>;
    using F_TS = CortexM3::Field<ValueType, 4, 3>;
    using F_SMS = CortexM3::Field<ValueType, 0, 3>;
};

class DIER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTDE() noexcept -> ValueType { return Reg::Read<F_TDE>(); }
    static void WriteTDE(ValueType value) noexcept { Reg::Write<F_TDE>(value); }
    static auto ReadCOMDE() noexcept -> ValueType { return Reg::Read<F_COMDE>(); }
    static void WriteCOMDE(ValueType value) noexcept { Reg::Write<F_COMDE>(value); }
    static auto ReadCC4DE() noexcept -> ValueType { return Reg::Read<F_CC4DE>(); }
    static void WriteCC4DE(ValueType value) noexcept { Reg::Write<F_CC4DE>(value); }
    static auto ReadCC3DE() noexcept -> ValueType { return Reg::Read<F_CC3DE>(); }
    static void WriteCC3DE(ValueType value) noexcept { Reg::Write<F_CC3DE>(value); }
    static auto ReadCC2DE() noexcept -> ValueType { return Reg::Read<F_CC2DE>(); }
    static void WriteCC2DE(ValueType value) noexcept { Reg::Write<F_CC2DE>(value); }
    static auto ReadCC1DE() noexcept -> ValueType { return Reg::Read<F_CC1DE>(); }
    static void WriteCC1DE(ValueType value) noexcept { Reg::Write<F_CC1DE>(value); }
    static auto ReadUDE() noexcept -> ValueType { return Reg::Read<F_UDE>(); }
    static void WriteUDE(ValueType value) noexcept { Reg::Write<F_UDE>(value); }
    static auto ReadTIE() noexcept -> ValueType { return Reg::Read<F_TIE>(); }
    static void WriteTIE(ValueType value) noexcept { Reg::Write<F_TIE>(value); }
    static auto ReadCC4IE() noexcept -> ValueType { return Reg::Read<F_CC4IE>(); }
    static void WriteCC4IE(ValueType value) noexcept { Reg::Write<F_CC4IE>(value); }
    static auto ReadCC3IE() noexcept -> ValueType { return Reg::Read<F_CC3IE>(); }
    static void WriteCC3IE(ValueType value) noexcept { Reg::Write<F_CC3IE>(value); }
    static auto ReadCC2IE() noexcept -> ValueType { return Reg::Read<F_CC2IE>(); }
    static void WriteCC2IE(ValueType value) noexcept { Reg::Write<F_CC2IE>(value); }
    static auto ReadCC1IE() noexcept -> ValueType { return Reg::Read<F_CC1IE>(); }
    static void WriteCC1IE(ValueType value) noexcept { Reg::Write<F_CC1IE>(value); }
    static auto ReadUIE() noexcept -> ValueType { return Reg::Read<F_UIE>(); }
    static void WriteUIE(ValueType value) noexcept { Reg::Write<F_UIE>(value); }
    static auto ReadBIE() noexcept -> ValueType { return Reg::Read<F_BIE>(); }
    static void WriteBIE(ValueType value) noexcept { Reg::Write<F_BIE>(value); }
    static auto ReadCOMIE() noexcept -> ValueType { return Reg::Read<F_COMIE>(); }
    static void WriteCOMIE(ValueType value) noexcept { Reg::Write<F_COMIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c0c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TDE = CortexM3::Field<ValueType, 14, 1>;
    using F_COMDE = CortexM3::Field<ValueType, 13, 1>;
    using F_CC4DE = CortexM3::Field<ValueType, 12, 1>;
    using F_CC3DE = CortexM3::Field<ValueType, 11, 1>;
    using F_CC2DE = CortexM3::Field<ValueType, 10, 1>;
    using F_CC1DE = CortexM3::Field<ValueType, 9, 1>;
    using F_UDE = CortexM3::Field<ValueType, 8, 1>;
    using F_TIE = CortexM3::Field<ValueType, 6, 1>;
    using F_CC4IE = CortexM3::Field<ValueType, 4, 1>;
    using F_CC3IE = CortexM3::Field<ValueType, 3, 1>;
    using F_CC2IE = CortexM3::Field<ValueType, 2, 1>;
    using F_CC1IE = CortexM3::Field<ValueType, 1, 1>;
    using F_UIE = CortexM3::Field<ValueType, 0, 1>;
    using F_BIE = CortexM3::Field<ValueType, 7, 1>;
    using F_COMIE = CortexM3::Field<ValueType, 5, 1>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCC4OF() noexcept -> ValueType { return Reg::Read<F_CC4OF>(); }
    static void WriteCC4OF(ValueType value) noexcept { Reg::Write<F_CC4OF>(value); }
    static auto ReadCC3OF() noexcept -> ValueType { return Reg::Read<F_CC3OF>(); }
    static void WriteCC3OF(ValueType value) noexcept { Reg::Write<F_CC3OF>(value); }
    static auto ReadCC2OF() noexcept -> ValueType { return Reg::Read<F_CC2OF>(); }
    static void WriteCC2OF(ValueType value) noexcept { Reg::Write<F_CC2OF>(value); }
    static auto ReadCC1OF() noexcept -> ValueType { return Reg::Read<F_CC1OF>(); }
    static void WriteCC1OF(ValueType value) noexcept { Reg::Write<F_CC1OF>(value); }
    static auto ReadBIF() noexcept -> ValueType { return Reg::Read<F_BIF>(); }
    static void WriteBIF(ValueType value) noexcept { Reg::Write<F_BIF>(value); }
    static auto ReadTIF() noexcept -> ValueType { return Reg::Read<F_TIF>(); }
    static void WriteTIF(ValueType value) noexcept { Reg::Write<F_TIF>(value); }
    static auto ReadCOMIF() noexcept -> ValueType { return Reg::Read<F_COMIF>(); }
    static void WriteCOMIF(ValueType value) noexcept { Reg::Write<F_COMIF>(value); }
    static auto ReadCC4IF() noexcept -> ValueType { return Reg::Read<F_CC4IF>(); }
    static void WriteCC4IF(ValueType value) noexcept { Reg::Write<F_CC4IF>(value); }
    static auto ReadCC3IF() noexcept -> ValueType { return Reg::Read<F_CC3IF>(); }
    static void WriteCC3IF(ValueType value) noexcept { Reg::Write<F_CC3IF>(value); }
    static auto ReadCC2IF() noexcept -> ValueType { return Reg::Read<F_CC2IF>(); }
    static void WriteCC2IF(ValueType value) noexcept { Reg::Write<F_CC2IF>(value); }
    static auto ReadCC1IF() noexcept -> ValueType { return Reg::Read<F_CC1IF>(); }
    static void WriteCC1IF(ValueType value) noexcept { Reg::Write<F_CC1IF>(value); }
    static auto ReadUIF() noexcept -> ValueType { return Reg::Read<F_UIF>(); }
    static void WriteUIF(ValueType value) noexcept { Reg::Write<F_UIF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c10;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC4OF = CortexM3::Field<ValueType, 12, 1>;
    using F_CC3OF = CortexM3::Field<ValueType, 11, 1>;
    using F_CC2OF = CortexM3::Field<ValueType, 10, 1>;
    using F_CC1OF = CortexM3::Field<ValueType, 9, 1>;
    using F_BIF = CortexM3::Field<ValueType, 7, 1>;
    using F_TIF = CortexM3::Field<ValueType, 6, 1>;
    using F_COMIF = CortexM3::Field<ValueType, 5, 1>;
    using F_CC4IF = CortexM3::Field<ValueType, 4, 1>;
    using F_CC3IF = CortexM3::Field<ValueType, 3, 1>;
    using F_CC2IF = CortexM3::Field<ValueType, 2, 1>;
    using F_CC1IF = CortexM3::Field<ValueType, 1, 1>;
    using F_UIF = CortexM3::Field<ValueType, 0, 1>;
};

class EGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteBG(ValueType value) noexcept { Reg::Write<F_BG>(value); }
    static void WriteTG(ValueType value) noexcept { Reg::Write<F_TG>(value); }
    static void WriteCOMG(ValueType value) noexcept { Reg::Write<F_COMG>(value); }
    static void WriteCC4G(ValueType value) noexcept { Reg::Write<F_CC4G>(value); }
    static void WriteCC3G(ValueType value) noexcept { Reg::Write<F_CC3G>(value); }
    static void WriteCC2G(ValueType value) noexcept { Reg::Write<F_CC2G>(value); }
    static void WriteCC1G(ValueType value) noexcept { Reg::Write<F_CC1G>(value); }
    static void WriteUG(ValueType value) noexcept { Reg::Write<F_UG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c14;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BG = CortexM3::Field<ValueType, 7, 1>;
    using F_TG = CortexM3::Field<ValueType, 6, 1>;
    using F_COMG = CortexM3::Field<ValueType, 5, 1>;
    using F_CC4G = CortexM3::Field<ValueType, 4, 1>;
    using F_CC3G = CortexM3::Field<ValueType, 3, 1>;
    using F_CC2G = CortexM3::Field<ValueType, 2, 1>;
    using F_CC1G = CortexM3::Field<ValueType, 1, 1>;
    using F_UG = CortexM3::Field<ValueType, 0, 1>;
};

class CCMR1_Output {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadOC2CE() noexcept -> ValueType { return Reg::Read<F_OC2CE>(); }
    static void WriteOC2CE(ValueType value) noexcept { Reg::Write<F_OC2CE>(value); }
    static auto ReadOC2M() noexcept -> ValueType { return Reg::Read<F_OC2M>(); }
    static void WriteOC2M(ValueType value) noexcept { Reg::Write<F_OC2M>(value); }
    static auto ReadOC2PE() noexcept -> ValueType { return Reg::Read<F_OC2PE>(); }
    static void WriteOC2PE(ValueType value) noexcept { Reg::Write<F_OC2PE>(value); }
    static auto ReadOC2FE() noexcept -> ValueType { return Reg::Read<F_OC2FE>(); }
    static void WriteOC2FE(ValueType value) noexcept { Reg::Write<F_OC2FE>(value); }
    static auto ReadCC2S() noexcept -> ValueType { return Reg::Read<F_CC2S>(); }
    static void WriteCC2S(ValueType value) noexcept { Reg::Write<F_CC2S>(value); }
    static auto ReadOC1CE() noexcept -> ValueType { return Reg::Read<F_OC1CE>(); }
    static void WriteOC1CE(ValueType value) noexcept { Reg::Write<F_OC1CE>(value); }
    static auto ReadOC1M() noexcept -> ValueType { return Reg::Read<F_OC1M>(); }
    static void WriteOC1M(ValueType value) noexcept { Reg::Write<F_OC1M>(value); }
    static auto ReadOC1PE() noexcept -> ValueType { return Reg::Read<F_OC1PE>(); }
    static void WriteOC1PE(ValueType value) noexcept { Reg::Write<F_OC1PE>(value); }
    static auto ReadOC1FE() noexcept -> ValueType { return Reg::Read<F_OC1FE>(); }
    static void WriteOC1FE(ValueType value) noexcept { Reg::Write<F_OC1FE>(value); }
    static auto ReadCC1S() noexcept -> ValueType { return Reg::Read<F_CC1S>(); }
    static void WriteCC1S(ValueType value) noexcept { Reg::Write<F_CC1S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c18;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OC2CE = CortexM3::Field<ValueType, 15, 1>;
    using F_OC2M = CortexM3::Field<ValueType, 12, 3>;
    using F_OC2PE = CortexM3::Field<ValueType, 11, 1>;
    using F_OC2FE = CortexM3::Field<ValueType, 10, 1>;
    using F_CC2S = CortexM3::Field<ValueType, 8, 2>;
    using F_OC1CE = CortexM3::Field<ValueType, 7, 1>;
    using F_OC1M = CortexM3::Field<ValueType, 4, 3>;
    using F_OC1PE = CortexM3::Field<ValueType, 3, 1>;
    using F_OC1FE = CortexM3::Field<ValueType, 2, 1>;
    using F_CC1S = CortexM3::Field<ValueType, 0, 2>;
};

class CCMR1_Input {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIC2F() noexcept -> ValueType { return Reg::Read<F_IC2F>(); }
    static void WriteIC2F(ValueType value) noexcept { Reg::Write<F_IC2F>(value); }
    static auto ReadIC2PSC() noexcept -> ValueType { return Reg::Read<F_IC2PSC>(); }
    static void WriteIC2PSC(ValueType value) noexcept { Reg::Write<F_IC2PSC>(value); }
    static auto ReadCC2S() noexcept -> ValueType { return Reg::Read<F_CC2S>(); }
    static void WriteCC2S(ValueType value) noexcept { Reg::Write<F_CC2S>(value); }
    static auto ReadIC1F() noexcept -> ValueType { return Reg::Read<F_IC1F>(); }
    static void WriteIC1F(ValueType value) noexcept { Reg::Write<F_IC1F>(value); }
    static auto ReadIC1PSC() noexcept -> ValueType { return Reg::Read<F_IC1PSC>(); }
    static void WriteIC1PSC(ValueType value) noexcept { Reg::Write<F_IC1PSC>(value); }
    static auto ReadCC1S() noexcept -> ValueType { return Reg::Read<F_CC1S>(); }
    static void WriteCC1S(ValueType value) noexcept { Reg::Write<F_CC1S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c18;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IC2F = CortexM3::Field<ValueType, 12, 4>;
    using F_IC2PSC = CortexM3::Field<ValueType, 10, 2>;
    using F_CC2S = CortexM3::Field<ValueType, 8, 2>;
    using F_IC1F = CortexM3::Field<ValueType, 4, 4>;
    using F_IC1PSC = CortexM3::Field<ValueType, 2, 2>;
    using F_CC1S = CortexM3::Field<ValueType, 0, 2>;
};

class CCMR2_Output {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadOC4CE() noexcept -> ValueType { return Reg::Read<F_OC4CE>(); }
    static void WriteOC4CE(ValueType value) noexcept { Reg::Write<F_OC4CE>(value); }
    static auto ReadOC4M() noexcept -> ValueType { return Reg::Read<F_OC4M>(); }
    static void WriteOC4M(ValueType value) noexcept { Reg::Write<F_OC4M>(value); }
    static auto ReadOC4PE() noexcept -> ValueType { return Reg::Read<F_OC4PE>(); }
    static void WriteOC4PE(ValueType value) noexcept { Reg::Write<F_OC4PE>(value); }
    static auto ReadOC4FE() noexcept -> ValueType { return Reg::Read<F_OC4FE>(); }
    static void WriteOC4FE(ValueType value) noexcept { Reg::Write<F_OC4FE>(value); }
    static auto ReadCC4S() noexcept -> ValueType { return Reg::Read<F_CC4S>(); }
    static void WriteCC4S(ValueType value) noexcept { Reg::Write<F_CC4S>(value); }
    static auto ReadOC3CE() noexcept -> ValueType { return Reg::Read<F_OC3CE>(); }
    static void WriteOC3CE(ValueType value) noexcept { Reg::Write<F_OC3CE>(value); }
    static auto ReadOC3M() noexcept -> ValueType { return Reg::Read<F_OC3M>(); }
    static void WriteOC3M(ValueType value) noexcept { Reg::Write<F_OC3M>(value); }
    static auto ReadOC3PE() noexcept -> ValueType { return Reg::Read<F_OC3PE>(); }
    static void WriteOC3PE(ValueType value) noexcept { Reg::Write<F_OC3PE>(value); }
    static auto ReadOC3FE() noexcept -> ValueType { return Reg::Read<F_OC3FE>(); }
    static void WriteOC3FE(ValueType value) noexcept { Reg::Write<F_OC3FE>(value); }
    static auto ReadCC3S() noexcept -> ValueType { return Reg::Read<F_CC3S>(); }
    static void WriteCC3S(ValueType value) noexcept { Reg::Write<F_CC3S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c1c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OC4CE = CortexM3::Field<ValueType, 15, 1>;
    using F_OC4M = CortexM3::Field<ValueType, 12, 3>;
    using F_OC4PE = CortexM3::Field<ValueType, 11, 1>;
    using F_OC4FE = CortexM3::Field<ValueType, 10, 1>;
    using F_CC4S = CortexM3::Field<ValueType, 8, 2>;
    using F_OC3CE = CortexM3::Field<ValueType, 7, 1>;
    using F_OC3M = CortexM3::Field<ValueType, 4, 3>;
    using F_OC3PE = CortexM3::Field<ValueType, 3, 1>;
    using F_OC3FE = CortexM3::Field<ValueType, 2, 1>;
    using F_CC3S = CortexM3::Field<ValueType, 0, 2>;
};

class CCMR2_Input {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIC4F() noexcept -> ValueType { return Reg::Read<F_IC4F>(); }
    static void WriteIC4F(ValueType value) noexcept { Reg::Write<F_IC4F>(value); }
    static auto ReadIC4PSC() noexcept -> ValueType { return Reg::Read<F_IC4PSC>(); }
    static void WriteIC4PSC(ValueType value) noexcept { Reg::Write<F_IC4PSC>(value); }
    static auto ReadCC4S() noexcept -> ValueType { return Reg::Read<F_CC4S>(); }
    static void WriteCC4S(ValueType value) noexcept { Reg::Write<F_CC4S>(value); }
    static auto ReadIC3F() noexcept -> ValueType { return Reg::Read<F_IC3F>(); }
    static void WriteIC3F(ValueType value) noexcept { Reg::Write<F_IC3F>(value); }
    static auto ReadIC3PSC() noexcept -> ValueType { return Reg::Read<F_IC3PSC>(); }
    static void WriteIC3PSC(ValueType value) noexcept { Reg::Write<F_IC3PSC>(value); }
    static auto ReadCC3S() noexcept -> ValueType { return Reg::Read<F_CC3S>(); }
    static void WriteCC3S(ValueType value) noexcept { Reg::Write<F_CC3S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c1c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IC4F = CortexM3::Field<ValueType, 12, 4>;
    using F_IC4PSC = CortexM3::Field<ValueType, 10, 2>;
    using F_CC4S = CortexM3::Field<ValueType, 8, 2>;
    using F_IC3F = CortexM3::Field<ValueType, 4, 4>;
    using F_IC3PSC = CortexM3::Field<ValueType, 2, 2>;
    using F_CC3S = CortexM3::Field<ValueType, 0, 2>;
};

class CCER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCC4P() noexcept -> ValueType { return Reg::Read<F_CC4P>(); }
    static void WriteCC4P(ValueType value) noexcept { Reg::Write<F_CC4P>(value); }
    static auto ReadCC4E() noexcept -> ValueType { return Reg::Read<F_CC4E>(); }
    static void WriteCC4E(ValueType value) noexcept { Reg::Write<F_CC4E>(value); }
    static auto ReadCC3NP() noexcept -> ValueType { return Reg::Read<F_CC3NP>(); }
    static void WriteCC3NP(ValueType value) noexcept { Reg::Write<F_CC3NP>(value); }
    static auto ReadCC3NE() noexcept -> ValueType { return Reg::Read<F_CC3NE>(); }
    static void WriteCC3NE(ValueType value) noexcept { Reg::Write<F_CC3NE>(value); }
    static auto ReadCC3P() noexcept -> ValueType { return Reg::Read<F_CC3P>(); }
    static void WriteCC3P(ValueType value) noexcept { Reg::Write<F_CC3P>(value); }
    static auto ReadCC3E() noexcept -> ValueType { return Reg::Read<F_CC3E>(); }
    static void WriteCC3E(ValueType value) noexcept { Reg::Write<F_CC3E>(value); }
    static auto ReadCC2NP() noexcept -> ValueType { return Reg::Read<F_CC2NP>(); }
    static void WriteCC2NP(ValueType value) noexcept { Reg::Write<F_CC2NP>(value); }
    static auto ReadCC2NE() noexcept -> ValueType { return Reg::Read<F_CC2NE>(); }
    static void WriteCC2NE(ValueType value) noexcept { Reg::Write<F_CC2NE>(value); }
    static auto ReadCC2P() noexcept -> ValueType { return Reg::Read<F_CC2P>(); }
    static void WriteCC2P(ValueType value) noexcept { Reg::Write<F_CC2P>(value); }
    static auto ReadCC2E() noexcept -> ValueType { return Reg::Read<F_CC2E>(); }
    static void WriteCC2E(ValueType value) noexcept { Reg::Write<F_CC2E>(value); }
    static auto ReadCC1NP() noexcept -> ValueType { return Reg::Read<F_CC1NP>(); }
    static void WriteCC1NP(ValueType value) noexcept { Reg::Write<F_CC1NP>(value); }
    static auto ReadCC1NE() noexcept -> ValueType { return Reg::Read<F_CC1NE>(); }
    static void WriteCC1NE(ValueType value) noexcept { Reg::Write<F_CC1NE>(value); }
    static auto ReadCC1P() noexcept -> ValueType { return Reg::Read<F_CC1P>(); }
    static void WriteCC1P(ValueType value) noexcept { Reg::Write<F_CC1P>(value); }
    static auto ReadCC1E() noexcept -> ValueType { return Reg::Read<F_CC1E>(); }
    static void WriteCC1E(ValueType value) noexcept { Reg::Write<F_CC1E>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c20;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC4P = CortexM3::Field<ValueType, 13, 1>;
    using F_CC4E = CortexM3::Field<ValueType, 12, 1>;
    using F_CC3NP = CortexM3::Field<ValueType, 11, 1>;
    using F_CC3NE = CortexM3::Field<ValueType, 10, 1>;
    using F_CC3P = CortexM3::Field<ValueType, 9, 1>;
    using F_CC3E = CortexM3::Field<ValueType, 8, 1>;
    using F_CC2NP = CortexM3::Field<ValueType, 7, 1>;
    using F_CC2NE = CortexM3::Field<ValueType, 6, 1>;
    using F_CC2P = CortexM3::Field<ValueType, 5, 1>;
    using F_CC2E = CortexM3::Field<ValueType, 4, 1>;
    using F_CC1NP = CortexM3::Field<ValueType, 3, 1>;
    using F_CC1NE = CortexM3::Field<ValueType, 2, 1>;
    using F_CC1P = CortexM3::Field<ValueType, 1, 1>;
    using F_CC1E = CortexM3::Field<ValueType, 0, 1>;
};

class CNT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCNT() noexcept -> ValueType { return Reg::Read<F_CNT>(); }
    static void WriteCNT(ValueType value) noexcept { Reg::Write<F_CNT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c24;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CNT = CortexM3::Field<ValueType, 0, 16>;
};

class PSC {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPSC() noexcept -> ValueType { return Reg::Read<F_PSC>(); }
    static void WritePSC(ValueType value) noexcept { Reg::Write<F_PSC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c28;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PSC = CortexM3::Field<ValueType, 0, 16>;
};

class ARR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadARR() noexcept -> ValueType { return Reg::Read<F_ARR>(); }
    static void WriteARR(ValueType value) noexcept { Reg::Write<F_ARR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c2c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ARR = CortexM3::Field<ValueType, 0, 16>;
};

class CCR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCR1() noexcept -> ValueType { return Reg::Read<F_CCR1>(); }
    static void WriteCCR1(ValueType value) noexcept { Reg::Write<F_CCR1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c34;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCR1 = CortexM3::Field<ValueType, 0, 16>;
};

class CCR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCR2() noexcept -> ValueType { return Reg::Read<F_CCR2>(); }
    static void WriteCCR2(ValueType value) noexcept { Reg::Write<F_CCR2>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c38;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCR2 = CortexM3::Field<ValueType, 0, 16>;
};

class CCR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCR3() noexcept -> ValueType { return Reg::Read<F_CCR3>(); }
    static void WriteCCR3(ValueType value) noexcept { Reg::Write<F_CCR3>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c3c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCR3 = CortexM3::Field<ValueType, 0, 16>;
};

class CCR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCR4() noexcept -> ValueType { return Reg::Read<F_CCR4>(); }
    static void WriteCCR4(ValueType value) noexcept { Reg::Write<F_CCR4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c40;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCR4 = CortexM3::Field<ValueType, 0, 16>;
};

class DCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDBL() noexcept -> ValueType { return Reg::Read<F_DBL>(); }
    static void WriteDBL(ValueType value) noexcept { Reg::Write<F_DBL>(value); }
    static auto ReadDBA() noexcept -> ValueType { return Reg::Read<F_DBA>(); }
    static void WriteDBA(ValueType value) noexcept { Reg::Write<F_DBA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c48;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DBL = CortexM3::Field<ValueType, 8, 5>;
    using F_DBA = CortexM3::Field<ValueType, 0, 5>;
};

class DMAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDMAB() noexcept -> ValueType { return Reg::Read<F_DMAB>(); }
    static void WriteDMAB(ValueType value) noexcept { Reg::Write<F_DMAB>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c4c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DMAB = CortexM3::Field<ValueType, 0, 16>;
};

class RCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREP() noexcept -> ValueType { return Reg::Read<F_REP>(); }
    static void WriteREP(ValueType value) noexcept { Reg::Write<F_REP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c30;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REP = CortexM3::Field<ValueType, 0, 8>;
};

class BDTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMOE() noexcept -> ValueType { return Reg::Read<F_MOE>(); }
    static void WriteMOE(ValueType value) noexcept { Reg::Write<F_MOE>(value); }
    static auto ReadAOE() noexcept -> ValueType { return Reg::Read<F_AOE>(); }
    static void WriteAOE(ValueType value) noexcept { Reg::Write<F_AOE>(value); }
    static auto ReadBKP() noexcept -> ValueType { return Reg::Read<F_BKP>(); }
    static void WriteBKP(ValueType value) noexcept { Reg::Write<F_BKP>(value); }
    static auto ReadBKE() noexcept -> ValueType { return Reg::Read<F_BKE>(); }
    static void WriteBKE(ValueType value) noexcept { Reg::Write<F_BKE>(value); }
    static auto ReadOSSR() noexcept -> ValueType { return Reg::Read<F_OSSR>(); }
    static void WriteOSSR(ValueType value) noexcept { Reg::Write<F_OSSR>(value); }
    static auto ReadOSSI() noexcept -> ValueType { return Reg::Read<F_OSSI>(); }
    static void WriteOSSI(ValueType value) noexcept { Reg::Write<F_OSSI>(value); }
    static auto ReadLOCK() noexcept -> ValueType { return Reg::Read<F_LOCK>(); }
    static void WriteLOCK(ValueType value) noexcept { Reg::Write<F_LOCK>(value); }
    static auto ReadDTG() noexcept -> ValueType { return Reg::Read<F_DTG>(); }
    static void WriteDTG(ValueType value) noexcept { Reg::Write<F_DTG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012c44;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MOE = CortexM3::Field<ValueType, 15, 1>;
    using F_AOE = CortexM3::Field<ValueType, 14, 1>;
    using F_BKP = CortexM3::Field<ValueType, 13, 1>;
    using F_BKE = CortexM3::Field<ValueType, 12, 1>;
    using F_OSSR = CortexM3::Field<ValueType, 11, 1>;
    using F_OSSI = CortexM3::Field<ValueType, 10, 1>;
    using F_LOCK = CortexM3::Field<ValueType, 8, 2>;
    using F_DTG = CortexM3::Field<ValueType, 0, 8>;
};

} // namespace STM32F103::TIM1
