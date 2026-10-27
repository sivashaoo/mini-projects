# Project 5 — Hardware Connections

| Module | ESP32 pin | Notes |
|---|---|---|
| IR sensor digital OUT | GPIO27 | The sketch counts FALLING edges; check the sensor's output polarity |
| HC-SR04 TRIG | GPIO5 | Trigger output |
| HC-SR04 ECHO | GPIO18 through a voltage divider/level shifter | Do not feed 5 V directly into ESP32 |
| LED anode | GPIO2 through current-limiting resistor | LED cathode to GND |
| Sensor grounds | ESP32 GND | Common ground for low-voltage modules |
| BME280 (optional) SDA/SCL | GPIO21/GPIO22 | Not read by the included starter sketch |
| Gas sensor (optional) | Per module interface | Not read by the included starter sketch; check voltage/current needs |

## Test
1. Test the IR output and confirm the event counter increments.
2. Measure known distances with the HC-SR04.
3. Verify the LED turns on only below the example 10 cm threshold.
4. Adjust the threshold for the actual bin geometry.

The PDF code uses the pins shown above. The BME280/gas sensor are listed as optional components in the report but are not implemented in this starter program.