/// @file Gpio.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief General purpose input output (GPIO) implementation file.

#include "Gpio.hpp"

#include <stm32f1xx.h>

using GpioType = Peripherals::Gpio::Gpio;

GpioType::Gpio(GPIO_TypeDef* port,
  const size_t pin,
  const Peripherals::Gpio::Mode mode,
  const Peripherals::Gpio::InputOutputType ioType)
  : port {port}, pin {pin}, pinMask {1U << pin}
{
  // Enable the clock for the GPIO port
  if (port == GPIOA)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  }
  else if (port == GPIOB)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  }
  else if (port == GPIOC)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  }
  else if (port == GPIOD)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
  }
  else if (port == GPIOE)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
  }

  // Configure the pin mode and type
  if (pin < LOW_PIN_COUNT)
  {
    port->CRL &= ~(PIN_CONFIG_MASK << (pin * MODE_SHIFT_MULTIPLIER));
    port->CRL |= (static_cast<uint32_t>(mode) << (pin * MODE_SHIFT_MULTIPLIER)) |
                 (static_cast<uint32_t>(ioType) << (pin * MODE_SHIFT_MULTIPLIER + CONFIG_SHIFT_ADDITION));
  }
  else
  {
    auto highPin = pin - LOW_PIN_COUNT;
    port->CRH &= ~(PIN_CONFIG_MASK << (highPin * MODE_SHIFT_MULTIPLIER));
    port->CRH |= (static_cast<uint32_t>(mode) << (highPin * MODE_SHIFT_MULTIPLIER)) |
                 (static_cast<uint32_t>(ioType) << (highPin * MODE_SHIFT_MULTIPLIER + CONFIG_SHIFT_ADDITION));
  }
}

GpioType::Gpio(GPIO_TypeDef* port,
  const size_t pin,
  const Peripherals::Gpio::Mode mode,
  const Peripherals::Gpio::InputOutputType ioType,
  const Peripherals::Gpio::AfioConfig& afioConfig)
  : Gpio(port, pin, mode, ioType)
{
  // Enable the AFIO clock
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

  // Configure the AFIO
  AFIO->MAPR &= ~afioConfig.afioMask;
  AFIO->MAPR |= afioConfig.afioMode;
}

void GpioType::SetState(const bool state) const
{
  if (state)
  {
    port->ODR |= pinMask;
  }
  else
  {
    port->ODR &= ~pinMask;
  }
}

void GpioType::ToggleState() const
{
  port->ODR ^= pinMask;
}

bool GpioType::GetState() const
{
  return static_cast<bool>(port->IDR & pinMask);
}
