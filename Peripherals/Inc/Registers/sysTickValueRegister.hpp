/// @file sysTickValueRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the value register and associated fields for the System Timer (SysTick) of the STM32F103
///        microcontroller.
/// @details The `SysTickValueRegister` structure encapsulates the current value of the SysTick timer, which is the
///          value the timer is currently counting down from.

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKVALUEREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKVALUEREGISTER_HPP

#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  /// @brief Structure representing the value register of the SysTick module.
  struct SysTickValueRegister
  {
    /// @brief Current counter value.
    /// @details The VAL register contains the current value of the SysTick counter.
    ///          Reads return the current value of the SysTick counter.
    ///           A write of any value clears the field to 0, and also clears the COUNTFLAG bit in the STK_CTRL register
    ///           to 0.
    uint32_t CurrentValue : 24;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
