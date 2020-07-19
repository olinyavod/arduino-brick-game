#ifndef _GAME_OVER_STATE_INCLUDED
#define _GAME_OVER_STATE_INCLUDED

#include <GameStateBase.h>
#include <BrickGameBase.h>

constexpr uint16_t SPEED = 10;

class GameOverState : public GameStateBase
{
private:
    int8_t _dx, _dy;
    uint8_t _spin;
    uint16_t _x, _y;
public:
    GameOverState(BrickGameBase * game)
        :GameStateBase(game){
        _dx = 1,
        _dy = 0;
        _spin = 0;
        _x = 0;
        _y = 0;
    }

    ~GameOverState(){

    }

    void loop(uint8_t delta) override;
    void init() override;
};

#endif