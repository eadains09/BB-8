//BB-8 Main Board (Arduino Uno)

#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include <Servo.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

//Servo mast;  // The servo that moves BB-8's mast
Adafruit_DCMotor *motorR = AFMS.getMotor(1);
Adafruit_DCMotor *motorL = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
//  mast.attach(10);  //AF Motorshield uses pin 10 as servo #1
  AFMS.begin();  // create with the default frequency 1.6KHz

  motorR->setSpeed (150);
  motorR->run(FORWARD);
  motorR->run(RELEASE);

  motorL->setSpeed (150);
  motorL->run(FORWARD);
  motorL->run(RELEASE);

}

void loop() { 
  int i = 0;
//  int pos = 0;
  
//Mast Servio
//Currently setup to do a 180 sweep for testing

//  for (pos = 0; pos <= 180; pos += 1) { 
//    
//    mast.write(pos);              
//    delay(15);                       
//  }
//  for (pos = 180; pos >= 0; pos -= 1) {
//    mast.write(pos);              
//    delay(15);                       
//  }

   delay(100);


//Drive Wheels
//Currently setup to do speed cycling for testing
    motorR->run(FORWARD);
    motorL->run(BACKWARD);  

  Serial.println("start");
  for (i=0; i<25; i++) {
    motorR->setSpeed(i);
    motorL->setSpeed(i);  
    delay(100);
  }   
   
   motorR->run(RELEASE);
   motorL->run(RELEASE);
     
   delay(100);

   motorR->run(BACKWARD);
   motorL->run(FORWARD);  

  for (i=25; i>0; i--) {
    motorR->setSpeed(i);
    motorL->setSpeed(i);  
    delay(100);
  }
    
  motorR->run(RELEASE);
  motorL->run(RELEASE);
  delay(1000);

}

