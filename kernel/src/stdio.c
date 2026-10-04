#include "stdio.h"
#include "keyboard.h"
#include "stddef.h"
#include "stdint.h"

static color_t bg_color = BLACK;
static color_t text_color = WHITE;

static volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;

static uint16_t cursor_row = 0;
static uint16_t cursor_col = 0;

void putc(char c) {
        if (c == '\b') {
                if (cursor_col > 0) {
                        cursor_col--;

                        uint16_t color = (bg_color << 12) | (text_color << 8);
                        volatile uint16_t* location =
                            vga_buffer + (cursor_row * VGA_WIDTH + cursor_col);

                        *location = color | ' ';
                }

                return;
        }

        if (c == '\n') {
                cursor_col = 0;
                cursor_row++;
        } else if (c == '\t') {
                cursor_col += 8;
        } else {
                uint16_t color = (bg_color << 12) | (text_color << 8);
                volatile uint16_t* location = vga_buffer + (cursor_row * VGA_WIDTH + cursor_col);

                *location = color | (uint8_t)c;
                cursor_col++;
        }
}

void puts(const char* str) {
        while (*str)
                putc(*str++);
}

void clear(void) {
        cursor_col = 0;
        cursor_row = 0;

        uint16_t color = (bg_color << 12) | (text_color << 8);

        for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
                vga_buffer[i] = color | ' ';
        }
}

void set_color(color_t bg, color_t text) {
        bg_color = bg;
        text_color = text;
}

void set_text_color(color_t text) {
        text_color = text;
}

void set_bg_color(color_t bg) {
        bg_color = bg;
}

color_t get_text_color(void) {
        return text_color;
}

color_t get_bg_color(void) {
        return text_color;
}

void gets(char* buffer, uint16_t size) {
        if (size <= 0)
                return;

        uint16_t i = 0;

        while (i < size - 1) {
                char c = keyboard_getc();

                if (c == '\n')
                        break;

                if (c == '\x1b')
                        continue;

                if (c == '\b') {
                        if (i > 0) {
                                i--;
                                putc('\b');
                        }

                        continue;
                }

                buffer[i++] = c;
                putc(c);
        }

        buffer[i] = '\0';
}