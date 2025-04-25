/// @file Rcc.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief
/// @details

#include <Rcc.hpp>

using RccType = Peripherals::Rcc::ResetAndClockControl;

void RccType::ConfigureClocks()
{
  RCC->CFGR &= ~RCC_CFGR_PLLMULL;
  RCC->CFGR |= RCC_CFGR_PLLMULL9;
  RCC->CFGR &= ~RCC_CFGR_USBPRE;

  RCC->CR |= RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) == 0)
  {
  }

  RCC->CFGR |= RCC_CFGR_PLLSRC;

  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) == 0)
  {
  }

  FLASH->ACR &= ~FLASH_ACR_LATENCY;
  FLASH->ACR |= FLASH_ACR_LATENCY_1;
  FLASH->ACR |= FLASH_ACR_PRFTBE;

  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) == 0)
  {
  }

  RCC->CFGR &= ~RCC_CFGR_HPRE;
  RCC->CFGR &= ~RCC_CFGR_PPRE1;
  RCC->CFGR |= RCC_CFGR_PPRE1_2;
  RCC->CFGR &= ~RCC_CFGR_PPRE2;
  RCC->CFGR &= ~RCC_CFGR_ADCPRE;
  RCC->CFGR |= RCC_CFGR_ADCPRE_1;

}

void RccType::ConfigureSysTick()
{
  SysTick->CTRL = 0x00UL;
  SysTick->LOAD = Ticks - 1;
  SysTick->VAL = 0x00UL;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}
