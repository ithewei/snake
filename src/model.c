#include "model.h"

#include <stdlib.h>

#include "setting.h"

snake_t* g_snake = NULL;
foods_t* g_foods = NULL;

snake_t* alloc_snake(int len) {
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    snake->head = NULL;
    snake->len = 0;
    snake->dirc = RIGHT;
    snake->state = NORMAL;

    snake_node_t* prev = NULL;
    for (int i = 0; i < len; ++i) {
        snake_node_t* node = (snake_node_t*)malloc(sizeof(snake_node_t));
        node->y = WALL_HEIGHT/2;
        node->x = WALL_WIDTH/2 - i;
        node->next = NULL;
        if (i == 0) {
            snake->head = node;
        } else {
            prev->next = node;
        }
        ++snake->len;
        prev = node;
    }

    return snake;
}

void free_snake(snake_t* snake) {
    if (snake == NULL) return;

    snake_node_t* cur = snake->head;
    while (cur) {
        snake_node_t* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(snake);
}

bool is_snake(int x, int y) {
    if (g_snake && g_snake->head) {
        snake_node_t* cur = g_snake->head->next;
        while (cur) {
            if (x == cur->x && y == cur->y) {
                return true;
            }
            cur = cur->next;
        }
    }

    return false;
}

bool is_wall(int x, int y) {
    return x <= 0 || x >= WALL_WIDTH-1 || y <= 0 || y >= WALL_HEIGHT - 1;
}

void random_food(food_t* food) {
    // [1, W-2]
    food->x = random() % (WALL_WIDTH-2) + 1;

    // [1, H-2]
    food->y = random() % (WALL_HEIGHT-2) + 1;
}

foods_t* alloc_foods(int num) {
    foods_t* foods = (foods_t*)malloc(sizeof(foods_t));
    foods->num = num;
    foods->foods = (food_t*)malloc(sizeof(food_t)*num);
    for (int i = 0; i < num; ++i) {
        random_food(&foods->foods[i]);
    }
    return foods;
}

void free_foods(foods_t* foods) {
    if (foods == NULL) return;

    if (foods->foods) {
        free(foods->foods);
        foods->foods = NULL;
        foods->num = 0;
    }
    free(foods);
}

bool eat_food(int x, int y) {
    if (g_foods == NULL || g_foods->foods == NULL) return false;

    for (int i = 0; i < g_foods->num; ++i) {
        if (x == g_foods->foods[i].x &&
            y == g_foods->foods[i].y) {
            random_food(&g_foods->foods[i]);
            return true;
        }
    }

    return false;
}

void init_model() {
    deinit_model();

    g_snake = alloc_snake(INIT_SNAKE_LEN);
    g_foods = alloc_foods(FOOD_NUM);
}

void deinit_model() {
    if (g_snake) {
        free_snake(g_snake);
        g_snake = NULL;
    }

    if (g_foods) {
        free_foods(g_foods);
        g_foods = NULL;
    }
}

void move_snake(snake_t* snake) {
    if (snake == NULL || snake->head == NULL) return;

    snake_node_t* head = snake->head;
    int x = head->x;
    int y = head->y;
    switch (snake->dirc) {
    case LEFT:
        --x;
        break;
    case UP:
        --y;
        break;
    case RIGHT:
        ++x;
        break;
    case DOWN:
        ++y;
        break;
    }

    if (is_snake(x, y)) {
        snake->state = HIT_SNAKE;
        return;
    } else if (is_wall(x, y)) {
        snake->state = HIT_WALL;
        return;
    } else {
        snake_node_t* node = NULL;
        if (eat_food(x, y)) {
            // malloc node
            node = (snake_node_t*)malloc(sizeof(snake_node_t));
            ++snake->len;
        } else {
            snake_node_t* cur = head;
            while (cur->next != NULL && cur->next->next != NULL) {
                cur = cur->next;
            }
            // tail as node
            node = cur->next;
            cur->next = NULL;
        }

        if (node) {
            node->x = x;
            node->y = y;
            node->next = snake->head;
            snake->head = node;
        }

        snake->state = NORMAL;
    }
}

