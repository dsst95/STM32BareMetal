/// @file resetAndClockControl.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#include <stm32f103xb.h>

#include <core.hpp>
#include <cstddef>
#include <flashAccessControlRegister.hpp>
#include <rccConfigRegister.hpp>
#include <rccControlRegister.hpp>
#include <resetAndClockControl.hpp>
#include <sysTickControlRegister.hpp>
#include <sysTickReloadRegister.hpp>
#include <sysTickValueRegister.hpp>

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
Peripherals::ResetAndClockControl::ResetAndClockControl::ResetAndClockControl()
  : configRegister(reinterpret_cast<Registers::ConfigRegister*>(reinterpret_cast<RCC_TypeDef*>(RCC_BASE)->CFGR)),
    controlRegister(reinterpret_cast<Registers::ControlRegister*>(reinterpret_cast<RCC_TypeDef*>(RCC_BASE)->CR)),
    flashAccessControlRegister(
      reinterpret_cast<FlashRegisters::AccessControlRegister*>(reinterpret_cast<RCC_TypeDef*>(RCC_BASE)->CR)),
    sysTickControlRegister(
      reinterpret_cast<SysTickRegisters::SysTickControlRegister*>(reinterpret_cast<SysTick_Type*>(SysTick_BASE)->CTRL)),
    sysTickValueRegister(
      reinterpret_cast<SysTickRegisters::SysTickValueRegister*>(reinterpret_cast<SysTick_Type*>(SysTick_BASE)->VAL)),
    sysTickReloadRegister(
      reinterpret_cast<SysTickRegisters::SysTickReloadRegister*>(reinterpret_cast<SysTick_Type*>(SysTick_BASE)->LOAD))
{
  sysTick = 0;
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

void Peripherals::ResetAndClockControl::ResetAndClockControl::ConfigureClocks()
{
  configRegister->PLLMultiplicator = Registers::PhaseLockedLoopMultiplicator::Multiplicate9;

  controlRegister->ExternalHighSpeeClockEnabled = Core::State::Set;
  while (controlRegister->ExternalHighSpeeClockReady != Core::State::Set)
  {
  }

  configRegister->PLLSource = Registers::PhaseLockedLoopSource::InternalHighSpeedClock;

  controlRegister->PhaseLockedLoopEnabled = Core::State::Set;
  while (controlRegister->PhaseLockedLoopReady != Core::State::Set)
  {
  }

  flashAccessControlRegister->AccessLatency = FlashRegisters::Latency::Two;
  flashAccessControlRegister->PrefetchBufferEnabled = Core::State::Set;

  configRegister->SystemClockSwitch = Registers::SystemClockSwitchSource::PhaseLockedLoop;
  while (configRegister->SystemClockSwitchStatus != Registers::SystemClockSwitchSource::PhaseLockedLoop)
  {
  }

  configRegister->AHBPrescaler = Registers::AdvancedHighPerformanceBusPrescaler::Divide1;

  configRegister->APBLowSpeedPrescaler = Registers::AdvancedPeripheralBusPrescaler::Divide2;
  configRegister->APBHighSpeedPrescaler = Registers::AdvancedPeripheralBusPrescaler::Divide1;
  configRegister->ADCPrescaler = Registers::AnalogDigitalConverterPrescaler::Divide6;
}

void Peripherals::ResetAndClockControl::ResetAndClockControl::ConfigureSysTick()
{
  sysTickControlRegister->Enabled = Core::State::Reset;
  sysTickControlRegister->ExceptionRequestEnabled = Core::State::Reset;
  sysTickControlRegister->Source = SysTickRegisters::ClockSource::AHB8;

  sysTickValueRegister->CurrentValue = 0;
  sysTickReloadRegister->ReloadValue = ticks - 1;
  NVIC_SetPriority(SysTick_IRQn, 0);

  sysTickControlRegister->Enabled = Core::State::Set;
  sysTickControlRegister->ExceptionRequestEnabled = Core::State::Set;
  sysTickControlRegister->Source = SysTickRegisters::ClockSource::AHB;
}

void Peripherals::ResetAndClockControl::ResetAndClockControl::IncreaseSystick()
{
  sysTick++;
}

size_t Peripherals::ResetAndClockControl::ResetAndClockControl::GetSysTick()
{
  return sysTick;
}

void Peripherals::ResetAndClockControl::ResetAndClockControl::Delay(size_t milliseconds)
{
  const size_t start = GetSysTick();

  while ((GetSysTick() - start) < milliseconds)
  {
  }
}

// NOLINTBEGIN
extern "C" void SysTick_Handler() {
  Peripherals::ResetAndClockControl::ResetAndClockControl::IncreaseSystick();
}
// NOLINTEND
