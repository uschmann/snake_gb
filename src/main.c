#include <gb/gb.h>
#include <gbdk/font.h>
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
    font_init();
    font_set(font_load(font_spect));

    set_bkg_data(0, 4u, snake_tiles);
    set_sprite_data(0, 2u, snake_sprites);

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 18; j++)
        {
            set_bkg_tile_xy(i, j, 0);
        }
    }

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
        // Title
        case STATE_TITLE_INIT:
            state_title_init();
            break;
        case STATE_TITLE:
            state_title_update();
            break;
        // Game
        case STATE_GAME_INIT:
            state_game_init();
            break;
        case STATE_GAME:
            state_game_update();
            break;
        }
    }
}
