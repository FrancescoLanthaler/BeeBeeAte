#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>
#include <PID_v1.h>

int microZeit;
int maxFrequenz = 7000;

float Ch1PWM = 0;
float Ch2PWM = 0;
float Ch3PWM = 0;
float Ch4PWM = 0;

float winkelX;
float winkelY;
float x;
float y;
float z;

float istBerechnungX, istBerechnungY, GyroX, GyroY, filterXAlt, filterYAlt;


const int motor12Channel = 0;
const int motor34Channel = 1;

const int toterWinkel = 4;

const int stepsPerRev = 1000;

double SetpointY, IstWertY, OutputY;
double SetpointX, IstWertX, OutputX;

PID pidX(&IstWertX, &OutputX, &SetpointX, 12, 0.5, 2, DIRECT);
PID pidY(&IstWertY, &OutputY, &SetpointY, 12, 0.5, 2, DIRECT);

void SetupMotor(){
  SetpointX = 0;
  SetpointY = 0;

    pidX.SetMode(AUTOMATIC);
    pidX.SetOutputLimits(-255, 255);
    pidY.SetMode(AUTOMATIC);
    pidY.SetOutputLimits(-255, 255);

    pidX.SetSampleTime(10);
    pidY.SetSampleTime(10);

    ledcSetup(motor12Channel, maxFrequenz, 8);
    ledcSetup(motor34Channel, maxFrequenz, 8);

    ledcAttachPin(stepPin1, motor12Channel);
    ledcAttachPin(stepPin2, motor12Channel);


    ledcAttachPin(stepPin3, motor34Channel);
    ledcAttachPin(stepPin4, motor34Channel);

}

void SensorAusrechnung()
{
    mpu.update();

    winkelX = 0.3 * filterXAlt + 0.7 * mpu.getAngleX(); // Filter für Winkel
    winkelY = 0.3 * filterYAlt + 0.7 * mpu.getAngleY();

    istBerechnungX = 0.85  *(istBerechnungX+mpu.getAccX()*dt) + 0.15*winkelX;       // Filter und Mix von Winkel und Beschleunigung
    istBerechnungY = 0.85 *(istBerechnungY+mpu.getAccY()*dt) + 0.15*winkelY;
}

void PIDBerechnung(){
    //PID-Loop berechnung
    IstWertY = istBerechnungY;
    pidY.Compute();
    Ch1PWM = abs(OutputY);
    Ch1PWM = map(Ch1PWM, 0, 255, 3000, maxFrequenz);        // PID Output wird auf eine Frequenz aufgespreitzt

    IstWertX = istBerechnungX;
    pidX.Compute();
    Ch2PWM = abs(OutputX);
    Ch2PWM = map(Ch2PWM, 0, 255, 3000, maxFrequenz);

    // Serial Output
    Serial.print("Y: ");
    Serial.print(winkelY);
    Serial.print(" X: ");
    Serial.print(winkelX);
    Serial.print("mixY: ");
    Serial.print(mpu.getAngleY());
    Serial.print(" mixX: ");
    Serial.println(mpu.getAngleX());

    // Auflösung 8!!!
    ledcSetup(motor12Channel, Ch1PWM, 8);
    ledcSetup(motor34Channel, Ch2PWM, 8);

    // Motor Ansteuerung
    if (winkelX <= toterWinkel*-1){
        digitalWrite(dirPin1, backward);
        digitalWrite(dirPin2, backward);    
        ledcWrite(motor12Channel, 50); 
    }
    else if(winkelX >= toterWinkel){
        digitalWrite(dirPin1, forward);
        digitalWrite(dirPin2, forward);    
        ledcWrite(motor12Channel, 50);
    }
    else{
        ledcWrite(motor12Channel, 0);
    }
    if (winkelY <= toterWinkel*-1){
        digitalWrite(dirPin3, forward);
        digitalWrite(dirPin4, forward); 
        ledcWrite(motor34Channel, 50);
    }
    else if(winkelY >= toterWinkel){
        digitalWrite(dirPin3, backward);
        digitalWrite(dirPin4, backward);    
        ledcWrite(motor34Channel, 50);
    }
    else{   
        ledcWrite(motor34Channel, 0);
    }
}
