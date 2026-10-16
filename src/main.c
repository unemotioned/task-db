#include <stdbool.h>
#include <stdio.h>

#include "../include/pre_render.h"
#ifdef _WIN32
#include "../include/menu_win.h"
#endif

int main(void) {
    pre_render();

#ifdef _WIN32
    if (!menu_win()) {
        fprintf(stderr, "ERROR: Failed to get the console information: \n");
        return 1;
    }
#endif

    return 0;
}
