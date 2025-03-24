/// @file sysTickControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the control register and associated fields for the System Timer (SysTick) of the STM32F103
/// microcontroller.
/// @details The `SysTickControlRegister` structure encapsulates the control bits for enabling the SysTick timer,
/// selecting the clock source, and monitoring the count flag.

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKCONTROLREGISTER_HPP

#include <core.hpp>
#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  /// @brief Enumeration of possible clock sources for the SysTick timer.
  enum class ClockSource : uint8_t
  {
    /// @brief AHB/8.
    AHB8 = 0x00,

    /// @brief AHB.
    AHB = 0x01
  };

  /// @brief Structure representing the control register of the SysTick module.
  struct SysTickControlRegister
  {
    /// @brief SysTick timer enabled state.
    /// @details Enables the counter. When ENABLE is set to 1, the counter loads the RELOAD value from the LOAD register
    ///          and then counts down. On reaching 0, it sets the COUNTFLAG to 1 and optionally asserts the SysTick
    ///          depending on the value of TICKINT. It then loads the RELOAD value again, and begins counting.
    Core::State Enabled : 1;

    /// @brief SysTick timer exception request enabled state.
    Core::State ExceptionRequestEnabled : 1;

    /// @brief SysTick timer clock source.
    ClockSource Source : 1;

    uint16_t _ : 13;

    /// @brief SysTick timer count flag.
    /// @details Indicates whether the timer has counted to 0 since the last time this flag was read.
    Core::State CountFlag : 1;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
