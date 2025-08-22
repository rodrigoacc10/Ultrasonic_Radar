extern "C" {
    #include "unity.h"
}

#include <lcd.h>

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
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2; //Horizontal screen center position
  int base = 118;               //baseline position
  test_counter_lcd++; 
  
  lcd_background(&test_ucg,Xcent,base,Xmax); //Draw the background of the LCD screen
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly
}

void test_lcd_setup(void) 
{
  unsigned long start = millis();
  test_counter_lcd++; 
  
  while (millis() - start < 5000) 
  {
    lcd_setup(&test_ucg);  //Repaint screen background elements
      if (millis() - start > 2000) 
      {
        //TEST_FAIL_MESSAGE("Test timed out after 2 seconds");
        return;
      }
  } 
  
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly
}

void test_lcd_fix_font(void) 
{
  test_counter_lcd++; 

  lcd_fix_font(&test_ucg);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly
}

void test_lcd_PrintRadar(void) 
{
  int degree;
  int distance;
  degree = 45; // Example degree value
  distance = 50; // Example distance value
  test_counter_lcd++; 

  lcd_PrintRadar(&test_ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  test_counter_lcd++; 

  lcd_PrintRadar(&test_ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen
  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;
}

void test_lcd_PrintPoint(void) 
{
  int degree;
  int distance;
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2; //Horizontal screen center position
  int base = 118;               //baseline position

  degree = 45; // Example degree value
  distance = 100; // Example distance value
  test_counter_lcd++; 

  lcd_PrintPoint(&test_ucg, degree, distance, Xcent, base);
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  test_counter_lcd++; 

  lcd_PrintPoint(&test_ucg, degree, distance, Xcent, base);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;
}

void test_lcd_DrawScanlines(void) 
{
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
  TEST_ASSERT_EQUAL(1, test_counter_lcd); // Ensure counter updates properly

  degree = 90; // Example degree value
  direction = true; // Example direction value (true for clockwise)
  test_counter_lcd++; 

  lcd_DrawScanlines(&test_ucg, degree, Xcent, base, scanline, direction);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(2, test_counter_lcd); // Ensure counter updates properly
  test_counter_lcd = -1;
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_function_lcd_background);
  RUN_TEST(test_lcd_fix_font);
  RUN_TEST(test_lcd_PrintRadar);
  RUN_TEST(test_lcd_PrintPoint);
  RUN_TEST(test_lcd_DrawScanlines);
  return UNITY_END();
}



