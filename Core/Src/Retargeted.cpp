/// @file Retargeted.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Retargeting of the standard output functions to USART1.

#include <Peripherals.hpp>
#include <Usart.hpp>
#include <span>

namespace Usart = Peripherals::Usart;

using UsartType = Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

// NOLINTBEGIN
extern "C" int _write(int file, const char *ptr, int len)
{
  UsartType::GetInstance<Usart::UsartInstance::Usart1>().Transmit(std::span(ptr, len), Peripherals::Timeout);

  return len;
}
// NOLINTEND
