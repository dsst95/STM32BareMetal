/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#ifndef PERIPHERALS_INC_INTERRUPTMANAGER_HPP
#define PERIPHERALS_INC_INTERRUPTMANAGER_HPP

#include <stm32f1xx.h>

#include <cstdlib>

namespace Peripherals
{
  /// @brief
  class InterruptManager
  {
   public:
    constexpr InterruptManager() = delete;
    InterruptManager(const InterruptManager&) = delete;
    InterruptManager& operator=(const InterruptManager&) = delete;
    InterruptManager(InterruptManager&&) = delete;
    InterruptManager& operator=(InterruptManager&&) = delete;
    virtual ~InterruptManager() = delete;

    static void SetupNvicPriorities()
    {
      NVIC_SetPriority(IRQn_Type::SysTick_IRQn, 0);
    }
  };
}  // namespace Peripherals

#endif
