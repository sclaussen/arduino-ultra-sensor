#include "DHT.h"
#include "NewPing.h"

// Constants
#define ULTRASONIC_SENSOR_TRIGGER_PIN 13
#define ULTRASONIC_SENSOR_ECHO_PIN 11
#define DHT_TYPE DHT22
#define DHT_PIN 7
#define MAXIMUM_DISTANCE = 400;

// Variables
float humidity;
float temperature;
float duration;
float distance;
float soundMetersPerSecond;
float soundCentimetersPerMillisecond;
int iterations = 5;

NewPing sonar(ULTRASONIC_SENSOR_TRIGGER_PIN, ULTRASONIC_SENSOR_ECHO_PIN, MAXIMUM_DISTANCE);
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  /* pinMode(ultrasonicSensorTriggerPin, OUTPUT); */
  /* pinMode(ultrasonicSensorEchoPin, INPUT); */
  dht.begin();
}

void loop() {
  // Delay to enable the DHT-22 to stabalize
  delay(2000);

  // Read the humidity and temperature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Calculate the speed of sound in meters per second
  // and then convert to centimeters per millisecond
  soundMetersPerSecond = 331.4 + (0.606 * temperature) + (0.0124 * humidity);
  soundCentimetersPerMillisecond = soundMetersPerSecond / 10000;

  duration = sonar.ping_median(iterations);

  // 0.0343 meters per second is the speed of sound
  distance = (duration / 2) * .0343;

  // Print out the results of the sensor
  Serial.print("Sound: ");
  Serial.print(soundMetersPerSecond);
  Serial.print(" m/s, ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" C, ");
  Serial.print("Distance: ");

  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}
