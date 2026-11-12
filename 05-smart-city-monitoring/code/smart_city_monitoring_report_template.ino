// Project 5: Smart City Traffic, Waste, and Pollution Monitoring
// Source: Sensor Interfacing Technique Report, Project 5.
// ESP32: ultrasonic bin-distance estimate + IR event count.
// Starter template; environmental sensor/dashboard integration is not included.

const int TRIG = 5, ECHO = 18, IR_PIN = 27, LED = 2;
volatile unsigned long events = 0;
unsigned long lastCount = 0;

void IRAM_ATTR onEvent() {
  unsigned long now = millis();
  if (now - lastCount > 250) {
    events++;
    lastCount = now;
  }
}

float distanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);
  if (!us) return -1;
  return us * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(IR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR_PIN), onEvent, FALLING);
}

void loop() {
  float d = distanceCm();
  Serial.printf("events=%lu bin_distance_cm=%.1f\n", events, d);
  digitalWrite(LED, (d > 0 && d < 10) ? HIGH : LOW); // near-full alert example
  delay(1000);
}