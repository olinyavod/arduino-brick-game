#include <GameMenuState.h>

void GameMenuState::loop(uint8_t delta){
    
    auto addr = (uint16_t*) pgm_read_word_near((&_chartTable[_selectTypeGame]));
    for (uint8_t i = 0; i < 10; i++)
    {
        auto c = pgm_read_word_near(addr+i);
        _game->setRow(i, c);
    }
    
}