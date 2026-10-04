#pragma once

#include "stdint.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15,
} color_t;

void putc(char c);
void puts(const char* str);
void clear(void);

void set_color(color_t bg, color_t text);
void set_bg_color(color_t bg);
void set_text_color(color_t text);
color_t get_bg_color();
color_t get_text_color();