# Working Principle

The ESP32 Air Mouse converts hand motion into wireless mouse movement.

1. The MPU6050 measures angular motion through its gyroscope.
2. ESP32 reads the MPU6050 over I2C.
3. A dead zone filters small unwanted movements.
4. Sensitivity and smoothing convert the motion into practical cursor movement.
5. ESP32 sends the movement to the computer using Bluetooth HID through the BLE Mouse library.
6. GPIO 19 acts as left click and GPIO 18 acts as right click.

```text
Hand movement
     ↓
  MPU6050
     ↓ I2C
   ESP32
     ↓ Bluetooth HID
 Laptop / PC
     ↓
 Mouse cursor
```
