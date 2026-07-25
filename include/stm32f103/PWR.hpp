#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::PWR {

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLPDS() noexcept -> ValueType { return Reg::Read<F_LPDS>(); }
    static void WriteLPDS(ValueType value) noexcept { Reg::Write<F_LPDS>(value); }
    static auto ReadPDDS() noexcept -> ValueType { return Reg::Read<F_PDDS>(); }
    static void WritePDDS(ValueType value) noexcept { Reg::Write<F_PDDS>(value); }
    static auto ReadCWUF() noexcept -> ValueType { return Reg::Read<F_CWUF>(); }
    static void WriteCWUF(ValueType value) noexcept { Reg::Write<F_CWUF>(value); }
    static auto ReadCSBF() noexcept -> ValueType { return Reg::Read<F_CSBF>(); }
    static void WriteCSBF(ValueType value) noexcept { Reg::Write<F_CSBF>(value); }
    static auto ReadPVDE() noexcept -> ValueType { return Reg::Read<F_PVDE>(); }
    static void WritePVDE(ValueType value) noexcept { Reg::Write<F_PVDE>(value); }
    static auto ReadPLS() noexcept -> ValueType { return Reg::Read<F_PLS>(); }
    static void WritePLS(ValueType value) noexcept { Reg::Write<F_PLS>(value); }
    static auto ReadDBP() noexcept -> ValueType { return Reg::Read<F_DBP>(); }
    static void WriteDBP(ValueType value) noexcept { Reg::Write<F_DBP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LPDS = CortexM3::Field<ValueType, 0, 1>;
    using F_PDDS = CortexM3::Field<ValueType, 1, 1>;
    using F_CWUF = CortexM3::Field<ValueType, 2, 1>;
    using F_CSBF = CortexM3::Field<ValueType, 3, 1>;
    using F_PVDE = CortexM3::Field<ValueType, 4, 1>;
    using F_PLS = CortexM3::Field<ValueType, 5, 3>;
    using F_DBP = CortexM3::Field<ValueType, 8, 1>;
};

class CSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadWUF() noexcept -> ValueType { return Reg::Read<F_WUF>(); }
    static auto ReadSBF() noexcept -> ValueType { return Reg::Read<F_SBF>(); }
    static auto ReadPVDO() noexcept -> ValueType { return Reg::Read<F_PVDO>(); }
    static auto ReadEWUP() noexcept -> ValueType { return Reg::Read<F_EWUP>(); }
    static void WriteEWUP(ValueType value) noexcept { Reg::Write<F_EWUP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_WUF = CortexM3::Field<ValueType, 0, 1>;
    using F_SBF = CortexM3::Field<ValueType, 1, 1>;
    using F_PVDO = CortexM3::Field<ValueType, 2, 1>;
    using F_EWUP = CortexM3::Field<ValueType, 8, 1>;
};

} // namespace STM32F103::PWR
