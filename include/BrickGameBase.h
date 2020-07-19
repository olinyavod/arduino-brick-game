#ifndef _BRICK_GAME_BASE_INCLUDED
#define _BRICK_GAME_BASE_INCLUDED

#include <stdint.h>

constexpr uint8_t GAME_WIDTH = 10;
constexpr uint8_t GAME_HEIGHT = 20;
constexpr uint8_t ICON_SIZE = 4;

enum ButtonState{
    None = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGTH = 8,
    OK = 16
};

enum GameTrigger{
    Menu,
    GameOver,
    Tanks,
    Snake,
    Tetris,
    Racing,
    Arcanoid
};

class BrickGameBase
{
private:
    ButtonState _buttonState;
public:
    inline ButtonState getButtonState(){
        return _buttonState;
    }

    inline void setButtonState(ButtonState state){
       _buttonState = state;
    }

    virtual void setPixel(uint8_t x, uint8_t y, bool value) { }
    virtual void setScore(uint32_t score) { } 
    virtual uint32_t getScore() { return 0; }
    virtual void setIcon(uint8_t * data) { }
    virtual bool getPixel(uint8_t x, uint8_t y) { return false;  }
    virtual uint16_t getRow(uint8_t y) { return 0; }
    virtual void setRow(uint8_t y, uint16_t row) { }
    virtual void changeState(GameTrigger trigger) { }
};

#endif