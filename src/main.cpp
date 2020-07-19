#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <BrickGame.h>

constexpr uint16_t BLINKING_RATE = 1000;
constexpr uint8_t SCREEN_WIDTH = ST7735_TFTWIDTH_128;
constexpr uint8_t SCREEN_HEIGHT = ST7735_TFTHEIGHT_160;

#define TFT_CS        10         // TFT CS pin is connected to arduino pin 10
#define TFT_DC        9          // TFT DC pin is connected to arduino pin 9
#define TFT_RST       8 
#define BUTTONS_PIN   A0
#define BUTTON_UP     941
#define BUTTON_LEFT   1023
#define BUTTON_RIGTH  961
#define BUTTON_DOWN   1002
#define BUTTON_OK     923

Adafruit_ST7735 display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

auto _foreColor = ST7735_BLACK;
auto _backColor = ST7735_WHITE;
uint8_t _analog_ref = DEFAULT;

auto _game = BrickGame(&display, SCREEN_WIDTH, SCREEN_HEIGHT, _foreColor, _backColor);

uint32_t _seconds = 0;

ISR(ADC_vect){
  int result = (ADCL>> 6) | (ADCH << 2);

  switch (result)
  {
  case BUTTON_UP:
    _game.setButtonState(ButtonState::UP);
    break;

  case BUTTON_DOWN:
    _game.setButtonState(ButtonState::DOWN);
    break;

  case BUTTON_LEFT:
    _game.setButtonState(ButtonState::LEFT);
    break;

  case BUTTON_RIGTH:
    _game.setButtonState(ButtonState::RIGTH);
    break;

  case BUTTON_OK:
    _game.setButtonState(ButtonState::OK);
    break;
  
  default:
    _game.setButtonState(ButtonState::None);
    break;
  }
}

void setup() {

  // put your setup code here, to run once:
  //_seconds = 0;
  //pinMode(BUTTONS_PIN, INPUT);

  display.initR(INITR_18BLACKTAB);
  display.setRotation(2);

  _game.restart();

  /*display.setCursor(_lineX+3, 30);
  display.setTextColor(_foreColor);
  display.setTextSize(0);
  display.print("LEVEL:8");
  
  display.setCursor(_lineX+3, 40);
  display.print("SPEED:8");*/

  ADCSRA = 0;             // Сбрасываем регистр ADCSRA
  ADCSRB = 0;             // Сбрасываем регистр ADCSRB
  ADMUX |= (1 << REFS0);  // Задаем ИОН
  
  ADMUX |= (1 << ADLAR);  // Меняем порядок записи бит, чтобы можно было читать только 8 бит регистра ADCH
                          // Таким образом отсекаются 2 последних "шумных" бита, результат 8-битный (0...255)
  
  ADMUX |= (0 & 0x07);    // Выбираем пин A0 для преобразования
  // Устанавливаем предделитель - 128 (ADPS[2:0]=111)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);                     //Биту ADPS2 присваиваем единицу  

  ADCSRA |= (1 << ADATE); // Включаем автоматическое преобразование
  ADCSRA |= (1 << ADIE);  // Разрешаем прерывания по завершении преобразования
  ADCSRA |= (1 << ADEN);  // Включаем АЦП
  ADCSRA |= (1 << ADSC);  // Запускаем преобразование
}

unsigned long _time = 0;

void loop() {
  auto milliseconds = millis();
  auto delta = milliseconds-_time;
  
  _game.loop(delta);
  // put your main code here, to run repeatedly:  
  _time = milliseconds;  
}