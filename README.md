# Task Database

Practice project for **C** programming language.

- Pointer
- Manual memory allocation
- TUI rendering

---

## Features

- add task
- set priority
- change priority
- list task
- list by priority
- list by date
- list by title
- select task
- search task
- edit task
- remove task
- mark complete
- mark incomplete
- write to file (JSON)
- read from file
- vim keys to navigate menus
- fake loading screen
- configure nav keys
- cross platform (Windows, macOS, Linux)
- tui rendering

## TODOs

- [x] display menu
- [ ] navigate with vim keys
- [ ] option to use arrow keys
- [ ] adding task
- [ ] deleting task
- [ ] editing task
- [ ] write task to file
- [ ] read task from file
- [ ] loading screen
- [ ] list task
  - [ ] date
  - [ ] name
  - [ ] priority
- [ ] filter task
  - [ ] completed
  - [ ] incomplete
  - [ ] priorities
- [ ] search task
  - [ ] by name
  - [ ] by content
- [ ] execute with `td` command
- [ ] Cross-platform
  - [ ] Windows
  - [ ] macOS
  - [ ] Linux

---

## Task Structure

```c
#include <stdbool.h>

typedef struct {
    int id;
    int number;
    int priority;
    char title[50];
    char content[200];
    bool completed;
} Task;

typedef enum {
    URGENT = 1,
    HIGH,
    MID,
    LOW,
    NONE,
} Priority;
```

- `id`: unique number generated randomly
- `number`: sorted by date created
- `priority`: 1-5 using enum
