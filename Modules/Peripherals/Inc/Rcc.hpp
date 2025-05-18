/// @file Rcc.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the Reset and Clock Control (RCC) class.
/// @details The `ResetAndClockControl` class provides methods to configure the system clocks, SysTick timer, and to
///          manage delays using the SysTick timer.

#ifndef PERIPHERALS_INC_RCC_HPP
#define PERIPHERALS_INC_RCC_HPP

#include <stm32f1xx.h>

namespace Peripherals::Rcc
{
  /// @brief Class to manage the Reset and Clock Control (RCC).
  class ResetAndClockControl
  {
   private:
    /// @brief Current SysTick counter value.
    uint32_t sysTick;

    /// @brief Configures the system clocks.
    static void ConfigureClocks();

    /// @brief Configures the SysTick timer.
    static void ConfigureSysTick();

    /// @brief Constructor for the ResetAndClockControl class.
    /// @details Configures the system clocks and the SysTickTimer.
    inline ResetAndClockControl() : sysTick {0}
    {
      ConfigureClocks();
      ConfigureSysTick();
    }

   public:
    /// @brief Number of ticks per millisecond.
    static constexpr uint32_t Ticks = 72000;

    /// @brief Returns the singleton instance of the ResetAndClockControl class.
    /// @return Reference to the singleton instance.
    static ResetAndClockControl& GetInstance()
    {
      static ResetAndClockControl instance;
      return instance;
    }

    // Deleted copy constructor and assignment operator.
    ResetAndClockControl(const ResetAndClockControl&) = delete;
    ResetAndClockControl& operator=(const ResetAndClockControl&) = delete;
    ResetAndClockControl(ResetAndClockControl&&) = delete;
    ResetAndClockControl& operator=(ResetAndClockControl&&) = delete;
    ~ResetAndClockControl() = default;

    /// @brief Delays execution for a specified number of milliseconds.
    /// @param milliseconds Number of milliseconds to delay.
    inline void Delay(const uint32_t milliseconds) const
    {
      const auto start = GetSysTick();

      while ((GetSysTick() - start) < milliseconds)
      {
        __NOP();
      }
    }

    /// @brief Gets the current SysTick counter value.
    /// @return Current SysTick counter value.
    inline uint32_t GetSysTick() const
    {
      return sysTick;
    }

    /// @brief Handles the SysTick interrupt.
    inline void HandleInterrupt()
    {
      ++sysTick;
    }
  };
}  // namespace Peripherals::Rcc

#endif
