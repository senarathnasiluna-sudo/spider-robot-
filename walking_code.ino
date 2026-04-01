#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685(0x40);

#define SERVOMIN 110
#define SERVOMAX 510

#define FL1 0
#define FL2 4
#define FL3 8

#define BL1 1
#define BL2 5
#define BL3 9

#define BR1 2
#define BR2 6
#define BR3 10

#define FR1 3
#define FR2 7
#define FR3 11

int h1 = 90, h2 = 45, h3 = 55;

int fl1=h1, fl2=h2, fl3=h3;
int bl1=h1, bl2=h2, bl3=h3;
int br1=h1, br2=h2, br3=h3;
int fr1=h1, fr2=h2, fr3=h3;

bool walking = false;

int angleToPulse(int a){ return map(a,0,180,SERVOMIN,SERVOMAX); }

void setServo(int ch,int a){ pca9685.setPWM(ch,0,angleToPulse(constrain(a,0,180))); }

void moveAll(
  int fl1_t,int fl2_t,int fl3_t,
  int fr1_t,int fr2_t,int fr3_t,
  int bl1_t,int bl2_t,int bl3_t,
  int br1_t,int br2_t,int br3_t,
  int steps=20,int dly=15){

  int s_fl1=fl1, s_fl2=fl2, s_fl3=fl3;
  int s_fr1=fr1, s_fr2=fr2, s_fr3=fr3;
  int s_bl1=bl1, s_bl2=bl2, s_bl3=bl3;
  int s_br1=br1, s_br2=br2, s_br3=br3;

  for(int i=1;i<=steps;i++){
    setServo(FL1, s_fl1 + (fl1_t-s_fl1)*i/steps);
    setServo(FL2, s_fl2 + (fl2_t-s_fl2)*i/steps);
    setServo(FL3, s_fl3 + (fl3_t-s_fl3)*i/steps);

    setServo(FR1, s_fr1 + (fr1_t-s_fr1)*i/steps);
    setServo(FR2, s_fr2 + (fr2_t-s_fr2)*i/steps);
    setServo(FR3, s_fr3 + (fr3_t-s_fr3)*i/steps);

    setServo(BL1, s_bl1 + (bl1_t-s_bl1)*i/steps);
    setServo(BL2, s_bl2 + (bl2_t-s_bl2)*i/steps);
    setServo(BL3, s_bl3 + (bl3_t-s_bl3)*i/steps);

    setServo(BR1, s_br1 + (br1_t-s_br1)*i/steps);
    setServo(BR2, s_br2 + (br2_t-s_br2)*i/steps);
    setServo(BR3, s_br3 + (br3_t-s_br3)*i/steps);

    delay(dly);
  }

  fl1=fl1_t; fl2=fl2_t; fl3=fl3_t;
  fr1=fr1_t; fr2=fr2_t; fr3=fr3_t;
  bl1=bl1_t; bl2=bl2_t; bl3=bl3_t;
  br1=br1_t; br2=br2_t; br3=br3_t;
}

void HOME() {
  moveAll(h1,h2,h3, h1,h2,h3, h1,h2,h3, h1,h2,h3, 25,15);
}

void WALK() {
  moveAll(65,70,40, 115,45,55, 115,45,55, 65,70,40, 20,15);
  moveAll(65,45,55, 115,45,55, 115,45,55, 65,45,55, 20,15);
  moveAll(90,45,55, 90,45,55, 90,45,55, 90,45,55, 15,15);

  moveAll(115,45,55, 65,70,40, 65,70,40, 115,45,55, 20,15);
  moveAll(115,45,55, 65,45,55, 65,45,55, 115,45,55, 20,15);
  moveAll(90,45,55, 90,45,55, 90,45,55, 90,45,55, 15,15);
}

void setup(){
  Serial.begin(115200);
  Wire.begin(21,22);
  pca9685.begin();
  pca9685.setPWMFreq(50);
  delay(500);
  HOME();
}

void loop(){
  WALK();
}