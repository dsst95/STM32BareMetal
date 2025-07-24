/// @file Exti.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_EXTI_HPP
#define PERIPHERALS_INC_EXTI_HPP

#include <stm32f1xx.h>
#include <array>
#include <cstdio>

namespace Peripherals::Exti
{
  enum class ExtiPort
  {
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
    PortG = 6,
  };

  class ExternalInterruptManager
  {
   private:
    static constexpr int interruptHandlerAmount = 1;
    static constexpr std::array<void (*)(), interruptHandlerAmount> exti0interruptHandlers = {
      []() {
        printf("Hello World!\n");
      }
    };

   public:
    // Deleted copy constructor and assignment operator.
    ExternalInterruptManager() = delete;
    ExternalInterruptManager(const ExternalInterruptManager&) = delete;
    ExternalInterruptManager& operator=(const ExternalInterruptManager&) = delete;
    ExternalInterruptManager(ExternalInterruptManager&&) = delete;
    ExternalInterruptManager& operator=(ExternalInterruptManager&&) = delete;
    ~ExternalInterruptManager() = delete;

    static void SetupExti0Interrupt(ExtiPort port)
    {
      RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
      AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;
      AFIO->EXTICR[0] |= static_cast<uint32_t>(port) << AFIO_EXTICR1_EXTI0_Pos;
      EXTI->IMR |= EXTI_IMR_MR0;
      EXTI->RTSR |= EXTI_RTSR_TR0;  // Trigger on rising edge
      EXTI->FTSR &= ~EXTI_FTSR_TR0; // Disable falling
    }

    static constexpr void HandleExti0Interrupt()
    {
      // Clear the pending interrupt for EXTI0
      NVIC_ClearPendingIRQ(EXTI0_IRQn);

      ExecuteExti0InterruptHandler<interruptHandlerAmount - 1>();
    }

    template<int N>
    static constexpr void ExecuteExti0InterruptHandler()
    {
      if constexpr (N < interruptHandlerAmount)
      {
        if constexpr (exti0interruptHandlers[N] != 0)
        {
          exti0interruptHandlers[N]();
        }
      }

      if constexpr (N > 0)
      {
        // Recursively call the next handler
        ExecuteExti0InterruptHandler<N - 1>();
      }
    }
  };
}  // namespace Peripherals::Exti

#endif
