#include "io.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void main(void) {
        VGA_CURSOR_DISABLE();
        clear();
        set_color(BLACK, LIGHT_GREEN);

        puts("Welcome to BareOS!\n");
        while (true) {
                puts(" > ");

                char buffer[256];
                gets(buffer, sizeof(buffer));

                if (streq(buffer, "clear")) {
                        clear();
                } else if (streq(buffer, "")) {
                        puts("\n");
                } else if (streq(buffer, "help")) {
                        puts("\nAvailable commands:\n");
                        puts("  clear - Clear the screen\n");
                        puts("  help  - Show this message\n");
                } else if (streq(buffer, "exit")) {
                        puts("\nExiting the shell...\n");
                        break;
                } else {
                        puts("\nUnknown command: ");
                        puts(buffer);
                        puts("\n");
                }
        }
}