/// @file Peripherals.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Core header file of the STM32 bare metal tutorial project, containing base enums and constants for
///        peripherals.

#ifndef INC_PERIPHERALS_HPP
#define INC_PERIPHERALS_HPP

//#include <cstddef>
#include <cstdint>

namespace Peripherals
{
  /// @brief Status of an executed operation.
  enum class Status : uint8_t
  {
    /// @brief Operation was successful.
    Ok,

    /// @brief Operation failed.
    Error,

    /// @brief Operation timed out.
    Timeout
  };

  /// @brief Default timeout for peripheral operations.
  const uint8_t Timeout = 100;
}  // namespace Peripherals

#endif /* INC_PERIPHERALS_HPP */
