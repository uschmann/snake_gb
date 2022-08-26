#include <gb/gb.h>
#include <rand.h>
#include "state.h"

uint16_t seed;
extern uint8_t currentState;

void state_title_init() 
{
    currentState = STATE_TITLE;
}


void state_title_update()
{
    waitpad(0xFF);
    waitpad(J_START);
    seed = DIV_REG;
    initarand(seed);

    currentState = STATE_GAME_INIT;
}