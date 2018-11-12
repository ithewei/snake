#include <stdlib.h>
#include <curses.h>

#include "model.h"
#include "view.h"
#include "controller.h"

void snake_game() {
    init_view();
    atexit(deinit_view);

    init_controller();
    atexit(deinit_controller);

splash:
    splash();

    init_model();
    atexit(deinit_model);

    nodelay(stdscr, FALSE);
    int ch = getch();
    if (ch == 'q') {
        exit(0);
    }

    game_loop();

    gameover();

    while (1) {
        nodelay(stdscr, FALSE);
        int ch = getch();
        if (ch == 'q') {
            exit(0);
        } else if (ch == 'r') {
            goto splash;
        }
    }
}

int main(int argc, char** argv) {
    snake_game();
    return 0;
}

