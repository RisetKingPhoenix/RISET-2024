XL320 robot;

#include <SoftwareSerial.h>
#include <Servo.h>
#include "XL320.h"
SoftwareSerial mySerial(9, 8);
int servoID = 1;

Servo servoA0;
Servo servoA1;

const int buttonPin1 = 10, buttonPin2 = 11, buttonPin3 = 12 ;
int buttonState = 0;
int rev1=0,rev2=0,rev3=0;

void setup() {
  Serial.begin(57600);
  mySerial.begin(57600);
  robot.begin(mySerial);
  robot.setJointSpeed(servoID, 1023);

  servoA0.attach(A0);
  servoA1.attach(A1);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  servoA0.write(0);
  servoA1.write(0);

  robot.moveJoint(servoID, 300);

  Serial.println("KRTI 2024 - KING PHOENIX");
  Serial.println("===============================");

  Serial.println(" 1.Buka Arm\n 2.Close Arm\n 3.Open Ser1\n 4.Close Ser1\n 5.Open Ser2\n 6.Close Ser2\n 7.Open AllSer\n 8.Close AllSer\n");
}

void openGrip() {
  robot.setJointSpeed(servoID, 1023);
  delay(100);
  robot.moveJoint(servoID, 300);
  delay(100);
  Serial.print("Mekanik Open\n");
  delay(1500);
}

void closeGrip() {  
  robot.setJointSpeed(servoID, 1023);
  delay(100);
  robot.moveJoint(servoID, 390);
  delay(300);
  robot.setJointSpeed(servoID, 50); 
  delay(100);
  robot.moveJoint(servoID, 512);
  delay(1000);
  Serial.print("Mekanik grip\n");
  delay(100);
  robot.setJointSpeed(servoID, 1023);
  delay(1500);
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
  int button1 = digitalRead(buttonPin1);
  int button2 = digitalRead(buttonPin2);
  int button3 = digitalRead(buttonPin3);

  if (Serial.available() > 0) {
    int req = Serial.parseInt();
    if (req == 1) {
      openGrip();
    } else if (req == 2) {
      closeGrip();
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

  if (button1 == 1) {
    delay(400);
    if (rev1 % 2 == 0) {
      openGrip();
      rev1++;
    } else {
      closeGrip();
      rev1++;
    }
    delay(500);
    
  }

  if (button2 == 1) {
    delay(400);
    if (rev2 % 2 == 0) {
      openSer1();
      rev2++;
    } else {
      closeSer1();
      rev2++;
    }
    delay(500);
  }

  if (button3 == 1) {
    delay(400);
    if (rev3 % 2 == 0) {
      openSer2();
      rev3++;
    } else {
      closeSer2();
      rev3++;
    }
    delay(500);
  }
}
