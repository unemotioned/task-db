#include <conio.h> // _getch(): read a key without waiting for Enter
#include <stdbool.h>
#include <stdio.h>
#include <windows.h> // Windows console colors and cursor controls

#include "../include/menu_win.h"
#include "../include/menus.h"

static void draw_item(HANDLE output,
                      COORD start,
                      int row,
                      const char *text,
                      int selected,
                      WORD normal) {
    // X == col
    // Y == row
    // SHORT == Windows' coord type
    COORD position = {start.X, (SHORT)(start.Y + row)};
    SetConsoleCursorPosition(output, position);

    // Combine color flags with |: bright white background, black text.
    WORD highlight = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
                     BACKGROUND_INTENSITY;

    SetConsoleTextAttribute(output, selected ? highlight : normal);
    // %-20s left-aligns the text and pads it to at least 20 characters.
    printf(" %-20s ", text);
    fflush(stdout); // flush the buffer before changing colors back

    // restore original color
    SetConsoleTextAttribute(output, normal);
}

bool menu_win(void) {
    const int menu_cnt = sizeof(main_menu) / sizeof(main_menu[0]);
    int selected = 0;

    // `HANDLE` IDs the console
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    printf("Use Up/Down, then Enter:\n");
    fflush(stdout);

    if (!GetConsoleScreenBufferInfo(output, &info)) {
        return false;
    }

    COORD start = info.dwCursorPosition;      // menu's position
    const WORD word_color = info.wAttributes; // console's original colors.

    // Print the menu once.
    for (int i = 0; i < menu_cnt; i++) {
        printf(" %-20s \n", main_menu[i]);
    }

    fflush(stdout);

    // Account for scrolling caused by printing the menu.
    GetConsoleScreenBufferInfo(output, &info);
    start.Y = (SHORT)(info.dwCursorPosition.Y - menu_cnt);
    draw_item(output, start, selected, main_menu[selected], 1, word_color);

    // Keep reading keys until Enter breaks out of the loop.
    while (1) {
        const short enter_key = 13;

        int key = _getch();
        const int previous = selected;

        if (key == enter_key) {
            break;
        }

        // Arrow keys send a prefix first, then a second code for direction.
        if (key == 0 || key == 224) {
            const short up_key = 72;
            const short down_key = 80;

            key = _getch();

            // % wraps the selection around at either end of the list.
            if (key == up_key) {
                selected = (selected + menu_cnt - 1) % menu_cnt;
            } else if (key == down_key) {
                selected = (selected + 1) % menu_cnt;
            }
        }

        // redraw previous menu and then changed menu status to prevent
        // flickering
        if (selected != previous) {
            // if commented out prev cursor pos will still be highlighted
            draw_item(output,
                      start,
                      previous,
                      main_menu[previous],
                      0,
                      word_color);
            draw_item(output,
                      start,
                      selected,
                      main_menu[selected],
                      1,
                      word_color);
        }
    }

    // position of below the menu
    COORD end = {0, (SHORT)(start.Y + menu_cnt)};

    SetConsoleCursorPosition(output, end);
    printf("You selected: %s\n", main_menu[selected]);

    return true;
}
