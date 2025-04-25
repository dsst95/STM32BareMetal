/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Interrupt manager to configure the interrupts.

#include <stm32f1xx.h>

#include <InterruptManager.hpp>
#include <Rcc.hpp>

using InterruptManagerType = Peripherals::InterruptManager;
using RccType = Peripherals::Rcc::ResetAndClockControl;

// NOLINTBEGIN
extern "C" void SysTick_Handler()
{
  RccType::GetInstance().HandleInterrupt();
}
// NOLINTEND
