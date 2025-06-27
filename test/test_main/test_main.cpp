#include <Arduino.h>
#include <unity.h>
#include <serial.h>

// Global variable for testing setup and teardown
int test_counter;

void setUp(void) 
{
  test_counter = 0; //Initialize the test counter
}

void tearDown(void) 
{
  test_counter = -1;
}

void test_function_serial(void) 
{
  int degree = 45; // Example degree value
  int distance = 100; // Example distance value
  test_counter++; 

  Serial_Init();
  Serial_PrintRadar(degree, distance);
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_serial2(void) 
{
  int degree = 90; // Example degree value
  int distance = 75; // Example distance value
  test_counter++; 

  Serial_Init();
  Serial_PrintRadar(degree, distance);
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_serial3(void) 
{
  int degree = 25; // Example degree value
  int distance = 10; // Example distance value
  test_counter++; 
  
  Serial_Init();
  Serial_PrintRadar(degree, distance);
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}


int runUnityTests(void) 
{
  UNITY_BEGIN();
  RUN_TEST(test_function_serial);
  //RUN_TEST(test_function_serial2);
  //RUN_TEST(test_function_serial3);    
  return UNITY_END();
}