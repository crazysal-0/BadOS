#include "io.h"
#include "stdio.h"

void main(void) {
        VGA_CURSOR_DISABLE();
        clear();
        set_color(BLACK, LIGHT_GREEN);

        puts("Welcome to BareOS!");

        for (;;) {
        }
}