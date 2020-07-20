#ifndef _SNAKE_GAME_INCLUDED
#define _SNAKE_GAME_INCLUDED

#include <GameStateBase.h>
#include <Arduino.h>

class SnakeGame : public GameStateBase
{
private:
    struct TargetBrick
    {
        uint8_t x, y;
        bool isVisible;
    };
    
    TargetBrick _targetBrick;
    uint8_t _life;
    uint16_t _acseleration;

    void setLife(uint8_t value);
public:
    SnakeGame(BrickGameBase * game)
        :GameStateBase(game)
    {

    }
    
    ~SnakeGame(){

    }

    void loop(uint8_t delta) override;
    void init() override;
};

#endif