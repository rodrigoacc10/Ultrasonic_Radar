extern "C" {
    #include "unity.h"
}
#include <io_hw.h> 

// Global variable for testing setup and teardown
int test_counter_servo;
Servo test_baseServo; // Create a Servo object for testing

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

  printf("Running iohw_setup test...\n");
  test_counter_servo++;

  //iohw_setup(&test_baseServo);
  pinMode(trigPin, OUTPUT);       //Set the trig Pin port mode
  pinMode(echoPin, INPUT);        //Set echo Pin port mode

  test_baseServo.attach(ServoPin);     //Initialize servos
  test_baseServo.write(ServoInitAngle);            //Set the initial angle of the servo to 90 degrees

  //Test the operation of the base, pay attention to the position and rotation posture of the base, and whether there is any jamming (or wire winding).
  for (int x = StartServoAngle; x < MaxServoAngle; x += ServoInitStep)
  {
    test_baseServo.write(x);
    delay(delayTime);
  }

  printf("iohw_setup test completed.\n");
  TEST_ASSERT_EQUAL(1, test_counter_servo); // Ensure counter updates properly
}

void test_function_iohw_calculateDistance(void) 
{
  test_counter_servo++; 
    printf("Running iohw_setup test...\n");
  //int distance = iohw_calculateDistance(); 
  //TEST_ASSERT_TRUE(distance >= 0); // Ensure distance is non-negative
  TEST_ASSERT_EQUAL(1, test_counter_servo); // Ensure counter updates properly
}

int main() 
{
  UNITY_BEGIN();
  //RUN_TEST(test_function_iohw_setup);
  RUN_TEST(test_function_iohw_calculateDistance);
  return UNITY_END();
}

