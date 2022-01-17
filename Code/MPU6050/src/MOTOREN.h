#ifndef MOTOREN_H
#define MOTOREN_H

// Motor Pins
#define dirPin1 13 // Direction 1
#define stepPin1 12 // Step 1
#define dirPin2 15  // Direction 2
#define stepPin2 14 // Step 2
#define dirPin3 17  // Direction 3
#define stepPin3 16 // Step 3
#define dirPin4 19  // Direction 4
#define stepPin4 18 // Step 4

// Directions
#define forward 0
#define backward 1

// Methoden
extern void MotorenAnsteuern2(int motor1, int motor2, int motorspeed, int direction, int angle);
extern void MotorenAnsteuern4(int motor1, int motor2, int motor3, int motor4, int motorspeed, int direction, int direction2);

#endif