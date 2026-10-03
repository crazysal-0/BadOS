#include "keyboard.h"
#include "io.h"

static const char scancode_table[] = {
    0,    27,  '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',  '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']', '\n', 0,
    'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\', 'z',
    'x',  'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*',  0,   ' '};

char keyboard_getc(void) {
        for (;;) {
                uint8_t scancode;

                while (!(INB(0x64) & 1))
                        ;

                scancode = INB(0x60);

                if (scancode & 0x80)
                        continue;

                if (scancode < sizeof(scancode_table))
                        if (scancode_table[scancode])
                                return scancode_table[scancode];
        }
}