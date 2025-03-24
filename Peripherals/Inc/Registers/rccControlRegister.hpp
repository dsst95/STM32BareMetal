/// @file rccControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the control register and associated fields for the Reset and Clock Control (RCC) of the
///        STM32F103 microcontroller.
/// @details  The `ControlRegister` structure encapsulates the control bits for enabling and monitoring the status of
///           the internal and external high-speed clocks, as well as the phase-locked loop (PLL) and clock security
///           system.

#ifndef PERIPHERALS_INC_REGISTERS_RCCCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_RCCCONTROLREGISTER_HPP

#include <core.hpp>
#include <cstdint>

namespace Peripherals::ResetAndClockControl::Registers
{
  /// @brief Structure representing the control register of the RCC module.
  struct ControlRegister
  {
    /// @brief Internal high-speed clock enabled state.
    /// @details Set and cleared by software.
    ///          Set by hardware to force the internal 8 MHz RC oscillator ON when leaving Stop or Standby mode or in
    ///          case of failure of the external 4-16 MHz oscillator used directly or indirectly as system clock. This
    ///          bit cannot be reset if the internal 8 MHz RC is used directly or indirectly as system clock or is
    ///          selected to become the system clock.
    Core::State InternalHighSpeeClockEnabled : 1;

    /// @brief Internal high-speed clock ready state.
    /// @details Set by hardware to indicate that internal 8 MHz RC oscillator is stable. After the HSION bit is
    ///          cleared, HSIRDY goes low after 6 internal 8 MHz RC oscillator clock cycles.
    Core::State InternalHighSpeeClockReady : 1;

    uint8_t _ : 1;

    /// @brief Internal high-speed clock trimming.
    /// @details These bits provide an additional user-programmable trimming value that is added to the HSICAL[7:0]
    ///          bits. It can be programmed to adjust to variations in voltage and temperature that influence the
    ///          frequency of the internal HSI RC. The default value is 16, which, when added to the HSICAL value,
    ///          should trim the HSI to 8 MHz ± 1%. The trimming step (Fhsitrim) is around 40 kHz between two
    ///          consecutive HSICAL steps.
    uint8_t InternalHighSpeeClockTrimming : 5;

    /// @brief Internal high-speed clock calibration.
    /// @details These bits are initialized automatically at startup.
    uint8_t InternalHighSpeeClockCalibration : 8;

    /// @brief External high-speed clock enabled state.
    /// @details Set and cleared by software. Cleared by hardware to stop the HSE oscillator when entering Stop or
    ///          Standby mode. This bit cannot be reset if the HSE oscillator is used directly or indirectly as the
    ///          system clock.
    Core::State ExternalHighSpeeClockEnabled : 1;

    /// @brief External high-speed clock ready state.
    /// @details Set by hardware to indicate that the HSE oscillator is stable. This bit needs 6 cycles of the HSE
    ///          oscillator clock to fall down after HSEON reset.
    Core::State ExternalHighSpeeClockReady : 1;

    /// @brief External high-speed clock bypass.
    /// @details Set and cleared by software to bypass the oscillator with an external clock. The external clock must be
    ///          enabled with the HSEON bit set, to be used by the device. The HSEBYP bit can be written only if the HSE
    ///          oscillator is disabled.
    Core::State ExternalHighSpeeClockBypass : 1;

    /// @brief Clock security system enabled state.
    /// @details Set and cleared by software to enable the clock security system. When CSSON is set, the clock detector
    ///          is enabled by hardware when the HSE oscillator is ready, and disabled by hardware if a HSE clock
    ///          failure is detected.
    Core::State ClockSecuritySystemEnabled : 1;

    uint8_t __ : 4;

    /// @brief Phase-Locked Loop enabled state.
    /// @details Set and cleared by software to enable the PLL. Cleared by hardware when entering Stop or Standby mode
    ///          or in case of failure of the PLL used as system clock. This bit can’t be reset if the PLL is used as
    ///          the system clock.
    Core::State PhaseLockedLoopEnabled : 1;

    /// @brief Phase-Locked Loop ready state.
    /// @details Set by hardware to indicate that the PLL is locked.
    Core::State PhaseLockedLoopReady : 1;
  };
}  // namespace Peripherals::ResetAndClockControl::Registers

#endif
