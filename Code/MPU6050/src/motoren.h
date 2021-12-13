#ifndef motoren_h
#define motoren_h

extern const int STEPS_PER_REV = 1000;

extern const int dirPin1 = 18;  // Direction
extern const int stepPin1 = 5; // Step
extern const int dirPin2 = 18;  // Direction
extern const int stepPin2 = 5; // Step


extern void MotorenAnsteuern();

#endif