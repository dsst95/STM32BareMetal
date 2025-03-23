/// @file rccControlRegister.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#ifndef PERIPHERALS_INC_REGISTERS_RCCCONTROLREGISTER_HPP
#define PERIPHERALS_INC_REGISTERS_RCCCONTROLREGISTER_HPP

#include <core.hpp>
#include <cstdint>

namespace Peripherals::ResetAndClockControl::Registers
{
  struct ControlRegister
  {
    Core::State InternalHighSpeeClockEnabled : 1;
    Core::State InternalHighSpeeClockReady : 1;
    uint8_t _ : 1;
    uint8_t InternalHighSpeeClockTrimming : 5;
    uint8_t InternalHighSpeeClockCalibration : 8;
    Core::State ExternalHighSpeeClockEnabled : 1;
    Core::State ExternalHighSpeeClockReady : 1;
    Core::State ExternalHighSpeeClockBypass : 1;
    Core::State ClockSecuritySystemEnabled : 1;
    uint8_t __ : 4;
    Core::State PhaseLockedLoopEnabled : 1;
    Core::State PhaseLockedLoopReady : 1;
  };
}  // namespace Peripherals::ResetAndClockControl::Registers

#endif
