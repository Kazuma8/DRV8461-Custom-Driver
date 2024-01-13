#ifndef DRV8461_REGISTERS_H
#define DRV8461_REGISTERS_H

/*  DRV8461_Registers.h

    Register addresses and settings for the Texas Instruments DRV8461 stepper
    driver.

*/
#pragma once

#include <Arduino.h>
#include <SPI.h>

#include 'DRV8461_Register_Addresses.h' //includes stdint.h


///FROM POLOLU FILE**********************************************

/// This class provides low-level functions for reading and writing from the SPI
/// interface of a DRV8434S stepper motor controller IC.
///
/// Most users should use the HighPowerStepperDriver class, which provides a
/// higher-level interface, instead of this class.
class DRV8434SSPI
{
public:
  /// Configures this object to use the specified pin as a chip select pin.
  ///
  /// You must use a chip select pin; the DRV8434S requires it.
  void setChipSelectPin(uint8_t pin)
  {
    csPin = pin;
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);
  }

  /// Reads the register at the given address and returns its raw value.
  uint8_t readReg(uint8_t address)
  {
    // Arduino out / DRV8434 in: First byte contains read/write bit and register
    // address; second byte is unused.
    // Arduino in / DRV8434 out: First byte contains status; second byte
    // contains data in register being read.

    selectChip();
    lastStatus = transfer((0x20 | (address & 0b11111)) << 1);
    uint8_t data = transfer(0);
    deselectChip();
    return data;
  }

  /// Reads the register at the given address and returns its raw value.
  uint16_t readReg(DRV8461_REG_ADDR address)
  {
    return readReg((uint8_t)address);
  }

  /// Writes the specified value to a register.
  uint8_t writeReg(uint8_t address, uint8_t value)
  {
    // Arduino out / DRV8434 in: First byte contains read/write bit and register
    // address; second byte contains data to write to register.
    // Arduino in / DRV8434 out: First byte contains status; second byte
    // contains old (existing) data in register being written to.

    selectChip();
    lastStatus = transfer((address & 0b11111) << 1);
    uint8_t oldData = transfer(value);
    // The CS line must go low after writing for the value to actually take
    // effect.
    deselectChip();
    return oldData;
  }

  /// Writes the specified value to a register.
  void writeReg(DRV8461_REG_ADDR address, uint8_t value)
  {
    writeReg((uint8_t)address, value);
  }

private:

  SPISettings settings = SPISettings(500000, MSBFIRST, SPI_MODE1);

  uint8_t transfer(uint8_t value)
  {
    return SPI.transfer(value);
  }

  void selectChip()
  {
    digitalWrite(csPin, LOW);
    SPI.beginTransaction(settings);
  }

  void deselectChip()
  {
   SPI.endTransaction();
   digitalWrite(csPin, HIGH);
  }

  uint8_t csPin;

public:

  /// The status reported by the driver during the last read or write.  This
  /// status is the same as that which would be returned by reading the FAULT
  /// register with DRV8434S::readFault(), except the upper two bits are always
  /// 1.
  uint8_t lastStatus = 0;
};




/// This class provides high-level functions for controlling a DRV8461, labelled 8434S stepper
/// motor driver.
class DRV8434S
{
public:
  /// The default constructor.
  DRV8434S()   //Purpose Unknown
  {
    // All settings set to power-on defaults
    ctrl1  = 0x0F;
    ctrl2  = 0x06;
    ctrl3  = 0x38;
    ctrl4  = 0x49;
    ctrl5  = 0x03;
    ctrl6  = 0x20;
    ctrl9  = 0x10;
    ctrl10 = 0x80;
    ctrl11 = 0xFF;
    ctrl12 = 0x20;
    ctrl13 = 0x10;
    ctrl14 = 0x58;
  }

  /// Configures this object to use the specified pin as a chip select pin.
  /// You must use a chip select pin; the DRV8711 requires it.
  void setChipSelectPin(uint8_t pin)
  {
    driver.setChipSelectPin(pin);
  }

  /// Changes all of the driver's settings back to their default values.
  ///
  /// It is good to call this near the beginning of your program to ensure that
  /// there are no settings left over from an earlier time that might affect the
  /// operation of the driver.
  void resetSettings()
  {
    ctrl1  = 0x0F;
    ctrl2  = 0x06;
    ctrl3  = 0x38;
    ctrl4  = 0x49;
    ctrl5  = 0x03;
    ctrl6  = 0x20;
    ctrl9  = 0x10;
    ctrl10 = 0x80;
    ctrl11 = 0xFF;
    ctrl12 = 0x20;
    ctrl13 = 0x10;
    ctrl14 = 0x58;


    applySettings();
  }

  /// Reads back the SPI configuration registers from the device and verifies
  /// that they are equal to the cached copies stored in this class.
  ///
  /// This can be used to verify that the driver is powered on and has not lost
  /// them due to a power failure.  The STATUS register is not verified because
  /// it does not contain any driver settings.
  ///
  /// @return 1 if the settings from the device match the cached copies, 0 if
  /// they do not.
  bool verifySettings()
  {
    return driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL1)  == ctrl1  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2)  == ctrl2  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL3)  == ctrl3  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL4)  == ctrl4  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL5)  == ctrl5  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL6)  == ctrl6  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL9)  == ctrl9  &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL10) == ctrl10 &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL11) == ctrl11 &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL12) == ctrl12 &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL13) == ctrl13 &&
           driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL14) == ctrl14;
  }

  /// Re-writes the cached settings stored in this class to the device.
  ///
  /// You should not normally need to call this function because settings are
  /// written to the device whenever they are changed.  However, if
  /// verifySettings() returns false (due to a power interruption, for
  /// instance), then you could use applySettings() to get the device's settings
  /// back into the desired state.
  void applySettings()
  {
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL3);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL4);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL5);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL6);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL9);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL10);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL11);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL12);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL13);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL14);

    // CTRL1 is written last because it contains the EN_OUT bit, and we want to
    // try to have all the other settings correct first.
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL1);
  }

  /// Sets the driver's current scalar (TRQ_DAC), which scales the full current
  /// limit (as set by VREF) by the specified percentage. The available settings
  /// are multiples of 0.390625%.
  ///
  /// This function takes an integer, and if the desired current limit is not
  /// available, it generally tries to pick the closest current limit that is
  /// lower than the desired one (although the lowest possible setting is
  /// 6.25%). However, it will round up if the next setting is no more than
  /// 0.75% higher; this allows you to specify 43.75% by passing a value of 43,
  /// for example.
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// // This sets TRQ_DAC to 37.5% (the closest setting lower than 42%):
  /// sd.setCurrentPercent(42);
  ///
  /// // This sets TRQ_DAC to 43.75% (rounding 43 up by 0.75% to 43.75%):
  /// sd.setCurrentPercent(43);
  ///
  /// // This also sets TRQ_DAC to 43.75%; even though the argument is truncated
  /// // to an integer (43), that is then rounded up by 0.75% to 43.75%:
  /// sd.setCurrentPercent(43.75);
  /// ~~~
  void setCurrentPercent(uint8_t percent)
  {
    if (percent > 100) { percent = 100; }
    if (percent < 1) { percent = 1; }

    uint8_t td = ((uint16_t)percent * 64 / 25) - 1; // convert 0-100 to 0-255
    if (td == 0) { td = 1; }                   // restrict to 1-16
    ctrl11 = td;
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL11);
  }

  /// Sets the driver's current scalar (TRQ_DAC) to produce the specified scaled
  /// current limit in milliamps. In order to calculate the correct value for
  /// TRQ_DAC, this function also needs to know the full current limit set by
  /// VREF (i.e. what the current limit is when the scaling is set to 100%).
  /// This is specified by the optional `fullCurrent` argument, which defaults
  /// to 2000 milliamps (2 A).
  ///
  /// If the desired current limit is not
  /// available, this function tries to pick the closest current limit that is
  /// lower than the desired one (although the lowest possible setting is 6.25%
  /// of the full current limit).
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// // This specifies that we want a scaled current limit of 1200 mA and that
  /// // VREF is set to produce a full current limit of 1500 mA. TRQ_DAC will be
  /// // set to 75%, which will produce a 1125 mA scaled current limit.
  /// sd.setCurrentMilliamps(1200, 1500);
  /// ~~~
  void setCurrentMilliamps(uint16_t current, uint16_t fullCurrent = 2000)
  {
    if (fullCurrent > 4000) { fullCurrent = 4000; }
    if (current > fullCurrent) { current = fullCurrent; }

    uint8_t td = (current * 256 / fullCurrent); // convert 0-fullCurrent to 0-16
    if (td == 0) { td = 1; }                   // restrict to 1-16
    ctrl11 = td;
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL11);
  }

  /// Enables the driver (EN_OUT = 1).
  void enableDriver()
  {
    ctrl1 |= (1 << 7);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL1);
  }

  /// Disables the driver (EN_OUT = 0).
  void disableDriver()
  {
    ctrl1 &= ~(1 << 7);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL1);
  }

  /// Sets the driver's decay mode (DECAY).
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// sd.setDecayMode(DRV8434SDecayMode::DRV8461_DECAY_SLOW_SLOW);
  /// ~~~
  void setDecayMode(DRV8461_Decay_Mode mode)
  {
    ctrl1 = (ctrl1 & 0b11111000) | ((uint8_t)mode & 0b111);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL1);
  }

  /// Sets the motor direction (DIR).
  ///
  /// Allowed values are 0 or 1.
  ///
  /// You must first call enableSPIDirection() to allow the direction to be
  /// controlled through SPI.  Once you have done so, you can use this command
  /// to control the direction of the stepper motor and leave the DIR pin
  /// disconnected.
  void setDirection(bool value)
  {
    if (value)
    {
      ctrl2 |= (1 << 7);
    }
    else
    {
      ctrl2 &= ~(1 << 7);
    }
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Returns the cached value of the motor direction (DIR).
  ///
  /// This does not perform any SPI communication with the driver.
  bool getDirection()
  {
    return (ctrl2 >> 7) & 1;
  }

  /// Advances the indexer by one step (STEP = 1).
  ///
  /// You must first call enableSPIStep() to allow stepping to be controlled
  /// through SPI.  Once you have done so, you can use this command to step the
  /// motor and leave the STEP pin disconnected.
  ///
  /// The driver automatically clears the STEP bit after it is written.
  void step()
  {
    driver.writeReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2, ctrl2 | (1 << 6));
  }

  /// Enables direction control through SPI (SPI_DIR = 1), allowing
  /// setDirection() to override the DIR pin.
  void enableSPIDirection()
  {
    ctrl2 |= (1 << 5);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Disables direction control through SPI (SPI_DIR = 0), making the DIR pin
  /// control direction instead.
  void disableSPIDirection()
  {
    ctrl2 &= ~(1 << 5);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Enables stepping through SPI (SPI_STEP = 1), allowing step() to override
  /// the STEP pin.
  void enableSPIStep()
  {
    ctrl2 |= (1 << 4);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Disables stepping through SPI (SPI_STEP = 0), making the STEP pin control
  /// stepping instead.
  void disableSPIStep()
  {
    ctrl2 &= ~(1 << 4);
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Sets the driver's stepping mode (MICROSTEP_MODE).
  ///
  /// This affects many things about the performance of the motor, including how
  /// much the output moves for each step taken and how much current flows
  /// through the coils in each stepping position.
  ///
  /// If an invalid stepping mode is passed to this function, then it selects
  /// 1/16 micro-step, which is the driver's default.
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// sd.setStepMode(DRV8434SStepMode::MicroStep32);
  /// ~~~
  void setStepMode(DRV8461_Micostep_Mode mode)
  {
    if (mode > DRV8461_Micostep_Mode::DRV8461_MICROSTEP_256)
    {
      // Invalid mode; pick 1/16 micro-step by default.
      mode = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_16;
    }

    ctrl2 = (ctrl2 & 0b11110000) | (uint8_t)mode;
    writeCachedReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL2);
  }

  /// Sets the driver's stepping mode (MICROSTEP_MODE).
  ///
  /// This version of the function allows you to express the requested
  /// microstepping ratio as a number directly.
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// sd.setStepMode(32);
  /// ~~~
  int setStepMode(uint16_t mode)
  {
    DRV8461_Micostep_Mode sm;

    switch (mode)
    {
      case 1:   sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_1_71; break;
      case 2:   sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_2;    break;
      case 4:   sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_4;    break;
      case 8:   sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_8;    break;
      case 16:  sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_16;   break;
      case 32:  sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_32;   break;
      case 64:  sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_64;   break;
      case 128: sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_128;  break;
      case 256: sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_256;  break;

      // Invalid mode; pick 1/16 micro-step by default, returns 0 for error checking.
      default:  sm = DRV8461_Micostep_Mode::DRV8461_MICROSTEP_16; return(sm, 1);
    }

    setStepMode(sm, 0);
  }

  /// Reads the FAULT status register of the driver.
  ///
  /// The return value is an 8-bit unsigned integer that has one bit for each
  /// FAULT condition.  You can simply compare the return value to 0 to see if
  /// any of the bits are set, or you can use the logical AND operator (`&`) and
  /// the #DRV8434SFaultBit enum to check individual bits.
  ///
  /// Example usage:
  /// ~~~{.cpp}
  /// if (sd.readFault() & (1 << (uint8_t)DRV8434SFaultBit::UVLO))
  /// {
  ///   // Supply undervoltage lockout is active.
  /// }
  /// ~~~
  uint8_t readFault()
  {
    return driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_FAULT);
  }

  /// Reads the DIAG1 status register of the driver.
  ///
  /// The return value is an 8-bit unsigned integer that has one bit for each
  /// DIAG1 condition.  You can simply compare the return value to 0 to see if
  /// any of the bits are set, or you can use the logical AND operator (`&`) and
  /// the #DRV8434SDiag1Bit enum to check individual bits.
  uint8_t readDiag1()
  {
    return driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_DIAG1);
  }

  /// Reads the DIAG2 status register of the driver.
  ///
  /// The return value is an 8-bit unsigned integer that has one bit for each
  /// DIAG2 condition.  You can simply compare the return value to 0 to see if
  /// any of the bits are set, or you can use the logical AND operator (`&`) and
  /// the #DRV8434SDiag2Bit enum to check individual bits.
  uint8_t readDiag2()
  {
    return driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_DIAG2);
  }



//Reads the Mechanical Load Torque status.
  uint8_t readLoadTorque()
  {
    return driver.readReg(DRV8461_REG_ADDR::DRV8461_REG_ATQ;_CTRL1)
  }

  /// Clears any fault conditions that are currently latched in the driver
  /// (CLR_FLT = 1).
  ///
  /// WARNING: Calling this function clears latched faults, which might allow
  /// the motor driver outputs to reactivate.  If you do this repeatedly without
  /// fixing an abnormal condition (like a short circuit), you might damage the
  /// driver.
  ///
  /// The driver automatically clears the CLR_FLT bit after it is written.
  void clearFaults()
  {
    driver.writeReg(DRV8461_REG_ADDR::DRV8461_REG_CTRL3, ctrl3 | (1 << 7));
  }

  /// Gets the cached value of a register. If the given register address is not
  /// valid, this function returns 0.
  uint8_t getCachedReg(DRV8461_REG_ADDR address)
  {
    uint8_t * cachedReg = cachedRegPtr(address);
    if (!cachedReg) { return 0; }
    return *cachedReg;
  }

  /// Writes the specified value to a register after updating the cached value
  /// to match.
  ///
  /// Using this function keeps this object's cached settings consistent with
  /// the settings being written to the driver, so if you are using
  /// verifySettings(), applySettings(), and/or any of the other functions for
  /// specific settings that this library provides, you should use this function
  /// for direct register accesses instead of calling DRV8434SSPI::writeReg()
  /// directly.
  void setReg(DRV8461_REG_ADDR address, uint8_t value)
  {
    uint8_t * cachedReg = cachedRegPtr(address);
    if (!cachedReg) { return; }
    *cachedReg = value;
    driver.writeReg(address, value);
  }

protected:

  uint8_t ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl7, ctrl8, ctrl9, ctrl10, ctrl11, ctrl12, ctrl13, ctrl14, index1, index2, index3, index4, index5, custctrl1, custctrl2, custctrl3, custctrl4, custctrl5, custctrl6, custctrl7, custctrl8, custctrl9, atqctrl1, atqctrl2, atqctrl3, atqctrl4, atqctrl5, atqctrl6, atqctrl7, atqctrl8, atqctrl9, atqctrl10, atqctrl11, atqctrl12, atqctrl13, atqctrl14, atqctrl15, atqctrl16, atqctrl17, atqctrl18, ssctrl1, ssctrl2, ssctrl3, ssctrl4, ssctrl5;

  /// Returns a pointer to the variable containing the cached value for the
  /// given register.
  uint8_t * cachedRegPtr(DRV8461_REG_ADDR address)
  {
    switch (address)
    {
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL1: return &ctrl1;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL2: return &ctrl2;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL3: return &ctrl3;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL4: return &ctrl4;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL5: return &ctrl5;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL6: return &ctrl6;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL7: return &ctrl7;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL8: return &ctrl8;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL9: return &ctrl9;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL10: return &ctrl10;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL11: return &ctrl11;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL12: return &ctrl12;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL13: return &ctrl13;
      case DRV8461_REG_ADDR::DRV8461_REG_CTRL14: return &ctrl14;
      case DRV8461_REG_ADDR::DRV8461_REG_INDEX1: return &index1;
      case DRV8461_REG_ADDR::DRV8461_REG_INDEX2: return &index2;
      case DRV8461_REG_ADDR::DRV8461_REG_INDEX3: return &index3;
      case DRV8461_REG_ADDR::DRV8461_REG_INDEX4: return &index4;
      case DRV8461_REG_ADDR::DRV8461_REG_INDEX5: return &index5;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL1: return &custctrl1;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL2: return &custctrl2;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL3: return &custctrl3;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL4: return &custctrl4;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL5: return &custctrl5;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL6: return &custctrl6;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL7: return &custctrl7;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL8: return &custctrl8;
      case DRV8461_REG_ADDR::DRV8461_REG_CUSTOM_CTRL9: return &custctrl9;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL1: return &atqctrl1;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL2: return &atqctrl2;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL3: return &atqctrl3;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL4: return &atqctrl4;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL5: return &atqctrl5;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL6: return &atqctrl6;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL7: return &atqctrl7;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL8: return &atqctrl8;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL9: return &atqctrl9;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL11: return &atqctrl11;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL12: return &atqctrl12;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL13: return &atqctrl13;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL14: return &atqctrl14;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL15: return &atqctrl15;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL16: return &atqctrl16;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL17: return &atqctrl17;
      case DRV8461_REG_ADDR::DRV8461_REG_ATQ_CTRL18: return &atqctrl18;
      case DRV8461_REG_ADDR::DRV8461_REG_SS_CTRL1: return &ssctrl1;
      case DRV8461_REG_ADDR::DRV8461_REG_SS_CTRL2: return &ssctrl2;
      case DRV8461_REG_ADDR::DRV8461_REG_SS_CTRL3: return &ssctrl3;
      case DRV8461_REG_ADDR::DRV8461_REG_SS_CTRL4: return &ssctrl4;
      case DRV8461_REG_ADDR::DRV8461_REG_SS_CTRL5: return &ssctrl5;
  
      default: return nullptr;
    }
  }

  /// Writes the cached value of the given register to the device.
  void writeCachedReg(DRV8461_REG_ADDR address)
  {
    uint8_t * cachedReg = cachedRegPtr(address);
    if (!cachedReg) { return; }
    driver.writeReg(address, *cachedReg);
  }

public:
  /// This object handles all the communication with the DRV8711.  Generally,
  /// you should not need to use it in your code for basic usage of a
  /// High-Power Stepper Motor Driver, but you might want to use it to access
  /// more advanced settings that the HighPowerStepperDriver class does not
  /// provide functions for.
  DRV8434SSPI driver;
};


#endif                                    // #ifndef DRV8461_REGISTERS_H
