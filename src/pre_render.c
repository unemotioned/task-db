#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/pre_render.h"

static void print_sign();
static void clear_screen();

void pre_render() {

#ifdef _WIN32
    // to properly print UTF-8 chars
    SetConsoleOutputCP(CP_UTF8);
#endif

    clear_screen();
    print_sign();
}

void clear_screen() {
    const char clear[] = "\x1B[2J\x1B[H";

    printf("%s", clear);
}

void print_sign() {
    const char sign[] =
        "\n\n"
        "\t████████╗ █████╗ ███████╗██╗  ██╗    ██████╗ ██████╗ \n"
        "\t╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝    ██╔══██╗██╔══██╗\n"
        "\t   ██║   ███████║███████╗█████╔╝     ██║  ██║██████╔╝\n"
        "\t   ██║   ██╔══██║╚════██║██╔═██╗     ██║  ██║██╔══██╗\n"
        "\t   ██║   ██║  ██║███████║██║  ██╗    ██████╔╝██████╔╝\n"
        "\t   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═════╝ ╚═════╝ \n\n\n";

    printf("%s", sign);
}
