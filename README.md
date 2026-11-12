# Mini Projects – Embedded Systems & IoT

**Sivasahoo.N** · Electrical Engineering · Embedded Systems · IoT

A curated collection of practical mini projects focused on ESP32, Arduino, sensor interfacing, firmware development, and hardware prototyping. These projects are designed for learning, experimentation, and building a strong foundation in real-world embedded applications.

---

## Project Index

### Interactive & Display Projects

| Project | Description | Key Technologies | Link |
|---------|-------------|------------------|------|
| **ESP32 Air Mouse** | Motion-based cursor control using an inertial sensor | ESP32, MPU6050 / similar IMU | [View](./esp32-air-mouse/) |
| **ESP32 Dino Game** | Simple embedded display-based game | ESP32, OLED / display | [View](./esp32-dino-game/) |
| **ESP32 Blynk Temperature Monitor** | Temperature monitoring with Blynk IoT dashboard | ESP32, DHT / DS18B20, Blynk | [View](./esp32-blynk-temperature-monitor/) |

### Sensor Interfacing & Application Demonstrators

| Project | Description | Key Technologies | Link |
|---------|-------------|------------------|------|
| **Smart City Monitoring** | IR event counting + ultrasonic bin-distance demo | ESP32 / Arduino, IR, Ultrasonic | [View](./smart-city-monitoring/) |
| **Environmental Monitoring** | Temperature, humidity and motion alert demonstration | DHT22, PIR | [View](./environmental-monitoring/) |
| **Smart Parking** | Single-bay ultrasonic occupancy demonstrator | Ultrasonic (HC-SR04) | [View](./smart-parking/) |
| **Smart Waste Management** | Ultrasonic bin-fill estimation and threshold alert | Ultrasonic, ESP32 / Arduino | [View](./smart-waste-management/) |

---

## How to Use Any Project

1. Open the project folder and read its `README.md`
2. Review the required components and libraries
3. Check the hardware connection notes / wiring guide
4. Open the firmware in Arduino IDE
5. Select the correct board and port
6. Configure pins and calibrate thresholds for your specific sensor modules
7. Compile, upload, and test

---

## Engineering Notes & Limitations

- Most projects are **starter templates / demonstrators**. They are intentionally kept simple for learning and rapid prototyping.
- Sensor accuracy depends on module quality, calibration, wiring, and environmental conditions.
- **ESP32 GPIO pins are not 5 V tolerant.** Use a level shifter or voltage divider when interfacing 5 V sensors (e.g. HC-SR04 ECHO pin).
- Safety-critical, automotive, environmental monitoring, or payment applications require significantly more engineering, validation, and certification than these demonstration sketches provide.
- Always test on actual hardware before claiming successful operation.

---

## Related Work

- **Major Engineering Projects** → [sivashaoo/major-projects-](https://github.com/sivashaoo/major-projects-)
- **GitHub Profile** → [github.com/sivashaoo](https://github.com/sivashaoo)

---

**Built for learning, experimentation, and iterative engineering improvement.**
