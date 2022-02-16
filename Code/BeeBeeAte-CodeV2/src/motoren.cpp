#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>
#include <PID_v1.h>

int microZeit;

float Ch1PWM = 0;
float Ch2PWM = 0;
float Ch3PWM = 0;
float Ch4PWM = 0;

double motorGain = 9;
double motorStart = 0;

const int motor13Channel = 0;
const int motor24Channel = 1;

const int toterWinkel = 3;

double SetpointY, IstWertY, OutputY;
double SetpointX, IstWertX, OutputX;

PID pidX(&IstWertX, &OutputX, &SetpointX, 8, 0, 0.4, DIRECT);
PID pidY(&IstWertY, &OutputY, &SetpointY, 8, 0, 0.4, DIRECT);

void SetupMotor(){
  SetpointX = 0;
  SetpointY = 0;

    pidX.SetMode(AUTOMATIC);
    pidX.SetOutputLimits(-255, 255);
    pidY.SetMode(AUTOMATIC);
    pidY.SetOutputLimits(-255, 255);

    ledcAttachPin(stepPin1, motor13Channel);
    ledcAttachPin(stepPin3, motor13Channel);

    ledcAttachPin(stepPin2, motor24Channel);
    ledcAttachPin(stepPin4, motor24Channel);

    ledcSetup(motor13Channel, 1000, 8);
    ledcSetup(motor24Channel, 1000, 8);

}

void PIDBerechnung(){
    IstWertX = 0.98*(IstWertX+mpu.getGyroX()*0.01)+0.02*mpu.getAccX();
    pidX.Compute();
    Serial.println(OutputX);
    Ch2PWM = abs(OutputX);
    Ch2PWM = map(Ch2PWM, 0, 255, 0, 1000);
    Ch4PWM = Ch2PWM; 

    IstWertY = 0.98*(IstWertX+mpu.getGyroY()*0.01)+0.02*mpu.getAccY();
    pidY.Compute();
    Ch1PWM = abs(OutputY);
    Ch1PWM = map(Ch1PWM, 0, 255, 0, 1000);
    Ch1PWM = Ch3PWM; 

    ledcSetup(motor13Channel, Ch3PWM, 8);
    ledcSetup(motor24Channel, Ch2PWM, 8);

    SensorAuslesen();

    if (OutputY <= toterWinkel*-1){
        digitalWrite(dirPin1, forward);
        digitalWrite(dirPin3, forward);    
        for (int i = 0; i < 200; i++)
        {
            ledcWrite(motor13Channel, 50);
        }

    }
    else if(OutputY >= toterWinkel){
        digitalWrite(dirPin1, backward);
        digitalWrite(dirPin3, backward);    
        for (int i = 0; i < 200; i++)
        {
            ledcWrite(motor13Channel, 50);
        }
    }
    else{
        ledcWrite(motor13Channel, 0);
    }

    SensorAuslesen();

    if (OutputX <= toterWinkel*-1){
        digitalWrite(dirPin2, forward);
        digitalWrite(dirPin4, forward);    
        for (int i = 0; i < 200; i++)
        {
            ledcWrite(motor24Channel, 50);
        }
    }
    else if(OutputX >= toterWinkel){
        digitalWrite(dirPin2, backward);
        digitalWrite(dirPin4, backward);
        for (int i = 0; i < 200; i++)
        {
            ledcWrite(motor24Channel, 50);
        }
    }
    else{
        ledcWrite(motor24Channel, 0);
    }
}
