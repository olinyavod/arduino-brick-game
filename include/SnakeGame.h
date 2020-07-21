#ifndef _SNAKE_GAME_INCLUDED
#define _SNAKE_GAME_INCLUDED

#include <GameStateBase.h>

class SnakeGame : public GameStateBase
{
private:
    struct TargetBrick
    {
        uint8_t x, y;
        bool isVisible;
    };

    struct SnakeBrick{
        uint8_t x, y, oldX, oldY;        
        bool isVisible;
        SnakeBrick *next;
    };
    
    TargetBrick _targetBrick;
    uint8_t _life;
    uint16_t _acseleration;
    int8_t _dx, _dy;
    uint8_t _blink, _speed;

    SnakeBrick * _headSnake;


    void setLife(uint8_t value);
public:
    SnakeGame(BrickGameBase * game)
        :GameStateBase(game)
    {

    }
    
    ~SnakeGame(){
        auto next = _headSnake;

        while(next != NULL){
            auto c = next;
            next = next->next;
            delete c;
        }

    }

    void loop(uint8_t delta) override;
    void init() override;
};

#endif