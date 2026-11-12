# Project 6 — Hardware Connections

| Module | ESP32 pin | Notes |
|---|---|---|
| DHT22 VCC | Compatible supply for the module | Check breakout specifications |
| DHT22 DATA | GPIO4 | Bare sensors commonly require a pull-up; follow datasheet/module notes |
| DHT22 GND | GND | Common ground |
| PIR OUT | GPIO27 | Confirm output logic and warm-up behavior |
| PIR VCC/GND | As specified by PIR module | Check output voltage compatibility with ESP32 |
| LED anode | GPIO2 through current-limiting resistor | LED cathode to GND |

## Test
Install the DHT library, upload the firmware, and open Serial Monitor at 115200 baud. Wait for the PIR to stabilize, then move through its detection area. The alert LED activates for motion or a valid temperature reading at/above 40 °C.

The 40 °C limit is only a report demonstration value. This hobby prototype is not a certified fire detector or safety system.