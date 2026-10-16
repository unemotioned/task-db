CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic -g -O2
CPPFLAGS += -Iinclude

ifneq ($(OS),Windows_NT)
ifeq ($(shell uname -s),Darwin)
NCURSES_PREFIX := $(shell brew --prefix ncurses 2>/dev/null)
ifneq ($(NCURSES_PREFIX),)
CPPFLAGS += -I$(NCURSES_PREFIX)/include
LDFLAGS += -L$(NCURSES_PREFIX)/lib -Wl,-rpath,$(NCURSES_PREFIX)/lib
endif
LDLIBS += -lncurses
else
LDLIBS += -lncursesw
endif
endif

BUILD_DIR := build
TARGET := $(BUILD_DIR)/td.exe
SOURCES := $(wildcard src/*.c)
ifneq ($(OS),Windows_NT)
SOURCES := $(filter-out src/menu_win.c,$(SOURCES))
else
SOURCES := $(filter-out src/menu_unix.c,$(SOURCES))
endif

OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
.SHELLFLAGS := /C
endif

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p "$(BUILD_DIR)"

run: $(TARGET)
ifeq ($(OS),Windows_NT)
	.\$(subst /,\,$(TARGET))
else
	./$(TARGET)
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
else
	rm -rf "$(BUILD_DIR)"
endif

-include $(DEPS)
