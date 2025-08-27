// Description: Ultrasonic Radar Distance Measurement and Servo Control
//This program is used to control the ultrasonic radar distance measurement and servo steering gear control, and display the distance value on the LCD screen.
#include <Servo.h> 
#include <SPI.h>
#include <Ucglib.h>     
#include <lcd.h>
#include <serial.h>
#include <io_hw.h>

// Define the screen dimensions and other constants
int Ymax = 128;               //vertical pixels of the screen
int Xmax = 160;               //horizontal pixels of the screen
int Xcent = Xmax / ServoStep; //Horizontal screen center position
int base = 118;               //baseline position
int scanline = 105;           //Radar scan line length

// Messages to display
const char* message1[2] = {"Embeded Pipeline", "Cloud to Hardware"};
const char* message2[2] = {"Github:", "lruizv"};
const char* message3[2] = {"Github:", "rodrigoacc10"};

// Define the servo object and LCD object
Servo baseServo; 
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ Ucg_pin, /*cs=*/ Ucg_cs, /*reset=*/ Ucg_reset);

/**
 * Function Name: setup
 *
 * Description: Initialization function, called once at the beginning of the program.
 *
 * @param void
 * @return none
 */
void setup(void)
{ 
  // Welcome Message Function have high Memory Usage, read the requirements for more information
  lcd_initialize(&ucg, message1, message2, message3); //Initialize the LCD screen and display welcome messages
  Serial_Init(); //Initialize the Serial Rate
  lcd_setup(&ucg); //Initialize the LCD screen
  iohw_setup(&baseServo); //Initialize the IO hardware, including the servo and ultrasonic module
}    

/**
 * Function Name: loop
 *
 * Description: Main loop function, called repeatedly after setup.
 *
 * @param void
 * @return none
 */
void loop(void)
{
  int distance = 0; //Variable to store the distance value
  
  lcd_background(&ucg,Xcent,base,Xmax); //Draw the background of the LCD screen
  lcd_fix_font(&ucg);  //Repaint screen background elements

  for (int x=MaxServoAngle; x > MinServoAngleRange; x-=ServoStep) //The base servo rotates from 180 to 0 degrees
    {       
      //Adjust the steering gear angle
      baseServo.write(x);
      
      //Draw Radar Scanlines
      lcd_DrawScanlines(&ucg,x,Xcent,base,scanline,false);  
      
      //Get the distance value
      distance = iohw_calculateDistance();
    
      //Debug code, output angle and range value
      Serial_PrintRadar(x, distance);

      //Draw the point corresponding to the distance value
      lcd_PrintPoint(&ucg,x,distance,Xcent,base);

      delay(delayMovement);     //Delay for Movement

    }

  delay(delayTime);     //Delay for a while to allow the servo to stabilize
  lcd_cls(&ucg);          //Clear the LCD screen
  lcd_background(&ucg,Xcent,base,Xmax); //Draw the background of the LCD screen
  lcd_fix_font(&ucg);          //Repaint screen background elements
  delay(delayTime);     //Delay for a while to allow the servo to stabilize
  
  for (int  x=MinServoAngle; x < MaxServoAngleRange; x+=ServoStep)
    {     
      //Adjust the steering gear angle
      baseServo.write(x);
        
      //Draw Radar Scanlines
      lcd_DrawScanlines(&ucg,x,Xcent,base,scanline,true);  
      
      //Get the distance value
      distance = iohw_calculateDistance();

      //Debug code, output angle and range value
      Serial_PrintRadar(x, distance);
      
      //Draw the point corresponding to the distance value
      lcd_PrintPoint(&ucg,x,distance,Xcent,base);

      delay(delayMovement);     //Delay for Movement
            
    }

  delay(delayTime);   //Delay for a while to allow the servo to stabilize
  lcd_cls(&ucg);      //Clear the LCD screen

}