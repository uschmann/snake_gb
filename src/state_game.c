#include "state.h"
#include "snake.h"

extern uint8_t currentState;

void state_game_init() 
{     
    snake_initSnake();
    snake_placeFruit();

    currentState = STATE_GAME;
}

void state_game_update()
{
    snake_update();

    wait_vbl_done();
    
    snake_drawFruit();
    snake_drawSnake();
    snake_drawHead();
    snake_drawScore();
}
