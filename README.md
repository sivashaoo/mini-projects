<div align="center">

# SIVASAHOO.N

### Electrical Engineering • Embedded Systems • IoT

Designing practical hardware-focused projects with microcontrollers, sensors, automation, and connected systems.

[![GitHub](https://img.shields.io/badge/GitHub-sivashaoo-181717?style=flat&logo=github)](https://github.com/sivashaoo)
[![Mini Projects](https://img.shields.io/badge/Portfolio-Mini%20Projects-0A7EA4?style=flat&logo=arduino)](https://github.com/sivashaoo/mini-projects)
[![Major Projects](https://img.shields.io/badge/Portfolio-Major%20Projects-2457A7?style=flat&logo=github)](https://github.com/sivashaoo/major-projects-)

</div>

---

## About this repository

A curated collection of embedded and IoT mini projects focused on hands-on learning, sensor interfacing, firmware development, and hardware integration.

**Core areas:** ESP32 · Arduino · Sensor Interfacing · Embedded C/C++ · IoT Prototyping

## Project Index

### Embedded and Interactive Projects

| Project | Overview | Resources |
|---|---|---|
| **ESP32 Air Mouse** | Motion-based cursor control using an inertial sensor | [Code & docs](./esp32-air-mouse/) |
| **ESP32 Dino Game** | Embedded display-based mini-game | [Code & docs](./esp32-dino-game/) |
| **ESP32 Blynk Temperature Monitor** | Temperature monitoring with Blynk IoT integration | [Project folder](./esp32-blynk-temperature-monitor/) |

### Sensor Interfacing Technique Report Projects

| Project | Implementation scope | Resources |
|---|---|---|
| **Project 5 — Smart City Traffic, Waste, and Pollution Monitoring** | IR event counting and ultrasonic bin-distance demonstration | [README](./smart-city-monitoring/README.md) · [Firmware](./smart-city-monitoring/code/smart_city_monitoring_report_template.ino) · [Connections](./smart-city-monitoring/hardware/connections.md) |
| **Project 6 — Environmental Monitoring: Pollution, Wildfire, and Wildlife Observation** | DHT22 temperature/humidity and PIR motion alert demonstration | [README](./environmental-monitoring/README.md) · [Firmware](./environmental-monitoring/code/environmental_monitoring_report_template.ino) · [Connections](./environmental-monitoring/hardware/connections.md) |
| **Project 18 — Smart Parking Management and Payment-System Demonstrator** | Single-bay ultrasonic occupancy demonstration | [README](./smart-parking/README.md) · [Firmware](./smart-parking/code/smart_parking_report_template.ino) · [Connections](./smart-parking/hardware/connections.md) |
| **Project 20 — Smart Waste Management and Sustainable Recycling** | Ultrasonic bin-fill estimate and collection-threshold alert | [README](./smart-waste-management/README.md) · [Firmware](./smart-waste-management/code/smart_waste_management_report_template.ino) · [Connections](./smart-waste-management/hardware/connections.md) |

## How to use a project

1. Open its README and review the required components and libraries.
2. Check the hardware connection guide before wiring.
3. Open the firmware in Arduino IDE and select the correct board and port.
4. Configure pins and calibrate thresholds for the exact sensor modules.
5. Compile and test the project before adapting it to a real application.

## Engineering and verification notes

- Report-derived examples are identified as starter templates; they are not represented as fully validated systems.
- Sensor accuracy depends on module quality, calibration, wiring, and environment.
- ESP32 GPIO pins are **not 5 V tolerant**. Use a suitable level shifter or voltage divider for 5 V signals such as common HC-SR04 ECHO outputs.
- Safety-critical, automotive, environmental, and payment applications require substantially more engineering and validation than a demonstration sketch.

## Related work

- **Major engineering projects:** [sivashaoo/major-projects-](https://github.com/sivashaoo/major-projects-)
- **GitHub profile:** [github.com/sivashaoo](https://github.com/sivashaoo)

---

<div align="center">
<sub>Built for learning, experimentation, and iterative engineering improvement.</sub>
</div>
