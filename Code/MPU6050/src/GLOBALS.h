#ifndef GLOBALS_H
#define GLOBALS_H


// Motor Pins
#define dirPin1 13 // Direction 1
#define stepPin1 12 // Step 1
#define dirPin2 15  // Direction 2
#define stepPin2 14 // Step 2
#define dirPin3 17  // Direction 3
#define stepPin3 16 // Step 3
#define dirPin4 19  // Direction 4
#define stepPin4 18 // Step 4

// General Indexes
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

// Methoden
extern void SensorAuslesen();
extern void MotorenAnsteuern();

// Motoren
extern const int STEPS_PER_REV;

#endif