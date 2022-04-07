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

float pitchAccel;
float rollAccel;
float x;
float y;
float z;

float istBerechnungX, istBerechnungY, GyroX, GyroY;


const int motor13Channel = 0;
const int motor24Channel = 1;

const int toterWinkel = 5;

const int stepsPerRev = 1000;

double SetpointY, IstWertY, OutputY;
double SetpointX, IstWertX, OutputX;

PID pidX(&IstWertX, &OutputX, &SetpointX, 12, 0, 0.1, DIRECT);
PID pidY(&IstWertY, &OutputY, &SetpointY, 12, 0, 0.1, DIRECT);

void SetupMotor(){
  SetpointX = 0;
  SetpointY = 0;

    pidX.SetMode(AUTOMATIC);
    pidX.SetOutputLimits(-255, 255);
    pidY.SetMode(AUTOMATIC);
    pidY.SetOutputLimits(-255, 255);

    pidX.SetSampleTime(10);
    pidY.SetSampleTime(10);

    ledcSetup(motor13Channel, maxFrequenz, 8);
    ledcSetup(motor24Channel, maxFrequenz, 8);

    ledcAttachPin(stepPin1, motor13Channel);
    ledcAttachPin(stepPin2, motor13Channel);


    ledcAttachPin(stepPin3, motor24Channel);
    ledcAttachPin(stepPin4, motor24Channel);

}

void SensorAusrechnung()
{
    mpu.update();
    GyroY = mpu.getGyroX();         // read X Gyro into Y variable and vice versa
    GyroX = mpu.getGyroY(); 

    GyroX *= -1,

    istBerechnungX = 0.9  *(istBerechnungX+GyroX*dt) + 0.1*mpu.getAngleX();       // Complimentary filter for Y, mix Gyro and Accel with average over time dt
    istBerechnungY = 0.9 *(istBerechnungY+GyroY*dt) + 0.1*mpu.getAngleY();
}

void PIDBerechnung(){
    IstWertY = istBerechnungY;
    pidY.Compute();
    Ch1PWM = abs(OutputY);
    Ch1PWM = map(Ch1PWM, 0, 255, 5000, maxFrequenz);

    IstWertX = istBerechnungX;
    pidX.Compute();
    Ch2PWM = abs(OutputX);
    Ch2PWM = map(Ch2PWM, 0, 255, 5000, maxFrequenz);


    Serial.print("Y: ");
    Serial.print(OutputY);
    Serial.print(" X: ");
    Serial.print(OutputX);
    Serial.print("mixY: ");
    Serial.print(istBerechnungY);
    Serial.print(" mixX: ");
    Serial.println(istBerechnungX);

    ledcSetup(motor13Channel, Ch1PWM, 8);
    ledcSetup(motor24Channel, Ch2PWM, 8);


    if (OutputX <= toterWinkel*-1){
        digitalWrite(dirPin1, backward);
        digitalWrite(dirPin3, backward);    
        ledcWrite(motor13Channel, 50); 
    }
    else if(OutputX >= toterWinkel){
        digitalWrite(dirPin1, forward);
        digitalWrite(dirPin3, forward);    
        ledcWrite(motor13Channel, 50);
    }
    else{
        ledcWrite(motor13Channel, 0);
    }

    if (OutputY <= toterWinkel*-1){
        digitalWrite(dirPin2, forward);
        digitalWrite(dirPin4, forward); 
        ledcWrite(motor24Channel, 50);
    }
    else if(OutputY >= toterWinkel){
        digitalWrite(dirPin2, backward);
        digitalWrite(dirPin4, backward);    
        ledcWrite(motor24Channel, 50);

    }
    else{   
        ledcWrite(motor24Channel, 0);
    }
}
