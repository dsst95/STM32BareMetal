/// @file sysTickReloadRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_SYSTICKRELOADREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_SYSTICKRELOADREGISTER_HPP

#include <cstdint>

namespace Peripherals::SystemTimer::Registers
{
  struct SysTickReloadRegister
  {
    uint32_t ReloadValue : 24;
  };
}  // namespace Peripherals::SystemTimer::Registers

#endif
