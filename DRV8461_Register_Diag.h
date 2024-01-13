#ifndef DRV8461_Register_Diag
#define DRV8461_Register_Diag

#include <cstdint>

///DIAG
// DIAG STATUS 1 REGISTER SETINGS ************************************************************************************// 
enum class DRV8461_DIAG1_Reg_Val : uint8_t {
  DRV8461_DIAG1_OCP_LS2_B = 0x80,      // Indicates overcurrent fault on the low-side FET of half bridge 2 in BOUT.
  DRV8461_DIAG1_OCP_HS2_B = 0x40,      // Indicates overcurrent fault on the high-side FET of half bridge 2 in BOUT.
  DRV8461_DIAG1_OCP_LS1_B = 0x20,      // Indicates overcurrent fault on the low-side FET of half bridge 1 in BOUT.
  DRV8461_DIAG1_OCP_HS1_B = 0x10,      // Indicates overcurrent fault on the high-side FET of half bridge 1 in BOUT.
  DRV8461_DIAG1_OCP_LS2_A = 0x08,      // Indicates overcurrent fault on the low-side FET of half bridge 2 in AOUT.
  DRV8461_DIAG1_OCP_HS2_A = 0x04,      // Indicates overcurrent fault on the high-side FET of half bridge 2 in AOUT.
  DRV8461_DIAG1_OCP_LS1_A = 0x02,      // Indicates overcurrent fault on the low-side FET of half bridge 1 in AOUT.
  DRV8461_DIAG1_OCP_HS1_A = 0x01,      // Indicates overcurrent fault on the high-side FET of half bridge 1 in AOUT.
};


// DIAG STATUS 2 REGISTER SETINGS ************************************************************************************// 
enum class DRV8461_DIAG2_Reg_Val : uint8_t {
  DRV8461_DIAG2_STSL = 0x80,           // Indicates operating in standstill power saving mode
  DRV8461_DIAG2_OTW = 0x40,            // Indicates overtemperature warning.
  DRV8461_DIAG2_OTS = 0x20,            // Indicates overtemperature shutdown.
  DRV8461_DIAG2_STL_LRN_OK = 0x10,     // Indicates stall detection learning is successful.
  DRV8461_DIAG2_STALL = 0x08,          // Indicates motor stall condition.
  DRV8461_DIAG2_OL_B = 0x02,           // Indicates open-load detection on BOUT.
  DRV8461_DIAG2_OL_A = 0x01,           // Indicates open-load detection on AOUT
};


// DIAG STATUS 3 REGISTER SETINGS ************************************************************************************// 
enum class DRV8461_DIAG3_Reg_Val : uint8_t {
  DRV8461_DIAG3_NHOME = 0x40,          // Indicates indexer is at a position other than home.
  DRV8461_DIAG3_CNT_OFLW = 0x20,       // Indicates ATQ_CNT is more than ATQ_UL.
  DRV8461_DIAG3_CNT_UFLW = 0x10,       // Indicates ATQ_CNT is less than ATQ_LL.
  DRV8461_DIAG3_NPOR = 0x02,           // Low indicates a prior VCC UVLO event, High indicates that NPOR has been cleared by CLR_FLT or nSLEEP after a VCC UVLO.
};


#endif