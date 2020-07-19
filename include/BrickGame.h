#ifndef _BRICK_GAME_INCLUDED
#define _BRICK_GAME_INCLUDED

#include <Adafruit_SPITFT.h>
#include <GameStateBase.h>
#include <BrickGameBase.h>
#include <GameMenuState.h>
#include <GameOverState.h>

constexpr uint8_t BRICK_SIZE = 7;
constexpr uint8_t BRICK_INTO_SIZE = (BRICK_SIZE - 4);

const uint8_t _digitTable[10] PROGMEM = {
        0x5F,//0
        0x05,//1
        0x76,//2 
        0x75,//3
        0x2D,//4
        0x79,//5
        0x7B,//6
        0x45,//7 
        0x7F,//8
        0x7D//9
    };

class BrickGame : public BrickGameBase
{
private:
    const uint8_t _lineX = ((BRICK_SIZE+1)*GAME_WIDTH);
    uint16_t _x=0, _y=0;
    int8_t _dx=0, _dy=0, _spin = 00;

    uint32_t _score = 0;
    Adafruit_SPITFT * _display;
    GameStateBase * _currentState = NULL;
    uint8_t _screenWidth, _screenHeight;
    uint16_t _foreColor, _backColor;     
    uint16_t _gameDisplay[GAME_HEIGHT];
    uint16_t _actualGameDisplay[GAME_HEIGHT];
    uint8_t _icon[ICON_SIZE];

    void drawBrick(uint8_t x, uint8_t y, uint16_t color);
    void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint8_t size);
    
    inline uint16_t checkVisibleFlag(uint8_t &hash, uint8_t mask, uint16_t foreColor, uint16_t backColor){
        auto color = hash & mask ? foreColor : backColor; 
        hash<<=1;
        return color;
    }

    inline void pow10(uint32_t  &value, uint8_t pow){
        value = 1;
        for(uint8_t i = 0; i < pow; i++)
            value=value*10;
    }

public:
    BrickGame(Adafruit_SPITFT * display, uint8_t screenWidth, uint8_t screenHeight, uint16_t foreColor, uint16_t backColor)
        : _display(display), 
        _screenWidth(screenWidth), 
        _screenHeight(screenHeight), 
        _foreColor(foreColor), 
        _backColor(backColor)
    {

    }
    ~BrickGame();

    void loop(uint16_t delta);
    void restart();
    void setScore(uint32_t score) override;
    uint32_t getScore() override;
    void setIcon(uint8_t *data) override;
    void setPixel(uint8_t x, uint8_t y, bool value) override;
    bool getPixel(uint8_t x, uint8_t y) override;
    uint16_t getRow(uint8_t y) override;
    void setRow(uint8_t y, uint16_t row) override;
    void changeState(GameTrigger trigger) override;
};

#endif