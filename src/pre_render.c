#ifdef _WIN32
#include <windows.h>
#else
#include <ncurses.h>
#endif

#include "../include/pre_render.h"

static void print_sign(void);
static void clear_screen(void);

void pre_render(void) {

#ifdef _WIN32
    // to properly print UTF-8 chars
    SetConsoleOutputCP(CP_UTF8);
#endif

    clear_screen();
    print_sign();
}

void clear_screen(void) {
#ifdef _WIN32
    const char clear[] = "\x1B[2J\x1B[H";

    printf("%s", clear);
#else
    erase();
#endif
}

void print_sign(void) {
    const char sign[] =
        "\n\n"
        "\t████████╗ █████╗ ███████╗██╗  ██╗    ██████╗ ██████╗ \n"
        "\t╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝    ██╔══██╗██╔══██╗\n"
        "\t   ██║   ███████║███████╗█████╔╝     ██║  ██║██████╔╝\n"
        "\t   ██║   ██╔══██║╚════██║██╔═██╗     ██║  ██║██╔══██╗\n"
        "\t   ██║   ██║  ██║███████║██║  ██╗    ██████╔╝██████╔╝\n"
        "\t   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═════╝ ╚═════╝ \n\n\n";

#ifdef _WIN32
    printf("%s", sign);
#else
    printw("%s", sign);
#endif
}
