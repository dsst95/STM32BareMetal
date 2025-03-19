/// @file main.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Main header file of the STM32 bare metal tutorial project.

#ifndef INC_CORE_HPP
#define INC_CORE_HPP

#include <cstddef>

#include "stm32f1xx.h"

namespace Core
{
  /// @brief Status of an executed operation.
  enum class Status
  {
    Ok,
    Error,
    Timeout
  };

  /// @brief State of a register.
  enum class State : uint8_t
  {
    Reset = 0x00,
    Set = 0x01
  };

  /// @brief Default timeout for peripheral operations.
  const size_t Timeout = 100;
}  // namespace Core

#endif /* __INC_MAIN_HPP_ */
