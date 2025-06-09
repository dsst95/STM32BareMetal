/// @file TM1637.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief Header file for the TM1637 display driver.

#include <Gpio.hpp>
#include <array>

#ifndef TM1637_TM1637_HPP
#define TM1637_TM1637_HPP

namespace TM1637
{
  /// @brief Structure to hold GPIO pins for the TM1637 display.
  struct GpioPins
  {
    /// @brief GPIO pin for the clock signal.
    Peripherals::Gpio::Gpio* clockPin;

    /// @brief GPIO pin for the data signal.
    Peripherals::Gpio::Gpio* dataPin;
  };

  /// @brief Structure to represent time in hours and minutes.
  struct Time
  {
    /// @brief Hours in 24-hour format (0-23).
    uint8_t hours;

    /// @brief Minutes in 60-minute format (0-59).
    uint8_t minutes;
  };

  /// @brief Class to control the TM1637 display.
  /// @details This class provides methods to write digits, set brightness, and display time on the TM1637 display.
  /// @note The display supports 4 digits and a colon segment.
  class TM1637
  {
   private:
    /// @brief GPIO pin for the clock signal.
    Peripherals::Gpio::Gpio* clockPin = nullptr;

    /// @brief GPIO pin for the data signal.
    Peripherals::Gpio::Gpio* dataPin = nullptr;

    /// @brief Brightness level of the display (0-7).
    uint8_t brightness = 4U;

    /// @brief Flag to indicate if the colon segment is enabled.
    bool colonEnabled = false;

    /// @brief Array to map digits to their corresponding 7-segment display encoding.
    static constexpr std::array<uint8_t, 10> digitsToSegments = {
      0b00111111,  // 0
      0b00000110,  // 1
      0b01011011,  // 2
      0b01001111,  // 3
      0b01100110,  // 4
      0b01101101,  // 5
      0b01111101,  // 6
      0b00000111,  // 7
      0b01111111,  // 8
      0b01101111,  // 9
    };

    /// @brief Segment encoding for the colon.
    static constexpr uint8_t colonSegment = 0b10000000;

    /// @brief Number of bits in a byte.
    static constexpr uint8_t bitsInByte = 8;

    /// @brief Maximum brightness level for the display.
    static constexpr uint8_t maxBrightness = 0x07U;

    /// @brief Command to set the brightness of the display.
    static constexpr uint8_t setBrightnessCommand = 0x88U;

    /// @brief Command to set the address with auto-increment.
    static constexpr uint8_t addressWithAutoIncrementCommand = 0x40U;

    /// @brief Starting address for the display data.
    static constexpr uint8_t startAdress = 0xC0U;

    /// @brief Short delay in milliseconds for timing control.
    static constexpr uint8_t shortDelay = 2;

    /// @brief Middle delay in milliseconds for timing control.
    static constexpr uint8_t middleDelay = 3;

    /// @brief Long delay in milliseconds for timing control.
    static constexpr uint8_t longDelay = 5;

    /// @brief Sends a single byte to the TM1637 display.
    /// @param data The byte to send.
    void SendByte(uint8_t data);

    /// @brief Starts communication with the TM1637 display.
    void Start();

    /// @brief Stops communication with the TM1637 display.
    void Stop();

    /// @brief Acknowledges the receipt of data from the TM1637 display.
    void Acknowledge();

   public:
    /// @brief Constructor for the TM1637 class.
    /// @param gpioPins Structure containing GPIO pins for clock and data.
    TM1637(const GpioPins&& pins);

    // Deleted copy constructor and assignment operator.
    TM1637(const TM1637&) = delete;
    TM1637& operator=(const TM1637&) = delete;
    TM1637(TM1637&&) = delete;
    TM1637& operator=(TM1637&&) = delete;
    ~TM1637() = default;

    /// @brief Writes digits to the TM1637 display.
    /// @param digits Array of 4 digits to display (0-9).
    /// @param colon Flag to indicate if the colon segment should be displayed.
    void WriteDigits(std::array<uint8_t, 4>& digits, bool colon);

    /// @brief Sets the brightness of the TM1637 display.
    /// @param brightness Brightness level (0-7).
    /// @details The brightness level is set using a command that combines the set brightness command with the desired
    /// level.
    /// @note The brightness level is capped at 7 (maximum).
    void SetBrightness(uint8_t brightness);

    /// @brief Sets the counter value on the TM1637 display.
    /// @param counter The counter value to display (0-9999).
    /// @details The counter value is split into its individual digits and displayed on the TM1637.
    /// @note The counter value is expected to be in the range of 0 to 9999.
    /// @note If the counter exceeds 9999, it will wrap around to 0.
    void SetCounter(uint16_t counter);

    /// @brief Sets the current time on the TM1637 display.
    /// @param time The time to display, represented as a Time structure containing hours and minutes.
    /// @details The time is displayed in a 24-hour format, with hours ranging from 0 to 23 and minutes from 0 to 59.
    /// @note The display will show the time in the format HH:MM.
    void SetClock(Time& time);
  };
}  // namespace TM1637

#endif  // TM1637_TM1637_HPP
