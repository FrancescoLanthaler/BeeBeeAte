#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

// Own Includes
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>

float mpuAngle[3]; // 0 = X, 1 = Y, 2 = Z

// Timer Variables
unsigned long timeStamp1;
unsigned long timeStamp2;
unsigned long interval1 = 2;

void setup()
{
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);

  Serial.begin(115200);
  Wire.begin();

  // Setup for MPU6050
  MPUSetup();
  SetupMotor();
  timeStamp1 = millis();
}

void loop()
{
  if ((millis() - timeStamp1) > interval1) // Timestamp Auswertung Sensorwerte
  {
    timeStamp1 = millis();
    WinkelFilter();
    MotorSteuerung();
  }
}