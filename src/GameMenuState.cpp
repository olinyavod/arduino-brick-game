#include <GameMenuState.h>

void GameMenuState::loop(uint8_t delta){
    
    auto buttonState = _game->getButtonState();
    bool isChanged = false;

    if(buttonState != _oldButtonState){
        _acseleration = 0;
        _speed = MIN_SPEED; 
        isChanged = true;       
    }

    _oldButtonState = buttonState;
    _acseleration+=delta;
    switch (buttonState)
    {
    case ButtonState::LEFT:   
        if(isChanged || min(_acseleration, _speed)%_speed == 0)
        {    
            _selectTypeGame--;
            _speed=max(_speed-ACSELERATION, MAX_SPEED);
        }
        break;
    
    case ButtonState::RIGTH:   
        if(isChanged || min(_acseleration, _speed)%_speed == 0)
        {    
            _selectTypeGame++;
            _speed=max(_speed-ACSELERATION, MAX_SPEED);
        }
        break; 

    case ButtonState::OK:
        _game->changeState((GameTrigger) pgm_read_byte_near(_gamesTable + _selectTypeGame));
        return;
      
    default:
        _speed = MIN_SPEED;
        _acseleration = 0;    
        break;
    }

    if(_selectTypeGame < 0)
        _selectTypeGame = MAX_GAME_COUNT-1;

    if(_selectTypeGame >= MAX_GAME_COUNT)  
        _selectTypeGame = 0; 


    auto addr = (uint16_t*) pgm_read_word_near((&_chartTable[_selectTypeGame]));
    for (uint8_t i = 0; i < 10; i++)
    {
        auto c = pgm_read_word_near(addr+i);
        _game->setRow(i, c);
    }    
}

void GameMenuState::init(){
    for (uint8_t i = 0; i < GAME_HEIGHT; i++)
        _game->setRow(i, 0);
    
}