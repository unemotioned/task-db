#pragma once

#include <stdbool.h>

typedef struct {
    int id;
    int number;
    int priority;
    char title[50];    // 49 chars + NUL
    char content[200]; // 199 chars + NUL
    bool completed;
} Task;

typedef enum {
    URGENT = 1,
    HIGH,
    MID,
    LOW,
    NONE,
} Priority;
