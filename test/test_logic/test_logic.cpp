#include <gtest/gtest.h>

// Function under test
int add(int a, int b) {
    return a + b;
}

bool is_even(int x) {
    return x % 2 == 0;
}

int max_of_three(int a, int b, int c) {
    return std::max(a, std::max(b, c));
}

std::string greet(const std::string& name) {
    return "Hello, " + name;
}

double divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("Division by zero");
    return a / b;
}

// Test cases

TEST(MathTest, AdditionIsCorrect) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

TEST(MathTest, EvenCheckWorks) {
    EXPECT_TRUE(is_even(4));
    EXPECT_FALSE(is_even(7));
}

TEST(MathTest, MaxOfThreeReturnsLargest) {
    EXPECT_EQ(max_of_three(1, 5, 3), 5);
    EXPECT_EQ(max_of_three(9, 2, 7), 9);
}

TEST(StringTest, GreetingIsFormattedCorrectly) {
    EXPECT_EQ(greet("Rodrigo"), "Hello, Rodrigo");
    EXPECT_NE(greet("World"), "Hi, World");
}

TEST(MathTest, DivisionHandlesZeroSafely) {
    EXPECT_DOUBLE_EQ(divide(10.0, 2.0), 5.0);
    EXPECT_THROW(divide(5.0, 0.0), std::invalid_argument);
}

// Main runner
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}