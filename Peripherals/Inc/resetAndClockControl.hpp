/// @file resetAndClockControl.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_RESETANDCLOCKCONTROL_HPP
#define PERIPHERALS_INC_RESETANDCLOCKCONTROL_HPP

#include <cstddef>
#include <flashAccessControlRegister.hpp>
#include <rccConfigRegister.hpp>
#include <rccControlRegister.hpp>
#include <sysTickControlRegister.hpp>
#include <sysTickReloadRegister.hpp>
#include <sysTickValueRegister.hpp>

namespace FlashRegisters = Peripherals::Flash::Registers;
namespace SysTickRegisters = Peripherals::SystemTimer::Registers;

namespace Peripherals::ResetAndClockControl
{
  class ResetAndClockControl
  {
   private:
    Registers::ConfigRegister* configRegister;
    Registers::ControlRegister* controlRegister;
    FlashRegisters::AccessControlRegister* flashAccessControlRegister;
    SysTickRegisters::SysTickControlRegister* sysTickControlRegister;
    SysTickRegisters::SysTickValueRegister* sysTickValueRegister;
    SysTickRegisters::SysTickReloadRegister* sysTickReloadRegister;

    const size_t ticks = 72000;
    static size_t sysTick;

   public:
    ResetAndClockControl();

    void ConfigureClocks();

    void ConfigureSysTick();

    static void Delay(size_t milliseconds);

    static size_t GetSysTick();

    static void IncreaseSystick();
  };
}  // namespace Peripherals::ResetAndClockControl

#endif
