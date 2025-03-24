/// @file flashAccessControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Definition of the Flash Access Control Register (ACR) and its associated latency settings.
/// @details This file contains the definition of the AccessControlRegister struct and the Latency enum class
///          for configuring the flash memory access control settings on an STM32 microcontroller.

#ifndef PERIPHERALS_INC_REGISTERS_FLASHACCESSCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_FLASHACCESSCONTROLREGISTER_HPP

#include <stm32f103xb.h>

#include <core.hpp>
#include <cstdint>

namespace Peripherals::Flash::Registers
{
  /// @brief Enumeration for flash memory access latency settings.
  ///        It represent the ratio of the SYSCLK (system clock) period to the Flash access time.
  enum class Latency : uint8_t
  {
    /// @brief Zero wait state, if 0 < SYSCLK 24 MHz.
    Zero = (FLASH_ACR_LATENCY_0 >> FLASH_ACR_LATENCY_Pos),

    /// @brief One wait state, if 24 MHz < SYSCLK 48 MHz.
    One = (FLASH_ACR_LATENCY_1 >> FLASH_ACR_LATENCY_Pos),

    /// @brief Two wait states, if 48 MHz < SYSCLK 72 MHz.
    Two = (FLASH_ACR_LATENCY_2 >> FLASH_ACR_LATENCY_Pos),
  };

  /// @brief Structure representing the Flash Access Control Register (ACR).
  struct AccessControlRegister
  {
    /// @brief Access latency setting.
    Latency AccessLatency : 3;

    /// @brief Half cycle access enabled state.
    Core::State HalfCycleAccessEnabled : 1;

    /// @brief Prefetch buffer enabled state.
    Core::State PrefetchBufferEnabled : 1;

    /// @brief Prefetch buffer status.
    Core::State PrefetchBufferStatus : 1;
  };
}  // namespace Peripherals::Flash::Registers

#endif
