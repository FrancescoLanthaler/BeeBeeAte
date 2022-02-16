#ifndef SENSOREN_H
#define SENSOREN_H
#include <MPU6050_light.h>

#define dt 0.01

extern MPU6050 mpu;
extern void MPUSetup();
extern void SensorAuslesen();
extern void SensorAuswerten();

// Variablen

extern int speedMicro;

#endif