#include <SnakeGame.h>

void SnakeGame::loop(uint8_t delta){

    if(_acseleration%200==0)
        _targetBrick.isVisible = !_targetBrick.isVisible;

    _game->setPixel(_targetBrick.x, _targetBrick.y, _targetBrick.isVisible);
    _acseleration += delta;
}

void SnakeGame::init(){
    randomSeed(micros());
    for (uint8_t i = 0; i < GAME_HEIGHT; i++)
        _game->setRow(i, 0);

    _targetBrick.x = random(GAME_WIDTH);
    _targetBrick.y = random(GAME_HEIGHT);
    _targetBrick.isVisible = true;

    _acseleration = 0;

    _game->setScore(0);        
    setLife(3);
}

void SnakeGame::setLife(uint8_t value){
    _life = value;

    uint8_t lifeIcon[ICON_SIZE];

    for(uint8_t i = 0; i<ICON_SIZE; i++)
        lifeIcon[i] = i < _life ? 1 : 0;    

    _game->setIcon(lifeIcon);
}