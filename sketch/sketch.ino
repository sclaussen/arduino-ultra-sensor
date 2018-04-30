#include "DHT.h"
#include "NewPing.h"

// DHT Sensor Pins
// VCC    5V
// Data   7
// GND    GND

// HC-SR04 Ultrasonic Sensor Pins
// VCC    5V
// TRIG   11
// ECHO   13
// GND    GND

// Constants
#define DHT_PIN 7
#define DHT_TYPE DHT22  // aka AM2302

#define ULTRASONIC_SENSOR_TRIGGER_PIN 13
#define ULTRASONIC_SENSOR_ECHO_PIN 11
#define MAXIMUM_DISTANCE 400

// Variables
float humidity;
float temperatureCelcius;
float temperatureFahrenheit;
float duration;
float distance;
float soundMetersPerSecond;
float soundCentimetersPerMillisecond;
int iterations = 5;

NewPing sonar(ULTRASONIC_SENSOR_TRIGGER_PIN, ULTRASONIC_SENSOR_ECHO_PIN, MAXIMUM_DISTANCE);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Delay to enable the DHT-22 to stabalize
  delay(2000);

  // Read the humidity and temperature (in C & F)
  humidity = dht.readHumidity();
  temperatureCelcius = dht.readTemperature();
  temperatureFahrenheit = (temperatureCelcius * 1.8) + 32;

  // Calculate the speed of sound in meters per second
  // and then convert to centimeters per millisecond
  soundMetersPerSecond = 331.4 + (0.606 * temperatureCelcius) + (0.0124 * humidity);

  // Perform the ping
  duration = sonar.ping_median(iterations);

  // Print out the results of the sensors

  // Temperature
  Serial.print("  Celcius: ");
  Serial.print((int) temperatureCelcius);
  Serial.print("C");
  Serial.print("  Fahrenheit: ");
  Serial.print((int) temperatureFahrenheit);
  Serial.print("F");

  // Humidity
  Serial.print("  Humidity: ");
  Serial.print((int) humidity);
  Serial.print("%");

  // Speed of Sound
  Serial.print("  Speed of sound: ");
  Serial.print((int) soundMetersPerSecond);
  Serial.print(" m/s");

  // Distance
  distance = (duration / 2) * (soundMetersPerSecond / 10000);
  Serial.print("  Distance: ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("OOR");
  } else {
    Serial.print((int) distance);
    Serial.println(" cm");
  }
}
