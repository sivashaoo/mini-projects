// Project 20: Smart Waste Management and Sustainable Recycling
// Source: Sensor Interfacing Technique Report, Project 20.
// ESP32: ultrasonic waste-bin fill estimate.

const int TRIG = 5, ECHO = 18, LED = 2;
const float EMPTY_DEPTH_CM = 80.0;
const float FULL_THRESHOLD = 80.0; // percent; adjust to collection policy

float getDistance() {
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
  float d = getDistance();
  if (d < 0 || d > EMPTY_DEPTH_CM + 10) {
    Serial.println("SENSOR_ERROR");
    digitalWrite(LED, LOW);
  } else {
    float fill = constrain((EMPTY_DEPTH_CM - d) / EMPTY_DEPTH_CM * 100.0, 0, 100);
    bool collect = fill >= FULL_THRESHOLD;
    digitalWrite(LED, collect ? HIGH : LOW);
    Serial.printf("distance=%.1fcm fill_estimate=%.1f%% collect=%d\n", d, fill, collect);
  }
  delay(2000);
}