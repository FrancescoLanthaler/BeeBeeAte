#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

// Variables
#include <GLOBALS.h>

MPU6050 mpu(Wire);

float mpuAngle[3]; // 0 = X, 1 = Y, 2 = Z

// Timer Variables
unsigned long timeStamp1;
unsigned long timeStamp2;
unsigned long interval1 = 1000;
unsigned long interval2 = 50;

// Joystick Variables
int joyXValue, joyYValue;

// Methoden
void SensorAuslesen();
// extern void MotorenAnsteuern();

// Motoren
const int STEPS_PER_REV = 1000;
const int dirPin1 = 18;  // Direction
const int stepPin1 = 5; // Step
const int dirPin2 = 18;  // Direction
const int stepPin2 = 5; // Step

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

void SensorAuslesen()
{
  mpu.update();
  mpuAngle[X] = mpu.getAngleX();
  mpuAngle[Y] = mpu.getAngleY();
  mpuAngle[Z] = mpu.getAngleZ();
}

void loop()
{
  SensorAuslesen();
  // MotorenAnsteuern();

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