#include "pch.h"
#include "os_first_task.h"  
#include <gtest/gtest.h>

TEST(FibonacciTest, HandlesZeroInput) {
    EXPECT_EQ(fibonacci(0), std::vector<int>({}));
}

TEST(FibonacciTest, HandlesOneInput) {
    EXPECT_EQ(fibonacci(1), std::vector<int>({ 0 }));
}

TEST(FibonacciTest, HandlesTwoInput) {
    EXPECT_EQ(fibonacci(2), std::vector<int>({ 0, 1 }));
}

TEST(FibonacciTest, HandlesThreeInput) {
    EXPECT_EQ(fibonacci(3), std::vector<int>({ 0, 1, 1 }));
}

TEST(FibonacciTest, HandlesFourInput) {
    EXPECT_EQ(fibonacci(4), std::vector<int>({ 0, 1, 1, 2 })); 
}

TEST(FibonacciTest, HandlesNegativeInput) {   
    EXPECT_THROW(fibonacci(-1), std::invalid_argument); 
}

TEST(FibonacciTest, HandlesLargeInput) {
    EXPECT_NO_THROW(fibonacci(10));  // Проверяем, что не возникает исключений
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}