// Project 6: Environmental Monitoring — Pollution, Wildfire, and Wildlife Observation
// Source: Sensor Interfacing Technique Report, Project 6.
// ESP32: DHT22 + PIR event monitor. Demonstration only, not a certified fire alarm.

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int PIR = 27, ALERT_LED = 2;
const float TEMP_ALERT = 40.0; // demonstration threshold only

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PIR, INPUT);
  pinMode(ALERT_LED, OUTPUT);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  bool valid = !(isnan(t) || isnan(h));
  bool motion = digitalRead(PIR);
  bool alert = motion || (valid && t >= TEMP_ALERT);

  digitalWrite(ALERT_LED, alert ? HIGH : LOW);
  if (valid) Serial.printf("temp=%.1fC humidity=%.1f%% ", t, h);
  else Serial.print("DHT_ERROR ");
  Serial.printf("motion=%d alert=%d\n", motion, alert);
  delay(2000);
}