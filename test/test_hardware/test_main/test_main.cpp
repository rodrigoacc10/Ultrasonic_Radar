extern "C" {
    #include "unity.h"
}
#include <serial.h>
#include <lcd.h>
#include <io_hw.h> 

// Arduino Uno runs at 16 MHz → 16,000,000 cycles per second.
// 500 milliseconds = 0.5 seconds
// 16,000,000 cycles/sec × 0.5 sec = 8,000,000 cycles
#define WAIT_TIME 800000 

// Global variable for testing setup and teardown
int test_counter;
Ucglib_ST7735_18x128x160_HWSPI test_ucg_main(/*cd=*/ Ucg_pin, /*cs=*/ Ucg_cs, /*reset=*/ Ucg_reset);
// Messages to display
const char* message1_maintest[2] = {"Hardare Testing", "Serial Comms Test"};
const char* message2_maintest[2] = {"Puglie & ", "Pusheen <3"};

// Define the servo object and LCD object
Servo test_baseServo_main; 

void setUp() {
  test_counter = 0; //Initialize the test counter
}

void tearDown(void) 
{
  test_counter = -1;
}

void test_function_serial(void) 
{
  volatile unsigned long start = 0;
  int degree = 45; // Example degree value
  int distance = 100; // Example distance value
  test_counter++; 

  Serial_Init();
  Serial_PrintRadar(degree, distance);

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_serial2(void) 
{
  volatile unsigned long start = 0;
  int degree = 90; // Example degree value
  int distance = 75; // Example distance value
  test_counter++; 

  Serial_Init();
  Serial_PrintRadar(degree, distance);

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_serial3(void) 
{
  volatile unsigned long start = 0;
  int degree = 25; // Example degree value
  int distance = 10; // Example distance value
  test_counter++; 
  
  Serial_Init();
  Serial_PrintRadar(degree, distance);

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_function_setup(void)
{ 
  volatile unsigned long start = 0;
  test_counter++; 

  int yOffset = 0;

  test_ucg_main.clearScreen();                 // Clear the screen before starting the effects

  test_ucg_main.begin(UCG_FONT_MODE_SOLID);    // Initialize the Ucglib object
  test_ucg_main.setRotate90();                 // Set the display orientation to horizontal

  // Set the background color for the screen
  test_ucg_main.setColor(0, 0, 100, 0);
  test_ucg_main.setColor(1, 0, 100, 0);
  test_ucg_main.setColor(2, 20, 20, 20);
  test_ucg_main.setColor(3, 20, 20, 20);
  test_ucg_main.drawGradientBox(0, 0, 160, 128);

  // Set the color for the text
  test_ucg_main.setColor(255, 0, 0);

  // Font settings
  test_ucg_main.setFont(ucg_font_ncenR12_tr); // Font style

  // Movement effect (vertical offset)
  yOffset = 0;

  // Print the first line of text with an offset
  test_ucg_main.setPrintPos(10, 60 + yOffset);           // Set position for first line
  test_ucg_main.print(message1_maintest[0]);                      // Print first line of text

  // Movement effect (vertical offset)
  yOffset = 0;

  // Print the second line of text with an offset
  test_ucg_main.setPrintPos(10, 100 + yOffset);         // Set position for second line
  test_ucg_main.print(message1_maintest[1]);                      // Print second line of text

  test_ucg_main.clearScreen();                 // Clear the screen before starting the effects    

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }      

  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly    

  // Movement effect (vertical offset)
  yOffset = 0;
  test_counter++;   

  // Print the first line of text with an offset
  test_ucg_main.setPrintPos(10, 60 + yOffset);           // Set position for first line
  test_ucg_main.print(message2_maintest[0]);                      // Print first line of text

  // Movement effect (vertical offset)
  yOffset = 0;

  // Print the second line of text with an offset
  test_ucg_main.setPrintPos(10, 100 + yOffset);         // Set position for second line
  test_ucg_main.print(message2_maintest[1]);                      // Print second line of text

  TEST_ASSERT_EQUAL(2, test_counter); // Ensure counter updates properly    

  test_counter = -1;  
}    

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_function_serial);
  RUN_TEST(test_function_serial2);
  RUN_TEST(test_function_serial3);  
  RUN_TEST(test_function_setup);  
  return UNITY_END();
}