// BB-8 Motor and Bluetooth Communication AI
// HC-06 bluetooth module name, 1234 pairing key

#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

int inputState;
int debugFlag;
int inputHandled;

Adafruit_DCMotor *motorR = AFMS.getMotor(1);
Adafruit_DCMotor *motorL = AFMS.getMotor(2);
int motorRSpeed;
int motorLSpeed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  
  inputState = 0; // Motor Stop
  inputHandled = 1; // Initialized to input has been handled
  debugFlag = 1; // ??
  motorRSpeed = 0; // Speed initialized to 0
  motorLSpeed = 0; //Speed initialized to 0

// Doesn't seem necessary for set up
//  motorR->setSpeed (150);
//  motorR->run(FORWARD);
//  motorR->run(RELEASE);
//
//  motorL->setSpeed (150);
//  motorL->run(FORWARD);
//  motorL->run(RELEASE);

}

void loop() {
  // Get current command state  
  if(Serial.available() > 0) {
    inputState = Serial.read();
    inputHandled = 0;
    debugFlag = 1;
  }
  
  // Based on inputState call directional functions
  switch (inputState) {
    case '0':
      stop();
      break;
    case '1':
      forward();
      break;
    case '2':
      reverse();
      break;
    case '3':
      turnRight();
      break;
    case '4':
      turnLeft();
      break;
    default:
      if (debugFlag) {
        Serial.println("Command Not Found.");
        debugFlag = 0;
      }
      break;
  }
}

void forward() {
  if (!inputHandled) {
//    motorRSpeed = adjustSpeed(motorRSpeed, 10);
//    motorLSpeed = adjustSpeed(motorLSpeed, 10);
    motorControl(motorR, FORWARD, motorRSpeed);
    motorControl(motorL, BACKWARD, motorLSpeed);
    printDebug("Going forward!");
    inputHandled = 1;
  }
}

void reverse() {
  if (!inputHandled) {
    motorRSpeed = adjustSpeed(motorRSpeed, 10);
    motorLSpeed = adjustSpeed(motorLSpeed, 10);
    motorControl(motorR, BACKWARD, motorRSpeed);
    motorControl(motorL, FORWARD, motorLSpeed);
    printDebug("Reversing!");
    inputHandled = 1;
  }
}

void turnLeft() {
  if (!inputHandled) {
    motorRSpeed = adjustSpeed(motorRSpeed, 10);
    motorLSpeed = adjustSpeed(motorLSpeed, -10);
    motorControl(motorR, FORWARD, motorRSpeed);
    motorControl(motorL, BACKWARD, motorLSpeed);
    printDebug("Turning left!");
    inputHandled = 1;
  }
}

void turnRight() {
  if (!inputHandled) {
    motorRSpeed = adjustSpeed(motorRSpeed, -10);
    motorLSpeed = adjustSpeed(motorLSpeed, 10);
    motorControl(motorR, FORWARD, motorRSpeed);
    motorControl(motorL, BACKWARD, motorLSpeed);
    printDebug("Turning right!");
    inputHandled = 1;
  }
}
void stop() {
  if (!inputHandled) {
    motorRSpeed = 0;
    motorLSpeed = 0;
    motorControl(motorR, FORWARD, motorRSpeed);
    motorControl(motorL, BACKWARD, motorLSpeed);
    printDebug("Stopping!");
    inputHandled = 1;
  }
}

int adjustSpeed(int currSpeed, int change) {
  int tempSpeed = currSpeed + change;
  
  if (tempSpeed >= 0 && tempSpeed <= 255) {
    return tempSpeed;
  } else {
    return currSpeed;
  }
}

void motorControl(Adafruit_DCMotor *motor, uint8_t mDirection, int mSpeed) {
  motor->run(mDirection);
  motor->setSpeed(mSpeed);  
} 

void printDebug(String log) {
if(debugFlag){
    Serial.println(log);
    debugFlag = 0;
  }
}

//
//void rotateLeft() {
//  motorControl(FORWARD, FORWARD, 50, 50);
//  printDebug("Rotating left!");
//}
//
//void rotateRight() {
//  motorControl(BACKWARD, BACKWARD, 50, 50);
//  printDebug("Rotating right!");
//}
