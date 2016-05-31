// BB-8 Motor and Bluetooth Communication AI
// HC-06 bluetooth module name, 1234 pairing key
// TODO: We're going to need a failsafe that cuts motors when bluetooth disconnects

#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* motors[] = {AFMS.getMotor(1), AFMS.getMotor(2)};
float differential;
int motorSpeed;

String input;
int inputHandled;

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  reset();
}

void loop() {
  // Get current command state  
  if(Serial.available() > 0) {
    input = Serial.readString();
    inputHandled = 0;
  }
  
  // Based on input call directional functions
  if (!inputHandled) {
    int commaIndexA = input.indexOf(',');
    int commaIndexB = input.indexOf(',', commaIndexA + 1);
    int dirInput = input.substring(0, commaIndexA).toInt();
    int speedInput = input.substring(commaIndexA + 1, commaIndexB).toInt();
    float diffInput = input.substring(commaIndexB + 1).toFloat();
    
    if (dirInput) {
      setDirection(FORWARD);
    } else {
      setDirection(BACKWARD);
    }
    setDifferential(diffInput);
    setMotorSpeed(speedInput);
//    handleTextualInput(input[0]);
    inputHandled = 1;
  }
}

void reset() {
  differential = 0;
  motorSpeed = 0;
  inputHandled = 1; // Initialized to input has been handled
  setDirection(FORWARD);
}

void setDirection(uint8_t mDirection) {
  motors[0]->run(mDirection);
  motors[1]->run(mDirection);
  Serial.print("Direction is now ");
  Serial.println(mDirection);
}

void setMotorSpeed(int mSpeed) {
  if (mSpeed < 0) {
    motorSpeed = 0;
  } else if (mSpeed > 255) {
    motorSpeed = 255;
  } else {
    motorSpeed = mSpeed;
  }
  
  int adjustment = mSpeed * differential;
  int speeds[2] = {mSpeed + adjustment, mSpeed - adjustment};
 
  for (int i = 0; i < 2; i++) {
    int currSpeed = speeds[i];
    if (currSpeed < 0) {
      motors[i] -> setSpeed(0);
      Serial.println("Motor speed is now 0");
    } else if (currSpeed > 255) {
      motors[i] -> setSpeed(255);
      Serial.println("Motor speed is now 255");
    } else {
      motors[i] -> setSpeed(currSpeed);
      Serial.print("Motor speed is now ");
      Serial.println(currSpeed);
    }
  }
}

// Range of -1 to 1
// 0 is straight
// Negative numbers represent right turn
// Positive numbers represent left turn
// Closer to 1 in either direction, the tighter the turn
void setDifferential(float diff) {
  if (diff < -1) {
    differential = -1;
    Serial.println("Differential is now -1");
  } else if (diff > 1) {
    differential = 1;
    Serial.println("Differential is now 1");
  } else {
    differential = diff;
    Serial.print("Differential is now ");
    Serial.println(differential);
  }
  setMotorSpeed(motorSpeed);
}

void incrementDifferential() {
  setDifferential(differential + .1);
}

void decrementDifferential() {
  setDifferential(differential - .1);
}

void incrementSpeed() {
  setMotorSpeed(motorSpeed + 1);
}

void decrementSpeed() {
  setMotorSpeed(motorSpeed - 1);
}

void handleTextualInput(char inputState) {
  switch (inputState) {
      case '0':
        setMotorSpeed(0);
        break;
      case '1':
        setMotorSpeed(25);
        break;
      case '2':
        setMotorSpeed(50);
        break;
      case '3':
        setMotorSpeed(75);
        break;
      case '4':
        setMotorSpeed(100);
        break;
      case '5':
        setMotorSpeed(125);
        break;
      case '6':
        setMotorSpeed(150);
        break;
      case '7':
        setMotorSpeed(175);
        break;
      case '8':
        setMotorSpeed(200);
        break;
      case '9':
        setMotorSpeed(225);
        break;
      case 'a':
        incrementSpeed();
        break;
      case 'd':
        decrementSpeed();
        break;
      case 'f':
        setDirection(FORWARD);
        break;
      case 'b':
        setDirection(BACKWARD);
        break;
      case 'r':
        setDifferential(-0.5);
        break;
      case 'l':
        setDifferential(0.5);
        break;
      case 't':
        setDifferential(0);
        break;
      case 'h':
        incrementDifferential();
        break;
      case 's':
        decrementDifferential();
        break;
      case 'p':
        reset();
        break;
      default:
        Serial.println("Command Not Found.");
        break;
    }
}
