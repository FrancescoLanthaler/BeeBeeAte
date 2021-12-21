#include <Arduino.h>
#include <GLOBALS.h>
#include <MOTOREN.h>
#include <SENSOREN.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

const int maxWinkel = 5;
const int minWinkel = -5;

void MPUSetup()   // Setup for MPU6050
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

void SensorAuslesen()   // Reading MPU6050 Values
{
  mpu.update();
  mpuAngle[X] = mpu.getAngleX();
  mpuAngle[Y] = mpu.getAngleY();
  mpuAngle[Z] = mpu.getAngleZ();
}

void SensorAuswerten()    // Controlling motors through angle
{
  if (mpuAngle[X] < minWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X] * (-1));
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, forward);
  }

  else if (mpuAngle[X] > maxWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[X]);
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, forward);
  }

  if (mpuAngle[Y] < minWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[Y] * (-1));
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, forward);
  }

  else if (mpuAngle[Y] > maxWinkel)
  {
    speedMicro = SpeedBerechnung(mpuAngle[Y]);
    MotorenAnsteuern2(stepPin1, stepPin2, speedMicro, forward);
  }
}

int SpeedBerechnung(int winkel)   // Calculating speed of motors
{
  int speed = 0.3657 * pow(winkel, 4) - 18.912 * pow(winkel, 3) + 354.1 * pow(winkel, 2) - 2878.7 * winkel + 9061.7;
  return speed;
}