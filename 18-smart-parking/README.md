# Project 18 — Smart Parking Management and Payment-System Demonstrator

**Source:** Sensor Interfacing Technique Report, Project 18 — Program Code / Integration Template.  
**Category:** Mini project / smart mobility.

## Purpose
Use an ultrasonic sensor to classify a single model parking bay as occupied, vacant, or unknown and show status through Serial Monitor and an LED. Payment is only a mock concept in the report; the included code does not process payments.

## Components
- ESP32 development board
- HC-SR04 ultrasonic sensor
- LED with current-limiting resistor
- Model parking bay and small model vehicle
- Jumper wires
- Optional OLED/LCD or barrier servo (not included in starter code)

## Files
- [Report starter firmware](code/smart_parking_report_template.ino)
- [Hardware connections](hardware/connections.md)

## Setup
1. Connect the HC-SR04 according to the pin table.
2. Upload the sketch and open Serial Monitor at 115200 baud.
3. Measure the distance with the bay empty and occupied by the model vehicle.
4. Calibrate `OCCUPIED_CM` for your physical setup.
5. Check the `BAY=UNKNOWN` response when no echo is returned.

## Limitations
The report's code supports one bay only. It does not implement a multi-bay counter, display, cloud dashboard, barrier servo, or real payment provider. Do not collect or store financial credentials in this demonstrator.

## Safety
HC-SR04 ECHO is typically 5 V. Use a voltage divider or level shifter before GPIO18; never apply 5 V logic directly to ESP32 GPIO.