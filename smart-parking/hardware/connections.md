# Project 18 — Hardware Connections

| Component | ESP32 pin | Notes |
|---|---|---|
| HC-SR04 TRIG | GPIO5 | Trigger output |
| HC-SR04 ECHO | GPIO18 through a voltage divider/level shifter | Sensor ECHO is commonly 5 V |
| HC-SR04 VCC | 5 V supply as specified by module | Do not power from a GPIO |
| HC-SR04 GND | GND | Common ground |
| LED anode | GPIO2 through current-limiting resistor | LED cathode to GND |

## Calibration and testing
Measure the sensor distance with the model bay empty and with a model car present. Set `OCCUPIED_CM` to a value that reliably separates these two cases. If the sensor returns no echo, the code reports `BAY=UNKNOWN` and switches the LED off.

The report suggests a 35 cm example threshold, which must be calibrated for the actual model. This is a one-bay demonstrator; payment processing and multi-bay logic are not included.