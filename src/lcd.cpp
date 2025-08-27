#include <lcd.h>

// Function prototypes for the LCD operations
void lcd_cls(Ucglib_ST7735_18x128x160_HWSPI *ucg);
void lcd_setup(Ucglib_ST7735_18x128x160_HWSPI *ucg);
void lcd_fix_font(Ucglib_ST7735_18x128x160_HWSPI *ucg);
void lcd_background(Ucglib_ST7735_18x128x160_HWSPI *ucg,int Xcent,int base,int Xmax);
void lcd_PrintRadar(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance);
void lcd_PrintPoint(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance,int Xcent,int base);
void lcd_DrawScanlines(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree,int Xcent,int base,int scanline,bool direction);
void lcd_initialize(Ucglib_ST7735_18x128x160_HWSPI *ucg,const char *message1[], const char *message2[], const char *message3[]);

// Function prototypes for scanline calculations
int lcd_calculate_scanline_initial(int x, bool add); 
int lcd_calculate_scanline_step(int x, bool add);
void lcd_displayTextWithEffectsInTwoLines(const char *message[], int duration);

/**
 * Function Name: lcd_cls
 *
 * Description: Clears the LCD screen by drawing boxes to fill the screen with a black color.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_cls(Ucglib_ST7735_18x128x160_HWSPI *ucg)
{
    //clear screen
    ucg->setColor(0, 0, 0, 0);

    for (int s = 0; s < 128; s += 8)
        {
            for (int t = 0; t < 160; t += 16)
            {
                ucg->drawBox(t, s, 16, 8);
                // delay(1);
            }
        }
}

/**
 * Function Name: lcd_setup   
 *
 * Description: Initializes the LCD screen and sets up the initial display.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_setup(Ucglib_ST7735_18x128x160_HWSPI *ucg)
{
    ucg->begin(UCG_FONT_MODE_SOLID); //initialization screen
    ucg->setRotate90();              //Set to horizontal screen If the screen display direction is reversed, you can modify the function setRotate90 or setRotate270

    //screen startup interface
    ucg->setFontMode(UCG_FONT_MODE_TRANSPARENT);
    ucg->setColor(0, 0, 100, 0);
    ucg->setColor(1, 0, 100, 0);
    ucg->setColor(2, 20, 20, 20);
    ucg->setColor(3, 20, 20, 20);
    ucg->drawGradientBox(0, 0, 160, 128);
    ucg->setPrintDir(0);
    ucg->setColor(0, 5, 0);
    ucg->setPrintPos(27, 42);
    ucg->setFont(ucg_font_logisoso18_tf);
    ucg->print("Mini Radar Kit");
    ucg->setColor(0, 255, 0);
    ucg->setPrintPos(25, 40);
    ucg->print("Mini Radar");
    ucg->setFont(ucg_font_helvB08_tf);
    ucg->setColor(0, 255, 0);
    ucg->setPrintPos(40, 100);
    ucg->print("Initializing...");

    ucg->setColor(0, 255, 0);

    ucg->print("OK!");
    //delay(500);
    ucg->setColor(0, 0, 0, 0);
    ucg->setColor(1, 0, 0, 0);
    ucg->setColor(2, 0, 0, 0);
    ucg->setColor(3, 0, 0, 0);

    lcd_cls(ucg);

    ucg->setFont(ucg_font_orgv01_hr);
    ucg->setFontMode(UCG_FONT_MODE_SOLID);
}

/**
 * Function Name: fix_font
 *
 * Description: This function sets the font color and prints fixed text on the LCD screen.
 *
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.
 * @return none
 */
void lcd_fix_font(Ucglib_ST7735_18x128x160_HWSPI *ucg)
{
    ucg->setColor(0, 180, 0);
    ucg->setPrintPos(70,128-120+7);
    ucg->print("100cm");
    ucg->setPrintPos(70,128-85-11);
    ucg->print("75cm");
    ucg->setPrintPos(70,128-60-8);
    ucg->print("50cm");
    ucg->setPrintPos(70,128-35-4);
    ucg->print("25cm");
}

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
void lcd_background(Ucglib_ST7735_18x128x160_HWSPI *ucg,int Xcent,int base,int Xmax)
{
    ucg->setColor(0, 40, 0);
    //Draw a background image
    ucg->drawDisc(Xcent, base+1, 3, UCG_DRAW_ALL); 
    ucg->drawCircle(Xcent, base+1, 115, UCG_DRAW_UPPER_LEFT);
    ucg->drawCircle(Xcent, base+1, 115, UCG_DRAW_UPPER_RIGHT);
    ucg->drawCircle(Xcent, base+1, 86, UCG_DRAW_UPPER_LEFT);
    ucg->drawCircle(Xcent, base+1, 86, UCG_DRAW_UPPER_RIGHT);
    ucg->drawCircle(Xcent, base+1, 58, UCG_DRAW_UPPER_LEFT);
    ucg->drawCircle(Xcent, base+1, 58, UCG_DRAW_UPPER_RIGHT);
    ucg->drawCircle(Xcent, base+1, 29, UCG_DRAW_UPPER_LEFT);
    ucg->drawCircle(Xcent, base+1, 29, UCG_DRAW_UPPER_RIGHT);
    ucg->drawLine(0, base+1, Xmax,base+1);

    ucg->setColor(0, 120, 0);
    //draw scale
    for(int i= 40;i < 140; i+=2)
        {

            if (i % 10 == 0)
            {
                ucg->drawLine(105*cos(radians(i))+Xcent,base - 105*sin(radians(i)) , 113*cos(radians(i))+Xcent,base - 113*sin(radians(i)));
            }
        else
            {
                ucg->drawLine(110*cos(radians(i))+Xcent,base - 110*sin(radians(i)) , 113*cos(radians(i))+Xcent,base - 113*sin(radians(i)));
            }
        }

    //draw some decorative patterns
    ucg->setColor(0,200,0);
    ucg->drawLine(0,0,0,18);
    for(int i= 0;i < 5; i++)
        {
            ucg->setColor(random(255),random(255),random(255));
            ucg->drawBox(2,i*4,random(14)+2,3);
        }

    ucg->setColor(0,0,180);
    ucg->drawFrame(146,0,14,14);
    ucg->setColor(0,0,60);
    ucg->drawHLine(148,0,10);
    ucg->drawVLine(146,2,10);
    ucg->drawHLine(148,13,10);
    ucg->drawVLine(159,2,10);
    ucg->setColor(random(255),random(255),random(255));
    //ucg->setColor(0,220,0);
    ucg->drawBox(148,2,4,4);
    ucg->setColor(0,220,0);
    ucg->drawBox(148,8,4,4);
    ucg->setColor(random(255),random(255),random(255));
    //ucg->setColor(100,0,0);
    ucg->drawBox(154,8,4,4);
    ucg->setColor(random(255),random(255),random(255));
    //ucg->setColor(0,0,150);
    ucg->drawBox(154,2,4,4);
    ucg->setColor(0,0,90);
    ucg->drawTetragon(62,123,58,127,98,127,102,123);
    ucg->setColor(0,0,160);
    ucg->drawTetragon(67,123,63,127,93,127,97,123);
    ucg->setColor(0,255,0);
    ucg->drawTetragon(72,123,68,127,88,127,92,123);
}

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
void lcd_PrintRadar(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance)
{
    ucg->setColor(0,0,155,  0);
    ucg->setPrintPos(0,126);
    ucg->print("DEG: "); 
    ucg->setPrintPos(24,126);
    ucg->print(degree);
    ucg->print("   ");
    ucg->setPrintPos(125,126);
    ucg->print("   ");
    ucg->print(distance);
    ucg->print("cm   "); 
}

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
void lcd_PrintPoint(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree, int distance,int Xcent,int base)
{
    //Draw a point at the corresponding position according to the measured distance
    if (distance < 100)
    {
        ucg->setColor(255,0,0);
        ucg->drawDisc(1.15*distance*cos(radians(degree))+Xcent,-(1.15*distance*sin(radians(degree)))+base, 1, UCG_DRAW_ALL);
    }
    else
    { //If it is more than 1 meter, it is indicated by a yellow painting on the edge area
        ucg->setColor(255,255,0);
        ucg->drawDisc(116*cos(radians(degree))+Xcent,-116*sin(radians(degree))+base, 1, UCG_DRAW_ALL);
    }
            
    if (degree > 70 and degree < 110)
    {
        lcd_fix_font(ucg);  //When the scan line and the number coincide, redraw the number
    }            

    lcd_PrintRadar(ucg,degree, distance); //Print the angle and distance on the LCD screen
}


/**
 * Function Name: lcd_calculate_scanline_initial
 *
 * Description: Calculates the initial step for the scanline based on the given x-coordinate and a boolean indicating whether to add or subtract.
 *
 * @param  x: The x-coordinate to be used in the calculation.
 * @param  add: A boolean indicating whether to add or subtract the value from x.
 * @return The calculated step value for the scanline.
 */
int lcd_calculate_scanline_initial(int x, bool add) 
{
    if (add) {
        return x + 4;  // If `add` is true, perform addition
    } else {
        return x - 4;  // If `add` is false, perform subtraction
    }
}

/**
 * Function Name: lcd_calculate_scanline_step
 *
 * Description: Calculates the step for the scanline based on the given x-coordinate and a boolean indicating whether to add or subtract.
 *
 * @param  x: The x-coordinate to be used in the calculation.
 * @param  add: A boolean indicating whether to add or subtract the value from x.
 * @return The calculated step value for the scanline.
 */
int lcd_calculate_scanline_step(int x, bool add) 
{
    if (add) {
        return x + 2;  // If `add` is true, perform addition
    } else {
        return x - 2;  // If `add` is false, perform subtraction
    }
}

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
void lcd_DrawScanlines(Ucglib_ST7735_18x128x160_HWSPI *ucg,int degree,int Xcent,int base,int scanline,bool direction)
{
    //Draw Radar Scanlines
    int f = lcd_calculate_scanline_initial(degree, direction);
    ucg->setColor(0, 255, 0);
    ucg->drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
    f=lcd_calculate_scanline_step(degree, direction);
    ucg->setColor(0, 128, 0);
    ucg->drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
    f=lcd_calculate_scanline_step(degree, direction);
    ucg->setColor(0, 0, 0);
    ucg->drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
    ucg->setColor(0, 200, 0);
}


/**
 * Function Name:  lcd_displayTextWithEffectsInTwoLines
 *
 * Description: This function displays text on the LCD screen with effects such as fading and movement.
 *
 *                                                                  
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.                        
 * @param message: An array of two strings to be displayed on the screen.
 * @param duration: The duration for which the text will be displayed with effects.
 * @return none
 */
void lcd_displayTextWithEffectsInTwoLines(Ucglib_ST7735_18x128x160_HWSPI *ucg,const char *message[], int duration) 
{    
    int yOffset = 0;

    ucg->clearScreen();                 // Clear the screen before starting the effects

    ucg->begin(UCG_FONT_MODE_SOLID);    // Initialize the Ucglib object
    ucg->setRotate90();                 // Set the display orientation to horizontal

    // Set the background color for the screen
    ucg->setColor(0, 0, 100, 0);
    ucg->setColor(1, 0, 100, 0);
    ucg->setColor(2, 20, 20, 20);
    ucg->setColor(3, 20, 20, 20);
    ucg->drawGradientBox(0, 0, 160, 128);

    // Set the color for the text
    ucg->setColor(255, 0, 0);

    // Font settings
     ucg->setFont(ucg_font_ncenR12_tr); // Font style

    // Movement effect (vertical offset)
    yOffset = 0;

    // Print the first line of text with an offset
    ucg->setPrintPos(10, 60 + yOffset);           // Set position for first line
    ucg->print(message[0]);                      // Print first line of text

    // Movement effect (vertical offset)
    yOffset = 0;

    // Print the second line of text with an offset
    ucg->setPrintPos(10, 100 + yOffset);         // Set position for second line
    ucg->print(message[1]);                      // Print second line of text

    // Small delay to slow effects
     delay(duration);
    
}

/**
 * Function Name: lcd_initialize
 *
 * Description: This function initializes the LCD screen and displays a series of messages with effects.
 *                                                                  
 * @param ucg: Pointer to the Ucglib_ST7735_18x128x160_HWSPI object.                        
 * @return none
 */
void lcd_initialize(Ucglib_ST7735_18x128x160_HWSPI *ucg,const char *message1[], const char *message2[], const char *message3[])
{
    int displayTime = 2500; // Duration for each message display in milliseconds

    // Display the first message with effects
    lcd_displayTextWithEffectsInTwoLines(ucg,message1, displayTime);

    // Display the second message with effects
    lcd_displayTextWithEffectsInTwoLines(ucg,message2, displayTime);

    // Display the third message with effects
    lcd_displayTextWithEffectsInTwoLines(ucg,message3, displayTime);
}