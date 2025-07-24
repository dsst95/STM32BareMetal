/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Interrupt manager to configure the interrupts.

#include <stm32f1xx.h>

#include <Exti.hpp>
#include <InterruptManager.hpp>
#include <Rcc.hpp>

using InterruptManagerType = Peripherals::InterruptManager;
using RccType = Peripherals::Rcc::ResetAndClockControl;

// NOLINTBEGIN
extern "C" void SysTick_Handler()
{
  RccType::GetInstance().HandleInterrupt();
}

extern "C" void EXTI0_IRQHandler()
{
  Peripherals::Exti::ExternalInterruptManager::HandleExti0Interrupt();
}
// NOLINTEND
