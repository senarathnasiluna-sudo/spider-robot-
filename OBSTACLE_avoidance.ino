#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 110
#define SERVOMAX 510

// ===== FL =====
#define FL1 0
#define FL2 4
#define FL3 8

// ===== BL =====
#define BL1 1
#define BL2 5
#define BL3 9

// ===== BR =====
#define BR1 2
#define BR2 6
#define BR3 10

// ===== FR =====
#define FR1 3
#define FR2 7
#define FR3 11

// ===== Ultrasonic pins =====
#define TRIG_FRONT 25
#define ECHO_FRONT 32

#define TRIG_LEFT  26
#define ECHO_LEFT  33

#define TRIG_RIGHT 27
#define ECHO_RIGHT 34

// ===== Home pose =====
int h1 = 90, h2 = 45, h3 = 55;

// current angles
int fl1=h1, fl2=h2, fl3=h3;
int bl1=h1, bl2=h2, bl3=h3;
int br1=h1, br2=h2, br3=h3;
int fr1=h1, fr2=h2, fr3=h3;

// distance thresholds
float frontLimit = 18.0;   // cm
float sideLimit  = 15.0;   // cm

// ===========================
int angleToPulse(int a) {
  return map(a, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(int ch, int a) {
  a = constrain(a, 0, 180);
  pca9685.setPWM(ch, 0, angleToPulse(a));
}

// ===========================
// ultrasonic read
float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // 25ms timeout

  if (duration == 0) return -1;

  float distance = duration * 0.0343 / 2.0;
  return distance;
}

// ===========================
// move all legs smooth
void moveAll(
  int fl1_t, int fl2_t, int fl3_t,
  int fr1_t, int fr2_t, int fr3_t,
  int bl1_t, int bl2_t, int bl3_t,
  int br1_t, int br2_t, int br3_t,
  int steps = 20, int dly = 15
) {
  int s_fl1 = fl1, s_fl2 = fl2, s_fl3 = fl3;
  int s_fr1 = fr1, s_fr2 = fr2, s_fr3 = fr3;
  int s_bl1 = bl1, s_bl2 = bl2, s_bl3 = bl3;
  int s_br1 = br1, s_br2 = br2, s_br3 = br3;

  for (int i = 1; i <= steps; i++) {
    int a_fl1 = s_fl1 + (fl1_t - s_fl1) * i / steps;
    int a_fl2 = s_fl2 + (fl2_t - s_fl2) * i / steps;
    int a_fl3 = s_fl3 + (fl3_t - s_fl3) * i / steps;

    int a_fr1 = s_fr1 + (fr1_t - s_fr1) * i / steps;
    int a_fr2 = s_fr2 + (fr2_t - s_fr2) * i / steps;
    int a_fr3 = s_fr3 + (fr3_t - s_fr3) * i / steps;

    int a_bl1 = s_bl1 + (bl1_t - s_bl1) * i / steps;
    int a_bl2 = s_bl2 + (bl2_t - s_bl2) * i / steps;
    int a_bl3 = s_bl3 + (bl3_t - s_bl3) * i / steps;

    int a_br1 = s_br1 + (br1_t - s_br1) * i / steps;
    int a_br2 = s_br2 + (br2_t - s_br2) * i / steps;
    int a_br3 = s_br3 + (br3_t - s_br3) * i / steps;

    setServo(FL1, a_fl1); setServo(FL2, a_fl2); setServo(FL3, a_fl3);
    setServo(FR1, a_fr1); setServo(FR2, a_fr2); setServo(FR3, a_fr3);
    setServo(BL1, a_bl1); setServo(BL2, a_bl2); setServo(BL3, a_bl3);
    setServo(BR1, a_br1); setServo(BR2, a_br2); setServo(BR3, a_br3);

    delay(dly);
  }

  fl1 = fl1_t; fl2 = fl2_t; fl3 = fl3_t;
  fr1 = fr1_t; fr2 = fr2_t; fr3 = fr3_t;
  bl1 = bl1_t; bl2 = bl2_t; bl3 = bl3_t;
  br1 = br1_t; br2 = br2_t; br3 = br3_t;
}

// ===========================
void HOME() {
  moveAll(
    h1,h2,h3,
    h1,h2,h3,
    h1,h2,h3,
    h1,h2,h3,
    25,15
  );
}

// ===========================
// FORWARD
void stepForward() {
  moveAll(
    65,70,40,    115,45,55,   115,45,55,   65,70,40,   20,15
  );
  moveAll(
    65,45,55,    115,45,55,   115,45,55,   65,45,55,   20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );

  moveAll(
    115,45,55,   65,70,40,    65,70,40,    115,45,55,  20,15
  );
  moveAll(
    115,45,55,   65,45,55,    65,45,55,    115,45,55,  20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );
}

// ===========================
// BACKWARD
void stepBackward() {
  moveAll(
    115,70,40,   65,45,55,    65,45,55,    115,70,40,  20,15
  );
  moveAll(
    115,45,55,   65,45,55,    65,45,55,    115,45,55,  20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );

  moveAll(
    65,45,55,    115,70,40,   115,70,40,   65,45,55,   20,15
  );
  moveAll(
    65,45,55,    115,45,55,   115,45,55,   65,45,55,   20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );
}

// ===========================
// TURN LEFT
void stepLeft() {
  moveAll(
    90,45,55,    65,70,40,    90,45,55,    65,70,40,   20,15
  );
  moveAll(
    90,45,55,    65,45,55,    90,45,55,    65,45,55,   20,15
  );
  moveAll(
    115,70,40,   90,45,55,    115,70,40,   90,45,55,   20,15
  );
  moveAll(
    115,45,55,   90,45,55,    115,45,55,   90,45,55,   20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );
}

// ===========================
// TURN RIGHT
void stepRight() {
  moveAll(
    65,70,40,    90,45,55,    65,70,40,    90,45,55,   20,15
  );
  moveAll(
    65,45,55,    90,45,55,    65,45,55,    90,45,55,   20,15
  );
  moveAll(
    90,45,55,    115,70,40,   90,45,55,    115,70,40,  20,15
  );
  moveAll(
    90,45,55,    115,45,55,   90,45,55,    115,45,55,  20,15
  );
  moveAll(
    90,45,55,    90,45,55,    90,45,55,    90,45,55,   15,15
  );
}

// ===========================
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pca9685.begin();
  pca9685.setPWMFreq(50);
  delay(500);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  HOME();

  Serial.println("Spider Obstacle Avoid Ready");
}

// ===========================
void loop() {
  float frontDist = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  delay(30);
  float leftDist  = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  delay(30);
  float rightDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  delay(30);

  Serial.print("Front: "); Serial.print(frontDist);
  Serial.print(" | Left: "); Serial.print(leftDist);
  Serial.print(" | Right: "); Serial.println(rightDist);

  // no object in front -> go forward
  if (frontDist == -1 || frontDist > frontLimit) {
    stepForward();
  }
  else {
    // obstacle in front
    if ((leftDist == -1 || leftDist > sideLimit) && (rightDist != -1 && rightDist <= sideLimit)) {
      stepLeft();
    }
    else if ((rightDist == -1 || rightDist > sideLimit) && (leftDist != -1 && leftDist <= sideLimit)) {
      stepRight();
    }
    else if ((leftDist == -1 || leftDist > sideLimit) && (rightDist == -1 || rightDist > sideLimit)) {
      // both open -> choose bigger side
      if (leftDist > rightDist) stepLeft();
      else stepRight();
    }
    else {
      // all blocked
      stepBackward();
    }
  }
}