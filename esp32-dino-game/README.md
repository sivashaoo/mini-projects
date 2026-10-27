# 🎮 ESP32 Dino Game

A simple Chrome Dino-style game built with an **ESP32**, **ILI9341 240×320 TFT display**, and a **push button**.

The project demonstrates embedded graphics, button input, jump physics, obstacle movement, collision detection, score handling, and a progressively increasing game speed.

## ✨ Features

- ESP32-based standalone game
- ILI9341 TFT in portrait orientation
- Physical button for jumping
- Button also restarts the game after Game Over
- Pixel-style dinosaur and cactus graphics
- Gravity-based jumping
- Real-time collision detection
- Score counter
- Automatic difficulty increase every 5 points
- Partial screen redraw to reduce visible blinking
- Simple and low-cost hardware

## 🧰 Hardware

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 development board | 1 | Main controller |
| ILI9341 240×320 TFT | 1 | Game display |
| Push button | 1 | Jump / Restart |
| Jumper wires | As required | Connections |
| Breadboard | 1 | Prototype assembly |

## 🔌 Pin Connections

| ILI9341 / Input | ESP32 | Function |
|---|---:|---|
| CS | GPIO 15 | Chip Select |
| DC / RS | GPIO 2 | Data / Command |
| RST | GPIO 4 | Display Reset |
| SCK / CLK | GPIO 18 | SPI Clock |
| MOSI / SDI | GPIO 23 | SPI Data In |
| MISO / SDO | GPIO 19 | SPI Data Out |
| VCC | 3.3V | Display power |
| GND | GND | Common ground |
| Button | GPIO 14 | Game control |

> **Note:** The SPI pins above are the standard ESP32 VSPI pins used by the code through `SPI.h`. Check your particular ILI9341 module's pin labels before wiring it.

## 🎮 Controls

| Action | Control |
|---|---|
| Jump | Press button while running |
| Restart | Press button after Game Over |

The button uses `INPUT_PULLUP`, so it is connected between **GPIO 14 and GND**.

## 🧠 How It Works

```text
Push Button
     │
     ▼
   ESP32 ─────────► ILI9341 TFT
     │                    │
     │                    ▼
     │              Dino + Cactus
     │                    │
     ├── Jump Physics     │
     ├── Collision ───────┤
     ├── Score            │
     └── Speed Control    │
```

### Game loop

1. Read the button.
2. Start a jump when the button is pressed.
3. Apply gravity to the dinosaur.
4. Move the cactus toward the dinosaur.
5. Check the collision boxes.
6. Increase the score when the cactus leaves the screen.
7. Increase game speed every 5 points.
8. Update only the required screen areas to reduce blinking.
9. Show the Game Over screen after a collision.

## 🦖 Jump Physics

The dinosaur starts a jump with a negative vertical velocity:

```cpp
jumpForce = -12;
```

Gravity is then applied every game-loop iteration:

```cpp
dinoY += jumpForce;
jumpForce += 1;
```

When the dinosaur reaches the ground position, the jump is ended.

## 🌵 Obstacle and Difficulty

The cactus moves from right to left:

```cpp
obsX -= gameSpeed;
```

When the cactus leaves the display, the score increases. Every five points the game becomes faster:

```cpp
if (score % 5 == 0) gameSpeed++;
```

## 💥 Collision Detection

The game uses rectangular bounding boxes for the dinosaur and cactus. A collision changes the game state to `gameOver` and displays the restart screen.

## 📺 Display

The display is configured as a **240×320 portrait screen**:

```cpp
tft.setRotation(0);
```

The game uses a white background, black dinosaur, green cactus, black ground line, and a score display.

## 📚 Libraries

Install these libraries in the Arduino IDE:

- `Adafruit GFX Library`
- `Adafruit ILI9341`
- `SPI` (included with the Arduino ESP32 environment)

## 🚀 Upload Instructions

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Install the required Adafruit libraries.
4. Open `src/esp32-dino-game.ino`.
5. Select the correct ESP32 board.
6. Select the correct COM port.
7. Connect the circuit.
8. Upload the program.
9. Press the button to make the dinosaur jump.

## 📁 Repository Structure

```text
-esp32-dino-game/
│
├── README.md
│
├── src/
│   └── esp32-dino-game.ino
│
├── hardware/
│   ├── pinout.md
│   └── circuit-diagram.svg
│
└── docs/
    └── working-principle.md
```

## 🔧 Possible Improvements

Future versions can add:

- Buzzer sound effects
- Multiple obstacle types
- High-score storage using ESP32 NVS/Preferences
- Start menu
- Difficulty levels
- Two-button controls
- Touch-screen controls
- Battery operation
- More detailed sprite graphics
- OLED/TFT animation improvements
- Sleep mode for portable operation

## ⚠️ Note

This is an educational embedded-systems project. It is intended for learning, prototyping, and demonstration.

## 👨‍💻 Author

**Siva Shaoo**

Electrical Engineering / Embedded Systems Project
