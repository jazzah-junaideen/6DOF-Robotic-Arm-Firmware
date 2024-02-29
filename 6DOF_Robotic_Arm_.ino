#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 500 // this is the 'maximum' pulse length count (out of 4096)
#define FREQUENCY 50 // this is the 'maximum' pulse length count (out of 4096)

#define ChannelBase 0
#define ChannelShoulder 3
#define ChannelElbow 4
#define ChannelWrist 7
#define ChannelWristRoll 8
#define ChannelGripper 11

int baseAngle;

void rotateServo(int channel, int angle){
  int pulseWidth = map(angle,-90,90,SERVOMIN,SERVOMAX);
  Serial.println("Rotating Servo " + String(channel) + " turning to : " + String(angle));
  pwm.setPWM(channel, 0, pulseWidth);
}

void rotateBase(int angle){
  rotateServo(ChannelBase,angle);
}

void rotateSholder(int angle){
  rotateServo(ChannelShoulder,angle);
}

void rotateElbow(int angle){
  rotateServo(ChannelElbow,angle);
}

void rotateWrist(int angle){
  rotateServo(ChannelWrist,angle);
}

void rotateWristRoll(int angle){
  rotateServo(ChannelWristRoll,angle);
}

void rotateGripper(int angle){
  rotateServo(ChannelGripper,angle);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting..!");

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~50z updates
}

String data;
String values[5];
   
void loop() {
   if (Serial.available() > 0) {
    data = Serial.readString();
    int valueCount = splitString(data, ',', values, 5);
    //Serial.println("Received Degree : " + String(baseAngle));
    rotateBase(values[0].toInt());
    rotateSholder(values[1].toInt());
    rotateElbow(values[2].toInt());
    rotateWrist(values[3].toInt());
    rotateWristRoll(values[4].toInt());
    rotateGripper(values[5].toInt());
   }
   delay(1000);
}

int splitString(String str, char delimiter, String arr[], int size) {
  int arrIndex = 0;
  int startIndex = 0;
  
  for (int i = 0; i < str.length(); i++) {
    if (str.charAt(i) == delimiter) {
      arr[arrIndex++] = str.substring(startIndex, i);
      startIndex = i + 1;
      
      if (arrIndex >= size) {
        break;
      }
    }
  }
  
  if (startIndex < str.length()) {
    arr[arrIndex++] = str.substring(startIndex);
  }
  
  return arrIndex;
}