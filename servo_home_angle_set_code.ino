#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685(0x40);

#define SERVOMIN 110
#define SERVOMAX 510

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(uint8_t ch, int angle) {
  angle = constrain(angle, 0, 180);
  pca9685.setPWM(ch, 0, angleToPulse(angle));
}

void setup() {
  Wire.begin(21, 22);
  pca9685.begin();
  pca9685.setPWMFreq(50);
  delay(500);

  setServo(0, 90);
  setServo(1, 0);
  setServo(2, 90);
}

void loop() {
}