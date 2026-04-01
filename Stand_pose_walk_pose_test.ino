#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685(0x40);

#define SERVOMIN 110
#define SERVOMAX 510

#define FR1 4
#define FR2 8
#define FR3 12

int fr1_home = 90;
int fr2_home = 45;
int fr3_home = 55;

int fr1_cur = fr1_home;
int fr2_cur = fr2_home;
int fr3_cur = fr3_home;

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(uint8_t ch, int angle) {
  pca9685.setPWM(ch, 0, angleToPulse(constrain(angle, 0, 180)));
}

void moveFRSmooth(int t1, int t2, int t3, int steps = 25, int dly = 15) {
  int s1 = fr1_cur, s2 = fr2_cur, s3 = fr3_cur;

  for (int i = 1; i <= steps; i++) {
    setServo(FR1, s1 + (t1 - s1) * i / steps);
    setServo(FR2, s2 + (t2 - s2) * i / steps);
    setServo(FR3, s3 + (t3 - s3) * i / steps);
    delay(dly);
  }

  fr1_cur = t1;
  fr2_cur = t2;
  fr3_cur = t3;
}

void setup() {
  Wire.begin(21, 22);
  pca9685.begin();
  pca9685.setPWMFreq(50);
  delay(500);

  moveFRSmooth(90, 45, 55); // stand pose
  delay(2000);
  moveFRSmooth(65, 70, 40); // walk pose test
}

void loop() {
}