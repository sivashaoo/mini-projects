# Project 20 — Hardware Connections

| Component | ESP32 pin | Notes |
|---|---|---|
| HC-SR04 TRIG | GPIO5 | Trigger output |
| HC-SR04 ECHO | GPIO18 through a voltage divider/level shifter | Never apply 5 V directly to ESP32 GPIO |
| HC-SR04 VCC | 5 V supply as specified by module | Verify module requirements |
| HC-SR04 GND | GND | Common ground |
| LED anode | GPIO2 through current-limiting resistor | LED cathode to GND |

## Calibration
1. Measure the distance from the sensor to the bin floor with the bin empty.
2. Set `EMPTY_DEPTH_CM` to the measured usable depth.
3. Add safe test objects at different heights and compare estimated fill percentage.
4. Set `FULL_THRESHOLD` to the desired collection trigger.
5. Check that missing/invalid echoes report `SENSOR_ERROR`.

The PDF uses 80 cm and 80% as examples only. Ultrasonic readings can vary with angled, soft, dusty, or wet waste surfaces. Fill percentage does not classify recyclable material.