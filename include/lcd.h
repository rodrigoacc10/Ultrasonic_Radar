#ifndef _LCD_H_
#define _LCD_H_

#include <Ucglib.h>

#define  Ucg_pin 9 //Ucg pin for LCD control
#define  Ucg_cs 10 //Ucg chip select pin for LCD control
#define  Ucg_reset 8 //Ucg reset pin for LCD control

/**
 * Function Name: lcd_setup   
 *
 * Description: Initializes the LCD screen and sets up the initial display.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_setup(Ucglib_ST7735_18x128x160_HWSPI *ucg);

/**
 * Function Name: lcd_cls
 *
 * Description: Clears the LCD screen by drawing boxes to fill the screen with a black color.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_cls(Ucglib_ST7735_18x128x160_HWSPI *ucg);
/**
 * Function Name: fix_font
 *
 * Description: This function sets the font color and prints fixed text on the LCD screen.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_fix_font(Ucglib_ST7735_18x128x160_HWSPI *ucg);
/**
 * Function Name: lcd_background
 *
 * Description: This function draws a background image and scale on the LCD screen.
 *
 * @param  ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @param  Xcent: The x-coordinate of the center of the background image.
 * @param  base: The y-coordinate of the base line for the background image.
 * @param  Xmax: The maximum x-coordinate for the background image.
 * @return none
 */
void lcd_background(Ucglib_ST7735_18x128x160_HWSPI *ucg,int Xcent,int base,int Xmax);
/**
 * Function Name: lcd_PrintRadar
 *
 * Description: Prints the radar information (degree and distance) on the LCD screen.
 *
 * @param  ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @param  degree: The angle in degrees.
 * @param  distance: The distance measured in centimeters.
 * @return none
 */
void lcd_PrintRadar(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance);
/**
 * Function Name: lcd_PrintPoint
 *
 * Description: Prints the radar information (degree and distance) on the LCD screen.
 *
 * @param  ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @param  degree: The angle in degrees.
 * @param  distance: The distance measured in centimeters.
 * @param  Xcent: The x-coordinate of the center of the radar display.
 * @param  base: The y-coordinate of the base line for the radar display.
 * @return none
 */
void lcd_PrintPoint(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance,int Xcent,int base);
/**
 * Function Name: lcd_DrawScanlines
 *
 * Description: Draws radar scanlines on the LCD screen based on the given angle, center coordinates, base line, and scanline length.
 *
 * @param  ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @param  degree: The angle in degrees.
 * @param  Xcent: The x-coordinate of the center of the radar display.
 * @param  base: The y-coordinate of the base line for the radar display.
 * @param  scanline: The length of the scanline.
 * @param  direction: A boolean indicating the direction of the scanline (true for clockwise, false for counterclockwise).
 * @return none
 */
void lcd_DrawScanlines(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree,int Xcent,int base,int scanline,bool direction);
/**
 * Function Name: lcd_initialize
 *
 * Description: This function initializes the LCD screen and displays a series of messages with effects.
 *                                                                  
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.                        
 * @return none
 */
void lcd_initialize(Ucglib_ST7735_18x128x160_HWSPI *ucg,const char *message1[], const char *message2[], const char *message3[]);
#endif // _LCD_H_