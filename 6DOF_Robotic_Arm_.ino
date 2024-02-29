#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_GRIPPER_CHANNEL 5 // PWM channel for the gripper servo

// Create an instance of the Adafruit_PWMServoDriver class
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Function to move the gripper servo to a specific angle
void moveGripperToAngle(int angle) {
  int pulseWidth = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(SERVO_GRIPPER_CHANNEL, 0, pulseWidth);
  delay(10); // Optional delay for smoothness
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);  // Set PWM frequency to 60 Hz
}

void loop() {
  // Move the gripper from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    moveGripperToAngle(angle);
  }
  
  // Move the gripper from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    moveGripperToAngle(angle);
  }
}
