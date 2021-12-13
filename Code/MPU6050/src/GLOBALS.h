#ifndef GLOBALS_h
#define GLOBALS_h

#define joyX 4
#define joyY 2

#define X 0
#define Y 1
#define Z 2


// MPU Variable
extern float mpuAngle[3]; // 0 = X, 1 = Y, 2 = Z

// Timer Variables
extern unsigned long timeStamp1;
extern unsigned long timeStamp2;
extern unsigned long interval1 = 1000;
extern unsigned long interval2 = 50;

// Joystick Variables
extern int joyXValue, joyYValue;

// Methoden
extern void SensorAuslesen();

#endif