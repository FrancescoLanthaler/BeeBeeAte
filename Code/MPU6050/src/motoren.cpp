#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>

void MotorenAnsteuern2(int motor1, int motor2, int motorspeed, int direction)       // Controlling direction of motor
{
    if (direction == forward)
    {
        digitalWrite(motor1 + 1, LOW);
        digitalWrite(motor2 + 1, LOW);
    }
    else
    {
        digitalWrite(motor1 + 1, HIGH);
        digitalWrite(motor2 + 1, HIGH);
    }

    for (int i = 0; i < STEPS_PER_REV; i++) // Rotate motor
    {
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, HIGH);
        delayMicroseconds(motorspeed);
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        delayMicroseconds(motorspeed);
    }
}
