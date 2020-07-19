#ifndef _GAME_MENU_STATE_INCLUDED
#define _GAME_MENU_STATE_INCLUDED

#include <GameStateBase.h>

const uint16_t _chartA[] PROGMEM = {
    0xFFF, 0x387, 0x37B, 0x37B, 0x37B, 0x303, 0x37B, 0x37B, 0x37B, 0xFFF
};

const uint16_t _chartB[] PROGMEM = {
    0xFFF, 0x383, 0x37B, 0x37B, 0x383, 0x37B, 0x37B, 0x37B, 0x383, 0xFFF
};

const uint16_t _chartC[] PROGMEM = {
    0xFFF, 0x387, 0x37B, 0x3FB, 0x3FB, 0x3FB, 0x3FB, 0x37B, 0x387, 0xFFF
};

const uint16_t _chartD[] PROGMEM = {
    0xFFF, 0x383, 0x37B, 0x37B, 0x37B, 0x37B, 0x37B, 0x37B, 0x383, 0xFFF
};

const uint16_t _chartE[] PROGMEM = {
    0xFFF, 0x303, 0x3FB, 0x3FB, 0x383, 0x3FB, 0x3FB, 0x3FB, 0x303, 0xFFF
};

const uint16_t _chartF[] PROGMEM = {
    0xFFF, 0x303, 0x3FB, 0x3FB, 0x383, 0x3FB, 0x3FB, 0x3FB, 0x3FB, 0xFFF
};

const uint16_t *const _chartTable[] PROGMEM = {
    _chartA, _chartB, _chartC, _chartD, _chartE, _chartF
};

const uint8_t _gamesTable[] PROGMEM = {
    GameTrigger::GameOver, 
    GameTrigger::GameOver,
    GameTrigger::GameOver, 
    GameTrigger::GameOver, 
    GameTrigger::GameOver, 
    GameTrigger::GameOver
};

constexpr uint16_t MIN_SPEED = 1000;
constexpr uint16_t MAX_SPEED = 200;
constexpr uint8_t ACSELERATION = 50;
constexpr uint8_t MAX_GAME_COUNT = 6;

class GameMenuState : public GameStateBase
{
private:
    int8_t _selectTypeGame;
    uint16_t _speed, _acseleration;
    ButtonState _oldButtonState;
public:

    GameMenuState(BrickGameBase* game)
        :GameStateBase(game){
        _selectTypeGame = 0;
        _speed = MIN_SPEED;
        _acseleration = 0;
    }
    
    ~GameMenuState() override {

    }

    void loop(uint8_t delta) override;
    void init() override;
};

#endif
