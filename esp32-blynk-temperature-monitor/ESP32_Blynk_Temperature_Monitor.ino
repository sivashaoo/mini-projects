#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "ESP32 Temperature Monitor"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <DHT.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

#define DHT_PIN 6
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define OLED_SDA 5
#define OLED_SCL 4

U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(
  U8G2_R0,
  U8X8_PIN_NONE
);

BlynkTimer timer;

float temperature;
float humidity;
bool dangerAlertSent = false;

void readTemperature() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 ERROR");

    oled.clearBuffer();
    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(20, 25, "DHT11 ERROR");
    oled.setFont(u8g2_font_6x10_tr);
    oled.drawStr(15, 45, "CHECK SENSOR");
    oled.sendBuffer();
    return;
  }

  String level;

  if (temperature < 29.0) {
    level = "LOW";
  } else if (temperature <= 35.0) {
    level = "NORMAL";
  } else if (temperature <= 40.0) {
    level = "MID";
  } else {
    level = "DANGER";
  }

  Serial.println("-------------------------");
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Level: ");
  Serial.println(level);

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);

  oled.clearBuffer();

  oled.setFont(u8g2_font_ncenB08_tr);
  oled.drawStr(20, 10, "TEMP MONITOR");
  oled.drawLine(0, 13, 127, 13);

  oled.setFont(u8g2_font_6x10_tr);
  oled.drawStr(5, 27, "TEMP:");

  char tempText[20];
  snprintf(tempText, sizeof(tempText), "%.1f C", temperature);
  oled.drawStr(55, 27, tempText);

  oled.drawStr(5, 39, "HUM:");

  char humText[20];
  snprintf(humText, sizeof(humText), "%.1f %%", humidity);
  oled.drawStr(55, 39, humText);

  oled.drawStr(5, 52, "LEVEL:");

  oled.setFont(u8g2_font_ncenB08_tr);
  oled.drawStr(55, 52, level.c_str());

  if (temperature > 40.0) {
    oled.setFont(u8g2_font_6x10_tr);
    oled.drawStr(5, 63, "!! DANGER !!");
  }

  oled.sendBuffer();

  if (temperature > 40.0 && !dangerAlertSent) {
    Blynk.logEvent(
      "danger_temperature",
      "DANGER! Temperature exceeded 40 C"
    );

    Serial.println("BLYNK DANGER NOTIFICATION SENT");
    dangerAlertSent = true;
  }

  if (temperature <= 40.0) {
    dangerAlertSent = false;
  }
}

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);
  oled.begin();

  oled.clearBuffer();
  oled.setFont(u8g2_font_ncenB08_tr);
  oled.drawStr(20, 25, "TEMP MONITOR");
  oled.drawStr(25, 45, "CONNECTING...");
  oled.sendBuffer();

  delay(1500);

  dht.begin();

  Serial.println("Connecting to Blynk...");

  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  timer.setInterval(3000L, readTemperature);
}

void loop() {
  Blynk.run();
  timer.run();
}
