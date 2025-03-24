/// @file resetAndClockControl.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief This file defines the Reset and Clock Control (RCC) class for the STM32F103 microcontroller.
/// @details The `ResetAndClockControl` class provides methods to configure the system clocks, SysTick timer, and to
///          manage delays using the SysTick timer.

#ifndef PERIPHERALS_INC_RESETANDCLOCKCONTROL_HPP
#define PERIPHERALS_INC_RESETANDCLOCKCONTROL_HPP

#include <cstddef>
#include <flashAccessControlRegister.hpp>
#include <rccConfigRegister.hpp>
#include <rccControlRegister.hpp>
#include <sysTickControlRegister.hpp>
#include <sysTickReloadRegister.hpp>
#include <sysTickValueRegister.hpp>

namespace Peripherals::ResetAndClockControl
{
  namespace FlashRegisters = Peripherals::Flash::Registers;
  namespace SysTickRegisters = Peripherals::SystemTimer::Registers;

  /// @brief Class to manage the Reset and Clock Control (RCC) of the STM32F103 microcontroller.
  class ResetAndClockControl
  {
   private:
    /// @brief Pointer to the RCC configuration register.
    Registers::ConfigRegister* configRegister;

    /// @brief Pointer to the RCC control register.
    Registers::ControlRegister* controlRegister;

    /// @brief Pointer to the Flash access control register.
    FlashRegisters::AccessControlRegister* flashAccessControlRegister;

    /// @brief Pointer to the SysTick control register.
    SysTickRegisters::SysTickControlRegister* sysTickControlRegister;

    /// @brief Pointer to the SysTick value register.
    SysTickRegisters::SysTickValueRegister* sysTickValueRegister;

    /// @brief Pointer to the SysTick reload register.
    SysTickRegisters::SysTickReloadRegister* sysTickReloadRegister;

    /// @brief Number of ticks per millisecond.
    const size_t ticks = 72000;

    /// @brief Current SysTick counter value.
    static size_t sysTick;

   public:
    /// @brief Constructor for the ResetAndClockControl class.
    ResetAndClockControl();

    /// @brief Configures the system clocks.
    void ConfigureClocks();

    /// @brief Configures the SysTick timer.
    void ConfigureSysTick();

    /// @brief Delays execution for a specified number of milliseconds.
    /// @param milliseconds Number of milliseconds to delay.
    static void Delay(size_t milliseconds);

    /// @brief Gets the current SysTick counter value.
    /// @return Current SysTick counter value.
    static size_t GetSysTick();

    /// @brief Increases the SysTick counter value by one.
    static void IncreaseSystick();
  };
}  // namespace Peripherals::ResetAndClockControl

#endif
