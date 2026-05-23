#include <Servo.h>

Servo myServo;

int insideSensor = A0;
int outsideSensor = A1;

int insideValue = 0;
int outsideValue = 0;

int diffThreshold = 15;     // fresh air
int highInside = 260;       // inside air is bad
int highOutside = 240;      // outside air is bad

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  insideValue = analogRead(insideSensor);
  outsideValue = analogRead(outsideSensor);

  int diff = insideValue - outsideValue;

  Serial.print("Inside: ");
  Serial.print(insideValue);
  Serial.print(" | Outside: ");
  Serial.print(outsideValue);

  if (diff > diffThreshold) {
    Serial.println(" --> FRESH AIR");
    myServo.write(180);
  }

  else if (insideValue > highInside && outsideValue > highOutside && abs(diff) < diffThreshold) {
    Serial.println(" --> OPTIMIZE AIRFLOW");
    myServo.write(90);
  }

  else {
    Serial.println(" --> RECIRCULATION");
    myServo.write(0);
  }

  delay(1000);
}