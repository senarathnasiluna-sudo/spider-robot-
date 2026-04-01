#include <Arduino.h>

#define TRIG_FRONT 25
#define ECHO_FRONT 32

#define TRIG_LEFT  26
#define ECHO_LEFT  33

#define TRIG_RIGHT 27
#define ECHO_RIGHT 34

float readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
}

void loop() {
  float front = readDistance(TRIG_FRONT, ECHO_FRONT);
  delay(50);
  float left = readDistance(TRIG_LEFT, ECHO_LEFT);
  delay(50);
  float right = readDistance(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("Front: "); Serial.print(front); Serial.print(" cm | ");
  Serial.print("Left: ");  Serial.print(left);  Serial.print(" cm | ");
  Serial.print("Right: "); Serial.print(right); Serial.println(" cm");

  delay(500);
}