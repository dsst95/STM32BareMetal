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

#include <InterruptHandler.hpp>

namespace Peripherals::Rcc
{
  /// @brief Class to manage the Reset and Clock Control (RCC).
  class ResetAndClockControl
  {
   private:
    /// @brief Current SysTick counter value.
    uint32_t sysTick;

    /// @brief Configures the system clocks.
    inline static void ConfigureClocks()
    {
      // NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
      RCC->CFGR &= ~RCC_CFGR_PLLMULL;
      RCC->CFGR |= RCC_CFGR_PLLMULL9;
      RCC->CFGR &= ~RCC_CFGR_USBPRE;

      RCC->CR |= RCC_CR_HSEON;
      while ((RCC->CR & RCC_CR_HSERDY) == 0)
      {
      }

      RCC->CFGR |= RCC_CFGR_PLLSRC;

      RCC->CR |= RCC_CR_PLLON;
      while ((RCC->CR & RCC_CR_PLLRDY) == 0)
      {
      }

      FLASH->ACR &= ~FLASH_ACR_LATENCY;
      FLASH->ACR |= FLASH_ACR_LATENCY_1;
      FLASH->ACR |= FLASH_ACR_PRFTBE;

      RCC->CFGR &= ~RCC_CFGR_SW;
      RCC->CFGR |= RCC_CFGR_SW_PLL;
      while ((RCC->CFGR & RCC_CFGR_SWS) == 0)
      {
      }

      RCC->CFGR &= ~RCC_CFGR_HPRE;
      RCC->CFGR &= ~RCC_CFGR_PPRE1;
      RCC->CFGR |= RCC_CFGR_PPRE1_2;
      RCC->CFGR &= ~RCC_CFGR_PPRE2;
      RCC->CFGR &= ~RCC_CFGR_ADCPRE;
      RCC->CFGR |= RCC_CFGR_ADCPRE_1;

      // NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
    }

    /// @brief Configures the SysTick timer.
    inline static void ConfigureSysTick()
    {
      SysTick->CTRL = 0x00UL;
      SysTick->LOAD = Ticks - 1;
      SysTick->VAL = 0x00UL;
      SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    }

   public:
    /// @brief Number of ticks per millisecond.
    static constexpr uint32_t Ticks = 72000;

    /// @brief Constructor for the ResetAndClockControl class.
    /// @details Configures the system clocks and the SysTickTimer.
    inline ResetAndClockControl() : sysTick {0}
    {
      ConfigureClocks();
      ConfigureSysTick();
    }

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
      }
    }

    /// @brief Gets the current SysTick counter value.
    /// @return Current SysTick counter value.
    inline uint32_t GetSysTick() const
    {
      return sysTick;
    }

    // inline void HandleInterrupt() override
    // {
    //   ++sysTick;
    // }
  };
}  // namespace Peripherals::Rcc

#endif
