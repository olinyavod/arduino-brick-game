#include <SnakeGame.h>
#include <Arduino.h>

constexpr uint8_t BLINK_RATE = 200;
constexpr uint8_t DEFAULT_SNAKE_SIZE = 3;
constexpr uint16_t MIN_SPEED = 1000;
constexpr uint16_t MAX_SPEED = 100;
constexpr uint8_t MAX_LIFE = 3;

void SnakeGame::loop(uint8_t delta){

    if(_blink > BLINK_RATE){
        _blink = 0;
        _targetBrick.isVisible = !_targetBrick.isVisible;
    }
    
    _game->setPixel(_targetBrick.x, _targetBrick.y, _targetBrick.isVisible);

    this->_headSnake->isVisible = !_targetBrick.isVisible;
      
    auto next = _headSnake;

    auto button = _game->getButtonState();

    switch (button)
    {
    case ButtonState::DOWN:
        _dy = 1;
        _dx = 0;
        break;
    case ButtonState::LEFT:
        _dy = 0;
        _dx = 1;
        break;
    case ButtonState::UP:
        _dy = -1;
        _dx = 0;
        break;
    
    default:
        break;
    }

    if(_acseleration>MIN_SPEED-(_speed*100)){
        _acseleration = 0;
        next->x += _dx;
        next->y += _dy;
    }
    
    while (next != NULL)
    {
        auto c = next;

        next = c->next;

        if(c->oldX != c->x || c->oldY != c->y){
            next->x = c->oldX;                
            next->y = c->oldY;
            _game->setPixel(c->oldX, c->oldY, false);

            c->oldX = c->x;
            c->oldY = c->y;
        }

        _game->setPixel(c->x, c->y, c->isVisible);             
    }
    
    _blink += delta;
    _acseleration += delta;    
}

void SnakeGame::init(){
    randomSeed(micros());
    for (uint8_t i = 0; i < GAME_HEIGHT; i++)
        _game->setRow(i, 0);
    
    _speed = 0;

    if(_headSnake != NULL)
        delete _headSnake;

    _targetBrick.x = random(GAME_WIDTH-3)+3;
    _targetBrick.y = random(GAME_HEIGHT);
    _targetBrick.isVisible = true;

    _dx = 1; 
    _dy = 0;

    this->_headSnake = new SnakeBrick();

    auto current = this->_headSnake;

    for(int8_t i = 2; i >= 0; i--){
        current->isVisible = true;
        current->x = (uint8_t) i;
        current->oldX = (uint8_t) i;
        current->y = 0;
        current->oldY = 0;

        if(i == 0)
            break;

        auto c = new SnakeBrick();
        current->next = (SnakeBrick*) c;
        current = (SnakeBrick*) c;
    }
    current->next = NULL;          

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