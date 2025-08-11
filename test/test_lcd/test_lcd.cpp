#include <Arduino.h>
#include <unity.h>
#include <lcd.h>

// Global variable for testing setup and teardown
int test_counter;
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ Ucg_pin, /*cs=*/ Ucg_cs, /*reset=*/ Ucg_reset);

void setUp(void) {
  lcd_setup(&ucg); //Initialize the LCD screen
  test_counter = 0; //Initialize the test counter
}

void tearDown(void) {
  lcd_cls(&ucg);          //Clear the LCD screen
  test_counter = -1;
}

void test_function_lcd_background(void) 
{
  int Xmax = 160;               //horizontal pixels of the screen
  int Xcent = Xmax / 2; //Horizontal screen center position
  int base = 118;               //baseline position
  test_counter++; 
  
  lcd_background(&ucg,Xcent,base,Xmax); //Draw the background of the LCD screen
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_lcd_fix_font(void) 
{
  test_counter++; 

  lcd_fix_font(&ucg);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly
}

void test_lcd_PrintRadar(void) 
{
  int degree;
  int distance;
  degree = 45; // Example degree value
  distance = 50; // Example distance value
  test_counter++; 

  lcd_PrintRadar(&ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  test_counter++; 

  lcd_PrintRadar(&ucg, degree, distance); //Print the radar information (degree and distance) on the LCD screen
  TEST_ASSERT_EQUAL(2, test_counter); // Ensure counter updates properly
  test_counter = -1;
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
  test_counter++; 

  lcd_PrintPoint(&ucg, degree, distance, Xcent, base);
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly

  degree = 90; // Example degree value
  distance = 75; // Example distance value
  test_counter++; 

  lcd_PrintPoint(&ucg, degree, distance, Xcent, base);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(2, test_counter); // Ensure counter updates properly
  test_counter = -1;
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
  test_counter++; 

  lcd_DrawScanlines(&ucg, degree, Xcent, base, scanline, direction);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(1, test_counter); // Ensure counter updates properly

  degree = 90; // Example degree value
  direction = true; // Example direction value (true for clockwise)
  test_counter++; 

  lcd_DrawScanlines(&ucg, degree, Xcent, base, scanline, direction);  //Repaint screen background elements
  TEST_ASSERT_EQUAL(2, test_counter); // Ensure counter updates properly
  test_counter = -1;
}

int runUnityTests(void) 
{
  UNITY_BEGIN();
  //RUN_TEST(test_function_lcd_background);
  //RUN_TEST(test_lcd_fix_font);
  //RUN_TEST(test_lcd_PrintRadar);
  //RUN_TEST(test_lcd_PrintPoint);
  //RUN_TEST(test_lcd_DrawScanlines);
  return UNITY_END();
}



