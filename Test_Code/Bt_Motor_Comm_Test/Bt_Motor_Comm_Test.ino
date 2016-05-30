#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

int state = 0;
int flag = 0;

Adafruit_DCMotor *motorR = AFMS.getMotor(1);
Adafruit_DCMotor *motorL = AFMS.getMotor(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  AFMS.begin();  // create with the default frequency 1.6KHz

  motorR->setSpeed (150);
  motorR->run(FORWARD);
  motorR->run(RELEASE);

  motorL->setSpeed (150);
  motorL->run(FORWARD);
  motorL->run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0) {
    state = Serial.read();
    flag=0;
  }
  
  
  if (state == '0') {
    motorR->run(RELEASE);
    motorL->run(RELEASE);
    motorR->run(FORWARD);
    motorL->run(BACKWARD);  
    motorR->setSpeed(0);
    motorL->setSpeed(0);  
    if(flag == 0){
      Serial.println("Stopping!");
      flag = 1;
    }
  }
  // if the state is 1 the led will turn on
  else if (state == '1') {
    motorR->run(RELEASE);
    motorL->run(RELEASE);
    motorR->run(FORWARD);
    motorL->run(BACKWARD);  
    motorR->setSpeed(100);
    motorL->setSpeed(100);  
    if(flag == 0){
      Serial.println("Going Forward!");
      flag = 1;
    }
  }
}
