# 🖱️ ESP32 Air Mouse

A wireless air mouse built using an **ESP32** and **MPU6050** motion sensor. Hand movement controls the computer cursor through Bluetooth HID, while two physical buttons provide left and right mouse clicks.

## ✨ Features

- Wireless Bluetooth mouse control
- Motion-based cursor movement
- MPU6050 gyroscope sensing
- Left-click and right-click buttons
- Adjustable sensitivity
- Dead-zone filtering
- Movement smoothing
- Works as a HID mouse on compatible computers

## 🔧 Hardware

- ESP32 development board
- MPU6050 accelerometer/gyroscope
- 2 push buttons
- Jumper wires
- Breadboard
- USB cable for programming/power

## 🔌 Pin Connections

### MPU6050 → ESP32

| MPU6050 | ESP32 |
|---|---:|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### Buttons → ESP32

| Function | GPIO | Other button terminal |
|---|---:|---|
| Left click | GPIO 19 | GND |
| Right click | GPIO 18 | GND |

The buttons use the ESP32 internal pull-up resistors.

## 🧠 Working

```text
Hand Movement
      ↓
   MPU6050
      ↓ I2C
    ESP32
      ↓
 Bluetooth HID
      ↓
 Laptop / PC
      ↓
Mouse Cursor
```

The gyroscope detects rotation of the controller. ESP32 converts the measured motion into X/Y mouse movement and transmits it wirelessly over Bluetooth.

## 💻 Required Libraries

Install these libraries in Arduino IDE:

- Adafruit GFX is not required for this project.
- `MPU6050` compatible library
- `ESP32 BLE Mouse` library

The firmware uses `Wire.h` for I2C and `BleMouse.h` for Bluetooth HID mouse control.

## 🚀 Uploading

1. Open `src/esp32-air-mouse.ino` in Arduino IDE.
2. Select your ESP32 board.
3. Install the required libraries.
4. Connect ESP32 through USB.
5. Select the correct COM port.
6. Upload the program.
7. Open Serial Monitor at **115200 baud**.
8. Pair the computer with **ESP32 Air Mouse**.
9. Move the ESP32 to control the cursor.

## 🎮 Controls

| Action | Control |
|---|---|
| Move cursor | Rotate/move ESP32 |
| Left click | GPIO 19 button |
| Right click | GPIO 18 button |

## ⚙️ Sensitivity

The main sensitivity value is defined in the firmware:

```cpp
float sensitivity = 0.035;
```

Increase it for faster cursor movement or decrease it for finer control.

## 📁 Project Structure

```text
essp32-air-mouse/
├── README.md
├── src/
│   └── esp32-air-mouse.ino
├── hardware/
│   └── pinout.md
└── docs/
    └── working-principle.md
```

## 🔮 Future Improvements

- Scroll control using additional gesture
- Click-and-drag gesture
- Adjustable sensitivity buttons
- Battery-powered wearable enclosure
- Rechargeable Li-ion power system
- Gesture shortcuts
- Calibration mode
- 3D printed ergonomic enclosure

## ⚠️ Note

This is an educational prototype. Bluetooth HID compatibility can vary between host devices and ESP32 firmware/library versions.
