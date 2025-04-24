/// @file InterruptManager.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#include <stm32f1xx.h>

#include <InterruptManager.hpp>

using InterruptManagerType = Peripherals::InterruptManager;

// NOLINTBEGIN
extern "C" void SysTick_Handler()
{
  // InterruptManagerType::ExecuteInterruptHandler(IRQn_Type::SysTick_IRQn);
}
// NOLINTEND
