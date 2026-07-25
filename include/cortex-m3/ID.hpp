#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::ID {

class CPUID {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadImplementer() noexcept -> ValueType { return Reg::Read<F_Implementer>(); }
    static auto ReadVariant() noexcept -> ValueType { return Reg::Read<F_Variant>(); }
    static auto ReadConstant() noexcept -> ValueType { return Reg::Read<F_Constant>(); }
    static auto ReadPartno() noexcept -> ValueType { return Reg::Read<F_Partno>(); }
    static auto ReadRevision() noexcept -> ValueType { return Reg::Read<F_Revision>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_Implementer = CortexM3::Field<ValueType, 24, 8>;
    using F_Variant = CortexM3::Field<ValueType, 20, 4>;
    using F_Constant = CortexM3::Field<ValueType, 16, 4>;
    using F_Partno = CortexM3::Field<ValueType, 4, 12>;
    using F_Revision = CortexM3::Field<ValueType, 0, 4>;
};

class ID_PFR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadState1() noexcept -> ValueType { return Reg::Read<F_State1>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed40;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_State1 = CortexM3::Field<ValueType, 4, 4>;
};

class ID_PFR1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadM_Profile() noexcept -> ValueType { return Reg::Read<F_M_Profile>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed44;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_M_Profile = CortexM3::Field<ValueType, 8, 4>;
};

class ID_DFR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadM_Profile() noexcept -> ValueType { return Reg::Read<F_M_Profile>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed48;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_M_Profile = CortexM3::Field<ValueType, 20, 4>;
};

class ID_AFR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed4c;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class ID_MMFR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadAuxiliary_registers() noexcept -> ValueType { return Reg::Read<F_Auxiliary_registers>(); }
    static auto ReadShareability_levels() noexcept -> ValueType { return Reg::Read<F_Shareability_levels>(); }
    static auto ReadOutermost_shareability() noexcept -> ValueType { return Reg::Read<F_Outermost_shareability>(); }
    static auto ReadPMSA() noexcept -> ValueType { return Reg::Read<F_PMSA>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed50;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_Auxiliary_registers = CortexM3::Field<ValueType, 20, 4>;
    using F_Shareability_levels = CortexM3::Field<ValueType, 12, 4>;
    using F_Outermost_shareability = CortexM3::Field<ValueType, 8, 4>;
    using F_PMSA = CortexM3::Field<ValueType, 4, 4>;
};

class ID_MMFR1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed54;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class ID_MMFR2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadWFI() noexcept -> ValueType { return Reg::Read<F_WFI>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed58;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_WFI = CortexM3::Field<ValueType, 24, 4>;
};

class ID_MMFR3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed5c;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class ID_ISAR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDivide_instrs() noexcept -> ValueType { return Reg::Read<F_Divide_instrs>(); }
    static auto ReadDebug_instrs() noexcept -> ValueType { return Reg::Read<F_Debug_instrs>(); }
    static auto ReadCoproc_instrs() noexcept -> ValueType { return Reg::Read<F_Coproc_instrs>(); }
    static auto ReadCmpBranch_instrs() noexcept -> ValueType { return Reg::Read<F_CmpBranch_instrs>(); }
    static auto ReadBitfield_instrs() noexcept -> ValueType { return Reg::Read<F_Bitfield_instrs>(); }
    static auto ReadBitCount_instrs() noexcept -> ValueType { return Reg::Read<F_BitCount_instrs>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed60;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_Divide_instrs = CortexM3::Field<ValueType, 24, 4>;
    using F_Debug_instrs = CortexM3::Field<ValueType, 20, 4>;
    using F_Coproc_instrs = CortexM3::Field<ValueType, 16, 4>;
    using F_CmpBranch_instrs = CortexM3::Field<ValueType, 12, 4>;
    using F_Bitfield_instrs = CortexM3::Field<ValueType, 8, 4>;
    using F_BitCount_instrs = CortexM3::Field<ValueType, 4, 4>;
};

class ID_ISAR1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadInterwork_instrs() noexcept -> ValueType { return Reg::Read<F_Interwork_instrs>(); }
    static auto ReadImmediate_instrs() noexcept -> ValueType { return Reg::Read<F_Immediate_instrs>(); }
    static auto ReadIfThen_instrs() noexcept -> ValueType { return Reg::Read<F_IfThen_instrs>(); }
    static auto ReadExtend_instrs() noexcept -> ValueType { return Reg::Read<F_Extend_instrs>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed64;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_Interwork_instrs = CortexM3::Field<ValueType, 24, 4>;
    using F_Immediate_instrs = CortexM3::Field<ValueType, 20, 4>;
    using F_IfThen_instrs = CortexM3::Field<ValueType, 16, 4>;
    using F_Extend_instrs = CortexM3::Field<ValueType, 12, 4>;
};

class ID_ISAR2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadReversal_instrs() noexcept -> ValueType { return Reg::Read<F_Reversal_instrs>(); }
    static auto ReadMultU_instrs() noexcept -> ValueType { return Reg::Read<F_MultU_instrs>(); }
    static auto ReadMultS_instrs() noexcept -> ValueType { return Reg::Read<F_MultS_instrs>(); }
    static auto ReadMult_instrs() noexcept -> ValueType { return Reg::Read<F_Mult_instrs>(); }
    static auto ReadMultiAccessInt_instrs() noexcept -> ValueType { return Reg::Read<F_MultiAccessInt_instrs>(); }
    static auto ReadMultiAccessInt_instrs_Pos4() noexcept -> ValueType { return Reg::Read<F_MultiAccessInt_instrs_Pos4>(); }
    static auto ReadLoadStore_instrs() noexcept -> ValueType { return Reg::Read<F_LoadStore_instrs>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed68;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_Reversal_instrs = CortexM3::Field<ValueType, 28, 4>;
    using F_MultU_instrs = CortexM3::Field<ValueType, 20, 4>;
    using F_MultS_instrs = CortexM3::Field<ValueType, 16, 4>;
    using F_Mult_instrs = CortexM3::Field<ValueType, 12, 4>;
    using F_MultiAccessInt_instrs = CortexM3::Field<ValueType, 8, 4>;
    using F_MultiAccessInt_instrs_Pos4 = CortexM3::Field<ValueType, 4, 4>;
    using F_LoadStore_instrs = CortexM3::Field<ValueType, 0, 4>;
};

class ID_ISAR3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTrueNOP_instrs() noexcept -> ValueType { return Reg::Read<F_TrueNOP_instrs>(); }
    static auto ReadThumbCopy_instrs() noexcept -> ValueType { return Reg::Read<F_ThumbCopy_instrs>(); }
    static auto ReadTabBranch_instrs() noexcept -> ValueType { return Reg::Read<F_TabBranch_instrs>(); }
    static auto ReadSynchPrim_instrs() noexcept -> ValueType { return Reg::Read<F_SynchPrim_instrs>(); }
    static auto ReadSVC_instrs() noexcept -> ValueType { return Reg::Read<F_SVC_instrs>(); }
    static auto ReadSIMD_instrs() noexcept -> ValueType { return Reg::Read<F_SIMD_instrs>(); }
    static auto ReadSaturate_instrs() noexcept -> ValueType { return Reg::Read<F_Saturate_instrs>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed6c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TrueNOP_instrs = CortexM3::Field<ValueType, 24, 4>;
    using F_ThumbCopy_instrs = CortexM3::Field<ValueType, 20, 4>;
    using F_TabBranch_instrs = CortexM3::Field<ValueType, 16, 4>;
    using F_SynchPrim_instrs = CortexM3::Field<ValueType, 12, 4>;
    using F_SVC_instrs = CortexM3::Field<ValueType, 8, 4>;
    using F_SIMD_instrs = CortexM3::Field<ValueType, 4, 4>;
    using F_Saturate_instrs = CortexM3::Field<ValueType, 0, 4>;
};

class ID_ISAR4 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadPSR_M_instrs() noexcept -> ValueType { return Reg::Read<F_PSR_M_instrs>(); }
    static auto ReadSynchPrim_instrs_frac() noexcept -> ValueType { return Reg::Read<F_SynchPrim_instrs_frac>(); }
    static auto ReadBarrier_instrs() noexcept -> ValueType { return Reg::Read<F_Barrier_instrs>(); }
    static auto ReadWriteback_instrs() noexcept -> ValueType { return Reg::Read<F_Writeback_instrs>(); }
    static auto ReadWithShifts_instrs() noexcept -> ValueType { return Reg::Read<F_WithShifts_instrs>(); }
    static auto ReadUnpriv_instrs() noexcept -> ValueType { return Reg::Read<F_Unpriv_instrs>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed70;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PSR_M_instrs = CortexM3::Field<ValueType, 24, 4>;
    using F_SynchPrim_instrs_frac = CortexM3::Field<ValueType, 20, 4>;
    using F_Barrier_instrs = CortexM3::Field<ValueType, 16, 4>;
    using F_Writeback_instrs = CortexM3::Field<ValueType, 8, 4>;
    using F_WithShifts_instrs = CortexM3::Field<ValueType, 4, 4>;
    using F_Unpriv_instrs = CortexM3::Field<ValueType, 0, 4>;
};

} // namespace CortexM3::ID
