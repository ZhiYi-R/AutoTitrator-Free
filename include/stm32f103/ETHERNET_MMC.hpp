#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::ETHERNET_MMC {

class MMCCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCR() noexcept -> ValueType { return Reg::Read<F_CR>(); }
    static void WriteCR(ValueType value) noexcept { Reg::Write<F_CR>(value); }
    static auto ReadCSR() noexcept -> ValueType { return Reg::Read<F_CSR>(); }
    static void WriteCSR(ValueType value) noexcept { Reg::Write<F_CSR>(value); }
    static auto ReadROR() noexcept -> ValueType { return Reg::Read<F_ROR>(); }
    static void WriteROR(ValueType value) noexcept { Reg::Write<F_ROR>(value); }
    static auto ReadMCF() noexcept -> ValueType { return Reg::Read<F_MCF>(); }
    static void WriteMCF(ValueType value) noexcept { Reg::Write<F_MCF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028100;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CR = CortexM3::Field<ValueType, 0, 1>;
    using F_CSR = CortexM3::Field<ValueType, 1, 1>;
    using F_ROR = CortexM3::Field<ValueType, 2, 1>;
    using F_MCF = CortexM3::Field<ValueType, 31, 1>;
};

class MMCRIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRFCES() noexcept -> ValueType { return Reg::Read<F_RFCES>(); }
    static void WriteRFCES(ValueType value) noexcept { Reg::Write<F_RFCES>(value); }
    static auto ReadRFAES() noexcept -> ValueType { return Reg::Read<F_RFAES>(); }
    static void WriteRFAES(ValueType value) noexcept { Reg::Write<F_RFAES>(value); }
    static auto ReadRGUFS() noexcept -> ValueType { return Reg::Read<F_RGUFS>(); }
    static void WriteRGUFS(ValueType value) noexcept { Reg::Write<F_RGUFS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028104;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFCES = CortexM3::Field<ValueType, 5, 1>;
    using F_RFAES = CortexM3::Field<ValueType, 6, 1>;
    using F_RGUFS = CortexM3::Field<ValueType, 17, 1>;
};

class MMCTIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTGFSCS() noexcept -> ValueType { return Reg::Read<F_TGFSCS>(); }
    static void WriteTGFSCS(ValueType value) noexcept { Reg::Write<F_TGFSCS>(value); }
    static auto ReadTGFMSCS() noexcept -> ValueType { return Reg::Read<F_TGFMSCS>(); }
    static void WriteTGFMSCS(ValueType value) noexcept { Reg::Write<F_TGFMSCS>(value); }
    static auto ReadTGFS() noexcept -> ValueType { return Reg::Read<F_TGFS>(); }
    static void WriteTGFS(ValueType value) noexcept { Reg::Write<F_TGFS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028108;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TGFSCS = CortexM3::Field<ValueType, 14, 1>;
    using F_TGFMSCS = CortexM3::Field<ValueType, 15, 1>;
    using F_TGFS = CortexM3::Field<ValueType, 21, 1>;
};

class MMCRIMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRFCEM() noexcept -> ValueType { return Reg::Read<F_RFCEM>(); }
    static void WriteRFCEM(ValueType value) noexcept { Reg::Write<F_RFCEM>(value); }
    static auto ReadRFAEM() noexcept -> ValueType { return Reg::Read<F_RFAEM>(); }
    static void WriteRFAEM(ValueType value) noexcept { Reg::Write<F_RFAEM>(value); }
    static auto ReadRGUFM() noexcept -> ValueType { return Reg::Read<F_RGUFM>(); }
    static void WriteRGUFM(ValueType value) noexcept { Reg::Write<F_RGUFM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002810c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFCEM = CortexM3::Field<ValueType, 5, 1>;
    using F_RFAEM = CortexM3::Field<ValueType, 6, 1>;
    using F_RGUFM = CortexM3::Field<ValueType, 17, 1>;
};

class MMCTIMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTGFSCM() noexcept -> ValueType { return Reg::Read<F_TGFSCM>(); }
    static void WriteTGFSCM(ValueType value) noexcept { Reg::Write<F_TGFSCM>(value); }
    static auto ReadTGFMSCM() noexcept -> ValueType { return Reg::Read<F_TGFMSCM>(); }
    static void WriteTGFMSCM(ValueType value) noexcept { Reg::Write<F_TGFMSCM>(value); }
    static auto ReadTGFM() noexcept -> ValueType { return Reg::Read<F_TGFM>(); }
    static void WriteTGFM(ValueType value) noexcept { Reg::Write<F_TGFM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028110;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TGFSCM = CortexM3::Field<ValueType, 14, 1>;
    using F_TGFMSCM = CortexM3::Field<ValueType, 15, 1>;
    using F_TGFM = CortexM3::Field<ValueType, 21, 1>;
};

class MMCTGFSCCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTGFSCC() noexcept -> ValueType { return Reg::Read<F_TGFSCC>(); }

private:
    static constexpr std::uintptr_t Address = 0x4002814c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TGFSCC = CortexM3::Field<ValueType, 0, 32>;
};

class MMCTGFMSCCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTGFMSCC() noexcept -> ValueType { return Reg::Read<F_TGFMSCC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028150;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TGFMSCC = CortexM3::Field<ValueType, 0, 32>;
};

class MMCTGFCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTGFC() noexcept -> ValueType { return Reg::Read<F_TGFC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028168;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TGFC = CortexM3::Field<ValueType, 0, 32>;
};

class MMCRFCECR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadRFCFC() noexcept -> ValueType { return Reg::Read<F_RFCFC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028194;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFCFC = CortexM3::Field<ValueType, 0, 32>;
};

class MMCRFAECR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadRFAEC() noexcept -> ValueType { return Reg::Read<F_RFAEC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028198;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFAEC = CortexM3::Field<ValueType, 0, 32>;
};

class MMCRGUFCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadRGUFC() noexcept -> ValueType { return Reg::Read<F_RGUFC>(); }

private:
    static constexpr std::uintptr_t Address = 0x400281c4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RGUFC = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::ETHERNET_MMC
