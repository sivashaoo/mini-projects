// Project 18: Smart Parking Management and Payment-System Demonstrator
// Source: Sensor Interfacing Technique Report, Project 18.
// ESP32: one-bay ultrasonic occupancy demonstrator.
// Payment is not implemented; no credentials are collected.

const int TRIG = 5, ECHO = 18, LED = 2;
const float OCCUPIED_CM = 35.0; // calibrate for model

float readCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);
  return us ? us * 0.0343 / 2.0 : -1;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  float d = readCm();
  if (d < 0) {
    Serial.println("BAY=UNKNOWN");
    digitalWrite(LED, LOW);
  } else {
    bool occupied = d < OCCUPIED_CM;
    digitalWrite(LED, occupied ? HIGH : LOW);
    Serial.printf("distance=%.1fcm bay=%s\n", d, occupied ? "OCCUPIED" : "VACANT");
  }
  delay(500);
}