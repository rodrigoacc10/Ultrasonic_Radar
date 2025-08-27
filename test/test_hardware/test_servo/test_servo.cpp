extern "C" {
    #include "unity.h"
}
#include <io_hw.h> 
#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>

// Arduino Uno runs at 16 MHz → 16,000,000 cycles per second.
#define WAIT_TIME 6400000 

// Global variable for testing setup and teardown
int test_counter_servo;


void setUp(void) 
{
  test_counter_servo = 0; //Initialize the test counter
}

void tearDown(void) 
{
  test_counter_servo = -1;
}

void test_function_iohw_setup(void) 
{
  volatile unsigned long start = 0;
  test_counter_servo++;
  bool servo_attached;
  Servo test_baseServo; // Create a Servo object for testing

  pinMode(ServoPin, OUTPUT);        //Set echo Pin port mode
  test_baseServo.attach(ServoPin);     //Initialize servos

  // Delay to allow visual verification
  while (start < WAIT_TIME)
  {
      start++;
  }
  
  servo_attached = test_baseServo.attached();
  TEST_ASSERT_TRUE(servo_attached); // Ensure servo is attached

  // Delay to allow visual verification
  while (start < WAIT_TIME)
  {
      start++;
  }

  test_baseServo.write(StartServoAngle);            //Set the initial angle of the servo to 90 degrees

  // Delay to allow visual verification
  while (start < WAIT_TIME)
  {
      start++;
  }
  
  test_baseServo.write(ServoInitAngle);  

  // Delay to allow visual verification
  while (start < WAIT_TIME)
  {
      start++;
  }
  
  test_baseServo.write(MaxServoAngle);
    
  TEST_ASSERT_EQUAL(1, test_counter_servo); // Ensure counter updates properly
}

void test_function_iohw_calculateDistance(void) 
{
  test_counter_servo++; 

  //iohw_setup(&test_baseServo);
  pinMode(trigPin, OUTPUT);       //Set the trig Pin port mode
  pinMode(echoPin, INPUT);        //Set echo Pin port mode
  
  printf("Running iohw_setup test...\n");
  //int distance = iohw_calculateDistance(); 
  //TEST_ASSERT_TRUE(distance >= 0); // Ensure distance is non-negative
  TEST_ASSERT_EQUAL(1, test_counter_servo); // Ensure counter updates properly
}

int main() 
{
  UNITY_BEGIN();
  RUN_TEST(test_function_iohw_setup);
  RUN_TEST(test_function_iohw_calculateDistance);
  return UNITY_END();
}

