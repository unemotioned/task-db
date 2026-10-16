#pragma once

typedef enum {
    LIST,
    ADD,
    DEL_ALL,
    OPT,
    EXIT,
} MainMenu;

static const char *const main_menu[] = {
    [LIST] = "List tasks",
    [ADD] = "Add task",
    [DEL_ALL] = "Delete all",
    [OPT] = "Options",
    [EXIT] = "Exit",
};
