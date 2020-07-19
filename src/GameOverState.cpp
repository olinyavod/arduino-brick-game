#include <GameOverState.h>

void GameOverState::loop(uint8_t delta){       
    
    uint8_t x = _x/SPEED, y = _y/SPEED;
    int8_t px = x, py = y;     

    while(!_game->getPixel(px, py)){
        _game->setPixel(px, py, true);               
        px += -1*_dx;
        py += -1*_dy;
        if(px < _spin || py < _spin || px >= GAME_WIDTH || py >= GAME_HEIGHT)
            break;
    }

    if(x >= (GAME_WIDTH - 1 - _spin) && _dx == 1){
        _dx = 0;
        _dy = 1;
    }
    else if(y >= (GAME_HEIGHT - 1 - _spin) && _dy == 1){
        _dx = -1;
        _dy = 0;
    }
    else if(x <= _spin && _dx == -1){
        _dx = 0;
        _dy = -1;
    }
    else if(y <= _spin+1 && _dy == -1){
        _spin++;
        _dx = 1;
        _dy = 0;
    }

    if(x == (GAME_WIDTH-1)/2 && y == (GAME_HEIGHT-1)/2)
    {
        _game->changeState(GameTrigger::Menu);
        return;
    }  

    _x += delta*_dx;
    _y += delta*_dy;
}

void GameOverState::init(){
    for(uint8_t i = 0; i < GAME_HEIGHT; i++)
        _game->setRow(i, 0);
}