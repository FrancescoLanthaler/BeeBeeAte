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

// PID
extern double SetpointY, IstWertY, OutputY;
extern double SetpointX, IstWertX, OutputX;


// Motoren
extern double motorGain;
extern double motorStart;

extern const int motor12Channel;
extern const int motor34Channel;

extern const int toterWinkel;

// Methoden
extern void PIDBerechnung();
extern void SetupMotor();
extern void SensorAusrechnung();
#endif