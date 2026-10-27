# 🔌 ESP32 Dino Game Pinout

## ILI9341 TFT

| TFT Pin | ESP32 Pin | Purpose |
|---|---:|---|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| CS | GPIO 15 | Chip Select |
| DC / RS | GPIO 2 | Data / Command |
| RST | GPIO 4 | Reset |
| SCK / CLK | GPIO 18 | SPI Clock |
| MOSI / SDI | GPIO 23 | SPI Data In |
| MISO / SDO | GPIO 19 | SPI Data Out |
| LED | 3.3V | Backlight, if required by module |

## Push Button

Connect one side of the push button to **GPIO 14** and the other side to **GND**.

The code uses:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

Therefore the input is normally HIGH and becomes LOW when the button is pressed.

## Important

The exact labels can vary between ILI9341 breakout boards. Confirm the module's pin labels before powering the circuit. Use the display's supported supply voltage and avoid applying 5V to ESP32 GPIO pins.
