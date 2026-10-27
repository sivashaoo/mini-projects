#include <Wire.h>
#include <MPU6050.h>
#include <BleMouse.h>

MPU6050 mpu;
BleMouse bleMouse("ESP32 Air Mouse", "Siva", 100);

#define SDA_PIN 21
#define SCL_PIN 22
#define LEFT_BUTTON 19
#define RIGHT_BUTTON 18

float sensitivity = 0.035;
int deadZone = 1500;
float smoothX = 0;
float smoothY = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection FAILED!");
    while (1) delay(1000);
  }

  Serial.println("MPU6050 connected!");
  bleMouse.begin();
  Serial.println("ESP32 Air Mouse ready!");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (bleMouse.isConnected()) {
    int moveX = 0;
    int moveY = 0;

    if (abs(gy) > deadZone) moveX = gy * sensitivity;
    if (abs(gx) > deadZone) moveY = -gx * sensitivity;

    moveX = constrain(moveX, -15, 15);
    moveY = constrain(moveY, -15, 15);

    smoothX = smoothX * 0.7 + moveX * 0.3;
    smoothY = smoothY * 0.7 + moveY * 0.3;

    if (abs(smoothX) >= 1 || abs(smoothY) >= 1) {
      bleMouse.move((int)smoothX, (int)smoothY);
    }

    if (digitalRead(LEFT_BUTTON) == LOW) {
      bleMouse.click(MOUSE_LEFT);
      delay(250);
      while (digitalRead(LEFT_BUTTON) == LOW) delay(10);
    }

    if (digitalRead(RIGHT_BUTTON) == LOW) {
      bleMouse.click(MOUSE_RIGHT);
      delay(250);
      while (digitalRead(RIGHT_BUTTON) == LOW) delay(10);
    }
  }

  delay(10);
}
