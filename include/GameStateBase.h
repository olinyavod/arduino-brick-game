#ifndef _GAME_STATE_INCLUDED
#define _GAME_STATE_INCLUDED

#include <Arduino.h>
#include <BrickGameBase.h>

class GameStateBase
{
protected:
    BrickGameBase * _game;

public:
    GameStateBase(BrickGameBase *game)
        : _game(game){

    }
    
    virtual ~GameStateBase(){

    }

    virtual void loop(uint8_t delta) { }
    virtual void init() { }
};

#endif
