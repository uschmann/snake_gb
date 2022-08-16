#include "snake.h"
#include <stdlib.h>
#include "state.h"

extern uint8_t i, j;
extern uint16_t ii;
extern joypads_t joypads;
extern uint8_t currentState;

uint8_t hasMoved = 0;
uint8_t levelCounter = MAX_LEVEL_COUNTER;
uint8_t isGameOver = 0;

SnakePart *snakePart;
SnakePart *startSnakePart;
SnakePart *snakePartSrc;
SnakePart *snakePartDest;
SnakePart *head;

SnakePart tail;

Snake snake = {
    .length = SNAKE_START_LENGTH,
    .direction = SNAKE_START_DIR,
    .lastDirection = DIR_LEFT,
    .moveCounter = SNAKE_START_MOVE_COUNTER,
    .maxMoveCounter = SNAKE_START_MOVE_COUNTER};

Fruit fruit = {
    .x = 3,
    .y = 3};

const SnakePart startSnakeParts[] = {
    {5, 5},
    {6, 5},
    {7, 5},
    {8, 5},
    {9, 5},
    {10, 5},
    {11, 5},
};

void snake_update()
{
    snake_readPad();

    snake.moveCounter--;
    if (snake.moveCounter == 0)
    {
        snake_moveSnake();
        snake.moveCounter = snake.maxMoveCounter;
    }
}

void snake_readPad()
{
    if (joypads.joy0 & J_UP && snake.lastDirection != DIR_DOWN)
    {
        snake.direction = DIR_UP;
    }
    else if (joypads.joy0 & J_RIGHT && snake.lastDirection != DIR_LEFT)
    {
        snake.direction = DIR_RIGHT;
    }
    else if (joypads.joy0 & J_DOWN && snake.lastDirection != DIR_UP)
    {
        snake.direction = DIR_DOWN;
    }
    else if (joypads.joy0 & J_LEFT && snake.lastDirection != DIR_RIGHT)
    {
        snake.direction = DIR_LEFT;
    }
}

uint8_t snake_hasEatenFruit()
{
    if (snake.parts->x == fruit.x && snake.parts->y == fruit.y)
    {
        return 1;
    }
    return 0;
}

void snake_moveSnake()
{
    snakePartSrc = &snake.parts[snake.length - 2];
    snakePartDest = &snake.parts[snake.length - 1];

    tail.x = snakePartDest->x;
    tail.y = snakePartDest->y;

    for (i = 0; i < snake.length - 1; i++)
    {
        snakePartDest->x = snakePartSrc->x;
        snakePartDest->y = snakePartSrc->y;

        snakePartDest--;
        snakePartSrc--;
    }

    snakePart = snake.parts;
    if (snake.direction == DIR_LEFT)
    {
        if (snakePart->x == 0)
        {
            snakePart->x = MAP_WIDTH -1;
        }
        else
        {
            snakePart->x--;
        }
    }
    else if (snake.direction == DIR_RIGHT)
    {
        if (snakePart->x == MAP_WIDTH - 1)
        {
            snakePart->x = 0;
        }
        else
        {
            snakePart->x++;
        }
    }
    else if (snake.direction == DIR_UP)
    {
        if (snakePart->y == 0)
        {
            snakePart->y = MAP_HEIGHT - 1;
        }
        else
        {
            snakePart->y--;
        }
    }
    else if (snake.direction == DIR_DOWN)
    {
        if (snakePart->y == MAP_HEIGHT -1)
        {
            snakePart->y = 0;
        }
        else
        {
            snakePart->y++;
        }
    }

    snake.lastDirection = snake.direction;
    hasMoved = 1;

    if (snake_hasEatenFruit())
    {
        levelCounter--;
        if (levelCounter == 0)
        {
            levelCounter = MAX_LEVEL_COUNTER;
            if (snake.maxMoveCounter > MIN_MOVE_COUNTER)
            {
                snake.maxMoveCounter--;
            }
        }

        snake.length++;
        snake.parts[snake.length - 1].x = snake.parts[snake.length - 2].x;
        snake.parts[snake.length - 1].y = snake.parts[snake.length - 2].y;
        snake_placeFruit();
    }

    if (snake_hasEatenSelf())
    {
        currentState = STATE_TITLE_INIT;
    }
}

uint8_t snake_hasEatenSelf()
{
    head = snake.parts;
    snakePart = snake.parts;

    for (ii = 0; ii < snake.length - 1; ii++)
    {
        snakePart++;
        if (head->x == snakePart->x && head->y == snakePart->y)
        {
            return 1;
        }
    }

    return 0;
}

void snake_initSnake()
{
    isGameOver = 0;

    snake.length = SNAKE_START_LENGTH;
    snake.maxMoveCounter = SNAKE_START_MOVE_COUNTER;
    snake.moveCounter = SNAKE_START_MOVE_COUNTER;
    snake.direction = SNAKE_START_DIR;

    snakePart = snake.parts;
    startSnakePart = startSnakeParts;

    snake_clearScreen();

    for (i = 0; i < snake.length; i++)
    {
        snakePart->x = startSnakePart->x;
        snakePart->y = startSnakePart->y;
        snakePart++;
        startSnakePart++;
    }
}

void snake_drawSnake()
{
    snakePart = snake.parts;
    for (ii = 0; ii < snake.length; ii++)
    {
        set_bkg_tile_xy(snakePart->x, snakePart->y, ii == 0 ? TILE_HEAD : TILE_BODY);
        snakePart++;
    }

    // Delete tail if snake has moved...
    if (hasMoved == 1)
    {
        set_bkg_tile_xy(tail.x, tail.y, 0);
        hasMoved = 0;
    }
}

void snake_placeFruit()
{
    do
    {
        fruit.x = arand() % MAP_WIDTH;
        fruit.y = arand() % MAP_HEIGHT;
    } while (snake_collides(fruit.x, fruit.y));
}

uint8_t snake_collides(uint8_t x, uint8_t y)
{
    snakePart = snake.parts;
    for (ii = 0; ii < snake.length; ii++)
    {
        if (snakePart->x == x && snakePart->y == y)
        {
            return 1;
        }
        snakePart++;
    }
    return 0;
}

void snake_drawFruit()
{
    set_bkg_tile_xy(fruit.x, fruit.y, TILE_FRUIT);
}

void snake_clearScreen()
{
    wait_vbl_done();
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 18; j++)
        {
            set_bkg_tile_xy(i, j, 0);
        }
    }
}