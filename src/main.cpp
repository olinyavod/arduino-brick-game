#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <BrickGame.h>

constexpr uint16_t BLINKING_RATE = 1000;
constexpr uint8_t SCREEN_WIDTH = ST7735_TFTWIDTH_128;
constexpr uint8_t SCREEN_HEIGHT = ST7735_TFTHEIGHT_160;

#define TFT_CS     10         // TFT CS pin is connected to arduino pin 10
#define TFT_DC     9          // TFT DC pin is connected to arduino pin 9
#define TFT_RST    8 

Adafruit_ST7735 display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

auto _foreColor = ST7735_BLACK;
auto _backColor = ST7735_WHITE;

auto _game = BrickGame(&display, SCREEN_WIDTH, SCREEN_HEIGHT, _foreColor, _backColor);

uint32_t _seconds = 0;

void setup() {
  // put your setup code here, to run once:
  //_seconds = 0;

  display.initR(INITR_18BLACKTAB);
  display.setRotation(2);

  _game.restart();

  /*display.setCursor(_lineX+3, 30);
  display.setTextColor(_foreColor);
  display.setTextSize(0);
  display.print("LEVEL:8");
  
  display.setCursor(_lineX+3, 40);
  display.print("SPEED:8");*/

}

unsigned long _time = 0;

void loop() {
  auto milliseconds = millis();
  auto delta = milliseconds-_time;
  
  _game.loop(delta);
  // put your main code here, to run repeatedly:
  _game.setScore(delta);
  _time = milliseconds;  
}