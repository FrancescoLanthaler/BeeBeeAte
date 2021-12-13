#include <Arduino.h>
#include <motoren.h>
#include <GLOBALS.h>
#include <MPU6050_light.h>
#include <Wire.h>

void SensorAuslesen()
{
  mpu.update();
  mpuAngle[X] = mpu.getAngleX();
  mpuAngle[Y] = mpu.getAngleY();
  mpuAngle[Z] = mpu.getAngleZ();
}