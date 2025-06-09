#include <Gpio.hpp>
#include <TM1637.hpp>

#ifndef TASKS_DISPLAY_HPP
#define TASKS_DISPLAY_HPP

namespace Tasks::Display
{
  /// @brief DisplayTask class that manages the display of time on a TM1637 display.
  class DisplayTask
  {
   private:
    /// @brief Pin number for the clock signal of the TM1637 display.
    static constexpr auto DisplayClockPin = 10;

    /// @brief Pin number for the data signal of the TM1637 display.
    static constexpr auto DisplayDataPin = 11;

    /// @brief Number of seconds in a minute and minutes in an hour.
    static constexpr auto SecondsAndMinutes = 60U;

    /// @brief Number of hours in a day.
    static constexpr auto Hours = 24U;

    /// @brief Seconds counter to keep track of the time.
    uint8_t seconds = 0U;

    /// @brief Clock structure to hold the current time in hours and minutes.
    TM1637::Time clock = TM1637::Time {
      .hours = 0,
      .minutes = 0,
    };

    /// @brief Pin configuration for clock pin of the TM1637 display.
    Peripherals::Gpio::Gpio clockPin = Peripherals::Gpio::Gpio(GPIOB,
      DisplayClockPin,
      Peripherals::Gpio::Mode::OutputLow,
      Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

    /// @brief Pin configuration for data pin of the TM1637 display.
    Peripherals::Gpio::Gpio dataPin = Peripherals::Gpio::Gpio(GPIOB,
      DisplayDataPin,
      Peripherals::Gpio::Mode::OutputLow,
      Peripherals::Gpio::InputOutputType::AnalogMode_PushPull);

    /// @brief TM1637 display instance with the configured GPIO pins.
    TM1637::TM1637 display = TM1637::TM1637(TM1637::GpioPins {
      .clockPin = &clockPin,
      .dataPin = &dataPin,
    });

   public:
    /// @brief Constructor for the DisplayTask class.
    DisplayTask() = default;

    // Deleted copy and move constructors and assignment operators.
    DisplayTask(const DisplayTask&) = delete;
    DisplayTask& operator=(const DisplayTask&) = delete;
    DisplayTask(DisplayTask&&) = delete;
    DisplayTask& operator=(DisplayTask&&) = delete;
    ~DisplayTask() = default;

    /// @brief Runs the display task to update the clock every second.
    void Run()
    {
      ++seconds;

      if (seconds >= SecondsAndMinutes)
      {
        seconds = 0U;
        ++clock.minutes;

        if (clock.minutes >= SecondsAndMinutes)
        {
          clock.minutes = 0U;
          ++clock.hours;

          if (clock.hours >= Hours)
          {
            clock.hours = 0U;
          }
        }
      }

      display.SetClock(clock);
    }
  };
}  // namespace Tasks::Display

#endif  // TASKS_DISPLAY_HPP
