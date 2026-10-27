# 🧠 Working Principle

The ESP32 runs the complete game loop and controls the ILI9341 TFT through SPI.

## 1. Initialization

At startup the program:

- Configures GPIO 14 as an input with the internal pull-up.
- Initializes the ILI9341 display.
- Sets portrait orientation.
- Clears the screen.
- Draws the ground and initializes the game variables.

## 2. Button Input

When the button is pressed while the dinosaur is on the ground, a jump begins.

```cpp
if (digitalRead(BUTTON_PIN) == LOW && !isJumping) {
  isJumping = true;
  jumpForce = -12;
}
```

The same button restarts the game after Game Over.

## 3. Jump Physics

The dinosaur position is updated using a simple velocity-and-gravity model.

```cpp
dinoY += jumpForce;
jumpForce += 1;
```

When the dinosaur reaches its ground position, the jump is stopped.

## 4. Obstacle Movement

The cactus moves from the right side of the display toward the dinosaur.

```cpp
obsX -= gameSpeed;
```

After the cactus leaves the screen, it is respawned at the right edge and the score increases.

## 5. Difficulty

Every five points, the obstacle speed increases by one unit.

This creates progressively harder gameplay.

## 6. Collision Detection

The dinosaur and cactus are represented by rectangular bounding boxes. A collision occurs when their bounding boxes overlap.

When a collision occurs:

```text
Collision detected
       ↓
 gameOver = true
       ↓
Game Over screen
       ↓
Button press
       ↓
Game restart
```

## 7. Display Rendering

Instead of clearing the complete screen on every frame, the program clears the previous dinosaur and obstacle positions and redraws the updated objects. This reduces visible screen blinking.

## 8. Overall Flow

```text
             START
               │
               ▼
       Initialize ESP32/TFT
               │
               ▼
          Read Button
               │
               ▼
         Update Dino Jump
               │
               ▼
        Move Cactus
               │
               ▼
      Check Collision
          │          │
        YES          NO
          │          │
          ▼          ▼
     Game Over    Update Screen
          │          │
          └────┬─────┘
               ▼
          Update Score
               │
               ▼
          Repeat Loop
```
