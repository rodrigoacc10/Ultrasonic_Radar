#include <gtest/gtest.h>


/********************************************************/
/*                       Functions                      */
/********************************************************/

/* Math Functions */
int add(int a, int b) {
    return a + b;
}

int substract(int a, int b) {
    return a - b;
}

int lessthan(int a, int b) {
    if (a < b) return 1;
    return 0;
}

double divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("Division by zero");
    return a / b;
}

/* String/Serial Functions */
std::string greet(const std::string& name) {
    return "Hello, " + name;
}

std::string printdegree(const std::string& value) {
    return "Degree:  " + value;
}

std::string printdistance(const std::string& value) {
    return "    ,Distance:   " + value;
}

/* Radar Functions */
float distance_point(int a) {
    return a * 0.034 / 2;
}

/********************************************************/
/*                       Test Cases                     */
/********************************************************/

TEST(MathTest, AdditionIsCorrect) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

TEST(MathTest, SubstractIsCorrect) {
    EXPECT_EQ(substract(2, 3), -1);
    EXPECT_EQ(substract(-1, 1), -2);
}

TEST(MathTest, LessthanIsCorrect) {
    EXPECT_EQ(lessthan(2, 3), 1);
    EXPECT_EQ(lessthan(-1, 1), 1);
    EXPECT_EQ(lessthan(1, 1), 0);
}

TEST(MathTest, DivisionHandlesZeroSafely) {
    EXPECT_DOUBLE_EQ(divide(10.0, 2.0), 5.0);
    EXPECT_THROW(divide(5.0, 0.0), std::invalid_argument);
}

TEST(StringTest, GreetingIsFormattedCorrectly) {
    EXPECT_EQ(greet("Rodrigo"), "Hello, Rodrigo");
    EXPECT_NE(greet("World"), "Hi, World");
}

TEST(StringTest, PrintDegreeIsFormattedCorrectly) {
    EXPECT_EQ(printdegree("180"), "Degree:  180");
    EXPECT_NE(printdegree("90"), "Degree:  90C");
}

TEST(StringTest, PrintDistanceIsFormattedCorrectly) {
    EXPECT_EQ(printdistance("180"), "    ,Distance:   180");
    EXPECT_NE(printdistance("90"), "Distance:     90");
}

TEST(RadarTest, DistanceIsCalculatedCorrectly) {
    EXPECT_FLOAT_EQ(distance_point(10), 0.17);
    EXPECT_FLOAT_EQ(distance_point(20), 0.34);
}

/********************************************************/
/*                       Main runner                    */
/********************************************************/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}