ifeq ($(origin CC),default)
CC := gcc
endif

CFLAGS ?= -std=c11 -Wall -Wextra -pedantic -g -O2
CPPFLAGS += -Iinclude

BUILD_DIR := build
TARGET := $(BUILD_DIR)/td.exe
SOURCES := $(wildcard src/*.c)
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
	mkdir "$(BUILD_DIR)"

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
