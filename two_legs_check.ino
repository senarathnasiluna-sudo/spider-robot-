#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685(0x40);

#define SERVOMIN 110
#define SERVOMAX 510

#define FR1 4
#define FR2 8
#define FR3 12

#define BL1 5
#define BL2 9
#define BL3 13

int fr1_home = 90, fr2_home = 45, fr3_home = 55;
int bl1_home = 90, bl2_home = 45, bl3_home = 55;

int fr1_cur = fr1_home, fr2_cur = fr2_home, fr3_cur = fr3_home;
int bl1_cur = bl1_home, bl2_cur = bl2_home, bl3_cur = bl3_home;

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(uint8_t ch, int angle) {
  pca9685.setPWM(ch, 0, angleToPulse(constrain(angle, 0, 180)));
}

void movePairSmooth(int fr1_t, int fr2_t, int fr3_t,
                    int bl1_t, int bl2_t, int bl3_t,
                    int steps = 25, int dly = 15) {
  int s_fr1 = fr1_cur, s_fr2 = fr2_cur, s_fr3 = fr3_cur;
  int s_bl1 = bl1_cur, s_bl2 = bl2_cur, s_bl3 = bl3_cur;

  for (int i = 1; i <= steps; i++) {
    setServo(FR1, s_fr1 + (fr1_t - s_fr1) * i / steps);
    setServo(FR2, s_fr2 + (fr2_t - s_fr2) * i / steps);
    setServo(FR3, s_fr3 + (fr3_t - s_fr3) * i / steps);

    setServo(BL1, s_bl1 + (bl1_t - s_bl1) * i / steps);
    setServo(BL2, s_bl2 + (bl2_t - s_bl2) * i / steps);
    setServo(BL3, s_bl3 + (bl3_t - s_bl3) * i / steps);
    delay(dly);
  }

  fr1_cur = fr1_t; fr2_cur = fr2_t; fr3_cur = fr3_t;
  bl1_cur = bl1_t; bl2_cur = bl2_t; bl3_cur = bl3_t;
}

void setup() {
  Wire.begin(21, 22);
  pca9685.begin();
  pca9685.setPWMFreq(50);
  delay(500);
}

void loop() {
  movePairSmooth(90,70,40, 90,70,40);
  movePairSmooth(65,70,40, 65,70,40);
  movePairSmooth(65,45,55, 65,45,55);
  movePairSmooth(115,45,55,115,45,55);
  movePairSmooth(90,45,55, 90,45,55);
}