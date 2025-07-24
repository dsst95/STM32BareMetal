/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Interrupt manager to configure the interrupts.

#ifndef PERIPHERALS_INC_INTERRUPTMANAGER_HPP
#define PERIPHERALS_INC_INTERRUPTMANAGER_HPP

#include <stm32f1xx.h>

#include <cstdlib>

namespace Peripherals
{
  /// @brief Interrupt manager to configure the interrupts.
  class InterruptManager
  {
   public:
    // Delete not needed constructors and destructors
    constexpr InterruptManager() = delete;
    InterruptManager(const InterruptManager&) = delete;
    InterruptManager& operator=(const InterruptManager&) = delete;
    InterruptManager(InterruptManager&&) = delete;
    InterruptManager& operator=(InterruptManager&&) = delete;
    virtual ~InterruptManager() = delete;

    /// @brief Configures the NVIC priorities for the used interrupts.
    static void SetupNvicPriorities()
    {
      NVIC_SetPriority(IRQn_Type::SysTick_IRQn, 0);
      NVIC_SetPriority(IRQn_Type::EXTI0_IRQn, 5);

      NVIC_EnableIRQ(IRQn_Type::EXTI0_IRQn);
    }
  };
}  // namespace Peripherals

#endif
