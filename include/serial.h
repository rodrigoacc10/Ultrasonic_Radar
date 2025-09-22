#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "USBAPI.h"

/**
 * Function Name: Serial_Init
 *
 * Description: Initialize the serial port for communication.
 *
 * @param void
 * @return none
 */
void Serial_Init(void);

/**
 * Function Name: Serial_PrintRadar
 *
 * Description: Prints the radar data to the serial monitor.
 *
 * @param degree: The angle of the radar scan.
 * @param distance: The measured distance from the radar.
 * @return none
 */
void Serial_PrintRadar(int degree, int distance);

#endif // _SERIAL_H_