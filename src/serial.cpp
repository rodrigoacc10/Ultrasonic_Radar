#include <serial.h>

// Function prototypes for serial communication
void Init_Serial(void);
void Serial_PrintRadar(int degree, int distance);

// Define the baud rate for serial communication
#define BaudRate 115200

/**
 * Function Name: Serial_Init
 *
 * Description: Initialize the serial port for communication.
 *
 * @param void
 * @return none
 */
void Serial_Init(void)
{
    //Set the serial port transmission rate
    Serial.begin(BaudRate);
}

/**
 * Function Name: Serial_PrintRadar
 *
 * Description: Prints the radar data to the serial monitor.
 *
 * @param degree: The angle of the radar scan.
 * @param distance: The measured distance from the radar.
 * @return none
 */
void Serial_PrintRadar(int degree, int distance)
{
    //Debug code, output angle and range value
    Serial.print("Degree:  ");
    Serial.print(degree); 
    Serial.print("    ,Distance:   ");
    Serial.println(distance); 
}