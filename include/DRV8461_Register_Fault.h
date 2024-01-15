#ifndef DRV8461_Register_Fault
#define DRV8461_Register_Fault

#include <cstdint>


///FAULT
// FAULT REGISTER SETINGS ********************************************************************************************// 
enum class DRV8461_FAULT_Reg_Val : uint8_t {
  DRV8461_FAULT_FAULT = 0x80,          // Fault bit is high when nFAULT output is low.
  DRV8461_FAULT_SPI_ERR = 0x40,        // Indicates SPI protocol errors.
  DRV8461_FAULT_UVLO = 0x20,           // Indicates undervoltage lockout fault condition.
  DRV8461_FAULT_CPUV = 0x10,           // Indicates charge pump undervoltage fault condition.
  DRV8461_FAULT_OCP = 0x08,            // Indicates overcurrent fault condition.
  DRV8461_FAULT_STL = 0x04,            // Indicates motor stall condition.
  DRV8461_FAULT_TF = 0x02,             // Indicates overtemperature warning/shutdown condition.
  DRV8461_FAULT_OL = 0x01,             // Indicates open-load condition.
};

#endif