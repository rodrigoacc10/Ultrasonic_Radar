#include <Arduino.h>
#include <unity.h>
#include <io_hw.h> 

// Global variable for testing setup and teardown
int test_counter;
Servo baseServo; 

void setUp(void) 
{
  test_counter = 0; //Initialize the test counter
}

void tearDown(void) 
{
  test_counter = -1;
}

void test_function_iohw_setup(void) 
{
  test_counter++; 
  iohw_setup(&baseServo); 
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_iohw_calculateDistance(void) 
{
  test_counter++; 
  int distance = iohw_calculateDistance();
  TEST_ASSERT_TRUE(distance >= 0); // Ensure distance is non-negative
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

int runUnityTests(void) {
  UNITY_BEGIN();
  //RUN_TEST(test_function_iohw_setup);
  //RUN_TEST(test_function_iohw_calculateDistance);
  return UNITY_END();
}

