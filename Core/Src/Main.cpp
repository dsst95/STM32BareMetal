/// @file main.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Main file of the STM32 bare metal tutorial project.

#include <stm32f1xx.h>

#include <InterruptManager.hpp>
#include <Rcc.hpp>
#include <Usart.hpp>

using RccType = Peripherals::Rcc::ResetAndClockControl;
using InterruptManagerType = Peripherals::InterruptManager;
using UsartType = Peripherals::Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

int main()
{
  auto rcc = RccType();

  InterruptManagerType::SetupNvicPriorities();
  // InterruptManagerType::RegisterInterruptHandler(SysTick_IRQn, &rcc);

  auto usart1 = UsartType(USART1, rcc, UsartType::GetMantissaAndFraction(115200, rcc.Ticks));

  /* Loop forever */
  for (;;)
  {
    rcc.Delay(1000);
  }

  return 0;
}
