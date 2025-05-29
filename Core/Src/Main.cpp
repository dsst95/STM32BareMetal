/// @file Main.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Main file of the STM32 bare metal tutorial project.

#include <stm32f1xx.h>

#include <Gpio.hpp>
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
constexpr auto GreenLedPin = 13;
constexpr auto RedLedPin = 14;
constexpr auto PushButtonPin = 0;
constexpr auto SwitchGreenLedPin = 8;
constexpr auto SwitchRedLedPin = 15;

int main()
{
  InterruptManagerType::SetupNvicPriorities();

  // Get instance to configure RCC
  RccType::GetInstance();

  UsartType::GetInstance<Usart::UsartInstance::Usart1>().Configure(
    USART1, UsartType::GetMantissaAndFraction(BaudRate, RccType::Ticks));

  auto greenLed = Peripherals::Gpio::Gpio(
    GPIOB, GreenLedPin, Peripherals::Gpio::Mode::OutputLow, Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

  auto redLed = Peripherals::Gpio::Gpio(
    GPIOB, RedLedPin, Peripherals::Gpio::Mode::OutputLow, Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

  auto pushButton = Peripherals::Gpio::Gpio(
    GPIOA, PushButtonPin, Peripherals::Gpio::Mode::Input, Peripherals::Gpio::InputOutputType::Floating_OpenDrain);

  auto switchGreenLed = Peripherals::Gpio::Gpio(
    GPIOA, SwitchGreenLedPin, Peripherals::Gpio::Mode::Input, Peripherals::Gpio::InputOutputType::Floating_OpenDrain);

  auto switchRedLed = Peripherals::Gpio::Gpio(GPIOA,
    SwitchRedLedPin,
    Peripherals::Gpio::Mode::Input,
    Peripherals::Gpio::InputOutputType::Floating_OpenDrain,
    {
      .afioMask = AFIO_MAPR_SWJ_CFG_Msk,
      .afioMode = AFIO_MAPR_SWJ_CFG_JTAGDISABLE
    });

  greenLed.SetState(true);
  redLed.SetState(true);

  /* Loop forever */
  for (;;)
  {
    RccType::GetInstance().Delay(Delay);

    if (pushButton.GetState())
    {
      printf("Hello World!\n");
    }

    greenLed.SetState(switchGreenLed.GetState());
    redLed.SetState(switchRedLed.GetState());
  }

  return 0;
}
