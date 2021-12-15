#include <Arduino.h>
#include <GLOBALS.h>



void MotorenAnsteuern(){
if(mpuAngle[X] < -5.0){
    digitalWrite(dirPin1,LOW); 
  for(int x = 0; x < STEPS_PER_REV; x++) {
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(1000); 
  }
  Serial.println("Motor 1");
}

else if(mpuAngle[X] > 5.0){
//     Serial.print("ballz");
//     digitalWrite(dirPin1,HIGH);
//   for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
//     digitalWrite(stepPin1,HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(stepPin1,LOW);
//     delayMicroseconds(1000);
//   }
    Serial.println("Motor 2");
}

if(mpuAngle[Y] < -5.0){
//     digitalWrite(dirPin2,LOW); 
//   for(int x = 0; x < STEPS_PER_REV; x++) {
//     digitalWrite(stepPin2,HIGH); 
//     delayMicroseconds(1000); 
//     digitalWrite(stepPin2,LOW); 
//     delayMicroseconds(1000); 
//   }
    Serial.println("Motor 3");
}

else if(mpuAngle[Y] > 5.0){
//     Serial.print("ballz");
//     digitalWrite(dirPin2,HIGH);
//   for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
//     digitalWrite(stepPin2,HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(stepPin2,LOW);
//     delayMicroseconds(1000);
//   }
    Serial.println("Motor 4");
}
}