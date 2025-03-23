/// @file flashAccessControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_FLASHACCESSCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_FLASHACCESSCONTROLREGISTER_HPP

#include <stm32f103xb.h>

#include <core.hpp>
#include <cstdint>

namespace Peripherals::Flash::Registers
{
  enum class Latency : uint8_t
  {
    Zero = (FLASH_ACR_LATENCY_0 >> FLASH_ACR_LATENCY_Pos),
    One = (FLASH_ACR_LATENCY_1 >> FLASH_ACR_LATENCY_Pos),
    Two = (FLASH_ACR_LATENCY_2 >> FLASH_ACR_LATENCY_Pos),
  };

  struct AccessControlRegister
  {
    Latency AccessLatency : 3;
    Core::State HalfCycleAccessEnabled : 1;
    Core::State PrefetchBufferEnabled : 1;
    Core::State PrefetchBufferStatus : 1;
  };
}  // namespace Peripherals::Flash::Registers

#endif
