#ifndef SNAKE_CONTROLLER_H_
#define SNAKE_CONTROLLER_H_

#include <stdbool.h>
#include <time.h>

typedef enum {
    RUNNING,
    STOP,
    PAUSE,
} game_status_e;

typedef struct controller_s {
    bool nodelay;
    game_status_e status;
    int speed;
    time_t ctime;
} controller_t;

extern controller_t* g_cntl;

void init_controller();
void deinit_controller();

void game_loop();

#endif  // SNAKE_CONTROLLER_H_
