/// @file
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief

#include <Usart.hpp>
#include <span>

namespace Usart = Peripherals::Usart;

using UsartType = Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

constexpr auto PrintTimeout = 1000;

// NOLINTBEGIN
extern "C" int _write(int file, const char *ptr, int len)
{
  UsartType::GetInstance<Usart::UsartInstance::Usart1>().Transmit(std::span(ptr, len), PrintTimeout);

  return len;
}
// NOLINTEND
