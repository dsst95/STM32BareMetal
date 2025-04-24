/// @file Usart.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#ifndef PERIPHERALS_INC_USART_HPP
#define PERIPHERALS_INC_USART_HPP

#include <stm32f1xx.h>

#include <Peripherals.hpp>
#include <Rcc.hpp>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace Peripherals::Usart
{
  using RccType = Peripherals::Rcc::ResetAndClockControl;

  /// @brief
  class UniversalSynchronousAsynchronousReceiverTransmitter
  {
   private:
    USART_TypeDef* peripheral;
    const RccType& rcc;
    const size_t mantissa;
    const size_t fraction;

   public:
    /// @brief
    UniversalSynchronousAsynchronousReceiverTransmitter(
      USART_TypeDef* peripheral, const RccType& rcc, const std::pair<size_t, size_t> mantissaFraction)
      : peripheral {peripheral}, rcc {rcc}, mantissa {mantissaFraction.first}, fraction {mantissaFraction.second}
    {
      ConfigureClocks();
      ConfigureUsart();
    }

    UniversalSynchronousAsynchronousReceiverTransmitter(
      const UniversalSynchronousAsynchronousReceiverTransmitter&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter& operator=(
      const UniversalSynchronousAsynchronousReceiverTransmitter&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter(UniversalSynchronousAsynchronousReceiverTransmitter&&) = delete;
    UniversalSynchronousAsynchronousReceiverTransmitter& operator=(
      UniversalSynchronousAsynchronousReceiverTransmitter&&) = delete;
    ~UniversalSynchronousAsynchronousReceiverTransmitter() = default;

    static constexpr std::pair<size_t, size_t> GetMantissaAndFraction(
      const uint32_t baudRate, const uint32_t clockInTicks)
    {
      auto clock = clockInTicks * 1000;
      auto div = clock / (static_cast<float>(baudRate) * 16.0F);
      auto mantissa = truncf(div);
      auto fraction = static_cast<uint32_t>(ceilf((div - mantissa) * 16.0F)) % 16;
      auto carry = truncf(ceilf((div - mantissa) * 16.0F) / 16.0F);
      auto mantissaWithCarry = static_cast<uint32_t>(truncf(div) + carry);

      return {mantissaWithCarry, fraction};
    }

    /// @brief
    /// @param data
    /// @param timeout
    /// @return
    Peripherals::Status Transmit(const std::vector<size_t>& data, const size_t timeout) const;

   private:
    void ConfigureClocks() const;

    void ConfigureUsart() const;
  };
}  // namespace Peripherals::Usart

#endif
