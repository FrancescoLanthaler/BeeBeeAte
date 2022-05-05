#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>

// Frequenzen
int maxFrequenz = 10000;
int offsetFrequenz = 4000;
float Ch1PWM, Ch2PWM;

long winkelX, winkelY;
float x, y, z;

float filterXAlt, filterYAlt;

const int motor12Channel = 0;
const int motor34Channel = 2;

const float toterWinkel = 2.5;

void SetupMotor()
{
    ledcSetup(motor12Channel, 100, 8);
    ledcSetup(motor34Channel, 1000, 8);

    ledcAttachPin(stepPin1, motor12Channel);
    ledcAttachPin(stepPin2, motor12Channel);
    ledcAttachPin(stepPin3, motor34Channel);
    ledcAttachPin(stepPin4, motor34Channel);
}

void WinkelFilter()
{
    mpu.update();
    winkelX = 0.3 * filterXAlt + 0.7 * mpu.getAngleX(); // Filter für Winkel
    winkelY = 0.3 * filterYAlt + 0.7 * mpu.getAngleY();
}

void MotorSteuerung()
{
    Ch1PWM = abs(winkelY * winkelY * 2);    // Kanal 1 Winkel werden auf eine Frequenz angepasst
    Ch1PWM += offsetFrequenz; 

    Ch2PWM = abs(winkelX * winkelX * 2);    // Kanal 2
    Ch2PWM += offsetFrequenz;

    // Serial Output
    Serial.print("Y: ");
    Serial.print(winkelY);
    Serial.print(" X: ");
    Serial.print(winkelX);
    Serial.print("mixY: ");
    Serial.print(Ch1PWM);
    Serial.print(" mixX: ");
    Serial.println(Ch2PWM);

    // Auflösung 8!!!
    ledcSetup(motor12Channel, Ch2PWM, 8);
    ledcSetup(motor34Channel, Ch1PWM, 8);

    // Motor Ansteuerung
    if (winkelX <= toterWinkel * -1)
    {
        digitalWrite(dirPin1, backward);
        digitalWrite(dirPin2, backward);
        ledcWrite(motor12Channel, 50);
    }
    else if (winkelX >= toterWinkel)
    {
        digitalWrite(dirPin1, forward);
        digitalWrite(dirPin2, forward);
        ledcWrite(motor12Channel, 50);
    }
    else
    {
        ledcWrite(motor12Channel, 0);
    }
    if (winkelY <= toterWinkel * -1)
    {
        digitalWrite(dirPin3, forward);
        digitalWrite(dirPin4, forward);
        ledcWrite(motor34Channel, 50);
    }
    else if (winkelY >= toterWinkel)
    {
        digitalWrite(dirPin3, backward);
        digitalWrite(dirPin4, backward);
        ledcWrite(motor34Channel, 50);
    }
    else
    {
        ledcWrite(motor34Channel, 0);
    }
}
