///Header File with all Register Addresses for DRV8461.

#ifndef DRV8461_Register_Address_Locations
#define DRV8461_Register_Address_Locations

#include <cstdint>

#include "DRV8461_Register_Fault"
#include "DRV8461_Register_Diag.h"
#include "DRV8461_Register_CTRL.h"

// REGISTER ADDRESSES ************************************************************************************************// 
enum class DRV8461_REG_ADDR : uint8_t {
  DRV8461_REG_FAULT        = 0x00,            // Fault status register.
  DRV8461_REG_DIAG1        = 0x01,            // DIAG status 1.
  DRV8461_REG_DIAG2        = 0x02,            // DIAG status 2.
  DRV8461_REG_DIAG3        = 0x03,            // DIAG status 3.
  DRV8461_REG_CTRL1        = 0x04,            // Control register 1.
  DRV8461_REG_CTRL2        = 0x05,            // Control register 2.
  DRV8461_REG_CTRL3        = 0x06,            // Control register 3.
  DRV8461_REG_CTRL4        = 0x07,            // Control register 4.
  DRV8461_REG_CTRL5        = 0x08,            // Control register 5.
  DRV8461_REG_CTRL6        = 0x09,            // Control register 6.
  DRV8461_REG_CTRL7        = 0x0A,            // Control register 7.
  DRV8461_REG_CTRL8        = 0x0B,            // Control register 8.
  DRV8461_REG_CTRL9        = 0x0C,            // Control register 9.
  DRV8461_REG_CTRL10       = 0x0D,            // Control Register 10.
  DRV8461_REG_CTRL11       = 0x0E,            // Control Register 11.
  DRV8461_REG_CTRL12       = 0x0F,            // Control Register 12.
  DRV8461_REG_CTRL13       = 0x10,            // Control Register 13.
  DRV8461_REG_INDEX1       = 0x11,            // Index Register 1.
  DRV8461_REG_INDEX2       = 0x12,            // Index Register 2.
  DRV8461_REG_INDEX3       = 0x13,            // Index Register 3.
  DRV8461_REG_INDEX4       = 0x14,            // Index Register 4.
  DRV8461_REG_INDEX5       = 0x15,            // Index Register 5.
  DRV8461_REG_CUSTOM_CTRL1 = 0x16,            // Custom Microstep Register 1.
  DRV8461_REG_CUSTOM_CTRL2 = 0x17,            // Custom Microstep Register 2
  DRV8461_REG_CUSTOM_CTRL3 = 0x18,            // Custom Microstep Register 3
  DRV8461_REG_CUSTOM_CTRL4 = 0x19,            // Custom Microstep Register 4
  DRV8461_REG_CUSTOM_CTRL5 = 0x1A,            // Custom Microstep Register 5
  DRV8461_REG_CUSTOM_CTRL6 = 0x1B,            // Custom Microstep Register 6
  DRV8461_REG_CUSTOM_CTRL7 = 0x1C,            // Custom Microstep Register 7
  DRV8461_REG_CUSTOM_CTRL8 = 0x1D,            // Custom Microstep Register 8
  DRV8461_REG_CUSTOM_CTRL9 = 0x1E,            // Custom Microstep Register 9
  DRV8461_REG_ATQ_CTRL1    = 0x1F,            // Auto Torque Register 1.
  DRV8461_REG_ATQ_CTRL2    = 0x20,            // Auto Torque Register 2.
  DRV8461_REG_ATQ_CTRL3    = 0x21,            // Auto Torque Register 3.
  DRV8461_REG_ATQ_CTRL4    = 0x22,            // Auto Torque Register 4.
  DRV8461_REG_ATQ_CTRL5    = 0x23,            // Auto Torque Register 5.
  DRV8461_REG_ATQ_CTRL6    = 0x24,            // Auto Torque Register 6.
  DRV8461_REG_ATQ_CTRL7    = 0x25,            // Auto Torque Register 7.
  DRV8461_REG_ATQ_CTRL8    = 0x26,            // Auto Torque Register 8.
  DRV8461_REG_ATQ_CTRL9    = 0x27,            // Auto Torque Register 9.
  DRV8461_REG_ATQ_CTRL10   = 0x28,            // Auto Torque Register 10.
  DRV8461_REG_ATQ_CTRL11   = 0x29,            // Auto Torque Register 11.
  DRV8461_REG_ATQ_CTRL12   = 0x2A,            // Auto Torque Register 12.
  DRV8461_REG_ATQ_CTRL13   = 0x2B,            // Auto Torque Register 13.
  DRV8461_REG_ATQ_CTRL14   = 0x2C,            // Auto Torque Register 14.
  DRV8461_REG_ATQ_CTRL15   = 0x2D,            // Auto Torque Register 15.
  DRV8461_REG_ATQ_CTRL16   = 0x2E,            // Auto Torque Register 16.
  DRV8461_REG_ATQ_CTRL17   = 0x2F,            // Auto Torque Register 17.
  DRV8461_REG_ATQ_CTRL18   = 0x30,            // Auto Torque Register 18.
  DRV8461_REG_SS_CTRL1     = 0x31,            // Silent Step Register 1.
  DRV8461_REG_SS_CTRL2     = 0x32,            // Silent Step Register 2.
  DRV8461_REG_SS_CTRL3     = 0x33,            // Silent Step Register 3.
  DRV8461_REG_SS_CTRL4     = 0x34,            // Silent Step Register 4.
  DRV8461_REG_SS_CTRL5     = 0x35,            // Silent Step Register 5.
  DRV8461_REG_CTRL14       = 0x3C,            // Control Register 14.
};




#endif