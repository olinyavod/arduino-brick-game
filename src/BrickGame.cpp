#include <BrickGame.h>

BrickGame::~BrickGame()
{
    if(_currentState)
        delete _currentState;
    
    //delete _gameDisplay;
    //delete _actualGameDisplay;
    //delete _icon;
}

void BrickGame::loop(uint16_t delta)
{
    if(_currentState)
        _currentState->loop(delta);

    uint8_t x = 0, y = 0;
    uint16_t oldRow, actualRow;

    for(uint8_t i = 0; i < GAME_HEIGHT; i++){
        oldRow = _gameDisplay[i];
        actualRow = _actualGameDisplay[i];
        x = 0;

        for(uint8_t j = 0; j < GAME_WIDTH; j++){
            auto old = (oldRow>>j) & 0x1;
            auto actual = (actualRow>>j) & 0x1;

            if(old != actual)
                drawBrick(x, y, old ? _foreColor : _backColor);

            x+=BRICK_SIZE+1;
        }
        
        _actualGameDisplay[i] = oldRow;
        y += BRICK_SIZE+1;
    }
}

void BrickGame::restart(){
    _score = 0xFFFFFF;
    if(_currentState)
        delete _currentState;

    _currentState = new GameMenuState(this);

    for (uint8_t i = 0; i < GAME_HEIGHT; i++)
    {
        _gameDisplay[i] = 0x0;
        _actualGameDisplay[i] = 0x0;    
    }

    for(uint8_t i = 0; i < ICON_SIZE; i++)
        _icon[i] = 0x0;

    _display->fillScreen(_backColor);
    _display->drawFastVLine(_lineX, 0, _screenHeight, _foreColor);

    setScore(0);
    _x = 0;
    _y = 0;
    _dx = 0;
    _dy = 0;
}

void BrickGame::drawBrick(uint8_t x, uint8_t y, uint16_t color){
  _display->fillRect(x+2, y+2, BRICK_INTO_SIZE, BRICK_INTO_SIZE, color);
  _display->drawFastVLine(x, y+1, BRICK_SIZE-2, color);
  _display->drawFastVLine(x+6, y+1, BRICK_SIZE-2, color);
  _display->drawFastHLine(x, y, BRICK_SIZE, color);
  _display->drawFastHLine(x, y+BRICK_SIZE-1, BRICK_SIZE, color);
}

void BrickGame::drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint8_t size){

  auto vsize = size+1;
  auto hsize = size-2;
  auto hash = pgm_read_byte_near(_digitTable+digit);
  uint8_t mask = 0x40;
  auto color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastHLine(x+1, y, hsize, color);
  _display->drawFastHLine(x+2, y+1, hsize-2, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastHLine(x+2, y+((vsize+1)-1), hsize-2, color);
  _display->drawFastHLine(x+1, y+(vsize+1), hsize, color);
  _display->drawFastHLine(x+2, y+((vsize+1)+1), hsize-2, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastHLine(x+2, y+(vsize*2+1), hsize-2, color);
  _display->drawFastHLine(x+1, y+(vsize*2+2), hsize, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastVLine(x, y+1, vsize, color);
  _display->drawFastVLine(x+1, y+2, vsize-2, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastVLine(x+hsize+1, y+1, vsize, color);
  _display->drawFastVLine(x+hsize, y+2, vsize-2, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastVLine(x, y+vsize+2, vsize, color);
  _display->drawFastVLine(x+1, y+vsize+3, vsize-2, color);
  
  color = checkVisibleFlag(hash, mask, _foreColor, _backColor);
  _display->drawFastVLine(x+hsize+1, y+vsize+2, vsize, color);
  _display->drawFastVLine(x+hsize, y+vsize+3, vsize-2, color);
}

void BrickGame::setScore(uint32_t score){
   uint32_t del = 1, od = 0, nd = 0;
   auto x = _lineX + 4;
  for (uint8_t i = 6; i > 0; i--)
  {    
    pow10(del, i);
    
    od = _score%del;
    nd = score%del;

    pow10(del, i-1);
    
    od /= del;
    nd /= del;

    if(nd!=od)
        drawDigit(nd, x, 1, 6);

    x+=7;
  }
  
  _score = score;
}

uint32_t BrickGame::getScore(){
    return _score;
}

void BrickGame::setIcon(uint8_t * data){
    auto y = _screenHeight/2-((BRICK_SIZE+1)*ICON_SIZE)/2;
    for (uint8_t i = 0; i < ICON_SIZE; i++)
    {
        auto x = _lineX + ((_screenWidth-_lineX)/2 -  ((BRICK_SIZE+1)*ICON_SIZE)/2);
        auto row = *data;
        auto oldRow = _icon[i];
        for(uint8_t j = 0; j<ICON_SIZE; j++){
            auto v = (row>>j) & 0x1;
            auto ov = (oldRow>>j) & 0x1;

            if(v!=ov)
                drawBrick(x, y, v ? _foreColor : _backColor);

            x+=BRICK_SIZE+1;
        }

        y+=BRICK_SIZE+1;
        _icon[i] = *data;
        data++;
    }
}

void BrickGame::setPixel(uint8_t x, uint8_t y, bool value){
    if(y < 0 || y > GAME_HEIGHT || x < 0 || x > GAME_WIDTH)
        return;

    auto row = _gameDisplay[y];

    row = value ? row | (1 << x) : row & ~(1 << x);

    _gameDisplay[y] = row;
}

bool BrickGame::getPixel(uint8_t x, uint8_t y){
    if(x >= GAME_WIDTH && y >= GAME_HEIGHT)
        return false;

    auto row=getRow(y);

    return (row >> x) & 0x1;
}

uint16_t BrickGame::getRow(uint8_t y){
    if(y >= GAME_HEIGHT)
        return 0;
    
    return _gameDisplay[y];
}

void BrickGame::setRow(uint8_t y, uint16_t row){
     if(y >= GAME_HEIGHT)
        return;

    _gameDisplay[y] = row;
}