#include <gb/gb.h>
#include <stdint.h>
#include "../res/snake_tiles.h"
#include "../res/snake_sprites.h"
#include "snake.h"
#include "globals.h"
#include "state.h"

extern uint8_t i, j;
extern joypads_t joypads;
extern uint16_t seed;
extern uint8_t currentState;

void init_gfx()
{
    // Load Background tiles and then map
    set_bkg_data(0, 4u, snake_tiles);
    set_sprite_data(0, 2u, snake_sprites);

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 18; j++)
        {
            set_bkg_tile_xy(i, j, 0);
        }
    }

    // Turn the background map on to make it visible
    SHOW_BKG; 
    SHOW_SPRITES;

}

void main(void)
{
    init_gfx();
    joypad_init(1, &joypads);

    state_title_init();

    // Loop forever
    while (1)
    {
        joypad_ex(&joypads);

        switch (currentState)
        {
        case STATE_TITLE_INIT:
            state_title_init();
            break;
        case STATE_TITLE:
            state_title_update();
            break;
        case STATE_GAME_INIT:
            state_game_init();
            break;
        case STATE_GAME:
            state_game_update();
            break;
        }
    }
}
