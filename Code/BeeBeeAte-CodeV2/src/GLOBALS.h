#ifndef GLOBALS_H
#define GLOBALS_H

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

// Motoren
extern const int STEPS_PER_REV;
extern const int minWinkel;

#endif