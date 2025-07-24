#include <Gpio.hpp>
#include <Rcc.hpp>
#include <TM1637.hpp>
#include <Usart.hpp>
#include <Exti.hpp>
#include <cstdio>

#ifndef TASKS_PRINT_HPP
#define TASKS_PRINT_HPP

namespace Usart = Peripherals::Usart;

using UsartType = Usart::UniversalSynchronousAsynchronousReceiverTransmitter;
using RccType = Peripherals::Rcc::ResetAndClockControl;
using GpioType = Peripherals::Gpio::Gpio;

namespace Tasks::Print
{
  /// @brief Print task class that prints
  class PrintTask
  {
   private:
    /// @brief Baud rate for the USART communication.
    static constexpr auto BaudRate = 115200;

    /// @brief Pin number for the push button.
    static constexpr auto PushButtonPin = 0;

    /// @brief Push button GPIO configuration.
    GpioType pushButton = GpioType(
      GPIOA, PushButtonPin, Peripherals::Gpio::Mode::Input, Peripherals::Gpio::InputOutputType::Floating_OpenDrain);

   public:
    /// @brief Constructor for the PrintTask class.
    /// @details Configures the USART1 peripheral with the specified baud rate.
    PrintTask()
    {
      UsartType::GetInstance<Usart::UsartInstance::Usart1>().Configure(
        USART1, UsartType::GetMantissaAndFraction(BaudRate, RccType::Ticks));

      Peripherals::Exti::ExternalInterruptManager::SetupExti0Interrupt(Peripherals::Exti::ExtiPort::PortA);
    }

    // Deleted copy constructor and assignment operator.
    PrintTask(const PrintTask&) = delete;
    PrintTask& operator=(const PrintTask&) = delete;
    PrintTask(PrintTask&&) = delete;
    PrintTask& operator=(PrintTask&&) = delete;
    ~PrintTask() = default;

    /// @brief Runs the print task.
    void Run()
    {
      // Done by exti
      // if (pushButton.GetState())
      // {
      //   printf("Hello World!\n");
      // }
    }
  };
}  // namespace Tasks::Print

#endif  // TASKS_PRINT_HPP
