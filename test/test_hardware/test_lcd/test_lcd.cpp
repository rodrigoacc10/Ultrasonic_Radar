extern "C" {
    #include "unity.h"
}

#include <lcd.h>

// Arduino Uno runs at 16 MHz → 16,000,000 cycles per second.
// 16,000,000 cycles/sec × 1 sec = 16,000,000 cycles
#define WAIT_TIME 1600000 

// Global variable for testing setup and teardown
int test_counter_lcd;
Ucglib_ST7735_18x128x160_HWSPI test_ucg(/*cd=*/ Ucg_pin, /*cs=*/ Ucg_cs, /*reset=*/ Ucg_reset);

void setUp(void) {
  test_ucg.begin(UCG_FONT_MODE_SOLID); //initialization screen
  test_ucg.setRotate90();              //Set to horizontal screen If the screen display direction is reversed, you can modify the function setRotate90 or setRotate270
  test_counter_lcd = 0; //Initialize the test counter
}

void tearDown(void) {
  lcd_cls(&test_ucg);          //Clear the LCD screen
  test_counter_lcd = -1;
}

void test_function_lcd_background(void) 
{
  volatile unsigned long start = 0;
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2;         //Horizontal screen center position
  int base = 118;               //baseline position
  test_counter_lcd++; 
  
  lcd_background(&test_ucg,Xcent,base,Xmax); //Draw the background of the LCD screen

  // Delay to allow visual verification
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly
}

void test_lcd_setup(void) 
{
  volatile unsigned long start = 0;
  test_counter_lcd++; 

  lcd_setup(&test_ucg); //Initialize the LCD screen and set up the initial display
  lcd_cls(&test_ucg);          //Clear the LCD screen
  
   // Delay to allow visual verification 
  while (start < WAIT_TIME)
  {
      start++;
  }  
  
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly  
}

void test_lcd_fix_font(void) 
{
  volatile unsigned long start = 0;
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2;         //Horizontal screen center position
  int base = 118;               //baseline position
  test_counter_lcd++; 
  
  lcd_background(&test_ucg,Xcent,base,Xmax); //Draw the background of the LCD screen

  lcd_fix_font(&test_ucg);  //Repaint screen background elements
  
  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  
  
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly  
}

void test_lcd_PrintRadar(void) 
{
  volatile unsigned long start = 0;
  int degree;
  int distance;
  degree = 45; // Example degree value
  distance = 50; // Example distance value
  test_counter_lcd++; 

  lcd_PrintRadar(&test_ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  
  
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  start = 0;
  test_counter_lcd++; 

  lcd_PrintRadar(&test_ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  
  
  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;

}

void test_lcd_PrintPoint(void) 
{
  volatile unsigned long start = 0; 
  int degree;
  int distance;
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2; //Horizontal screen center position
  int base = 118;               //baseline position

  degree = 45; // Example degree value
  distance = 100; // Example distance value
  test_counter_lcd++; 

  lcd_PrintPoint(&test_ucg, degree, distance, Xcent, base);

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  test_counter_lcd++; 
  start = 0; 

  lcd_PrintPoint(&test_ucg, degree, distance, Xcent, base);  //Repaint screen background elements

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }  

  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;
}

void test_lcd_DrawScanlines(void) 
{
  volatile unsigned long start = 0;
  int degree;
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2; //Horizontal screen center position
  int base = 118;       //baseline position
  int scanline = 105;  
  bool direction;

  degree = 45; // Example degree value
  direction = false; // Example direction value (false for counterclockwise)
  test_counter_lcd++; 

  lcd_DrawScanlines(&test_ucg, degree, Xcent, base, scanline, direction);  //Repaint screen background elements
  
  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }

  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  direction = true; // Example direction value (true for clockwise)
  test_counter_lcd++; 
  start = 0;

  lcd_DrawScanlines(&test_ucg, degree, Xcent, base, scanline, direction);  //Repaint screen background elements

  // Delay to allow visual verification  
  while (start < WAIT_TIME)
  {
      start++;
  }

  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_lcd_setup);
  RUN_TEST(test_function_lcd_background);
  RUN_TEST(test_lcd_fix_font);
  RUN_TEST(test_lcd_PrintRadar);
  RUN_TEST(test_lcd_PrintPoint);
  RUN_TEST(test_lcd_DrawScanlines);
  return UNITY_END();
}



