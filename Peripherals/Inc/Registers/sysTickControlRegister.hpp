/// @file sysTickControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKCONTROLREGISTER_HPP

#include <core.hpp>
#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  enum class ClockSource : uint8_t
  {
    AHB8 = 0x00,
    AHB = 0x01
  };

  struct SysTickControlRegister
  {
    Core::State Enabled : 1;
    Core::State ExceptionRequestEnabled : 1;
    ClockSource Source : 1;
    uint16_t _ : 13;
    Core::State CountFlag : 1;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
