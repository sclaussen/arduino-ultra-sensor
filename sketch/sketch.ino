// https://github.com/microflo/NewPing/tree/master/examples
#include "NewPing.h"

int ultrasonicSensorTriggerPin = 13;
int ultrasonicSensorEchoPin = 11;
int maximumDistance = 400;

float duration;
float distance;
float rate;

NewPing sonar(ultrasonicSensorTriggerPin, ultrasonicSensorEchoPin, maximumDistance);

void setup() {
  Serial.begin(9600);
  pinMode(ultrasonicSensorTriggerPin, OUTPUT);
  pinMode(ultrasonicSensorEchoPin, INPUT);
}

void loop() {
  distance = sonar.ping_cm();

  Serial.print("Distance: ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of Range");
  } else {
    Serial.print(distance);
    Serial.println("cm");
  }

  delay(1000);
}
