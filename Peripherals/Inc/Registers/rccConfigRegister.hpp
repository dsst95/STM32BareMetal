/// @file rccConfigRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_RCCCONFIGREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_RCCCONFIGREGISTER_HPP

#include <stm32f103xb.h>

#include <cstdint>

namespace Peripherals::ResetAndClockControl::Registers
{
  enum class SystemClockSwitchSource : uint8_t
  {
    InternalHighSpeedClock = RCC_CFGR_SW_HSI,
    ExternalHighSpeedClock = RCC_CFGR_SW_HSE,
    PhaseLockedLoop = RCC_CFGR_SW_PLL,
  };

  enum class AdvancedHighPerformanceBusPrescaler : uint8_t
  {
    Divide1 = (RCC_CFGR_HPRE_DIV1 >> RCC_CFGR_HPRE_Pos),
    Divide2 = (RCC_CFGR_HPRE_DIV2 >> RCC_CFGR_HPRE_Pos),
    Divide4 = (RCC_CFGR_HPRE_DIV4 >> RCC_CFGR_HPRE_Pos),
    Divide8 = (RCC_CFGR_HPRE_DIV8 >> RCC_CFGR_HPRE_Pos),
    Divide16 = (RCC_CFGR_HPRE_DIV16 >> RCC_CFGR_HPRE_Pos),
    Divide64 = (RCC_CFGR_HPRE_DIV64 >> RCC_CFGR_HPRE_Pos),
    Divide128 = (RCC_CFGR_HPRE_DIV128 >> RCC_CFGR_HPRE_Pos),
    Divide256 = (RCC_CFGR_HPRE_DIV256 >> RCC_CFGR_HPRE_Pos),
    Divide512 = (RCC_CFGR_HPRE_DIV512 >> RCC_CFGR_HPRE_Pos),
  };

  enum class AdvancedPeripheralBusPrescaler : uint8_t
  {
    Divide1 = (RCC_CFGR_PPRE1_DIV1 >> RCC_CFGR_PPRE1_Pos),
    Divide2 = (RCC_CFGR_PPRE1_DIV2 >> RCC_CFGR_PPRE1_Pos),
    Divide4 = (RCC_CFGR_PPRE1_DIV4 >> RCC_CFGR_PPRE1_Pos),
    Divide8 = (RCC_CFGR_PPRE1_DIV8 >> RCC_CFGR_PPRE1_Pos),
    Divide16 = (RCC_CFGR_PPRE1_DIV16 >> RCC_CFGR_PPRE1_Pos),
  };

  enum class AnalogDigitalConverterPrescaler : uint8_t
  {
    Divide2 = (RCC_CFGR_ADCPRE_DIV2 >> RCC_CFGR_ADCPRE_Pos),
    Divide4 = (RCC_CFGR_ADCPRE_DIV4 >> RCC_CFGR_ADCPRE_Pos),
    Divide6 = (RCC_CFGR_ADCPRE_DIV6 >> RCC_CFGR_ADCPRE_Pos),
    Divide8 = (RCC_CFGR_ADCPRE_DIV8 >> RCC_CFGR_ADCPRE_Pos),
  };

  enum class PhaseLockedLoopSource : uint8_t
  {
    InternalHighSpeedClock = 0x00,
    ExternalHighSpeedClock = (RCC_CFGR_PLLSRC >> RCC_CFGR_PLLSRC_Pos),
  };

  enum class PhaseLockedLoopPrescaler : uint8_t
  {
    Divide1 = RCC_CFGR_PLLXTPRE_HSE,
    Divide2 = (RCC_CFGR_PLLXTPRE_HSE_DIV2 >> RCC_CFGR_PLLXTPRE_Pos),
  };

  enum class PhaseLockedLoopMultiplicator : uint8_t
  {
    Multiplicate2 = (RCC_CFGR_PLLMULL2 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate3 = (RCC_CFGR_PLLMULL3 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate4 = (RCC_CFGR_PLLMULL4 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate5 = (RCC_CFGR_PLLMULL5 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate6 = (RCC_CFGR_PLLMULL6 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate7 = (RCC_CFGR_PLLMULL7 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate8 = (RCC_CFGR_PLLMULL8 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate9 = (RCC_CFGR_PLLMULL9 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate10 = (RCC_CFGR_PLLMULL10 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate11 = (RCC_CFGR_PLLMULL11 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate12 = (RCC_CFGR_PLLMULL12 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate13 = (RCC_CFGR_PLLMULL13 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate14 = (RCC_CFGR_PLLMULL14 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate15 = (RCC_CFGR_PLLMULL15 >> RCC_CFGR_PLLMULL3_Pos),
    Multiplicate16 = (RCC_CFGR_PLLMULL16 >> RCC_CFGR_PLLMULL3_Pos),
  };

  enum class UniversalSerialBusPrescaler : uint8_t
  {
    Divide15 = 0x00,
    Divide1 = (RCC_CFGR_USBPRE >> RCC_CFGR_USBPRE_Pos),
  };

  enum class MicrocontrollerClockOutput : uint8_t
  {
    None = (RCC_CFGR_MCO_NOCLOCK >> RCC_CFGR_MCO_Pos),
    SystemClock = (RCC_CFGR_MCO_SYSCLK >> RCC_CFGR_MCO_Pos),
    InternalHighSpeedClock = (RCC_CFGR_MCO_HSI >> RCC_CFGR_MCO_Pos),
    ExternalHighSpeedClock = (RCC_CFGR_MCO_HSE >> RCC_CFGR_MCO_Pos),
    PhaseLockedLoop = (RCC_CFGR_MCO_PLLCLK_DIV2 >> RCC_CFGR_MCO_Pos),
  };

  struct ConfigRegister
  {
    SystemClockSwitchSource SystemClockSwitch : 2;
    SystemClockSwitchSource SystemClockSwitchStatus : 2;
    AdvancedHighPerformanceBusPrescaler AHBPrescaler : 4;
    AdvancedPeripheralBusPrescaler APBLowSpeedPrescaler : 3;
    AdvancedPeripheralBusPrescaler APBHighSpeedPrescaler : 3;
    AnalogDigitalConverterPrescaler ADCPrescaler : 2;
    PhaseLockedLoopSource PLLSource : 1;
    PhaseLockedLoopPrescaler PLLPrescaler : 1;
    PhaseLockedLoopMultiplicator PLLMultiplicator : 4;
    UniversalSerialBusPrescaler USBPrescaler : 1;
    MicrocontrollerClockOutput ClockOutput : 3;
  };
}  // namespace Peripherals::ResetAndClockControl::Registers

#endif
