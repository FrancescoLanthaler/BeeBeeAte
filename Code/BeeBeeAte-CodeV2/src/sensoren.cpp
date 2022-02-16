#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);


int speedMicro;

void MPUSetup() // Setup for MPU6050
{
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

void SensorAuslesen() // Reading MPU6050 Values
{
  mpu.update();
  mpuAngle[X] = mpu.getAngleX();
  mpuAngle[Y] = mpu.getAngleY();
  mpuAngle[Z] = mpu.getAngleZ();
}

void SensorAuswerten() // Controlling motors through angle
{

}
