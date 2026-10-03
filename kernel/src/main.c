#include "io.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void main(void) {
        VGA_CURSOR_DISABLE();
        clear();
        set_color(BLACK, LIGHT_GREEN);

        puts("Welcome to BareOS!\n\n");

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
                        puts("  echo  - Print a message\n");
                } else if (strncmp(buffer, "echo", 4) == 0 &&
                           (buffer[4] == ' ' || buffer[4] == '\0')) {
                        size_t index = 4;

                        if (buffer[index] == '\0') {
                                puts("\nUsage: echo <message>\n");
                        } else {
                                index++;

                                puts("\n");
                                puts(buffer + index);
                                puts("\n");
                        }
                } else {
                        puts("\nUnknown command: ");
                        puts(buffer);
                        puts("\n");
                }
        }
}