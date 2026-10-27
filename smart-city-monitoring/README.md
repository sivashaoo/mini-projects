# Smart City Monitoring

**Source:** Sensor Interfacing Technique Report, Project 5 — Program Code / Integration Template.  
**Category:** Mini project / smart-city monitoring.

## Purpose
Combine a simple traffic-event counter, ultrasonic bin-distance reading, and optional environmental sensor readings into one ESP32 monitoring node. This folder preserves the report's starter sketch and documents its actual scope.

## Components
- ESP32 development board
- IR break-beam or reflective sensor
- HC-SR04 ultrasonic sensor
- LED with current-limiting resistor
- Optional BME280 and/or suitable calibrated gas-sensor module
- Jumper wires and breadboard

## Files
- [Report starter firmware](code/smart_city_monitoring_report_template.ino)
- [Hardware connections](hardware/connections.md)

## What the included code does
- Counts debounced falling-edge events from an IR sensor.
- Measures distance to a surface using the ultrasonic sensor.
- Prints event count and bin distance to Serial Monitor.
- Turns on an LED when a valid distance is under 10 cm.

## Setup
1. Select ESP32 in Arduino IDE.
2. Connect the sensors according to the connection table.
3. Upload the firmware and open Serial Monitor at 115200 baud.
4. Test the IR sensor by interrupting its beam and test ultrasonic distance with a flat target.
5. Calibrate the near-full distance for your bin.

## Scope limitations
The included PDF starter code does not read BME280 or gas-sensor values and does not implement a Wi-Fi dashboard. The LED threshold is an example, not a calibrated fill-level percentage. Vehicle-like events may not correspond to unique vehicles. This prototype does not provide certified pollution measurements.

## Safety
HC-SR04 ECHO is typically 5 V; use a voltage divider or suitable level shifter before connecting it to ESP32 GPIO18. Never apply 5 V logic directly to ESP32 GPIO.