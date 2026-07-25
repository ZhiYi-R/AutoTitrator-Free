#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::Control {

class ACTLR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDISFOLD() noexcept -> ValueType { return Reg::Read<F_DISFOLD>(); }
    static void WriteDISFOLD(ValueType value) noexcept { Reg::Write<F_DISFOLD>(value); }
    static auto ReadDISDEFWBUF() noexcept -> ValueType { return Reg::Read<F_DISDEFWBUF>(); }
    static void WriteDISDEFWBUF(ValueType value) noexcept { Reg::Write<F_DISDEFWBUF>(value); }
    static auto ReadDISMCYCINT() noexcept -> ValueType { return Reg::Read<F_DISMCYCINT>(); }
    static void WriteDISMCYCINT(ValueType value) noexcept { Reg::Write<F_DISMCYCINT>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DISFOLD = CortexM3::Field<ValueType, 2, 1>;
    using F_DISDEFWBUF = CortexM3::Field<ValueType, 1, 1>;
    using F_DISMCYCINT = CortexM3::Field<ValueType, 0, 1>;
};

class ICSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNMIPENDSET() noexcept -> ValueType { return Reg::Read<F_NMIPENDSET>(); }
    static void WriteNMIPENDSET(ValueType value) noexcept { Reg::Write<F_NMIPENDSET>(value); }
    static auto ReadPENDSVSET() noexcept -> ValueType { return Reg::Read<F_PENDSVSET>(); }
    static void WritePENDSVSET(ValueType value) noexcept { Reg::Write<F_PENDSVSET>(value); }
    static auto ReadPENDSVCLR() noexcept -> ValueType { return Reg::Read<F_PENDSVCLR>(); }
    static void WritePENDSVCLR(ValueType value) noexcept { Reg::Write<F_PENDSVCLR>(value); }
    static auto ReadPENDSTSET() noexcept -> ValueType { return Reg::Read<F_PENDSTSET>(); }
    static void WritePENDSTSET(ValueType value) noexcept { Reg::Write<F_PENDSTSET>(value); }
    static auto ReadPENDSTCLR() noexcept -> ValueType { return Reg::Read<F_PENDSTCLR>(); }
    static void WritePENDSTCLR(ValueType value) noexcept { Reg::Write<F_PENDSTCLR>(value); }
    static auto ReadISRPREEMPT() noexcept -> ValueType { return Reg::Read<F_ISRPREEMPT>(); }
    static void WriteISRPREEMPT(ValueType value) noexcept { Reg::Write<F_ISRPREEMPT>(value); }
    static auto ReadISRPENDING() noexcept -> ValueType { return Reg::Read<F_ISRPENDING>(); }
    static void WriteISRPENDING(ValueType value) noexcept { Reg::Write<F_ISRPENDING>(value); }
    static auto ReadVECTPENDING() noexcept -> ValueType { return Reg::Read<F_VECTPENDING>(); }
    static void WriteVECTPENDING(ValueType value) noexcept { Reg::Write<F_VECTPENDING>(value); }
    static auto ReadRETTOBASE() noexcept -> ValueType { return Reg::Read<F_RETTOBASE>(); }
    static void WriteRETTOBASE(ValueType value) noexcept { Reg::Write<F_RETTOBASE>(value); }
    static auto ReadVECTACTIVE() noexcept -> ValueType { return Reg::Read<F_VECTACTIVE>(); }
    static void WriteVECTACTIVE(ValueType value) noexcept { Reg::Write<F_VECTACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed04;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NMIPENDSET = CortexM3::Field<ValueType, 31, 1>;
    using F_PENDSVSET = CortexM3::Field<ValueType, 28, 1>;
    using F_PENDSVCLR = CortexM3::Field<ValueType, 27, 1>;
    using F_PENDSTSET = CortexM3::Field<ValueType, 26, 1>;
    using F_PENDSTCLR = CortexM3::Field<ValueType, 25, 1>;
    using F_ISRPREEMPT = CortexM3::Field<ValueType, 23, 1>;
    using F_ISRPENDING = CortexM3::Field<ValueType, 22, 1>;
    using F_VECTPENDING = CortexM3::Field<ValueType, 12, 9>;
    using F_RETTOBASE = CortexM3::Field<ValueType, 11, 1>;
    using F_VECTACTIVE = CortexM3::Field<ValueType, 0, 9>;
};

class VTOR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTBLOFF() noexcept -> ValueType { return Reg::Read<F_TBLOFF>(); }
    static void WriteTBLOFF(ValueType value) noexcept { Reg::Write<F_TBLOFF>(value); }
    static auto ReadTBLBASE() noexcept -> ValueType { return Reg::Read<F_TBLBASE>(); }
    static void WriteTBLBASE(ValueType value) noexcept { Reg::Write<F_TBLBASE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TBLOFF = CortexM3::Field<ValueType, 7, 25>;
    using F_TBLBASE = CortexM3::Field<ValueType, 29, 1>;
};

class DEMCR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadMON_EN() noexcept -> ValueType { return Reg::Read<F_MON_EN>(); }
    static auto ReadMON_PEND() noexcept -> ValueType { return Reg::Read<F_MON_PEND>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000edfc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MON_EN = CortexM3::Field<ValueType, 16, 1>;
    using F_MON_PEND = CortexM3::Field<ValueType, 17, 1>;
};

class AIRCR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadVECTKEY() noexcept -> ValueType { return Reg::Read<F_VECTKEY>(); }
    static void WriteVECTKEY(ValueType value) noexcept { Reg::Write<F_VECTKEY>(value); }
    static auto ReadVECTKEYSTAT() noexcept -> ValueType { return Reg::Read<F_VECTKEYSTAT>(); }
    static void WriteVECTKEYSTAT(ValueType value) noexcept { Reg::Write<F_VECTKEYSTAT>(value); }
    static auto ReadENDIANNESS() noexcept -> ValueType { return Reg::Read<F_ENDIANNESS>(); }
    static void WriteENDIANNESS(ValueType value) noexcept { Reg::Write<F_ENDIANNESS>(value); }
    static auto ReadPRIGROUP() noexcept -> ValueType { return Reg::Read<F_PRIGROUP>(); }
    static void WritePRIGROUP(ValueType value) noexcept { Reg::Write<F_PRIGROUP>(value); }
    static auto ReadSYSRESETREQ() noexcept -> ValueType { return Reg::Read<F_SYSRESETREQ>(); }
    static void WriteSYSRESETREQ(ValueType value) noexcept { Reg::Write<F_SYSRESETREQ>(value); }
    static auto ReadVECTCLRACTIVE() noexcept -> ValueType { return Reg::Read<F_VECTCLRACTIVE>(); }
    static void WriteVECTCLRACTIVE(ValueType value) noexcept { Reg::Write<F_VECTCLRACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed0c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_VECTKEY = CortexM3::Field<ValueType, 16, 16>;
    using F_VECTKEYSTAT = CortexM3::Field<ValueType, 16, 16>;
    using F_ENDIANNESS = CortexM3::Field<ValueType, 15, 1>;
    using F_PRIGROUP = CortexM3::Field<ValueType, 8, 3>;
    using F_SYSRESETREQ = CortexM3::Field<ValueType, 2, 1>;
    using F_VECTCLRACTIVE = CortexM3::Field<ValueType, 1, 1>;
};

class SCR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSEVONPEND() noexcept -> ValueType { return Reg::Read<F_SEVONPEND>(); }
    static void WriteSEVONPEND(ValueType value) noexcept { Reg::Write<F_SEVONPEND>(value); }
    static auto ReadSLEEPDEEP() noexcept -> ValueType { return Reg::Read<F_SLEEPDEEP>(); }
    static void WriteSLEEPDEEP(ValueType value) noexcept { Reg::Write<F_SLEEPDEEP>(value); }
    static auto ReadSLEEPONEXIT() noexcept -> ValueType { return Reg::Read<F_SLEEPONEXIT>(); }
    static void WriteSLEEPONEXIT(ValueType value) noexcept { Reg::Write<F_SLEEPONEXIT>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed10;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SEVONPEND = CortexM3::Field<ValueType, 4, 1>;
    using F_SLEEPDEEP = CortexM3::Field<ValueType, 2, 1>;
    using F_SLEEPONEXIT = CortexM3::Field<ValueType, 1, 1>;
};

class CCR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTKALIGN() noexcept -> ValueType { return Reg::Read<F_STKALIGN>(); }
    static void WriteSTKALIGN(ValueType value) noexcept { Reg::Write<F_STKALIGN>(value); }
    static auto ReadBFHFNMIGN() noexcept -> ValueType { return Reg::Read<F_BFHFNMIGN>(); }
    static void WriteBFHFNMIGN(ValueType value) noexcept { Reg::Write<F_BFHFNMIGN>(value); }
    static auto ReadDIV_0_TRP() noexcept -> ValueType { return Reg::Read<F_DIV_0_TRP>(); }
    static void WriteDIV_0_TRP(ValueType value) noexcept { Reg::Write<F_DIV_0_TRP>(value); }
    static auto ReadUNALIGN_TRP() noexcept -> ValueType { return Reg::Read<F_UNALIGN_TRP>(); }
    static void WriteUNALIGN_TRP(ValueType value) noexcept { Reg::Write<F_UNALIGN_TRP>(value); }
    static auto ReadUSERSETMPEND() noexcept -> ValueType { return Reg::Read<F_USERSETMPEND>(); }
    static void WriteUSERSETMPEND(ValueType value) noexcept { Reg::Write<F_USERSETMPEND>(value); }
    static auto ReadNONBASETHRDENA() noexcept -> ValueType { return Reg::Read<F_NONBASETHRDENA>(); }
    static void WriteNONBASETHRDENA(ValueType value) noexcept { Reg::Write<F_NONBASETHRDENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed14;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STKALIGN = CortexM3::Field<ValueType, 9, 1>;
    using F_BFHFNMIGN = CortexM3::Field<ValueType, 8, 1>;
    using F_DIV_0_TRP = CortexM3::Field<ValueType, 4, 1>;
    using F_UNALIGN_TRP = CortexM3::Field<ValueType, 3, 1>;
    using F_USERSETMPEND = CortexM3::Field<ValueType, 1, 1>;
    using F_NONBASETHRDENA = CortexM3::Field<ValueType, 0, 1>;
};

class SHPR1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_7() noexcept -> ValueType { return Reg::Read<F_PRI_7>(); }
    static void WritePRI_7(ValueType value) noexcept { Reg::Write<F_PRI_7>(value); }
    static auto ReadPRI_6() noexcept -> ValueType { return Reg::Read<F_PRI_6>(); }
    static void WritePRI_6(ValueType value) noexcept { Reg::Write<F_PRI_6>(value); }
    static auto ReadPRI_5() noexcept -> ValueType { return Reg::Read<F_PRI_5>(); }
    static void WritePRI_5(ValueType value) noexcept { Reg::Write<F_PRI_5>(value); }
    static auto ReadPRI_4() noexcept -> ValueType { return Reg::Read<F_PRI_4>(); }
    static void WritePRI_4(ValueType value) noexcept { Reg::Write<F_PRI_4>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed18;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_7 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_6 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_5 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_4 = CortexM3::Field<ValueType, 0, 8>;
};

class SHPR2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_11() noexcept -> ValueType { return Reg::Read<F_PRI_11>(); }
    static void WritePRI_11(ValueType value) noexcept { Reg::Write<F_PRI_11>(value); }
    static auto ReadPRI_10() noexcept -> ValueType { return Reg::Read<F_PRI_10>(); }
    static void WritePRI_10(ValueType value) noexcept { Reg::Write<F_PRI_10>(value); }
    static auto ReadPRI_9() noexcept -> ValueType { return Reg::Read<F_PRI_9>(); }
    static void WritePRI_9(ValueType value) noexcept { Reg::Write<F_PRI_9>(value); }
    static auto ReadPRI_8() noexcept -> ValueType { return Reg::Read<F_PRI_8>(); }
    static void WritePRI_8(ValueType value) noexcept { Reg::Write<F_PRI_8>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed1c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_11 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_10 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_9 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_8 = CortexM3::Field<ValueType, 0, 8>;
};

class SHPR3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_15() noexcept -> ValueType { return Reg::Read<F_PRI_15>(); }
    static void WritePRI_15(ValueType value) noexcept { Reg::Write<F_PRI_15>(value); }
    static auto ReadPRI_14() noexcept -> ValueType { return Reg::Read<F_PRI_14>(); }
    static void WritePRI_14(ValueType value) noexcept { Reg::Write<F_PRI_14>(value); }
    static auto ReadPRI_13() noexcept -> ValueType { return Reg::Read<F_PRI_13>(); }
    static void WritePRI_13(ValueType value) noexcept { Reg::Write<F_PRI_13>(value); }
    static auto ReadPRI_12() noexcept -> ValueType { return Reg::Read<F_PRI_12>(); }
    static void WritePRI_12(ValueType value) noexcept { Reg::Write<F_PRI_12>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed20;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_15 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_14 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_13 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_12 = CortexM3::Field<ValueType, 0, 8>;
};

class SHCSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadUSGFAULTENA() noexcept -> ValueType { return Reg::Read<F_USGFAULTENA>(); }
    static void WriteUSGFAULTENA(ValueType value) noexcept { Reg::Write<F_USGFAULTENA>(value); }
    static auto ReadBUSFAULTENA() noexcept -> ValueType { return Reg::Read<F_BUSFAULTENA>(); }
    static void WriteBUSFAULTENA(ValueType value) noexcept { Reg::Write<F_BUSFAULTENA>(value); }
    static auto ReadMEMFAULTENA() noexcept -> ValueType { return Reg::Read<F_MEMFAULTENA>(); }
    static void WriteMEMFAULTENA(ValueType value) noexcept { Reg::Write<F_MEMFAULTENA>(value); }
    static auto ReadSVCALLPENDED() noexcept -> ValueType { return Reg::Read<F_SVCALLPENDED>(); }
    static void WriteSVCALLPENDED(ValueType value) noexcept { Reg::Write<F_SVCALLPENDED>(value); }
    static auto ReadBUSFAULTPENDED() noexcept -> ValueType { return Reg::Read<F_BUSFAULTPENDED>(); }
    static void WriteBUSFAULTPENDED(ValueType value) noexcept { Reg::Write<F_BUSFAULTPENDED>(value); }
    static auto ReadMEMFAULTPENDED() noexcept -> ValueType { return Reg::Read<F_MEMFAULTPENDED>(); }
    static void WriteMEMFAULTPENDED(ValueType value) noexcept { Reg::Write<F_MEMFAULTPENDED>(value); }
    static auto ReadUSGFAULTPENDED() noexcept -> ValueType { return Reg::Read<F_USGFAULTPENDED>(); }
    static void WriteUSGFAULTPENDED(ValueType value) noexcept { Reg::Write<F_USGFAULTPENDED>(value); }
    static auto ReadSYSTICKACT() noexcept -> ValueType { return Reg::Read<F_SYSTICKACT>(); }
    static void WriteSYSTICKACT(ValueType value) noexcept { Reg::Write<F_SYSTICKACT>(value); }
    static auto ReadPENDSVACT() noexcept -> ValueType { return Reg::Read<F_PENDSVACT>(); }
    static void WritePENDSVACT(ValueType value) noexcept { Reg::Write<F_PENDSVACT>(value); }
    static auto ReadMONITORACT() noexcept -> ValueType { return Reg::Read<F_MONITORACT>(); }
    static void WriteMONITORACT(ValueType value) noexcept { Reg::Write<F_MONITORACT>(value); }
    static auto ReadSVCALLACT() noexcept -> ValueType { return Reg::Read<F_SVCALLACT>(); }
    static void WriteSVCALLACT(ValueType value) noexcept { Reg::Write<F_SVCALLACT>(value); }
    static auto ReadUSGFAULTACT() noexcept -> ValueType { return Reg::Read<F_USGFAULTACT>(); }
    static void WriteUSGFAULTACT(ValueType value) noexcept { Reg::Write<F_USGFAULTACT>(value); }
    static auto ReadBUSFAULTACT() noexcept -> ValueType { return Reg::Read<F_BUSFAULTACT>(); }
    static void WriteBUSFAULTACT(ValueType value) noexcept { Reg::Write<F_BUSFAULTACT>(value); }
    static auto ReadMEMFAULTACT() noexcept -> ValueType { return Reg::Read<F_MEMFAULTACT>(); }
    static void WriteMEMFAULTACT(ValueType value) noexcept { Reg::Write<F_MEMFAULTACT>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed24;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_USGFAULTENA = CortexM3::Field<ValueType, 18, 1>;
    using F_BUSFAULTENA = CortexM3::Field<ValueType, 17, 1>;
    using F_MEMFAULTENA = CortexM3::Field<ValueType, 16, 1>;
    using F_SVCALLPENDED = CortexM3::Field<ValueType, 15, 1>;
    using F_BUSFAULTPENDED = CortexM3::Field<ValueType, 14, 1>;
    using F_MEMFAULTPENDED = CortexM3::Field<ValueType, 13, 1>;
    using F_USGFAULTPENDED = CortexM3::Field<ValueType, 12, 1>;
    using F_SYSTICKACT = CortexM3::Field<ValueType, 11, 1>;
    using F_PENDSVACT = CortexM3::Field<ValueType, 10, 1>;
    using F_MONITORACT = CortexM3::Field<ValueType, 8, 1>;
    using F_SVCALLACT = CortexM3::Field<ValueType, 7, 1>;
    using F_USGFAULTACT = CortexM3::Field<ValueType, 3, 1>;
    using F_BUSFAULTACT = CortexM3::Field<ValueType, 1, 1>;
    using F_MEMFAULTACT = CortexM3::Field<ValueType, 0, 1>;
};

class CFSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDIVBYZERO() noexcept -> ValueType { return Reg::Read<F_DIVBYZERO>(); }
    static void WriteDIVBYZERO(ValueType value) noexcept { Reg::Write<F_DIVBYZERO>(value); }
    static auto ReadUNALIGNED() noexcept -> ValueType { return Reg::Read<F_UNALIGNED>(); }
    static void WriteUNALIGNED(ValueType value) noexcept { Reg::Write<F_UNALIGNED>(value); }
    static auto ReadNOCP() noexcept -> ValueType { return Reg::Read<F_NOCP>(); }
    static void WriteNOCP(ValueType value) noexcept { Reg::Write<F_NOCP>(value); }
    static auto ReadINVPC() noexcept -> ValueType { return Reg::Read<F_INVPC>(); }
    static void WriteINVPC(ValueType value) noexcept { Reg::Write<F_INVPC>(value); }
    static auto ReadINVSTATE() noexcept -> ValueType { return Reg::Read<F_INVSTATE>(); }
    static void WriteINVSTATE(ValueType value) noexcept { Reg::Write<F_INVSTATE>(value); }
    static auto ReadUNDEFINSTR() noexcept -> ValueType { return Reg::Read<F_UNDEFINSTR>(); }
    static void WriteUNDEFINSTR(ValueType value) noexcept { Reg::Write<F_UNDEFINSTR>(value); }
    static auto ReadBFARVALID() noexcept -> ValueType { return Reg::Read<F_BFARVALID>(); }
    static void WriteBFARVALID(ValueType value) noexcept { Reg::Write<F_BFARVALID>(value); }
    static auto ReadLSPERR() noexcept -> ValueType { return Reg::Read<F_LSPERR>(); }
    static void WriteLSPERR(ValueType value) noexcept { Reg::Write<F_LSPERR>(value); }
    static auto ReadSTKERR() noexcept -> ValueType { return Reg::Read<F_STKERR>(); }
    static void WriteSTKERR(ValueType value) noexcept { Reg::Write<F_STKERR>(value); }
    static auto ReadUNSTKERR() noexcept -> ValueType { return Reg::Read<F_UNSTKERR>(); }
    static void WriteUNSTKERR(ValueType value) noexcept { Reg::Write<F_UNSTKERR>(value); }
    static auto ReadIMPRECISERR() noexcept -> ValueType { return Reg::Read<F_IMPRECISERR>(); }
    static void WriteIMPRECISERR(ValueType value) noexcept { Reg::Write<F_IMPRECISERR>(value); }
    static auto ReadPRECISERR() noexcept -> ValueType { return Reg::Read<F_PRECISERR>(); }
    static void WritePRECISERR(ValueType value) noexcept { Reg::Write<F_PRECISERR>(value); }
    static auto ReadIBUSERR() noexcept -> ValueType { return Reg::Read<F_IBUSERR>(); }
    static void WriteIBUSERR(ValueType value) noexcept { Reg::Write<F_IBUSERR>(value); }
    static auto ReadMMARVALID() noexcept -> ValueType { return Reg::Read<F_MMARVALID>(); }
    static void WriteMMARVALID(ValueType value) noexcept { Reg::Write<F_MMARVALID>(value); }
    static auto ReadMLSPERR() noexcept -> ValueType { return Reg::Read<F_MLSPERR>(); }
    static void WriteMLSPERR(ValueType value) noexcept { Reg::Write<F_MLSPERR>(value); }
    static auto ReadMSTKERR() noexcept -> ValueType { return Reg::Read<F_MSTKERR>(); }
    static void WriteMSTKERR(ValueType value) noexcept { Reg::Write<F_MSTKERR>(value); }
    static auto ReadMUNSTKERR() noexcept -> ValueType { return Reg::Read<F_MUNSTKERR>(); }
    static void WriteMUNSTKERR(ValueType value) noexcept { Reg::Write<F_MUNSTKERR>(value); }
    static auto ReadDACCVIOL() noexcept -> ValueType { return Reg::Read<F_DACCVIOL>(); }
    static void WriteDACCVIOL(ValueType value) noexcept { Reg::Write<F_DACCVIOL>(value); }
    static auto ReadIACCVIOL() noexcept -> ValueType { return Reg::Read<F_IACCVIOL>(); }
    static void WriteIACCVIOL(ValueType value) noexcept { Reg::Write<F_IACCVIOL>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed28;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DIVBYZERO = CortexM3::Field<ValueType, 25, 1>;
    using F_UNALIGNED = CortexM3::Field<ValueType, 24, 1>;
    using F_NOCP = CortexM3::Field<ValueType, 19, 1>;
    using F_INVPC = CortexM3::Field<ValueType, 18, 1>;
    using F_INVSTATE = CortexM3::Field<ValueType, 17, 1>;
    using F_UNDEFINSTR = CortexM3::Field<ValueType, 16, 1>;
    using F_BFARVALID = CortexM3::Field<ValueType, 15, 1>;
    using F_LSPERR = CortexM3::Field<ValueType, 13, 1>;
    using F_STKERR = CortexM3::Field<ValueType, 12, 1>;
    using F_UNSTKERR = CortexM3::Field<ValueType, 11, 1>;
    using F_IMPRECISERR = CortexM3::Field<ValueType, 10, 1>;
    using F_PRECISERR = CortexM3::Field<ValueType, 9, 1>;
    using F_IBUSERR = CortexM3::Field<ValueType, 8, 1>;
    using F_MMARVALID = CortexM3::Field<ValueType, 7, 1>;
    using F_MLSPERR = CortexM3::Field<ValueType, 5, 1>;
    using F_MSTKERR = CortexM3::Field<ValueType, 4, 1>;
    using F_MUNSTKERR = CortexM3::Field<ValueType, 3, 1>;
    using F_DACCVIOL = CortexM3::Field<ValueType, 1, 1>;
    using F_IACCVIOL = CortexM3::Field<ValueType, 0, 1>;
};

class HFSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDEBUGEVT() noexcept -> ValueType { return Reg::Read<F_DEBUGEVT>(); }
    static void WriteDEBUGEVT(ValueType value) noexcept { Reg::Write<F_DEBUGEVT>(value); }
    static auto ReadFORCED() noexcept -> ValueType { return Reg::Read<F_FORCED>(); }
    static void WriteFORCED(ValueType value) noexcept { Reg::Write<F_FORCED>(value); }
    static auto ReadVECTTBL() noexcept -> ValueType { return Reg::Read<F_VECTTBL>(); }
    static void WriteVECTTBL(ValueType value) noexcept { Reg::Write<F_VECTTBL>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed2c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DEBUGEVT = CortexM3::Field<ValueType, 31, 1>;
    using F_FORCED = CortexM3::Field<ValueType, 30, 1>;
    using F_VECTTBL = CortexM3::Field<ValueType, 1, 1>;
};

class DFSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEXTERNAL() noexcept -> ValueType { return Reg::Read<F_EXTERNAL>(); }
    static void WriteEXTERNAL(ValueType value) noexcept { Reg::Write<F_EXTERNAL>(value); }
    static auto ReadVCATCH() noexcept -> ValueType { return Reg::Read<F_VCATCH>(); }
    static void WriteVCATCH(ValueType value) noexcept { Reg::Write<F_VCATCH>(value); }
    static auto ReadDWTTRAP() noexcept -> ValueType { return Reg::Read<F_DWTTRAP>(); }
    static void WriteDWTTRAP(ValueType value) noexcept { Reg::Write<F_DWTTRAP>(value); }
    static auto ReadBKPT() noexcept -> ValueType { return Reg::Read<F_BKPT>(); }
    static void WriteBKPT(ValueType value) noexcept { Reg::Write<F_BKPT>(value); }
    static auto ReadHALTED() noexcept -> ValueType { return Reg::Read<F_HALTED>(); }
    static void WriteHALTED(ValueType value) noexcept { Reg::Write<F_HALTED>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed30;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EXTERNAL = CortexM3::Field<ValueType, 4, 1>;
    using F_VCATCH = CortexM3::Field<ValueType, 3, 1>;
    using F_DWTTRAP = CortexM3::Field<ValueType, 2, 1>;
    using F_BKPT = CortexM3::Field<ValueType, 1, 1>;
    using F_HALTED = CortexM3::Field<ValueType, 0, 1>;
};

class MMFAR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed34;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class BFAR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed38;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class AFSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed3c;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class CPACR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCP11() noexcept -> ValueType { return Reg::Read<F_CP11>(); }
    static void WriteCP11(ValueType value) noexcept { Reg::Write<F_CP11>(value); }
    static auto ReadCP10() noexcept -> ValueType { return Reg::Read<F_CP10>(); }
    static void WriteCP10(ValueType value) noexcept { Reg::Write<F_CP10>(value); }
    static auto ReadCP7() noexcept -> ValueType { return Reg::Read<F_CP7>(); }
    static void WriteCP7(ValueType value) noexcept { Reg::Write<F_CP7>(value); }
    static auto ReadCP6() noexcept -> ValueType { return Reg::Read<F_CP6>(); }
    static void WriteCP6(ValueType value) noexcept { Reg::Write<F_CP6>(value); }
    static auto ReadCP5() noexcept -> ValueType { return Reg::Read<F_CP5>(); }
    static void WriteCP5(ValueType value) noexcept { Reg::Write<F_CP5>(value); }
    static auto ReadCP4() noexcept -> ValueType { return Reg::Read<F_CP4>(); }
    static void WriteCP4(ValueType value) noexcept { Reg::Write<F_CP4>(value); }
    static auto ReadCP3() noexcept -> ValueType { return Reg::Read<F_CP3>(); }
    static void WriteCP3(ValueType value) noexcept { Reg::Write<F_CP3>(value); }
    static auto ReadCP2() noexcept -> ValueType { return Reg::Read<F_CP2>(); }
    static void WriteCP2(ValueType value) noexcept { Reg::Write<F_CP2>(value); }
    static auto ReadCP1() noexcept -> ValueType { return Reg::Read<F_CP1>(); }
    static void WriteCP1(ValueType value) noexcept { Reg::Write<F_CP1>(value); }
    static auto ReadCP0() noexcept -> ValueType { return Reg::Read<F_CP0>(); }
    static void WriteCP0(ValueType value) noexcept { Reg::Write<F_CP0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ed88;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CP11 = CortexM3::Field<ValueType, 22, 2>;
    using F_CP10 = CortexM3::Field<ValueType, 20, 2>;
    using F_CP7 = CortexM3::Field<ValueType, 14, 2>;
    using F_CP6 = CortexM3::Field<ValueType, 12, 2>;
    using F_CP5 = CortexM3::Field<ValueType, 10, 2>;
    using F_CP4 = CortexM3::Field<ValueType, 8, 2>;
    using F_CP3 = CortexM3::Field<ValueType, 6, 2>;
    using F_CP2 = CortexM3::Field<ValueType, 4, 2>;
    using F_CP1 = CortexM3::Field<ValueType, 2, 2>;
    using F_CP0 = CortexM3::Field<ValueType, 0, 2>;
};

class STIR {
public:
    using ValueType = std::uint32_t;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteINTID(ValueType value) noexcept { Reg::Write<F_INTID>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ef00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INTID = CortexM3::Field<ValueType, 0, 9>;
};

} // namespace CortexM3::Control
