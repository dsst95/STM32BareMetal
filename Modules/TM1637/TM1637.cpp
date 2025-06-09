#include <Rcc.hpp>
#include <TM1637.hpp>

using RccType = Peripherals::Rcc::ResetAndClockControl;
using TM1637Type = TM1637::TM1637;

TM1637Type::TM1637(const GpioPins&& gpioPins) : clockPin {gpioPins.clockPin}, dataPin {gpioPins.dataPin}
{
  SetBrightness(4);
}

void TM1637Type::WriteDigits(std::array<uint8_t, 4>& digits, bool colon)
{
  // Prepare data for the display
  digits[0] = digitsToSegments[digits[0]];
  digits[1] = digitsToSegments[digits[1]] | (colon ? colonSegment : 0U);  // Add colon segment if needed
  digits[2] = digitsToSegments[digits[2]];
  digits[3] = digitsToSegments[digits[3]];

  // Set Address command
  Start();
  SendByte(addressWithAutoIncrementCommand);
  Acknowledge();
  Stop();

  // Send Address and Data
  Start();
  SendByte(startAdress);  // Set address to 0xC0 (first digit)
  Acknowledge();

  for (const auto& digit : digits)
  {
    SendByte(digit);
    Acknowledge();
  }

  Stop();
  SetBrightness(brightness);
}

void TM1637Type::SetBrightness(uint8_t brightness)
{
  this->brightness = brightness;
  Start();
  SendByte(setBrightnessCommand | static_cast<uint8_t>(brightness & maxBrightness));
  Acknowledge();
  Stop();
}

void TM1637Type::SetCounter(uint16_t counter)
{
  std::array<uint8_t, 4> digits = {0, 0, 0, 0};
  constexpr auto thousandsDivisor = 1000U;
  constexpr auto hundredsDivisor = 100U;
  constexpr auto tensDivisor = 10U;
  constexpr auto digitsDivisor = 10U;

  // Convert counter to digits
  digits[0] = (counter / thousandsDivisor) % digitsDivisor;  // Thousands
  digits[1] = (counter / hundredsDivisor) % digitsDivisor;   // Hundreds
  digits[2] = (counter / tensDivisor) % digitsDivisor;       // Tens
  digits[3] = counter % digitsDivisor;                       // Units

  WriteDigits(digits, false);
}

void TM1637Type::SetClock(Time& time)
{
  std::array<uint8_t, 4> digits = {0, 0, 0, 0};
  constexpr auto digitsDivisor = 10U;

  // Convert hours and minutes to digits
  digits[0] = (time.hours / digitsDivisor) % digitsDivisor;    // Tens of hours
  digits[1] = time.hours % digitsDivisor;                      // Units of hours
  digits[2] = (time.minutes / digitsDivisor) % digitsDivisor;  // Tens of minutes
  digits[3] = time.minutes % digitsDivisor;                    // Units of minutes
  colonEnabled = !colonEnabled;                                // Toggle colon state for clock display

  WriteDigits(digits, colonEnabled);  // Add colon for clock display
}

void TM1637Type::SendByte(uint8_t data)
{
  for (uint8_t i = 0; i < bitsInByte; ++i)
  {
    clockPin->SetState(false);
    dataPin->SetState(static_cast<bool>(data & 0x01U));
    RccType::GetInstance().Delay(middleDelay);
    clockPin->SetState(true);
    RccType::GetInstance().Delay(middleDelay);
    data >>= 1U;
  }
}

void TM1637Type::Start()
{
  clockPin->SetState(true);
  dataPin->SetState(true);
  RccType::GetInstance().Delay(shortDelay);
  dataPin->SetState(false);
}

void TM1637Type::Stop()
{
  clockPin->SetState(false);
  RccType::GetInstance().Delay(shortDelay);
  dataPin->SetState(false);
  RccType::GetInstance().Delay(shortDelay);
  clockPin->SetState(true);
  RccType::GetInstance().Delay(shortDelay);
  dataPin->SetState(true);
}

void TM1637Type::Acknowledge()
{
  clockPin->SetState(false);
  RccType::GetInstance().Delay(longDelay);
  clockPin->SetState(true);
  RccType::GetInstance().Delay(shortDelay);
  clockPin->SetState(false);
}
