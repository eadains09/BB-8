//BB-8 Main Board (Arduino Uno)


#include <Servo.h>
#include <AFMotor.h>

Servo mast;  // The servo that moves BB-8's mast
AF_DCMotor motorR (1); // BB-8's right side drive motor
AF_DCMotor motorL (2); // BB-8's right side drive motor

int pos = 0;
int i;

void setup() {
  Serial.begin(9600);     
  mast.attach(10);  //AF Motorshield uses pin 10 as servo #1
  motorR.setSpeed (0);
  motorL.setSpeed (0);
}

void loop() { 
  
//Mast Servio
//Currently setup to do a 180 sweep for testing

  for (pos = 0; pos <= 180; pos += 1) { 
    
    mast.write(pos);              
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    mast.write(pos);              
    delay(15);                       
  }

//Drive Wheels
//Currently setup to do speed cycling for testing

  for (i=0; i<255; i++) {
    motorR.run(FORWARD);
    motorR.setSpeed(i);
    motorL.run(BACKWARD);  
    motorL.setSpeed(i);  
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    motorR.run(BACKWARD);
    motorR.setSpeed(i);
    motorL.run(FORWARD);  
    motorL.setSpeed(i);  
    delay(3);
  }

}

