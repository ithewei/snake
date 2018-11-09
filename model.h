#ifndef SNAKE_MODEL_H_
#define SNAKE_MODEL_H_

#include <stdbool.h>

typedef struct snake_node_s {
    int x, y;
    struct snake_node_s* next;
} snake_node_t;

typedef enum {
    LEFT = 1,
    UP = 2,
    RIGHT = 3,
    DOWN = 4,
} direction_e;

typedef enum {
    NORMAL,
    HIT_SNAKE,
    HIT_WALL,
} snake_state_e;

typedef struct snake_s {
    snake_node_t* head;
    int len;
    direction_e   dirc;
    snake_state_e state;
} snake_t;

typedef struct food_s {
    int x, y;
} food_t;

typedef struct foods_s {
    food_t* foods;
    int num;
} foods_t;

extern foods_t* g_foods;
extern snake_t* g_snake;

void init_model();
void deinit_model();

void move_snake(snake_t* snake);

#endif  // SNAKE_MODEL_H_

