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
#include <span>
#include <utility>

namespace Peripherals::Usart
{
  enum class UsartInstance : uint8_t
  {
    Usart1 = 0,
    Usart2 = 1,
    Usart3 = 2,
  };

  /// @brief
  class UniversalSynchronousAsynchronousReceiverTransmitter
  {
   private:
    USART_TypeDef* peripheral;
    size_t mantissa;
    size_t fraction;

    UniversalSynchronousAsynchronousReceiverTransmitter() = default;

    void ConfigureClocks() const;
    void ConfigureUsart() const;

   public:
    /// @brief
    // UniversalSynchronousAsynchronousReceiverTransmitter(
    //   USART_TypeDef* peripheral, const std::pair<size_t, size_t> mantissaFraction)
    //   : peripheral {peripheral}, mantissa {mantissaFraction.first}, fraction {mantissaFraction.second}
    // {
    //   ConfigureClocks();
    //   ConfigureUsart();
    // }
    template<UsartInstance Instance>
    static UniversalSynchronousAsynchronousReceiverTransmitter& GetInstance()
    {
      static UniversalSynchronousAsynchronousReceiverTransmitter instance;
      return instance;
    }

    void Configure(USART_TypeDef* peripheral, const std::pair<size_t, size_t> mantissaFraction)
    {
      this->peripheral = peripheral;
      this->mantissa = mantissaFraction.first;
      this->fraction = mantissaFraction.second;

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
    template<class T, std::size_t N>
    Peripherals::Status Transmit(const std::span<T, N>& data, const size_t timeout) const;
  };
}  // namespace Peripherals::Usart

#endif
