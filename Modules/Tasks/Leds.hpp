#include <Gpio.hpp>

#ifndef TASKS_LEDS_HPP
#define TASKS_LEDS_HPP

using GpioType = Peripherals::Gpio::Gpio;

namespace Tasks::Leds
{
  /// @brief LedsTask class that manages the state of two LEDs based on the state of two switches.
  class LedsTask
  {
   private:
    /// @brief Pin number for the green LED.
    static constexpr auto GreenLedPin = 13;

    /// @brief Pin number for the red LED.
    static constexpr auto RedLedPin = 14;

    /// @brief Pin number for the switch controlling the green LED.
    static constexpr auto SwitchGreenLedPin = 8;

    /// @brief Pin number for the switch controlling the red LED.
    static constexpr auto SwitchRedLedPin = 15;

    /// @brief GPIO configuration for the green LED.
    GpioType greenLed = GpioType(
      GPIOB, GreenLedPin, Peripherals::Gpio::Mode::OutputLow, Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

    /// @brief GPIO configuration for the red LED.
    GpioType redLed = GpioType(
      GPIOB, RedLedPin, Peripherals::Gpio::Mode::OutputLow, Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

    /// @brief GPIO configuration for the switch controlling the green LED.
    GpioType switchGreenLed = GpioType(
      GPIOA, SwitchGreenLedPin, Peripherals::Gpio::Mode::Input, Peripherals::Gpio::InputOutputType::Floating_OpenDrain);

    /// @brief GPIO configuration for the switch controlling the red LED.
    GpioType switchRedLed = GpioType(GPIOA,
      SwitchRedLedPin,
      Peripherals::Gpio::Mode::Input,
      Peripherals::Gpio::InputOutputType::Floating_OpenDrain,
      {
        .afioMask = AFIO_MAPR_SWJ_CFG_Msk,
        .afioMode = AFIO_MAPR_SWJ_CFG_JTAGDISABLE,
      });

   public:
    /// @brief Constructor for the LedsTask class.
    LedsTask()
    {
      greenLed.SetState(true);
      redLed.SetState(true);
    }

    // Deleted copy and move constructors and assignment operators.
    LedsTask(const LedsTask&) = delete;
    LedsTask& operator=(const LedsTask&) = delete;
    LedsTask(LedsTask&&) = delete;
    LedsTask& operator=(LedsTask&&) = delete;
    ~LedsTask() = default;

    /// @brief Runs the LedsTask, updating the state of the LEDs based on the switches.
    void Run()
    {
      greenLed.SetState(switchGreenLed.GetState());
      redLed.SetState(switchRedLed.GetState());
    }
  };
}  // namespace Tasks::Leds

#endif  // TASKS_LEDS_HPP
