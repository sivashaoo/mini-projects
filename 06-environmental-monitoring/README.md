# Project 6 — Environmental Monitoring: Pollution, Wildfire, and Wildlife Observation

**Source:** Sensor Interfacing Technique Report, Project 6 — Program Code / Integration Template.  
**Category:** Mini project / environmental sensing.

## Purpose
Read temperature and humidity from a DHT22, monitor motion with a PIR sensor, and activate a status LED when motion is detected or the example temperature threshold is reached.

## Components
- ESP32 development board
- DHT22 temperature/humidity sensor
- PIR motion sensor
- LED with current-limiting resistor
- Breadboard and jumper wires
- Optional buzzer driver, SD card, or environmental sensor modules (not included in the starter code)

## Files
- [Report starter firmware](code/environmental_monitoring_report_template.ino)
- [Hardware connections](hardware/connections.md)

## Setup
1. Install the DHT sensor library supported by your Arduino IDE.
2. Connect the DHT22 data line to GPIO4 and PIR output to GPIO27.
3. Connect the LED to GPIO2 through a current-limiting resistor.
4. Upload the sketch and open Serial Monitor at 115200 baud.
5. Allow the DHT22 to settle and wait for the PIR sensor's warm-up period.
6. Test motion detection and confirm the temperature threshold is suitable for your controlled demo.

## Limitations
The report's starter code does not read smoke/particulate sensors, does not identify wildlife species, and is not a certified wildfire alarm. The 40 °C threshold is a demonstration value only. PIR detects changes in infrared patterns, not species identity. Use safe test stimuli; do not create smoke or fire for testing.