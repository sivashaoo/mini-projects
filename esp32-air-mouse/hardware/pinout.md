# ESP32 Air Mouse Pinout

## MPU6050

| MPU6050 | ESP32 | Function |
|---|---:|---|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| SDA | GPIO 21 | I2C data |
| SCL | GPIO 22 | I2C clock |

## Buttons

| Button | ESP32 | Connection |
|---|---:|---|
| Left Click | GPIO 19 | Other side to GND |
| Right Click | GPIO 18 | Other side to GND |

The firmware uses `INPUT_PULLUP`, so an unpressed button reads HIGH and a pressed button reads LOW.
