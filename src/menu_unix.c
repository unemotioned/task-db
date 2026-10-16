#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

#include "../include/menu_unix.h"
#include "../include/menus.h"
#include "../include/pre_render.h"

bool menu_unix(void) {
    const int menu_cnt = sizeof(main_menu) / sizeof(main_menu[0]);
    int selected = 0;

    // Use the terminal's locale for the UTF-8 banner.
    setlocale(LC_ALL, "");
    SCREEN *screen = newterm(NULL, stdout, stdin);
    if (screen == NULL) {
        return false;
    }

    if (cbreak() == ERR || noecho() == ERR || keypad(stdscr, TRUE) == ERR) {
        endwin();
        delscreen(screen);
        return false;
    }

    const int cursor = curs_set(0);
    bool success = true;
    bool done = false;

    // build virtual screen
    // refresh only changed terminal cells
    while (!done) {
        pre_render();

        printw("Use Up/Down, then Enter:\n");
        for (int i = 0; i < menu_cnt; i++) {
            if (i == selected) {
                attron(A_REVERSE);
            }
            printw(" %-20s ", main_menu[i]);
            attroff(A_REVERSE);
            addch('\n');
        }
        refresh();

        switch (getch()) {
        case KEY_UP:
            selected = (selected + menu_cnt - 1) % menu_cnt;
            break;
        case KEY_DOWN:
            selected = (selected + 1) % menu_cnt;
            break;
        case '\n':
        case '\r':
        case KEY_ENTER:
            done = true;
            break;
        case ERR:
            success = false;
            done = true;
            break;
        case KEY_RESIZE:
            // The next frame uses ncurses' updated screen dimensions.
            break;
        }
    }

    if (cursor != ERR) {
        curs_set(cursor);
    }
    endwin();
    delscreen(screen);

    if (success) {
        printf("You selected: %s\n", main_menu[selected]);
    }
    return success;
}
