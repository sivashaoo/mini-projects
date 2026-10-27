# Project 20 — Smart Waste Management and Sustainable Recycling

**Source:** Sensor Interfacing Technique Report, Project 20 — Program Code / Integration Template.  
**Category:** Mini project / waste management.

## Purpose
Estimate the fill percentage of a bin using an ultrasonic sensor and switch on an LED when the configured collection threshold is reached. Sensor errors are reported in Serial Monitor.

## Components
- ESP32 development board
- HC-SR04 ultrasonic sensor
- LED with current-limiting resistor
- Bin/container model
- Jumper wires
- Optional load cell, battery/solar supply, or IoT dashboard (not included in starter code)

## Files
- [Report starter firmware](code/smart_waste_management_report_template.ino)
- [Hardware connections](hardware/connections.md)

## Setup
1. Measure the usable bin depth and set `EMPTY_DEPTH_CM`.
2. Connect the HC-SR04 and LED as listed in the hardware guide.
3. Upload the firmware and open Serial Monitor at 115200 baud.
4. Test at several safe fill heights.
5. Set `FULL_THRESHOLD` to match the chosen collection policy.

## Limitations
Fill percentage is an estimate and does not identify recyclable material. The report's sample depth of 80 cm and collection threshold of 80% are examples and must be calibrated. The starter code does not implement route planning, a dashboard, load-cell sensing, or automatic material recognition.

## Safety
HC-SR04 ECHO is typically 5 V. Use a voltage divider or suitable level shifter before ESP32 GPIO18. Mount the sensor away from lid movement and condensation.