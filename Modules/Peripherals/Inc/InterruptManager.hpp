/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#ifndef PERIPHERALS_INC_INTERRUPTMANAGER_HPP
#define PERIPHERALS_INC_INTERRUPTMANAGER_HPP

#include <stm32f1xx.h>

#include <InterruptHandler.hpp>
#include <array>
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

    // static constexpr void ExecuteInterruptHandler(IRQn_Type interrupt)
    // {
    //   auto handler = Handlers[(static_cast<int>(interrupt) + abs(FirstInterrupt))];

    //   if (handler != nullptr)
    //   {
    //     handler->HandleInterrupt();
    //   }
    // }

    // static constexpr void RegisterInterruptHandler(IRQn_Type interrupt, Peripherals::InterruptHandler* handler)
    // {
    //   Handlers[(static_cast<int>(interrupt) + abs(FirstInterrupt))] = handler;
    // }

    static void SetupNvicPriorities()
    {
      NVIC_SetPriority(IRQn_Type::SysTick_IRQn, 0);
    }

   private:
    // static const auto FirstInterrupt = static_cast<int>(IRQn_Type::NonMaskableInt_IRQn);
    // static const auto LastInterrupt = static_cast<int>(IRQn_Type::USBWakeUp_IRQn);
    // static constexpr size_t InterruptHandlerAmount = LastInterrupt + abs(FirstInterrupt) + 1;

    // inline static std::array<Peripherals::InterruptHandler*, InterruptHandlerAmount> Handlers = {nullptr};
  };
}  // namespace Peripherals

#endif
