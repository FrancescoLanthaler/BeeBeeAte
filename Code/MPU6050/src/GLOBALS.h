#ifndef GLOBALS_H
#define GLOBALS_H

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
extern unsigned long interval1;
extern unsigned long interval2;

// Joystick Variables
extern int joyXValue, joyYValue;

// Methoden
extern void SensorAuslesen();
// extern void MotorenAnsteuern();

// Motoren
extern const int STEPS_PER_REV;
extern const int dirPin1;  // Direction
extern const int stepPin1; // Step
extern const int dirPin2;  // Direction
extern const int stepPin2; // Step

#endif