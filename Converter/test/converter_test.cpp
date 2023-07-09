#include <gtest/gtest.h>
#include "converter.hpp"

TEST(ConverterTest, convert_WhenPositiveInput_ThenPositiveResult)
{
    // given
    converter test_object(10, 2);
    // when
    std::string result = test_object.convert("+25");
    //then
    EXPECT_EQ("11001", result);
}

TEST(ConverterTest, convert_WhenNegativeInput_ThenNegativeResult)
{
    // given
    converter test_object(10, 2);
    // when
    std::string result = test_object.convert("-25");
    //then
    EXPECT_EQ("-11001", result);
}

TEST(ConverterTest, convert_WhenLeadingZeros_ThenResultWithoutLeadingZeros)
{
    // given
    converter test_object(8, 10);
    // when
    std::string result = test_object.convert("000157");
    //then
    EXPECT_EQ("111", result);
}

TEST(ConverterTest, convert_WhenInputBaseOver10_ThenLettersAreCaseIndependent)
{
    // given
    converter test_object(16, 10);
    // when
    std::string result = test_object.convert("c3F");
    //then
    EXPECT_EQ("3135", result);
}

TEST(ConverterTest, convert_WhenOutputBaseOver10_ThenUppercaseLettersAsDigits)
{
    // given
    converter test_object(10, 16);
    // when
    std::string result = test_object.convert("1200");
    //then
    EXPECT_EQ("4B0", result);
}

TEST(ConverterTest, convert_WhenInvalidInputBase_ThenConverterException)
{
    // when
    auto exec = []() { return converter(1, 10); };
    //then
    EXPECT_THROW(exec(), converter_exception);
}

TEST(ConverterTest, convert_WhenInvalidOutputBase_ThenConverterException)
{
    // when
    auto exec = []() { return converter(10, 25); };
    //then
    EXPECT_THROW(exec(), converter_exception);
}

TEST(ConverterTest, convert_WhenInvalidDigits_ThenConverterException)
{
    // given
    converter test_object(4, 10);
    // when
    auto exec = [&]() { return test_object.convert("109"); };
    //then
    EXPECT_THROW(exec(), converter_exception);
}
