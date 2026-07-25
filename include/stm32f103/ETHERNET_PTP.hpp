#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::ETHERNET_PTP {

class PTPTSCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTSE() noexcept -> ValueType { return Reg::Read<F_TSE>(); }
    static void WriteTSE(ValueType value) noexcept { Reg::Write<F_TSE>(value); }
    static auto ReadTSFCU() noexcept -> ValueType { return Reg::Read<F_TSFCU>(); }
    static void WriteTSFCU(ValueType value) noexcept { Reg::Write<F_TSFCU>(value); }
    static auto ReadTSSTI() noexcept -> ValueType { return Reg::Read<F_TSSTI>(); }
    static void WriteTSSTI(ValueType value) noexcept { Reg::Write<F_TSSTI>(value); }
    static auto ReadTSSTU() noexcept -> ValueType { return Reg::Read<F_TSSTU>(); }
    static void WriteTSSTU(ValueType value) noexcept { Reg::Write<F_TSSTU>(value); }
    static auto ReadTSITE() noexcept -> ValueType { return Reg::Read<F_TSITE>(); }
    static void WriteTSITE(ValueType value) noexcept { Reg::Write<F_TSITE>(value); }
    static auto ReadTSARU() noexcept -> ValueType { return Reg::Read<F_TSARU>(); }
    static void WriteTSARU(ValueType value) noexcept { Reg::Write<F_TSARU>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028700;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TSE = CortexM3::Field<ValueType, 0, 1>;
    using F_TSFCU = CortexM3::Field<ValueType, 1, 1>;
    using F_TSSTI = CortexM3::Field<ValueType, 2, 1>;
    using F_TSSTU = CortexM3::Field<ValueType, 3, 1>;
    using F_TSITE = CortexM3::Field<ValueType, 4, 1>;
    using F_TSARU = CortexM3::Field<ValueType, 5, 1>;
};

class PTPSSIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTSSI() noexcept -> ValueType { return Reg::Read<F_STSSI>(); }
    static void WriteSTSSI(ValueType value) noexcept { Reg::Write<F_STSSI>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028704;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STSSI = CortexM3::Field<ValueType, 0, 8>;
};

class PTPTSHR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSTS() noexcept -> ValueType { return Reg::Read<F_STS>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028708;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STS = CortexM3::Field<ValueType, 0, 32>;
};

class PTPTSLR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSTSS() noexcept -> ValueType { return Reg::Read<F_STSS>(); }
    static auto ReadSTPNS() noexcept -> ValueType { return Reg::Read<F_STPNS>(); }

private:
    static constexpr std::uintptr_t Address = 0x4002870c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STSS = CortexM3::Field<ValueType, 0, 31>;
    using F_STPNS = CortexM3::Field<ValueType, 31, 1>;
};

class PTPTSHUR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTSUS() noexcept -> ValueType { return Reg::Read<F_TSUS>(); }
    static void WriteTSUS(ValueType value) noexcept { Reg::Write<F_TSUS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028710;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TSUS = CortexM3::Field<ValueType, 0, 32>;
};

class PTPTSLUR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTSUSS() noexcept -> ValueType { return Reg::Read<F_TSUSS>(); }
    static void WriteTSUSS(ValueType value) noexcept { Reg::Write<F_TSUSS>(value); }
    static auto ReadTSUPNS() noexcept -> ValueType { return Reg::Read<F_TSUPNS>(); }
    static void WriteTSUPNS(ValueType value) noexcept { Reg::Write<F_TSUPNS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028714;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TSUSS = CortexM3::Field<ValueType, 0, 31>;
    using F_TSUPNS = CortexM3::Field<ValueType, 31, 1>;
};

class PTPTSAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTSA() noexcept -> ValueType { return Reg::Read<F_TSA>(); }
    static void WriteTSA(ValueType value) noexcept { Reg::Write<F_TSA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028718;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TSA = CortexM3::Field<ValueType, 0, 32>;
};

class PTPTTHR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTTSH() noexcept -> ValueType { return Reg::Read<F_TTSH>(); }
    static void WriteTTSH(ValueType value) noexcept { Reg::Write<F_TTSH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002871c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TTSH = CortexM3::Field<ValueType, 0, 32>;
};

class PTPTTLR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTTSL() noexcept -> ValueType { return Reg::Read<F_TTSL>(); }
    static void WriteTTSL(ValueType value) noexcept { Reg::Write<F_TTSL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028720;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TTSL = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::ETHERNET_PTP
