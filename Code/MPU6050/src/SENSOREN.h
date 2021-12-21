#ifndef SENSOREN_H
#define SENSOREN_H
#include <MPU6050_light.h>

extern MPU6050 mpu;
extern void MPUSetup();
extern void SensorAuslesen();
extern void SensorAuswerten();

extern const int minWinkel;
extern const int maxWinkel;

extern int speedMicro;

#endif