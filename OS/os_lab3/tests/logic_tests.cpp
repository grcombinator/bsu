#include <gtest/gtest.h>
#include "utils.h"

// Тест фильтрации строк
TEST(FilterStringsTest, AllValidCharacters) {
    std::vector<std::string> input = { "abc", "bcd" };
    char A = 'a', B = 'z';
    std::vector<std::string> expected = { "abc", "bcd" };
    EXPECT_EQ(filterStrings(input, A, B), expected);
}

TEST(FilterStringsTest, SomeInvalid) {
    std::vector<std::string> input = { "abc", "bca!", "def" };
    char A = 'a', B = 'z';
    std::vector<std::string> expected = { "abc", "def" };
    EXPECT_EQ(filterStrings(input, A, B), expected);
}

TEST(FilterStringsTest, EmptyString) {
    std::vector<std::string> input = { "" };
    char A = 'a', B = 'z';
    std::vector<std::string> expected = { "" }; // Пустая строка считается подходящей
    EXPECT_EQ(filterStrings(input, A, B), expected);
}

TEST(FilterStringsTest, OutOfRange) {
    std::vector<std::string> input = { "ABCD", "XYZ" };
    char A = 'a', B = 'z';
    std::vector<std::string> expected = {};
    EXPECT_EQ(filterStrings(input, A, B), expected);
}

// Тест умножения длин строк
TEST(MultiplyLengthsTest, BasicCase) {
    std::vector<std::string> input = { "one", "two", "three" };
    EXPECT_EQ(multiplyLengths(input), 3 * 3 * 5); // 45
}

TEST(MultiplyLengthsTest, EmptyVector) {
    std::vector<std::string> input = {};
    EXPECT_EQ(multiplyLengths(input), 1); // По правилам умножения
}

TEST(MultiplyLengthsTest, ZeroLength) {
    std::vector<std::string> input = { "", "", "" };
    EXPECT_EQ(multiplyLengths(input), 0);
}

TEST(MultiplyLengthsTest, OneElement) {
    std::vector<std::string> input = { "test" };
    EXPECT_EQ(multiplyLengths(input), 4);
}