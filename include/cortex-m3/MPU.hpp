#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::MPU {

class MPU_TYPE {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSEPARATE() noexcept -> ValueType { return Reg::Read<F_SEPARATE>(); }
    static auto ReadDREGION() noexcept -> ValueType { return Reg::Read<F_DREGION>(); }
    static auto ReadIREGION() noexcept -> ValueType { return Reg::Read<F_IREGION>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed90;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SEPARATE = CortexM3::Field<ValueType, 0, 1>;
    using F_DREGION = CortexM3::Field<ValueType, 8, 8>;
    using F_IREGION = CortexM3::Field<ValueType, 16, 8>;
};

class MPU_CTRL {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }
    static auto ReadHFNMIENA() noexcept -> ValueType { return Reg::Read<F_HFNMIENA>(); }
    static void WriteHFNMIENA(ValueType value) noexcept { Reg::Write<F_HFNMIENA>(value); }
    static auto ReadPRIVDEFENA() noexcept -> ValueType { return Reg::Read<F_PRIVDEFENA>(); }
    static void WritePRIVDEFENA(ValueType value) noexcept { Reg::Write<F_PRIVDEFENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed94;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
    using F_HFNMIENA = CortexM3::Field<ValueType, 1, 1>;
    using F_PRIVDEFENA = CortexM3::Field<ValueType, 2, 1>;
};

class MPU_RNR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREGION() noexcept -> ValueType { return Reg::Read<F_REGION>(); }
    static void WriteREGION(ValueType value) noexcept { Reg::Write<F_REGION>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed98;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REGION = CortexM3::Field<ValueType, 0, 8>;
};

class MPU_RBAR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREGION() noexcept -> ValueType { return Reg::Read<F_REGION>(); }
    static void WriteREGION(ValueType value) noexcept { Reg::Write<F_REGION>(value); }
    static auto ReadVALID() noexcept -> ValueType { return Reg::Read<F_VALID>(); }
    static void WriteVALID(ValueType value) noexcept { Reg::Write<F_VALID>(value); }
    static auto ReadADDR() noexcept -> ValueType { return Reg::Read<F_ADDR>(); }
    static void WriteADDR(ValueType value) noexcept { Reg::Write<F_ADDR>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed9c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REGION = CortexM3::Field<ValueType, 0, 4>;
    using F_VALID = CortexM3::Field<ValueType, 4, 1>;
    using F_ADDR = CortexM3::Field<ValueType, 5, 27>;
};

class MPU_RASR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }
    static auto ReadSIZE() noexcept -> ValueType { return Reg::Read<F_SIZE>(); }
    static void WriteSIZE(ValueType value) noexcept { Reg::Write<F_SIZE>(value); }
    static auto ReadSRD() noexcept -> ValueType { return Reg::Read<F_SRD>(); }
    static void WriteSRD(ValueType value) noexcept { Reg::Write<F_SRD>(value); }
    static auto ReadB() noexcept -> ValueType { return Reg::Read<F_B>(); }
    static void WriteB(ValueType value) noexcept { Reg::Write<F_B>(value); }
    static auto ReadC() noexcept -> ValueType { return Reg::Read<F_C>(); }
    static void WriteC(ValueType value) noexcept { Reg::Write<F_C>(value); }
    static auto ReadS() noexcept -> ValueType { return Reg::Read<F_S>(); }
    static void WriteS(ValueType value) noexcept { Reg::Write<F_S>(value); }
    static auto ReadTEX() noexcept -> ValueType { return Reg::Read<F_TEX>(); }
    static void WriteTEX(ValueType value) noexcept { Reg::Write<F_TEX>(value); }
    static auto ReadAP() noexcept -> ValueType { return Reg::Read<F_AP>(); }
    static void WriteAP(ValueType value) noexcept { Reg::Write<F_AP>(value); }
    static auto ReadXN() noexcept -> ValueType { return Reg::Read<F_XN>(); }
    static void WriteXN(ValueType value) noexcept { Reg::Write<F_XN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000eda0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
    using F_SIZE = CortexM3::Field<ValueType, 1, 5>;
    using F_SRD = CortexM3::Field<ValueType, 8, 8>;
    using F_B = CortexM3::Field<ValueType, 16, 1>;
    using F_C = CortexM3::Field<ValueType, 17, 1>;
    using F_S = CortexM3::Field<ValueType, 18, 1>;
    using F_TEX = CortexM3::Field<ValueType, 19, 3>;
    using F_AP = CortexM3::Field<ValueType, 24, 3>;
    using F_XN = CortexM3::Field<ValueType, 28, 1>;
};

class MPU_RBAR_A1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREGION() noexcept -> ValueType { return Reg::Read<F_REGION>(); }
    static void WriteREGION(ValueType value) noexcept { Reg::Write<F_REGION>(value); }
    static auto ReadVALID() noexcept -> ValueType { return Reg::Read<F_VALID>(); }
    static void WriteVALID(ValueType value) noexcept { Reg::Write<F_VALID>(value); }
    static auto ReadADDR() noexcept -> ValueType { return Reg::Read<F_ADDR>(); }
    static void WriteADDR(ValueType value) noexcept { Reg::Write<F_ADDR>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000eda4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REGION = CortexM3::Field<ValueType, 0, 4>;
    using F_VALID = CortexM3::Field<ValueType, 4, 1>;
    using F_ADDR = CortexM3::Field<ValueType, 5, 27>;
};

class MPU_RASR_A1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }
    static auto ReadSIZE() noexcept -> ValueType { return Reg::Read<F_SIZE>(); }
    static void WriteSIZE(ValueType value) noexcept { Reg::Write<F_SIZE>(value); }
    static auto ReadSRD() noexcept -> ValueType { return Reg::Read<F_SRD>(); }
    static void WriteSRD(ValueType value) noexcept { Reg::Write<F_SRD>(value); }
    static auto ReadB() noexcept -> ValueType { return Reg::Read<F_B>(); }
    static void WriteB(ValueType value) noexcept { Reg::Write<F_B>(value); }
    static auto ReadC() noexcept -> ValueType { return Reg::Read<F_C>(); }
    static void WriteC(ValueType value) noexcept { Reg::Write<F_C>(value); }
    static auto ReadS() noexcept -> ValueType { return Reg::Read<F_S>(); }
    static void WriteS(ValueType value) noexcept { Reg::Write<F_S>(value); }
    static auto ReadTEX() noexcept -> ValueType { return Reg::Read<F_TEX>(); }
    static void WriteTEX(ValueType value) noexcept { Reg::Write<F_TEX>(value); }
    static auto ReadAP() noexcept -> ValueType { return Reg::Read<F_AP>(); }
    static void WriteAP(ValueType value) noexcept { Reg::Write<F_AP>(value); }
    static auto ReadXN() noexcept -> ValueType { return Reg::Read<F_XN>(); }
    static void WriteXN(ValueType value) noexcept { Reg::Write<F_XN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000eda8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
    using F_SIZE = CortexM3::Field<ValueType, 1, 5>;
    using F_SRD = CortexM3::Field<ValueType, 8, 8>;
    using F_B = CortexM3::Field<ValueType, 16, 1>;
    using F_C = CortexM3::Field<ValueType, 17, 1>;
    using F_S = CortexM3::Field<ValueType, 18, 1>;
    using F_TEX = CortexM3::Field<ValueType, 19, 3>;
    using F_AP = CortexM3::Field<ValueType, 24, 3>;
    using F_XN = CortexM3::Field<ValueType, 28, 1>;
};

class MPU_RBAR_A2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREGION() noexcept -> ValueType { return Reg::Read<F_REGION>(); }
    static void WriteREGION(ValueType value) noexcept { Reg::Write<F_REGION>(value); }
    static auto ReadVALID() noexcept -> ValueType { return Reg::Read<F_VALID>(); }
    static void WriteVALID(ValueType value) noexcept { Reg::Write<F_VALID>(value); }
    static auto ReadADDR() noexcept -> ValueType { return Reg::Read<F_ADDR>(); }
    static void WriteADDR(ValueType value) noexcept { Reg::Write<F_ADDR>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000edac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REGION = CortexM3::Field<ValueType, 0, 4>;
    using F_VALID = CortexM3::Field<ValueType, 4, 1>;
    using F_ADDR = CortexM3::Field<ValueType, 5, 27>;
};

class MPU_RASR_A2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }
    static auto ReadSIZE() noexcept -> ValueType { return Reg::Read<F_SIZE>(); }
    static void WriteSIZE(ValueType value) noexcept { Reg::Write<F_SIZE>(value); }
    static auto ReadSRD() noexcept -> ValueType { return Reg::Read<F_SRD>(); }
    static void WriteSRD(ValueType value) noexcept { Reg::Write<F_SRD>(value); }
    static auto ReadB() noexcept -> ValueType { return Reg::Read<F_B>(); }
    static void WriteB(ValueType value) noexcept { Reg::Write<F_B>(value); }
    static auto ReadC() noexcept -> ValueType { return Reg::Read<F_C>(); }
    static void WriteC(ValueType value) noexcept { Reg::Write<F_C>(value); }
    static auto ReadS() noexcept -> ValueType { return Reg::Read<F_S>(); }
    static void WriteS(ValueType value) noexcept { Reg::Write<F_S>(value); }
    static auto ReadTEX() noexcept -> ValueType { return Reg::Read<F_TEX>(); }
    static void WriteTEX(ValueType value) noexcept { Reg::Write<F_TEX>(value); }
    static auto ReadAP() noexcept -> ValueType { return Reg::Read<F_AP>(); }
    static void WriteAP(ValueType value) noexcept { Reg::Write<F_AP>(value); }
    static auto ReadXN() noexcept -> ValueType { return Reg::Read<F_XN>(); }
    static void WriteXN(ValueType value) noexcept { Reg::Write<F_XN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000edb0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
    using F_SIZE = CortexM3::Field<ValueType, 1, 5>;
    using F_SRD = CortexM3::Field<ValueType, 8, 8>;
    using F_B = CortexM3::Field<ValueType, 16, 1>;
    using F_C = CortexM3::Field<ValueType, 17, 1>;
    using F_S = CortexM3::Field<ValueType, 18, 1>;
    using F_TEX = CortexM3::Field<ValueType, 19, 3>;
    using F_AP = CortexM3::Field<ValueType, 24, 3>;
    using F_XN = CortexM3::Field<ValueType, 28, 1>;
};

class MPU_RBAR_A3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREGION() noexcept -> ValueType { return Reg::Read<F_REGION>(); }
    static void WriteREGION(ValueType value) noexcept { Reg::Write<F_REGION>(value); }
    static auto ReadVALID() noexcept -> ValueType { return Reg::Read<F_VALID>(); }
    static void WriteVALID(ValueType value) noexcept { Reg::Write<F_VALID>(value); }
    static auto ReadADDR() noexcept -> ValueType { return Reg::Read<F_ADDR>(); }
    static void WriteADDR(ValueType value) noexcept { Reg::Write<F_ADDR>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000edb4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REGION = CortexM3::Field<ValueType, 0, 4>;
    using F_VALID = CortexM3::Field<ValueType, 4, 1>;
    using F_ADDR = CortexM3::Field<ValueType, 5, 27>;
};

class MPU_RASR_A3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }
    static auto ReadSIZE() noexcept -> ValueType { return Reg::Read<F_SIZE>(); }
    static void WriteSIZE(ValueType value) noexcept { Reg::Write<F_SIZE>(value); }
    static auto ReadSRD() noexcept -> ValueType { return Reg::Read<F_SRD>(); }
    static void WriteSRD(ValueType value) noexcept { Reg::Write<F_SRD>(value); }
    static auto ReadB() noexcept -> ValueType { return Reg::Read<F_B>(); }
    static void WriteB(ValueType value) noexcept { Reg::Write<F_B>(value); }
    static auto ReadC() noexcept -> ValueType { return Reg::Read<F_C>(); }
    static void WriteC(ValueType value) noexcept { Reg::Write<F_C>(value); }
    static auto ReadS() noexcept -> ValueType { return Reg::Read<F_S>(); }
    static void WriteS(ValueType value) noexcept { Reg::Write<F_S>(value); }
    static auto ReadTEX() noexcept -> ValueType { return Reg::Read<F_TEX>(); }
    static void WriteTEX(ValueType value) noexcept { Reg::Write<F_TEX>(value); }
    static auto ReadAP() noexcept -> ValueType { return Reg::Read<F_AP>(); }
    static void WriteAP(ValueType value) noexcept { Reg::Write<F_AP>(value); }
    static auto ReadXN() noexcept -> ValueType { return Reg::Read<F_XN>(); }
    static void WriteXN(ValueType value) noexcept { Reg::Write<F_XN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000edb8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
    using F_SIZE = CortexM3::Field<ValueType, 1, 5>;
    using F_SRD = CortexM3::Field<ValueType, 8, 8>;
    using F_B = CortexM3::Field<ValueType, 16, 1>;
    using F_C = CortexM3::Field<ValueType, 17, 1>;
    using F_S = CortexM3::Field<ValueType, 18, 1>;
    using F_TEX = CortexM3::Field<ValueType, 19, 3>;
    using F_AP = CortexM3::Field<ValueType, 24, 3>;
    using F_XN = CortexM3::Field<ValueType, 28, 1>;
};

} // namespace CortexM3::MPU
