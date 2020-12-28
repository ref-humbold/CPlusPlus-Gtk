#include <gtest/gtest.h>
#include "converter.hpp"

TEST(ConverterTest, convert_WhenPositiveInput_ThenPositiveResult)
{
    // given
    converter test_object(10, 2);
    // when
    std::string result = test_object.convert("10");
    //then
    EXPECT_EQ("1010", result);
}

TEST(ConverterTest, convert_WhenNegativeInput_ThenNegativeResult)
{
    // given
    converter test_object(10, 2);
    // when
    std::string result = test_object.convert("-10");
    //then
    EXPECT_EQ("-1010", result);
}
