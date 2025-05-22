/// @file Usart.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Provides the Universal Synchronous Asynchronous Receiver Transmitter (USART) class.
/// @details The `UniversalSynchronousAsynchronousReceiverTransmitter` class provides methods to configure and use
///          the USART peripheral. It includes methods for configuring the USART, transmitting data, and calculating
///          the mantissa and fraction for the baud rate.

#ifndef PERIPHERALS_INC_USART_HPP
#define PERIPHERALS_INC_USART_HPP

#include <stm32f1xx.h>

#include <Peripherals.hpp>
#include <Rcc.hpp>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>

using RccType = Peripherals::Rcc::ResetAndClockControl;

namespace Peripherals::Usart
{
  /// @brief USART instance enumeration.
  /// @details This enumeration defines the available USART instances.
  enum class UsartInstance : uint8_t
  {
    /// @brief USART1 instance.
    Usart1 = 0,

    /// @brief USART2 instance.
    Usart2 = 1,

    /// @brief USART3 instance.
    Usart3 = 2,
  };

  /// @brief Universal Synchronous Asynchronous Receiver Transmitter (USART) class.
  /// @details This class provides methods to configure and use the USART peripheral.
  class UniversalSynchronousAsynchronousReceiverTransmitter
  {
   private:
    /// @brief Pointer to the USART peripheral.
    USART_TypeDef* peripheral;

    /// @brief Mantissa part of the baud rate.
    size_t mantissa;

    /// @brief Fraction part of the baud rate.
    size_t fraction;

    /// @brief Private constructor to prevent instantiation.
    UniversalSynchronousAsynchronousReceiverTransmitter() = default;

    /// @brief Configures the clocks for the USART peripheral.
    void ConfigureClocks() const;

    /// @brief Configures the USART peripheral settings.
    void ConfigureUsart() const;

   public:
    /// @brief Returns the singleton instance of the USART class.
    /// @param Instance USART instance to get the singleton for.
    /// @return Reference to the singleton instance.
    template<UsartInstance Instance>
    static UniversalSynchronousAsynchronousReceiverTransmitter& GetInstance()
    {
      static UniversalSynchronousAsynchronousReceiverTransmitter instance;
      return instance;
    }

    /// @brief Configures the USART peripheral with specified baud rate settings.
    /// @param peripheral Pointer to the USART peripheral.
    /// @param mantissaFraction Pair containing the mantissa and fraction for the baud rate.
    void Configure(USART_TypeDef* peripheral, const std::pair<size_t, size_t> mantissaFraction);

    // Deleted constructor and assignment operator.
    UniversalSynchronousAsynchronousReceiverTransmitter(
      const UniversalSynchronousAsynchronousReceiverTransmitter&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter& operator=(
      const UniversalSynchronousAsynchronousReceiverTransmitter&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter(UniversalSynchronousAsynchronousReceiverTransmitter&&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter& operator=(
      UniversalSynchronousAsynchronousReceiverTransmitter&&) = delete;
    ~UniversalSynchronousAsynchronousReceiverTransmitter() = default;

    /// @brief Calculates the mantissa and fraction for the specified baud rate at compile time.
    /// @param baudRate Baud rate to calculate the mantissa and fraction for.
    /// @param clockInTicks Clock frequency in ticks.
    /// @return Pair containing the mantissa and fraction for the baud rate.
    static constexpr std::pair<size_t, size_t> GetMantissaAndFraction(
      const uint32_t baudRate, const uint32_t clockInTicks)
    {
      auto clock = clockInTicks * 1000;
      // Div rounded to 4 decimal places more precision gets wrong fraction result
      auto div = round(clock / (static_cast<float>(baudRate) * 16.0F) * 10000) / 10000;
      auto mantissa = truncf(div);
      auto fraction = static_cast<uint32_t>(ceilf((div - mantissa) * 16.0F)) % 16;
      auto carry = truncf(ceilf((div - mantissa) * 16.0F) / 16.0F);
      auto mantissaWithCarry = static_cast<uint32_t>(truncf(div) + carry);

      return {mantissaWithCarry, fraction};
    }

    // TODO: Move to a separate file
    /// @brief Transmits data over the USART peripheral.
    /// @param data Data to transmit.
    /// @param timeout Timeout for the transmission in milliseconds.
    /// @return Status of the transmission operation.
    template<class T, std::size_t N>
    Peripherals::Status Transmit(const std::span<T, N>& data, const size_t timeout) const;
  };
}  // namespace Peripherals::Usart

#endif
