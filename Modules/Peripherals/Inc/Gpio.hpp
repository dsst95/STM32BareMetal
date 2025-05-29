/// @file Gpio.hpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief General purpose input output (GPIO) header file.

#ifndef PERIPHERALS_INC_GPIO_HPP
#define PERIPHERALS_INC_GPIO_HPP

#include <stddef.h>
#include <stm32f1xx.h>

#include <cstdint>

namespace Peripherals::Gpio
{
  /// @brief Enum class representing the mode of a GPIO pin.
  enum class Mode
  {
    /// @brief Input mode
    Input = 0,

    /// @brief Output mode, max speed 10 MHz
    OutputMiddle = 1,

    /// @brief Output mode, max speed 2 MHz
    OutputLow = 2,

    /// @brief Output mode, max speed 50 MHz
    OutputHigh = 3,
  };

  /// @brief Enum class representing the input/output type of a GPIO pin.
  enum class InputOutputType
  {
    /// @brief Analog mode in input mode or push-pull in output mode
    AnalogMode_PushPull = 0,

    /// @brief Floating input or open-drain output
    Floating_OpenDrain = 1,

    /// @brief Push-pull input or push-pull output
    PushPull_AFIOPushPull = 2,

    /// @brief Open-drain output
    Reversed_AFIOOpenDrain = 3,
  };

  /// @brief Struct representing the AFIO configuration for a GPIO pin.
  struct AfioConfig
  {
    /// @brief Mask for the AFIO configuration bits.
    size_t afioMask;

    /// @brief Mode for the AFIO configuration.
    size_t afioMode;
  };

  /// @brief Class representing a General Purpose Input Output (GPIO) pin.
  /// @details This class provides methods to configure and control GPIO pins on STM32 microcontrollers.
  class Gpio
  {
   private:
    /// @brief Pointer to the GPIO port.
    GPIO_TypeDef* port;

    /// @brief The pin number within the GPIO port.
    const size_t pin;

    /// @brief Bitmask for the pin within the GPIO port.
    const uint32_t pinMask;

    /// @brief Amount of pins in the low configuration register.
    constexpr static uint32_t LOW_PIN_COUNT = 8U;

    /// @brief Bitmask and shift values for configuring GPIO pins.
    constexpr static uint32_t PIN_CONFIG_MASK = 0xFU;

    /// @brief Shift multiplier for the mode bits in the GPIO configuration.
    /// @details The mode bits are shifted by 4 bits for each pin in the configuration registers.
    constexpr static uint32_t MODE_SHIFT_MULTIPLIER = 4U;

    /// @brief Additional shift for the configuration bits in the GPIO configuration.
    /// @details This is used to shift the configuration bits in the GPIO register.
    constexpr static uint32_t CONFIG_SHIFT_ADDITION = 2U;

   public:
    // Deleted copy constructor and assignment operator.
    Gpio(const Gpio&) = delete;
    Gpio& operator=(const Gpio&) = delete;
    Gpio(Gpio&&) = delete;
    Gpio& operator=(Gpio&&) = delete;
    ~Gpio() = default;

    /// @brief Constructor for the Gpio class.
    /// @param port Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.).
    /// @param pin The pin number within the GPIO port (0-15).
    /// @param mode The mode of the GPIO pin (e.g., Input, OutputLow, etc.).
    /// @param ioType The input/output type of the GPIO pin (e.g., AnalogMode_PushPull, Floating_OpenDrain, etc.).
    Gpio(GPIO_TypeDef* port, const size_t pin, const Mode mode, const InputOutputType ioType);

    /// @brief Constructor for the Gpio class with AFIO configuration.
    /// @param port Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.).
    /// @param pin The pin number within the GPIO port (0-15).
    /// @param mode The mode of the GPIO pin (e.g., Input, OutputLow, etc.).
    /// @param ioType The input/output type of the GPIO pin (e.g., AnalogMode_PushPull, Floating_OpenDrain, etc.).
    /// @param afioConfig The AFIO configuration for the GPIO pin.
    Gpio(GPIO_TypeDef* port,
      const size_t pin,
      const Mode mode,
      const InputOutputType ioType,
      const AfioConfig& afioConfig);

    /// @brief Sets the state of the GPIO pin.
    /// @param state The desired state of the GPIO pin (true for high, false for low).
    /// @details This method sets the output state of the GPIO pin. If the pin is configured as an input, this method
    ///          has no effect.
    void SetState(const bool state) const;

    /// @brief Toggles the state of the GPIO pin.
    /// @details This method toggles the output state of the GPIO pin. If the pin is configured as an input, this method
    ///          has no effect.
    void ToggleState() const;

    /// @brief Gets the current state of the GPIO pin.
    /// @return The current state of the GPIO pin (true for high, false for low).
    /// @details This method reads the input state of the GPIO pin. If the pin is configured as an output, this method
    ///          reads the output state.
    bool GetState() const;
  };
}  // namespace Peripherals::Gpio

#endif
