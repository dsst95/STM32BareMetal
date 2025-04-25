/// @file Main.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Main file of the STM32 bare metal tutorial project.

#include <stm32f1xx.h>

#include <InterruptManager.hpp>
#include <Rcc.hpp>
#include <Usart.hpp>
#include <cstdio>

namespace Usart = Peripherals::Usart;

using RccType = Peripherals::Rcc::ResetAndClockControl;
using InterruptManagerType = Peripherals::InterruptManager;
using UsartType = Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

constexpr auto BaudRate = 115200;
constexpr auto Delay = 1000;

int main()
{
  InterruptManagerType::SetupNvicPriorities();

  // Get instance to configure RCC
  RccType::GetInstance();

  UsartType::GetInstance<Usart::UsartInstance::Usart1>().Configure(
    USART1, UsartType::GetMantissaAndFraction(BaudRate, RccType::Ticks));

  /* Loop forever */
  for (;;)
  {
    RccType::GetInstance().Delay(Delay);
    printf("Hello World!\n");
  }

  return 0;
}
