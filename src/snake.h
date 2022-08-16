#ifndef _SNAKE_H
#define _SNAKE_H

#include <gb/gb.h>

#define DIR_UP 1
#define DIR_RIGHT 2
#define DIR_DOWN 3
#define DIR_LEFT 4

#define SNAKE_START_LENGTH 7
#define SNAKE_START_MOVE_COUNTER 10
#define SNAKE_MAX_LENGTH 300
#define SNAKE_START_DIR DIR_LEFT

#define TILE_BODY 1
#define TILE_FRUIT 2
#define TILE_HEAD 3

#define MAP_WIDTH 20
#define MAP_HEIGHT 18

#define MIN_MOVE_COUNTER 3
#define MAX_LEVEL_COUNTER 3

typedef struct SnakePart {
    uint8_t x;
    uint8_t y;
} SnakePart;

typedef struct Snake {
    uint8_t length;
    SnakePart parts[SNAKE_MAX_LENGTH];
    uint8_t direction;
    uint8_t lastDirection;
    uint8_t moveCounter;
    uint8_t maxMoveCounter;
} Snake;

typedef struct Fruit {
    uint8_t x;
    uint8_t y;
} Fruit;

uint8_t snake_collides(uint8_t x, uint8_t y);
uint8_t snake_hasEatenSelf();

void snake_initSnake();
void snake_drawSnake();
void snake_moveSnake();
void snake_readPad();
void snake_update();
uint8_t snake_hasEatenFruit();


void snake_placeFruit();
void snake_drawFruit();
void snake_clearScreen();

#endif