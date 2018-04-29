int ultrasonicSensorTriggerPin = 13;
int ultrasonicSensorEchoPin = 11;

float duration;
float distance;
float rate;

void setup() {
  Serial.begin(9600);
  pinMode(ultrasonicSensorTriggerPin, OUTPUT);
  pinMode(ultrasonicSensorEchoPin, INPUT);
}

void loop() {
  digitalWrite(ultrasonicSensorTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicSensorTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicSensorTriggerPin, LOW);

  duration = pulseIn(ultrasonicSensorEchoPin, HIGH);
  distance = (duration / 2) * .0343;

  Serial.print("Distance: ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of Range");
  } else {
    Serial.print(distance);
    Serial.println("cm");
  }

  delay(1000);
}
