/// @file sysTickValueRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKVALUEREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKVALUEREGISTER_HPP

#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  struct SysTickValueRegister
  {
    uint32_t CurrentValue : 24;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
