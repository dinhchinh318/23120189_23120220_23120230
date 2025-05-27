#include <gtest/gtest.h>
#include "PhoneManagement/Phone.h"

// Test round_to_decimal
TEST(PhoneUtilsTest, RoundToDecimal) {
    EXPECT_FLOAT_EQ(round_to_decimal(3.14159f, 2), 3.14f);
    EXPECT_FLOAT_EQ(round_to_decimal(2.71828f, 3), 2.718f);
    EXPECT_FLOAT_EQ(round_to_decimal(-1.23456f, 4), -1.2346f);
}

// Test priceStandardize
TEST(PhoneUtilsTest, PriceStandardize) {
    EXPECT_EQ(priceStandardize("1234567"), "1.234.567");
    EXPECT_EQ(priceStandardize("1000000"), "1.000.000");
    EXPECT_EQ(priceStandardize("abc123"), "123");
    EXPECT_EQ(priceStandardize(""), "0");
    EXPECT_EQ(priceStandardize("000123456"), "123.456");
}