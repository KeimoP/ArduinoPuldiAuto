#include <AFMotor.h>


// Motor setup
AF_DCMotor rearLeft(1);
AF_DCMotor rearRight(2); // M2 inverted
AF_DCMotor frontRight(3);
AF_DCMotor frontLeft(4);


// Receiver pins
#define THROTTLE_PIN A2  // throttle
#define STEER_PIN    A0  // steering


void setup() {
  Serial.begin(9600);
}


void loop() {
  // Read RC PWM signals
  unsigned long throttle = pulseIn(THROTTLE_PIN, HIGH, 50000);
  unsigned long steer    = pulseIn(STEER_PIN, HIGH, 50000);


  int speed = 0;


  // ----- Forward -----
  if (throttle > 1600) {
    speed = map(throttle, 1601, 2000, 0, 200);
    speed = constrain(speed, 0, 200);


    int leftSpeed = speed;
    int rightSpeed = speed;


    // Steering
    if (steer > 1600) {       // turn left
      leftSpeed = 0;
    }
    else if (steer < 1400) {  // turn right
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(FORWARD);
    frontLeft.run(FORWARD);


    rearRight.run(BACKWARD); // M2 inverted
    frontRight.run(FORWARD);
  }
  // ----- Reverse -----
  else if (throttle >= 1150 && throttle <= 1400) {
    speed = map(throttle, 1150, 1400, 0, 200);
    speed = constrain(speed, 0, 200);


    int leftSpeed = speed;
    int rightSpeed = speed;


    // Steering in reverse
    if (steer > 1600) {       // turn left
      leftSpeed = 0;
    }
    else if (steer < 1400) {  // turn right
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(BACKWARD);
    frontLeft.run(BACKWARD);


    rearRight.run(FORWARD); // M2 inverted
    frontRight.run(BACKWARD);
  }
  // ----- Neutral / Steering only -----
  else if (throttle > 1400 && throttle <= 1600) {
    int leftSpeed  = 0;
    int rightSpeed = 0;


    if (steer > 1600) {       // turn left
      leftSpeed = 0;
      rightSpeed = 150;
    }
    else if (steer < 1400) {  // turn right
      leftSpeed = 150;
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(FORWARD);
    frontLeft.run(FORWARD);


    rearRight.run(BACKWARD); // M2 inverted
    frontRight.run(FORWARD);
  }
  // ----- Full Neutral below 1150 -----
  else {
    rearLeft.run(RELEASE);
    frontLeft.run(RELEASE);
    rearRight.run(RELEASE);
    frontRight.run(RELEASE);
  }


  // ----- Serial debug -----
  Serial.print("Throttle: "); Serial.print(throttle);
  Serial.print(" | Steering: "); Serial.print(steer);
  Serial.print(" | Speed: "); Serial.println(speed);


  delay(50);
}