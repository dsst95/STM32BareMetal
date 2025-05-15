#include <gtest/gtest.h>

#include <Usart.hpp>
#include <utility>

using UsartType = Peripherals::Usart::UniversalSynchronousAsynchronousReceiverTransmitter;

class GetMantissaAndFraction : public ::testing::TestWithParam<std::tuple<int, int, int, int>>
{
};

TEST_P(GetMantissaAndFraction, ReturnsCorrectMantissaAndFraction)
{
  auto [baudRate, clockFrequency, expectedMantissa, expectedFraction] = GetParam();
  auto result = UsartType::GetMantissaAndFraction(baudRate, clockFrequency);

  EXPECT_EQ(result.first, expectedMantissa);
  EXPECT_EQ(result.second, expectedFraction);
}

INSTANTIATE_TEST_SUITE_P(MantissaAndFractionsForMaxClock,
  GetMantissaAndFraction,
  testing::Values(std::tuple<int, int, int, int>(2400, 72000, 1875, 0),
    std::tuple<int, int, int, int>(9600, 72000, 468, 12),
    std::tuple<int, int, int, int>(19200, 72000, 234, 6),
    std::tuple<int, int, int, int>(57600, 72000, 78, 2),
    std::tuple<int, int, int, int>(88253, 72000, 51, 0),
    std::tuple<int, int, int, int>(115200, 72000, 39, 1),
    std::tuple<int, int, int, int>(230769, 72000, 19, 8),
    std::tuple<int, int, int, int>(461538, 72000, 9, 12),
    std::tuple<int, int, int, int>(923076, 72000, 4, 14),
    std::tuple<int, int, int, int>(2250000, 72000, 2, 0),
    std::tuple<int, int, int, int>(4500000, 72000, 1, 0)));

