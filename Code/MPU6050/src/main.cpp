#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

// Variables
#include <GLOBALS.h>
#include <motoren.h>

MPU6050 mpu(Wire);

void setup()
{
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);

  Serial.begin(115200);
  Wire.begin();

  timeStamp1 = millis();

  // Setup for MPU6050
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0)
    Serial.print(status); // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop()
{
  SensorAuslesen();
  MotorenAnsteuern();

  if ((millis() - timeStamp1) > interval1) //Timestamp Auswertung Sensorwerte
  {  
    timeStamp1 = millis();
    Serial.print("X : ");
    Serial.print(mpuAngle[X]);
    Serial.print("\tY : ");
    Serial.print(mpuAngle[Y]);
    Serial.print("\tZ : ");
    Serial.println(mpuAngle[Z]);
  }
}