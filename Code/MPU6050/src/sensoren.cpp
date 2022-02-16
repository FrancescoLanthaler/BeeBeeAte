#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

const int maxWinkel = 5;
const int minWinkel = -5;
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

float SpeedBerechnung(float winkel) // Calculating speed of motors
{
  float speed = 100;
  return speed;
}

void SensorAuswerten() // Controlling motors through angle
{
  if (mpuAngle[X] < minWinkel && mpuAngle[Y] < minWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, forward, forward);
  }

  else if (mpuAngle[X] < minWinkel && mpuAngle[Y] > maxWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, forward, backward);
  }

  else if (mpuAngle[X] > maxWinkel && mpuAngle[Y] > maxWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, backward, backward);
  }

  else if (mpuAngle[X] > maxWinkel && mpuAngle[Y] < minWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern4(stepPin1, stepPin2, stepPin3, stepPin4, speedMicro, backward, forward);
  }

  else if (mpuAngle[X] < minWinkel && (mpuAngle[Y] < maxWinkel && mpuAngle[Y] > minWinkel))
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, forward, X);
  }

  else if (mpuAngle[X] > maxWinkel && (mpuAngle[Y] < maxWinkel && mpuAngle[Y] > minWinkel))
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, backward, X);
  }

  else if (mpuAngle[Y] < minWinkel && (mpuAngle[X] < maxWinkel && mpuAngle[X] > minWinkel))
  {
    speedMicro = SpeedBerechnung(mpuAngle[Y]);
    MotorenAnsteuern2(stepPin3, stepPin4, speedMicro, forward, Y);
  }

  else if (mpuAngle[Y] > maxWinkel && (mpuAngle[X] < maxWinkel && mpuAngle[X] > minWinkel))
  {
    speedMicro = SpeedBerechnung(mpuAngle[Y]);
    MotorenAnsteuern2(stepPin3, stepPin4, speedMicro, backward, Y);
  }
}
