#include <io_hw.h> 

// Function prototypes for the IO hardware operations
void iohw_setup(Servo *baseServo);
int iohw_calculateDistance();

/**
 * Function Name: iohw_setup
 *
 * Description: Initialization function, called once at the beginning of the program.
 *
 * @param baseServo: Pointer to the Servo object representing the base servo.
 * @return none
 */
void iohw_setup(Servo *baseServo)
{      
  pinMode(trigPin, OUTPUT);       //Set the trig Pin port mode
  pinMode(echoPin, INPUT);        //Set echo Pin port mode

  baseServo->attach(ServoPin);     //Initialize servos
  baseServo->write(ServoInitAngle);            //Set the initial angle of the servo to 90 degrees

  //Test the operation of the base, pay attention to the position and rotation posture of the base, and whether there is any jamming (or wire winding).
    for (int x = StartServoAngle; x < MaxServoAngle; x += ServoInitStep)
        {
            baseServo->write(x);
            delay(delayTime);
        }
}    


/**
 * Function Name: iohw_calculateDistance
 *
 * Description: This function calculates the distance using the ultrasonic sensor.
 *
 * @param void
 * @return int: The calculated distance in centimeters.
 */
int iohw_calculateDistance()
{ 
    long duration;
    //power off trigPin and wait 2 microseconds
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(Two_us);
    //TrigPin power on delay 10 microseconds and then power off
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(Ten_us);
    digitalWrite(trigPin, LOW);
    //Reading the echoPin returns the travel time of the sound wave (in microseconds)
    duration = pulseIn(echoPin, HIGH);
    //Convert echo time to distance value
    return DISTANCE_CALC(duration);
}