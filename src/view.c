#include "view.h"

#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "setting.h"
#include "model.h"
#include "controller.h"

#include "curses_ex.h"

// BLK R G Y B M C W
enum {
    CP_R_BLK = 1,
    CP_G_BLK,
    CP_Y_BLK,
    CP_B_BLK,
    CP_M_BLK,
    CP_C_BLK,
    CP_W_BLK,
};

void init_view() {
    initscr();

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    start_color();
    init_pair(CP_R_BLK, COLOR_RED, COLOR_BLACK);
    init_pair(CP_G_BLK, COLOR_GREEN, COLOR_BLACK);
    init_pair(CP_Y_BLK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_B_BLK, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_M_BLK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CP_C_BLK, COLOR_CYAN, COLOR_BLACK);
    init_pair(CP_W_BLK, COLOR_WHITE, COLOR_BLACK);
    
    attron(A_BOLD);

    clear();
    refresh();
}

void deinit_view() {
    endwin();
}

// [0, OUTLINE_HEIGHT-1]
void draw_outline() {
    attron(COLOR_PAIR(CP_W_BLK));
    for (int c = 0; c < OUTLINE_WIDTH; ++c) {
        mvaddch(0, c, WALL_CHAR);
        mvaddch(OUTLINE_HEIGHT-1, c, WALL_CHAR);
    }

    for (int r = 0; r < OUTLINE_HEIGHT; ++r) {
        mvaddch(r, 0, WALL_CHAR);
        mvaddch(r, OUTLINE_WIDTH-1, WALL_CHAR);
    }
}

// [1, BBS_HEIGHT]
void draw_bbs() {
    attron(COLOR_PAIR(CP_B_BLK));
    
    int speed = 0, score = 0;
    time_t elapse = 0;
    if (g_snake) {
        score = g_snake->len - INIT_SNAKE_LEN;
    }
    if (g_cntl) {
        speed = g_cntl->speed;
        elapse = time(NULL) - g_cntl->ctime;
    }
    char info1[64];
    snprintf(info1, sizeof(info1), "speed: %d\ttime: %lus\tscore: %d",
             speed, elapse, score);
    mvaddstr(1, 2, info1);

    attron(COLOR_PAIR(CP_W_BLK));
    for (int c = 0; c < OUTLINE_WIDTH; ++c) {
        mvaddch(BBS_HEIGHT, c, WALL_CHAR);
    }
}

void draw_snake(snake_t* snake) {
    attron(COLOR_PAIR(CP_C_BLK));
    
    snake_node_t* cur = snake->head;
    while (cur) {
        mvaddch(cur->y + BBS_HEIGHT, cur->x, SNAKE_CHAR);
        cur = cur->next;
    }
}

void draw_foods(foods_t* foods) {
    if (foods == NULL || foods->foods == NULL) return;

    attron(COLOR_PAIR(CP_Y_BLK));
    for (int i = 0; i < foods->num; ++i) {
        mvaddch(foods->foods[i].y + BBS_HEIGHT, foods->foods[i].x, FOOD_CHAR);
    }
}

void splash() {
    clear();

    draw_outline();

    attron(COLOR_PAIR(CP_G_BLK));
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, "Snake 1.0", ALIGN_TOP | ALIGN_HCENTER, 5, 0);
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, "Author: HeWei", ALIGN_TOP | ALIGN_HCENTER, 7, 0);
    
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH/4, "Usage:",    ALIGN_VCENTER | ALIGN_XFIXED, 0, 0);
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH/4, "q => quit", ALIGN_VCENTER | ALIGN_XFIXED, 1, 0);
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH/4, "f => fast", ALIGN_VCENTER | ALIGN_XFIXED, 2, 0);
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH/4, "s => slow", ALIGN_VCENTER | ALIGN_XFIXED, 3, 0);
    
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, "Press any key to start or 'q' to quit...", ALIGN_CENTER, 6, 0);
    
    refresh();
}

void mainscene() {
    clear();

    draw_outline();
    draw_bbs();
    draw_snake(g_snake);
    draw_foods(g_foods);

    refresh();
}

void gameover() {
    attron(COLOR_PAIR(CP_R_BLK));
    attron(A_STANDOUT);
    
    // no clear
    // clear();
    // draw_outline();
    
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, "Game Over", ALIGN_CENTER, -3, 0);
    
    char* reason = NULL;
    if (g_snake->state == HIT_SNAKE) {
        reason = "Hit Snake!";
    } else if (g_snake->state == HIT_WALL) {
        reason = "Hit Wall!";
    }
    if (reason) {
        mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, reason, ALIGN_CENTER, 0, 0);
    }
    
    mvaddstr_ex(WALL_HEIGHT, WALL_WIDTH, "Press 'r' to restart or 'q' to quit...", ALIGN_CENTER, 3, 0);
    attroff(A_STANDOUT);
    refresh();
}

