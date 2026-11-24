# Mini Projects – Embedded Systems & IoT

**Sivasahoo.N** · Electrical Engineering · Embedded Systems · IoT

A growing collection of **practical, well-documented mini projects** using ESP32, Arduino, sensors, and IoT platforms.  
Perfect for students, hobbyists, and anyone learning real-world embedded development.

Every project includes:
- Clear objective
- Components list
- Hardware connection notes
- Working firmware
- Honest limitations

---

## Project Index

### Interactive & Display Projects

| Project | Description | Key Tech | Link |
|---------|-------------|----------|------|
| **ESP32 Air Mouse** | Control your computer cursor with hand motion using an IMU | ESP32 + MPU6050 | [View Project](./esp32-air-mouse/) |
| **ESP32 Dino Game** | Chrome Dino-style game on OLED display | ESP32 + OLED | [View Project](./esp32-dino-game/) |
| **ESP32 Blynk Temperature Monitor** | Live temperature dashboard with Blynk IoT | ESP32 + DHT/DS18B20 + Blynk | [View Project](./esp32-blynk-temperature-monitor/) |

### Sensor Interfacing & Real-World Demonstrators

| Project | Description | Key Tech | Link |
|---------|-------------|----------|------|
| **Smart City Monitoring** | IR event counting + ultrasonic distance demo | ESP32/Arduino + IR + Ultrasonic | [View Project](./smart-city-monitoring/) |
| **Environmental Monitoring** | Temperature, humidity & motion alerts | DHT22 + PIR | [View Project](./environmental-monitoring/) |
| **Smart Parking** | Single-bay ultrasonic occupancy detector | HC-SR04 Ultrasonic | [View Project](./smart-parking/) |
| **Smart Waste Management** | Bin fill-level estimation with threshold alerts | Ultrasonic + ESP32/Arduino | [View Project](./smart-waste-management/) |

---

## How to Use Any Project

1. Open the project folder and read its `README.md`
2. Gather the listed components
3. Follow the hardware connection / pinout guide
4. Open the `.ino` file in Arduino IDE
5. Select the correct board (ESP32 or Arduino) and port
6. Adjust pins/thresholds if needed for your hardware
7. Upload and test!

---

## Important Engineering Notes

- These are **learning-oriented demonstrators / starter templates** — intentionally kept clear and simple.
- Sensor performance depends on module quality, calibration, wiring quality, and environment.
- **ESP32 pins are not 5V tolerant.** Always use a level shifter or voltage divider with 5V sensors (especially HC-SR04 ECHO).
- These sketches are **not** production-ready for safety-critical, medical, automotive, or industrial control systems.
- Always validate on real hardware before relying on any project.

---

## Related Work

- **Major Projects** (larger electrical & industrial systems) → [sivashaoo/major-projects-](https://github.com/sivashaoo/major-projects-)
- **My GitHub Profile** → [github.com/sivashaoo](https://github.com/sivashaoo)

---

**Star this repo if you find the projects useful!**  
Feedback, improvements, and collaboration are always welcome.

Built for learning, experimentation, and iterative engineering improvement.
