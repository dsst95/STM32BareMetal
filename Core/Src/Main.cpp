/// @file Main.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Main file of the STM32 bare metal tutorial project.

#include <stm32f1xx.h>

#include <Display.hpp>
#include <InterruptManager.hpp>
#include <Leds.hpp>
#include <Print.hpp>
#include <Rcc.hpp>

using RccType = Peripherals::Rcc::ResetAndClockControl;
using InterruptManagerType = Peripherals::InterruptManager;

int main()
{
  InterruptManagerType::SetupNvicPriorities();

  // Get instance to configure RCC
  RccType::GetInstance();

  auto printTask = Tasks::Print::PrintTask();
  auto ledsTask = Tasks::Leds::LedsTask();
  auto displayTask = Tasks::Display::DisplayTask();

  /* Loop forever */
  for (;;)
  {
    constexpr auto delay = 1000;

    RccType::GetInstance().Delay(delay);

    printTask.Run();
    ledsTask.Run();
    displayTask.Run();
  }

  return 0;
}
