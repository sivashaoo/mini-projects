#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Hardware SPI Pins for ILI9341
#define TFT_CS  15
#define TFT_DC  2
#define TFT_RST 4

// Initialize the display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_PIN 14

// Game Variables for 240x320 Portrait Window
const int groundY = 240;
int dinoX = 20;
int dinoY = 220;
int dinoOldY = 220;
int dinoW = 16;
int dinoH = 20;
bool isJumping = false;
int jumpForce = 0;
int obsX = 240;
int obsOldX = 240;
int obsY = 224;
int obsW = 12;
int obsH = 16;
int score = 0;
int oldScore = -1;
int gameSpeed = 5;
bool gameOver = false;

void resetGame();
void drawGameOver();
void drawDino(int x, int y, uint16_t color);
void drawCactus(int x, int y, uint16_t color);
void drawGround();

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  tft.begin();
  tft.setRotation(0);
  resetGame();
}

void loop() {
  if (gameOver) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      resetGame();
      delay(300);
    }
    return;
  }

  // Save old positions before calculations
  dinoOldY = dinoY;
  obsOldX = obsX;

  // Jump input handling
  if (digitalRead(BUTTON_PIN) == LOW && !isJumping) {
    isJumping = true;
    jumpForce = -12;
  }

  // Vertical gravity engine
  dinoY += jumpForce;
  jumpForce += 1;

  if (dinoY >= 220) {
    dinoY = 220;
    isJumping = false;
  }

  // Move obstacle
  obsX -= gameSpeed;

  if (obsX < -obsW) {
    tft.fillRect(obsOldX, obsY, obsW + gameSpeed, obsH, ILI9341_WHITE);
    obsX = 240;
    score++;
    if (score % 5 == 0) gameSpeed++;
  }

  // Collision box engine
  if (obsX < dinoX + dinoW &&
      obsX + obsW > dinoX &&
      obsY < dinoY + dinoH &&
      obsY + obsH > dinoY) {
    gameOver = true;
    drawGameOver();
    return;
  }

  // Smart portrait redraw to reduce screen blinking
  if (dinoY != dinoOldY) {
    tft.fillRect(dinoX, dinoOldY, dinoW, dinoH, ILI9341_WHITE);
  }
  drawDino(dinoX, dinoY, ILI9341_BLACK);

  // Clear trailing obstacle edge and update obstacle location
  tft.fillRect(obsOldX + obsW - gameSpeed, obsY,
               gameSpeed + 2, obsH, ILI9341_WHITE);
  drawCactus(obsX, obsY, ILI9341_DARKGREEN);

  // Maintain ground line
  drawGround();

  // Update score
  if (score != oldScore) {
    tft.fillRect(40, 10, 160, 25, ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(60, 15);
    tft.setTextSize(2);
    tft.print("SCORE: ");
    tft.print(score);
    oldScore = score;
  }

  delay(25);
}

void resetGame() {
  tft.fillScreen(ILI9341_WHITE);
  drawGround();

  dinoY = 220;
  dinoOldY = 220;
  isJumping = false;
  jumpForce = 0;
  obsX = 240;
  obsOldX = 240;
  score = 0;
  oldScore = -1;
  gameSpeed = 5;
  gameOver = false;
}

// ---------------- GRAPHICS ----------------

void drawDino(int x, int y, uint16_t color) {
  // Torso
  tft.fillRoundRect(x, y + 6, 14, 10, 2, color);

  // Head
  tft.fillRoundRect(x + 8, y, 8, 8, 2, color);

  // Tail
  tft.fillTriangle(x, y + 8, x, y + 14, x - 4, y + 12, color);

  // Legs
  tft.fillRect(x + 2, y + 16, 4, 4, color);
  tft.fillRect(x + 9, y + 16, 4, 4, color);

  // Eye
  if (color != ILI9341_WHITE) {
    tft.drawPixel(x + 13, y + 3, ILI9341_WHITE);
  }
}

void drawCactus(int x, int y, uint16_t color) {
  // Main trunk
  tft.fillRect(x + 4, y, 4, 16, color);

  // Right arm
  tft.fillRect(x + 6, y + 4, 6, 3, color);
  tft.fillRect(x + 9, y + 1, 3, 6, color);

  // Left arm
  tft.fillRect(x, y + 8, 4, 3, color);
  tft.fillRect(x, y + 5, 3, 6, color);
}

void drawGround() {
  for (int gx = 0; gx < 240; gx += 8) {
    tft.drawFastHLine(gx, groundY, 5, ILI9341_BLACK);
  }
}

// ---------------- GAME OVER ----------------

void drawGameOver() {
  tft.fillScreen(ILI9341_WHITE);

  // Decorative dino + cactus
  drawDino(30, 60, ILI9341_BLACK);
  drawCactus(190, 56, ILI9341_DARKGREEN);

  tft.setTextColor(ILI9341_RED);
  tft.setCursor(35, 100);
  tft.setTextSize(3);
  tft.print("GAME OVER");

  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(25, 160);
  tft.setTextSize(2);
  tft.print("Press Button");

  tft.setCursor(45, 190);
  tft.print("to Restart");
}
