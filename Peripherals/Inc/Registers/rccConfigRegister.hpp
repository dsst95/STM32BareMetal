/// @file rccConfigRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the configuration registers and associated enumerations for the Reset and Clock Control
///        (RCC) of the STM32F103 microcontroller.
/// @details The enumerations in this file represent the various configuration options for the clock sources and
///          prescalers of the RCC peripheral. The `ConfigRegister` structure encapsulates these options into a single
///          register.

#ifndef PERIPHERALS_INC_REGISTERS_RCCCONFIGREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_RCCCONFIGREGISTER_HPP

#include <stm32f103xb.h>

#include <cstdint>

namespace Peripherals::ResetAndClockControl::Registers
{
  /// @brief Enumeration of possible sources for the system clock.
  enum class SystemClockSwitchSource : uint8_t
  {
    /// @brief Internal high-speed clock (HSI).
    InternalHighSpeedClock = RCC_CFGR_SW_HSI,

    /// @brief External high-speed clock (HSE).
    ExternalHighSpeedClock = RCC_CFGR_SW_HSE,

    /// @brief Phase-locked loop (PLL).
    PhaseLockedLoop = RCC_CFGR_SW_PLL,
  };

  /// @brief Enumeration of possible prescalers for the Advanced High Performance Bus (AHB).
  enum class AdvancedHighPerformanceBusPrescaler : uint8_t
  {
    /// @brief SYSCLK not divided.
    Divide1 = (RCC_CFGR_HPRE_DIV1 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 2.
    Divide2 = (RCC_CFGR_HPRE_DIV2 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 4.
    Divide4 = (RCC_CFGR_HPRE_DIV4 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 8.
    Divide8 = (RCC_CFGR_HPRE_DIV8 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 16.
    Divide16 = (RCC_CFGR_HPRE_DIV16 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 64.
    Divide64 = (RCC_CFGR_HPRE_DIV64 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 128.
    Divide128 = (RCC_CFGR_HPRE_DIV128 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 256.
    Divide256 = (RCC_CFGR_HPRE_DIV256 >> RCC_CFGR_HPRE_Pos),

    /// @brief SYSCLK divided by 512.
    Divide512 = (RCC_CFGR_HPRE_DIV512 >> RCC_CFGR_HPRE_Pos),
  };

  /// @brief Enumeration of possible prescalers for the Advanced Peripheral Bus (APB).
  enum class AdvancedPeripheralBusPrescaler : uint8_t
  {
    /// @brief HCLK not divided.
    Divide1 = (RCC_CFGR_PPRE1_DIV1 >> RCC_CFGR_PPRE1_Pos),

    /// @brief HCLK divided by 2.
    Divide2 = (RCC_CFGR_PPRE1_DIV2 >> RCC_CFGR_PPRE1_Pos),

    /// @brief HCLK divided by 4.
    Divide4 = (RCC_CFGR_PPRE1_DIV4 >> RCC_CFGR_PPRE1_Pos),

    /// @brief HCLK divided by 8.
    Divide8 = (RCC_CFGR_PPRE1_DIV8 >> RCC_CFGR_PPRE1_Pos),

    /// @brief HCLK divided by 16.
    Divide16 = (RCC_CFGR_PPRE1_DIV16 >> RCC_CFGR_PPRE1_Pos),
  };

  /// @brief Enumeration of possible prescalers for the Analog-to-Digital Converter (ADC).
  enum class AnalogDigitalConverterPrescaler : uint8_t
  {
    /// @brief PCLK2 divided by 2.
    Divide2 = (RCC_CFGR_ADCPRE_DIV2 >> RCC_CFGR_ADCPRE_Pos),

    /// @brief PCLK2 divided by 4.
    Divide4 = (RCC_CFGR_ADCPRE_DIV4 >> RCC_CFGR_ADCPRE_Pos),

    /// @brief PCLK2 divided by 6.
    Divide6 = (RCC_CFGR_ADCPRE_DIV6 >> RCC_CFGR_ADCPRE_Pos),

    /// @brief PCLK2 divided by 8.
    Divide8 = (RCC_CFGR_ADCPRE_DIV8 >> RCC_CFGR_ADCPRE_Pos),
  };

  /// @brief Enumeration of possible sources for the Phase-Locked Loop (PLL).
  enum class PhaseLockedLoopSource : uint8_t
  {
    /// @brief Internal high-speed clock (HSI).
    InternalHighSpeedClock = 0x00,

    /// @brief External high-speed clock (HSE).
    ExternalHighSpeedClock = (RCC_CFGR_PLLSRC >> RCC_CFGR_PLLSRC_Pos),
  };

  /// @brief Enumeration of possible prescalers for the Phase-Locked Loop (PLL).
  enum class PhaseLockedLoopPrescaler : uint8_t
  {
    /// @brief HSE not divided.
    Divide1 = RCC_CFGR_PLLXTPRE_HSE,

    /// @brief HSE divided by 2.
    Divide2 = (RCC_CFGR_PLLXTPRE_HSE_DIV2 >> RCC_CFGR_PLLXTPRE_Pos),
  };

  /// @brief Enumeration of possible multiplicators for the Phase-Locked Loop (PLL).
  enum class PhaseLockedLoopMultiplicator : uint8_t
  {
    /// @brief PLL input clock x2.
    Multiplicate2 = (RCC_CFGR_PLLMULL2 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x3.
    Multiplicate3 = (RCC_CFGR_PLLMULL3 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x4.
    Multiplicate4 = (RCC_CFGR_PLLMULL4 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x5.
    Multiplicate5 = (RCC_CFGR_PLLMULL5 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x6.
    Multiplicate6 = (RCC_CFGR_PLLMULL6 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x7.
    Multiplicate7 = (RCC_CFGR_PLLMULL7 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x8.
    Multiplicate8 = (RCC_CFGR_PLLMULL8 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x9.
    Multiplicate9 = (RCC_CFGR_PLLMULL9 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x10.
    Multiplicate10 = (RCC_CFGR_PLLMULL10 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x11.
    Multiplicate11 = (RCC_CFGR_PLLMULL11 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x12.
    Multiplicate12 = (RCC_CFGR_PLLMULL12 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x13.
    Multiplicate13 = (RCC_CFGR_PLLMULL13 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x14.
    Multiplicate14 = (RCC_CFGR_PLLMULL14 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x15.
    Multiplicate15 = (RCC_CFGR_PLLMULL15 >> RCC_CFGR_PLLMULL3_Pos),

    /// @brief PLL input clock x16.
    Multiplicate16 = (RCC_CFGR_PLLMULL16 >> RCC_CFGR_PLLMULL3_Pos),
  };

  /// @brief Enumeration of possible prescalers for the Universal Serial Bus (USB).
  enum class UniversalSerialBusPrescaler : uint8_t
  {
    /// @brief PLL clock divided by 1.5.
    Divide15 = 0x00,

    /// @brief PLL clock not divided.
    Divide1 = (RCC_CFGR_USBPRE >> RCC_CFGR_USBPRE_Pos),
  };

  /// @brief Enumeration of possible outputs for the microcontroller clock.
  enum class MicrocontrollerClockOutput : uint8_t
  {
    /// @brief No clock output.
    None = (RCC_CFGR_MCO_NOCLOCK >> RCC_CFGR_MCO_Pos),

    /// @brief System clock.
    SystemClock = (RCC_CFGR_MCO_SYSCLK >> RCC_CFGR_MCO_Pos),

    /// @brief HSI clock.
    InternalHighSpeedClock = (RCC_CFGR_MCO_HSI >> RCC_CFGR_MCO_Pos),

    /// @brief HSE clock.
    ExternalHighSpeedClock = (RCC_CFGR_MCO_HSE >> RCC_CFGR_MCO_Pos),

    /// @brief PLL clock divided by 2.
    PhaseLockedLoop = (RCC_CFGR_MCO_PLLCLK_DIV2 >> RCC_CFGR_MCO_Pos),
  };

  /// @brief Structure representing the configuration registers of the RCC module.
  struct ConfigRegister
  {
    /// @brief Source for the system clock.
    /// @details Set and cleared by software to select SYSCLK source.
    ///          Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of
    ///          failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security
    ///          System is enabled).
    SystemClockSwitchSource SystemClockSwitch : 2;

    /// @brief System clock switch status.
    /// @details Set and cleared by hardware to indicate which clock source is used as system clock.
    SystemClockSwitchSource SystemClockSwitchStatus : 2;

    /// @brief Advanced High Performance Bus (AHB) prescaler.
    /// @details Set and cleared by software to control the division factor of the AHB clock.
    AdvancedHighPerformanceBusPrescaler AHBPrescaler : 4;

    /// @brief Advanced Peripheral Bus (APB1) low-speed prescaler.
    /// @details Set and cleared by software to control the division factor of the APB low-speed clock (PCLK1).
    ///          Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
    AdvancedPeripheralBusPrescaler APBLowSpeedPrescaler : 3;

    /// @brief Advanced Peripheral Bus (APB2) high-speed prescaler.
    /// @details Set and cleared by software to control the division factor of the APB high-speed clock (PCLK2).
    AdvancedPeripheralBusPrescaler APBHighSpeedPrescaler : 3;

    /// @brief Analog-to-Digital Converter (ADC) prescaler.
    /// @details Set and cleared by software to select the frequency of the clock to the ADCs
    AnalogDigitalConverterPrescaler ADCPrescaler : 2;

    /// @brief Phase-Locked Loop (PLL) source.
    /// @details Set and cleared by software to select PLL clock source. This bit can be written only when PLL is
    ///          disabled.
    PhaseLockedLoopSource PLLSource : 1;

    /// @brief Phase-Locked Loop (PLL) prescaler.
    /// @details Set and cleared by software to divide HSE before PLL entry. This bit can be written only when PLL is
    ///          disabled.
    PhaseLockedLoopPrescaler PLLPrescaler : 1;

    /// @brief Phase-Locked Loop (PLL) multiplicator.
    /// @details These bits are written by software to define the PLL multiplication factor. These bits can be written
    ///          only when PLL is disabled. Caution: The PLL output frequency must not exceed 72 MHz.
    PhaseLockedLoopMultiplicator PLLMultiplicator : 4;

    /// @brief Universal Serial Bus (USB) prescaler.
    /// @details Set and cleared by software to generate 48 MHz USB clock. This bit must be valid before enabling the USB
    ///          clock in the RCC_APB1ENR register. This bit can’t be reset if the USB clock is enabled.
    UniversalSerialBusPrescaler USBPrescaler : 1;

    /// @brief Microcontroller clock output.
    /// @details Set and cleared by software to select MCO (microcontroller clock output) source.
    MicrocontrollerClockOutput ClockOutput : 3;
  };
}  // namespace Peripherals::ResetAndClockControl::Registers

#endif
