#include <stdbool.h>
#include <stdio.h>

#if defined(_WIN32)
#include "../include/menu_win.h"
#else
#include "../include/menu_unix.h"
#endif

int main(void) {
#if defined(_WIN32)
    pre_render();

    if (!menu_win()) {
        fprintf(stderr, "ERROR: Failed to get the console information\n");
        return 1;
    }
#else
    if (!menu_unix()) {
        fprintf(stderr, "ERROR: Failed to display or read the terminal menu\n");
        return 1;
    }
#endif

    return 0;
}
