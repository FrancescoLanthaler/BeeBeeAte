#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>

int microZeit;

void MotorenAnsteuern2(int motor1, int motor2, int motorspeed, int direction, int angle) // Controlling direction of motor
{
    digitalWrite(motor1 + 1, direction);
    digitalWrite(motor2 + 1, direction);

    for (int i = 0; i < STEPS_PER_REV; i++) // Rotate motor
    {
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, HIGH);
        SensorAuslesen();
        if (mpuAngle[angle] < 5.0 && mpuAngle[angle] > -5.0)
            return;
        
        delayMicroseconds(100);
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        SensorAuslesen();
        if (mpuAngle[angle] < 5.0 && mpuAngle[angle] > -5.0)
            return;
        delayMicroseconds(100);
        
    }
}

void MotorenAnsteuern4(int motor1, int motor2, int motor3, int motor4, int motorspeed, int direction, int direction2) // Controlling direction of motor
{
    digitalWrite(motor1 + 1, direction);
    digitalWrite(motor2 + 1, direction);
    digitalWrite(motor3 + 1, direction2);
    digitalWrite(motor4 + 1, direction2);

    for (int i = 0; i < STEPS_PER_REV; i++) // Rotate motor
    {
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, HIGH);
        digitalWrite(motor3, HIGH);
        digitalWrite(motor4, HIGH);
        SensorAuslesen();
        if ((mpuAngle[X] < 5.0 && mpuAngle[X] > -5.0) || (mpuAngle[Y] < 5.0 && mpuAngle[Y] > -5.0))
            return;
        delayMicroseconds(500);

        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        digitalWrite(motor3, LOW);
        digitalWrite(motor4, LOW);
        SensorAuslesen();
        if ((mpuAngle[X] < 5.0 && mpuAngle[X] > -5.0) || (mpuAngle[Y] < 5.0 && mpuAngle[Y] > -5.0))
            return;
        delayMicroseconds(500);



        
    }
}
