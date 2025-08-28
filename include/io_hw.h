#ifndef _IO_HW_H_
#define _IO_HW_H_

#include <Servo.h> 
#include <Arduino.h>

// Define the speed of sound in air (in cm/us)
// The speed of sound is approximately 343 meters per second, which is 0.0343 cm/us.
// The formula for calculating distance is: distance = (duration * speed of sound)
// Since the ultrasonic sensor measures the round trip time, we divide by 2 to get the one-way distance.
#define DISTANCE_CALC(duration) ((duration) * 0.034 / 2)

// Define the pins for the ultrasonic module and servo
#define  trigPin   6          //Ultrasonic Module Trig->D6
#define  echoPin   5          //Ultrasonic Module Echo->D5
#define  Ten_us 10          //Delay time for ultrasonic module in microseconds
#define  Two_us 2           //Delay time for ultrasonic module in microseconds

#define  ServoPin  3          //Servo Signal->D3
#define  MaxServoAngle 180    //Maximum servo angle
#define  MinServoAngle 1      //Minimum servo angle
#define  StartServoAngle 0      //Starting servo angle
#define  MaxServoAngleRange 176    //Maximum servo angle range
#define  MinServoAngleRange 4      //Minimum servo angle range
#define  ServoStep 2         //Servo step size for each iteration
#define  ServoInitStep 5    //Initial servo step size for the first iteration
#define  ServoInitAngle 90   //Initial servo angle
#define  delayTime 50         //Delay time for servo movement
#define  delayMovement 5         //Delay time for servo movement
/**
 * Function Name: iohw_setup
 *
 * Description: Initialization function, called once at the beginning of the program.
 *
 * @param baseServo: Pointer to the Servo object representing the base servo.
 * @return none
 */
void iohw_setup(Servo *baseServo);

/**
 * Function Name: iohw_calculateDistance
 *
 * Description: This function calculates the distance using the ultrasonic sensor.
 *
 * @param void
 * @return int: The calculated distance in centimeters.
 */
int iohw_calculateDistance();

#endif // _IO_HW_H_