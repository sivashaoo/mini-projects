# Mini Projects — Electrical, Embedded Systems & IoT

A collection of practical mini projects using ESP32, sensors, displays, wireless control, and embedded programming. The sensor-interfacing projects below preserve the starter-code scope from the **Sensor Interfacing Technique Report** and include wiring notes.

## Existing projects

### ESP32 Air Mouse
A motion-controlled mouse using an ESP32 and an inertial sensor.

**Folder:** [esp32-air-mouse/](./esp32-air-mouse/)

- [Project README](./esp32-air-mouse/README.md)
- [Firmware](./esp32-air-mouse/src/esp32-air-mouse.ino)
- [Hardware pinout](./esp32-air-mouse/hardware/pinout.md)
- [Working principle](./esp32-air-mouse/docs/working-principle.md)

### ESP32 Dino Game
An embedded mini-game running on an ESP32.

**Folder:** [esp32-dino-game/](./esp32-dino-game/)

- [Project README](./esp32-dino-game/README.md)
- [Firmware](./esp32-dino-game/src/esp32-dino-game.ino)
- [Circuit diagram](./esp32-dino-game/hardware/circuit-diagram.svg)
- [Hardware pinout](./esp32-dino-game/hardware/pinout.md)
- [Working principle](./esp32-dino-game/docs/working-principle.md)

### ESP32 Blynk Temperature Monitor
An ESP32 temperature monitoring project with Blynk IoT integration.

**Folder:** [esp32-blynk-temperature-monitor/](./esp32-blynk-temperature-monitor/)

## Sensor Interfacing Technique Report — Selected Mini Projects

### Project 5 — Smart City Traffic, Waste, and Pollution Monitoring
ESP32 starter sketch counts IR sensor events and measures ultrasonic bin distance. Optional environmental sensors and the dashboard are not implemented in this starter code.

**Folder:** [05-smart-city-monitoring/](./smart-city-monitoring/)
- [README](./smart-city-monitoring/README.md)
- [Firmware](./smart-city-monitoring/code/smart_city_monitoring_report_template.ino)
- [Connections](./smart-city-monitoring/hardware/connections.md)

### Project 6 — Environmental Monitoring: Pollution, Wildfire, and Wildlife Observation
ESP32 + DHT22 + PIR starter sketch reports temperature/humidity and motion and triggers a demonstration LED alert. It is not a certified wildfire alarm.

**Folder:** [06-environmental-monitoring/](./environmental-monitoring/)
- [README](./environmental-monitoring/README.md)
- [Firmware](./environmental-monitoring/code/environmental_monitoring_report_template.ino)
- [Connections](./environmental-monitoring/hardware/connections.md)

### Project 18 — Smart Parking Management and Payment-System Demonstrator
ESP32 ultrasonic single-bay occupancy demonstrator with LED and serial status. Payment and multi-bay management are not implemented.

**Folder:** [18-smart-parking/](./smart-parking/)
- [README](./smart-parking/README.md)
- [Firmware](./smart-parking/code/smart_parking_report_template.ino)
- [Connections](./smart-parking/hardware/connections.md)

### Project 20 — Smart Waste Management and Sustainable Recycling
ESP32 ultrasonic bin-fill estimate with a configurable collection threshold and sensor-error status.

**Folder:** [20-smart-waste-management/](./smart-waste-management/)
- [README](./smart-waste-management/README.md)
- [Firmware](./smart-waste-management/code/smart_waste_management_report_template.ino)
- [Connections](./smart-waste-management/hardware/connections.md)

## Verification notes
- The sensor-interfacing programs are starter templates from the report, not experimentally verified production firmware.
- Check each project's README for libraries, pin connections, calibration and limitations.
- For ESP32, never connect 5 V logic directly to GPIO; use a suitable level shifter/divider where required.
- Compile and test on the intended hardware before claiming a working prototype.
