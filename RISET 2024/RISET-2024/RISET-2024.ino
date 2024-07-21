#include "XL320.h"
XL320 robot;
#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial mySerial(9, 8);
int servoID = 1;

Servo servoA0;
Servo servoA1;

void setup() {
  Serial.begin(57600);
  mySerial.begin(57600);
  robot.begin(mySerial);
  robot.setJointSpeed(servoID, 1023);

  servoA0.attach(A0);
  servoA1.attach(A1);

  servoA0.write(0);
  servoA1.write(0);

  Serial.println("KRTI 2024 - KING PHOENIX");
  Serial.println("===============================");

  Serial.println(" 1.Grip\n 2.Buka Grip\n 3.Open Ser1\n 4.Close Ser1\n 5.Open Ser2\n 6.Close Ser2\n 7.Open AllSer\n 8.Close AllSer\n");
}

void openGrip() {
  robot.moveJoint(servoID, 0);
  delay(100);
  Serial.print("Mekanik Open\n");
  delay(100);
}

void closeGrip() {  
  robot.setJointSpeed(servoID, 1023);
  delay(100);
  robot.moveJoint(servoID, 80);
  delay(400);
  robot.setJointSpeed(servoID, 70); 
  delay(100);
  robot.moveJoint(servoID, 164);
  delay(1000);
  Serial.print("Mekanik grip\n");
  delay(100);
  robot.setJointSpeed(servoID, 1023);  // Kembalikan ke kecepatan default
}

void openSer1(){
  servoA0.write(0);
  Serial.print("Servo 1 open\n");
}

void closeSer1(){
  servoA0.write(90);
  Serial.print("Servo 1 close\n");
}
void openSer2(){
  servoA1.write(0);
  Serial.print("Servo 2 open\n");
}

void closeSer2(){
  servoA1.write(90);
  Serial.print("Servo 2 close\n");
}

void openAllSer(){
  servoA0.write(0);
  servoA1.write(0);
  Serial.print("ALL servo open\n");
}

void closeAllSer(){
  servoA0.write(90);
  servoA1.write(90);
  Serial.print("ALL Servo close\n");
}

void loop() {
  if (Serial.available() > 0) {
    int req = Serial.parseInt();
    if (req == 1) {
      closeGrip();
    } else if (req == 2) {
      openGrip();
    }
    else if(req == 3){
      openSer1();
    }
    else if(req == 4){
      closeSer1();
    }    
    else if(req == 5){
      openSer2();
    }    
    else if(req == 6){
      closeSer2();
    }    
    else if(req == 7){
      openAllSer();
    }    
    else if(req == 8){
      closeAllSer();
    } else if (req == 0) {
      Serial.print("Menunggu input\n");
      Serial.println("------------------------\n");
    } else {
      Serial.println("Masukkan Inputan Yang Benar");
    }
  }
}
