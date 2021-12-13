#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

#define joyX 4
#define joyY 2

#define X 0
#define Y 1
#define Z 2

const int dirPin1 = 18;  // Direction
const int stepPin1 = 5; // Step
const int dirPin2 = 18;  // Direction
const int stepPin2 = 5; // Step

const int STEPS_PER_REV = 1000;

MPU6050 mpu(Wire);
unsigned long timeStamp1;
unsigned long timeStamp2;
unsigned long interval1 = 1000;
unsigned long interval2 = 50;

int joyXValue, joyYValue;
float mpuAngle[3]; // 0 = X, 1 = Y, 2 = Z

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

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0)
  {
      Serial.print(status);
  } // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void SensorAuslesen()
{
  mpu.update();
  mpuAngle[X] = mpu.getGyroX();
  mpuAngle[Y] = mpu.getGyroY();
  mpuAngle[Z] = mpu.getGyroZ();
}

void MotorenAuswerten()
{
// if(mpuAngle[X] < -5.0){
//     digitalWrite(dirPin1,LOW); 
//   for(int x = 0; x < STEPS_PER_REV; x++) {
//     digitalWrite(stepPin1,HIGH); 
//     delayMicroseconds(1000); 
//     digitalWrite(stepPin1,LOW); 
//     delayMicroseconds(1000); 
//   }
// }
  
//   // Set motor direction counterclockwise
// else if(mpuAngle[X] > 5.0){
//     Serial.print("ballz");
//     digitalWrite(dirPin1,HIGH);
//   for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
//     digitalWrite(stepPin1,HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(stepPin1,LOW);
//     delayMicroseconds(1000);
//   }
// }

// if(mpuAngle[Y] < -5.0){
//     digitalWrite(dirPin2,LOW); 
//   for(int x = 0; x < STEPS_PER_REV; x++) {
//     digitalWrite(stepPin2,HIGH); 
//     delayMicroseconds(1000); 
//     digitalWrite(stepPin2,LOW); 
//     delayMicroseconds(1000); 
//   }
// }
  
//   // Set motor direction counterclockwise
// else if(mpuAngle[Y] > 5.0){
//     Serial.print("ballz");
//     digitalWrite(dirPin2,HIGH);
//   for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
//     digitalWrite(stepPin2,HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(stepPin2,LOW);
//     delayMicroseconds(1000);
//   }
// }
}

void loop()
{
  
  MotorenAuswerten();
  if ((millis() - timeStamp1) > interval1)
  { // print data every 10ms
    SensorAuslesen();
    timeStamp1 = millis();
    Serial.print("Balls ");
    Serial.print(mpuAngle[X]);
    Serial.print("\tY : ");
    Serial.print(mpuAngle[Y]);
    Serial.print("\tZ : ");
    Serial.println(mpuAngle[Z]);
  }
}