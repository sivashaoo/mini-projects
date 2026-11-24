# 🖱️ ESP32 Air Mouse

**Control your computer cursor with hand gestures using ESP32 + MPU6050**

A fully wireless Bluetooth HID air mouse. Move your hand → the cursor moves. Two physical buttons give left and right clicks.

Perfect learning project for:
- Bluetooth HID on ESP32
- MPU6050 gyroscope/accelerometer
- Real-time sensor fusion & smoothing
- Practical embedded + HCI applications

---

## ✨ Features

- True wireless Bluetooth mouse (HID)
- Smooth motion-based cursor control
- Adjustable sensitivity + dead-zone filtering
- Left-click & right-click buttons
- Works on most modern computers (Windows, macOS, Linux, Android with HID support)
- Clean, readable Arduino code

---

## 🔧 Hardware Required

| Component              | Quantity |
|------------------------|----------|
| ESP32 Dev Board        | 1        |
| MPU6050 (GY-521)       | 1        |
| Push buttons           | 2        |
| Jumper wires           | -        |
| Breadboard (optional)  | 1        |
| USB cable              | 1        |

---

## 🔌 Pin Connections

### MPU6050 → ESP32

| MPU6050 | ESP32     |
|---------|-----------|
| VCC     | 3.3V      |
| GND     | GND       |
| SDA     | GPIO 21   |
| SCL     | GPIO 22   |

### Buttons → ESP32

| Function    | GPIO   | Other side |
|-------------|--------|------------|
| Left Click  | GPIO 19 | GND       |
| Right Click | GPIO 18 | GND       |

(Buttons use ESP32 internal pull-ups)

---

## 🧠 How It Works

```
Hand Movement
     ↓
  MPU6050 (Gyro)
     ↓ I2C
   ESP32
     ↓
Bluetooth HID
     ↓
Computer Cursor
```

The MPU6050 measures angular velocity. The ESP32 processes the data (dead-zone + sensitivity + smoothing) and sends standard mouse movement reports over Bluetooth Low Energy using the BLE Mouse library.

---

## 📚 Required Libraries

Install via Arduino Library Manager:

1. **ESP32 BLE Mouse** (by T-vK)
2. A compatible **MPU6050** library (or use the raw I2C approach in the code)

Also uses the built-in `Wire.h`.

---

## 🚀 Quick Start

1. Open `src/esp32-air-mouse.ino` in Arduino IDE
2. Select your **ESP32** board and correct COM port
3. Install the required libraries
4. Upload the sketch
5. Open Serial Monitor at **115200 baud** (for debug info)
6. On your computer, go to Bluetooth settings and pair with **"ESP32 Air Mouse"**
7. Move the board → cursor moves!

---

## 🎮 Controls

| Action          | How                          |
|-----------------|------------------------------|
| Move cursor     | Tilt / rotate the ESP32      |
| Left click      | Press button on GPIO 19      |
| Right click     | Press button on GPIO 18      |

### Sensitivity Tuning

In the code:

```cpp
float sensitivity = 0.035;   // Increase for faster movement
```

---

## 📁 Project Structure

```
esp32-air-mouse/
├── README.md
├── src/
│   └── esp32-air-mouse.ino
├── hardware/
│   └── pinout.md
└── docs/
    └── working-principle.md
```

---

## 🔮 Possible Upgrades

- Scroll wheel via gesture or extra button
- Click-and-drag support
- On-device sensitivity buttons
- Battery + 3D-printed handheld enclosure
- Gesture shortcuts (e.g. double-tap to click)
- Calibration routine on startup

---

## ⚠️ Notes

- This is an **educational prototype**. Bluetooth HID behaviour can vary slightly across operating systems and ESP32 core versions.
- Always power the MPU6050 from 3.3V.
- For best results, keep the sensor relatively still when not moving the cursor (dead-zone helps).

---

**Found this useful?** Give the [mini-projects repo](https://github.com/sivashaoo/mini-projects) a star ⭐  
Questions or improvements? Open an issue or PR!
