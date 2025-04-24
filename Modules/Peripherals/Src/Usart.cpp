/// @file Usart.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#include <stm32f1xx.h>

#include <Peripherals.hpp>
#include <Rcc.hpp>
#include <Usart.hpp>
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

using RccType = Peripherals::Rcc::ResetAndClockControl;
using UsartType = Peripherals::Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

Peripherals::Status UsartType::Transmit(const std::vector<size_t>& data, const size_t timeout) const
{
  const auto start = rcc.GetSysTick();
  auto iter = data.begin();

  while (iter != data.end())
  {
    if ((peripheral->SR & (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE)) != 0)
    {
      return Peripherals::Status::Error;
    }

    if ((peripheral->SR & USART_SR_TXE) == USART_SR_TXE)
    {
      peripheral->DR = *iter;
      ++iter;
    }
    else if ((rcc.GetSysTick() - start) >= timeout)
    {
      return Peripherals::Status::Timeout;
    }
  }

  while (true)
  {
    if ((peripheral->SR & (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE)) != 0)
    {
      return Peripherals::Status::Error;
    }

    if ((peripheral->SR & USART_SR_TC) != USART_SR_TC)
    {
      return Peripherals::Status::Ok;
    }

    if ((rcc.GetSysTick() - start) >= timeout)
    {
      return Peripherals::Status::Timeout;
    }
  }
}

void UsartType::ConfigureUsart() const
{
  // NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)

  // Enable transmitter
  peripheral->CR1 |= USART_CR1_TE;

  peripheral->CR1 &= ~USART_CR1_M;
  peripheral->CR1 &= ~USART_CR1_PS;
  peripheral->CR1 |= USART_CR1_PCE;

  // Disable interrupts
  peripheral->CR1 &= ~(USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE | USART_CR1_IDLEIE);
  peripheral->CR2 &= ~USART_CR2_LBDIE;
  peripheral->CR3 &= ~(USART_CR3_CTSIE | USART_CR3_EIE);

  // Disable receiver
  peripheral->CR1 &= ~USART_CR1_RE;

  // Send no break character
  peripheral->CR1 &= ~USART_CR1_SBK;

  // Disable not necessary modes (lin, hardware flow control, dma, smartcard, halfduplex, irda)
  peripheral->CR2 &= ~(USART_CR2_LINEN);
  peripheral->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE | USART_CR3_DMAR | USART_CR3_DMAT | USART_CR3_SCEN |
                       USART_CR3_HDSEL | USART_CR3_IREN | USART_CR3_NACK | USART_CR3_IRLP);

  // Set stop bits to 1
  peripheral->CR2 &= ~USART_CR2_STOP;

  // Set clock polarity, phase, last bit clock pulse and enable clock
  peripheral->CR2 |= USART_CR2_CPOL | USART_CR2_CPHA | USART_CR2_LBCL;

  // Configure Baud Rate
  peripheral->BRR |= fraction << USART_BRR_DIV_Fraction_Pos;
  peripheral->BRR |= mantissa << USART_BRR_DIV_Mantissa_Pos;

  // Enable UART
  peripheral->CR1 |= USART_CR1_UE;

  // NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
}

void UsartType::ConfigureClocks() const
{
  // NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
  if (peripheral == USART1)
  {
    // Enable Port A clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;
    // Configure GPIO Pins (PA9 - TX, PA10 - RX) with modes
    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0);
    GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
    GPIOA->CRH |= (GPIO_CRH_CNF10_0);
    AFIO->MAPR &= ~AFIO_MAPR_USART1_REMAP;
  }
  // NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
}
