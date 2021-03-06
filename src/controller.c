#include "controller.h"

#include <stdlib.h>
#include <curses.h>

#include "setting.h"
#include "model.h"
#include "view.h"

#include "platform.h"

controller_t* g_cntl = NULL;

void init_controller() {
    deinit_controller();

    g_cntl = (controller_t*)malloc(sizeof(controller_t));
}

void deinit_controller() {
    if (g_cntl) {
        free(g_cntl);
        g_cntl = NULL;
    }
}

void key_control() {
    nodelay(stdscr, TRUE);
    int ch = getch();
    if (ch == KEY_CTL_QUIT) {
        g_cntl->status = STOP;
        return;
    }
    if (ch == KEY_CTL_PAUSE) {
        if (g_cntl->status == RUNNING) {
            g_cntl->status = PAUSE;
        }
        else {
            g_cntl->status = RUNNING;
        }
        return;
    }
    switch (ch) {
    case KEY_CTL_LEFT:
    case 'h':
        if (g_snake->dirc == LEFT) {
            g_cntl->nodelay = true;
        }
        g_snake->dirc = (g_snake->dirc == RIGHT ? RIGHT : LEFT);
        break;
    case KEY_CTL_UP:
    case 'k':
        if (g_snake->dirc == UP) {
            g_cntl->nodelay = true;
        }
        g_snake->dirc = (g_snake->dirc == DOWN ? DOWN : UP);
        break;
    case KEY_CTL_RIGHT:
    case 'l':
        if (g_snake->dirc == RIGHT) {
            g_cntl->nodelay = true;
        }
        g_snake->dirc = (g_snake->dirc == LEFT ? LEFT : RIGHT);
        break;
    case KEY_CTL_DOWN:
    case 'j':
        if (g_snake->dirc == DOWN) {
            g_cntl->nodelay = true;
        }
        g_snake->dirc = (g_snake->dirc == UP ? UP : DOWN);
        break;
    case KEY_CTL_FAST:
        g_cntl->speed = (g_cntl->speed < MAX_SPEED ? g_cntl->speed+1 : g_cntl->speed);
        break;
    case KEY_CTL_SLOW:
        g_cntl->speed = (g_cntl->speed > MIN_SPEED ? g_cntl->speed-1 : g_cntl->speed);
        break;
    }
}

void game_loop() {
    g_cntl->status = RUNNING;
    g_cntl->speed = DEFAULT_SPEED;
    g_cntl->nodelay = false;
    g_cntl->ctime = time(NULL);

    // move_snake -> mainscene -> sleep -> key_control
    while (g_cntl->status != STOP) {
        move_snake(g_snake);

        mainscene();

        if (g_snake->state != NORMAL) {
            break;
        }

        if (!g_cntl->nodelay) {
            msleep(1000/g_cntl->speed);
        } else {
            g_cntl->nodelay = false;
        }

key_control:
        key_control();
        if (g_cntl->status == PAUSE) {
            pausescene();
            msleep(100);
            goto key_control;
        }
    }
}

