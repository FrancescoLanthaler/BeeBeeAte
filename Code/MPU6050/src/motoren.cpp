#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>

void MotorenAnsteuern2(int motor1, int motor2, int motorspeed, int direction, int angle) // Controlling direction of motor
{
    digitalWrite(motor1 + 1, direction);
    digitalWrite(motor2 + 1, direction);

    for (int i = 0; i < STEPS_PER_REV; i++) // Rotate motor
    {
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, HIGH);
        delayMicroseconds(motorspeed);
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        delayMicroseconds(motorspeed);
        SensorAuslesen();
        if (mpuAngle[angle] < 5.0 && mpuAngle[angle] > -5.0)
            return;
        if (mpuAngle[X] < minWinkel && mpuAngle[Y] < minWinkel)
        {
            speedMicro = SpeedBerechnung(mpuAngle[X]);
            MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, forward, forward);
        }

        else if (mpuAngle[X] > maxWinkel && mpuAngle[Y] > maxWinkel)
        {
            speedMicro = SpeedBerechnung(mpuAngle[X]);
            MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, backward, backward);
        }

        else if (mpuAngle[X] < minWinkel && mpuAngle[Y] > maxWinkel)
        {
            speedMicro = SpeedBerechnung(mpuAngle[X]);
            MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, forward, backward);
        }

        else if (mpuAngle[X] > maxWinkel && mpuAngle[Y] < minWinkel)
        {
            speedMicro = SpeedBerechnung(mpuAngle[X]);
            MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, backward, forward);
        }
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
        delayMicroseconds(motorspeed);
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
        digitalWrite(motor3, LOW);
        digitalWrite(motor4, LOW);
        delayMicroseconds(motorspeed);
        SensorAuslesen();
        if ((mpuAngle[X] < 5.0 && mpuAngle[X] > -5.0) || (mpuAngle[Y] < 5.0 && mpuAngle[Y] > -5.0))
            return;
    }
}
