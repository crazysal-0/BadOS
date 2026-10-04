#include "fs.h"
#include "io.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void main(void) {
        VGA_CURSOR_DISABLE();
        clear();
        set_color(BLACK, LIGHT_GREEN);

        bfs_init();
        Folder* root = bfs_root();

        bfs_create_file(root, "settings", "cfg");

        puts("Welcome to BadOS\n");

        while (true) {
                puts(" > ");

                char buffer[256];
                gets(buffer, sizeof(buffer));

                if (streq(buffer, "clear")) {
                        clear();
                } else if (strncmp(buffer, "echo", 4) == 0 &&
                           (buffer[4] == ' ' || buffer[4] == '\0')) {
                        size_t index = 4;

                        if (buffer[index] == '\0') {
                                puts("\nUsage: echo <message>\n");
                        } else {
                                index++;

                                puts("\n");
                                puts(buffer + index);
                        }
                } else if (streq(buffer, "ls")) {
                        puts("\n");
                        bfs_ls(root);
                } else if (strncmp(buffer, "mkd", 3) == 0 &&
                           (buffer[3] == ' ' || buffer[3] == '\0')) {
                        size_t index = 4;

                        if (buffer[index] == '\0') {
                                puts("\nUsage: mkd <name>\n");
                        } else {
                                index++;

                                bfs_create_folder(root, buffer + (index - 1));
                                putc('\n');
                        }
                } else if (streq(buffer, "pwd")) {
                        puts("\n");
                        bfs_pwd(root);
                        puts("\n");
                } else if (streq(buffer, "help")) {
                        puts("\nAvailable commands:\n");
                        puts("  clear - Clear the screen\n");
                        puts("  help  - Show this message\n");
                        puts("  echo  - Print a message\n");
                        puts("  ls    - List files in the current directory\n");
                        puts("  pwd   - Print the current directory\n");
                } else {
                        puts("\nUnknown command: ");
                        puts(buffer);
                        puts("\n");
                }
        }
}