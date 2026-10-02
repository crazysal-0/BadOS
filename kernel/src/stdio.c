#include "stdio.h"
#include "stdint.h"

static color_t bg_color = BLACK;
static color_t text_color = WHITE;

static volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;

static uint16_t cursor_row = 0;
static uint16_t cursor_col = 0;

void putc(char c) {
        if (c == '\n') {
                cursor_col = 0;
                cursor_row++;
        } else if (c == '\t') {
                cursor_col += 8;
        } else {
                uint16_t color = (bg_color << 12) | (text_color << 8); // make colors 1 byte
                volatile uint16_t* location = vga_buffer + (cursor_row * VGA_WIDTH + cursor_col);
                *location = color | (uint8_t)c;

                cursor_col++;
        }
}

void clear(void) {
        cursor_col = 0;
        cursor_row = 0;

        uint16_t color = (bg_color << 12) | (text_color << 8);

        for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
                vga_buffer[i] = color | ' ';
        }
}