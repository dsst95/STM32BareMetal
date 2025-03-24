/// @file sysTickReloadRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the reload register and associated fields for the System Timer (SysTick) of the STM32F103
///        microcontroller.
/// @details The `SysTickReloadRegister` structure encapsulates the reload value for the SysTick timer, which determines
///          the timer's countdown value.

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKRELOADREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKRELOADREGISTER_HPP

#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  /// @brief Structure representing the reload register of the SysTick timer.
  struct SysTickReloadRegister
  {
    /// @brief Reload value for the SysTick timer.
    /// @details The LOAD register specifies the start value to load into the VAL register when the counter is enabled
    ///          and when it reaches 0.
    ///          Calculating the RELOAD value The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. A
    ///          start value of 0 is possible, but has no effect because the SysTick exception request and COUNTFLAG are
    ///          activated when counting from 1 to 0. The RELOAD value is calculated according to its use:
    ///          - To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD value of N-1.
    ///            For example, if the SysTick interrupt is required every 100 clock pulses, set RELOAD to 99.
    ///          - To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a RELOAD of
    ///            value N. For example, if a SysTick interrupt is required after 400 clock pulses, set RELOAD to 400.
    uint32_t ReloadValue : 24;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
