#include "fs.h"
#include "io.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

extern unsigned char _binary_bin_hello_bin_start[];
extern unsigned char _binary_bin_hello_bin_end[];

void main(void) {
        VGA_CURSOR_DISABLE();
        clear();
        set_color(BLACK, LIGHT_GREEN);

        bfs_init();

        Folder* root = bfs_root();
        Folder* wd = root;

        bfs_create_file(root, "settings", "cfg");

        File* hello = bfs_create_file(root, "hello", "bin");

        if (hello != NULL) {
                size_t hello_size = _binary_bin_hello_bin_end - _binary_bin_hello_bin_start;

                bfs_write_file(hello, _binary_bin_hello_bin_start, hello_size);
        }

        puts("Welcome to BadOS\n");

        while (true) {
                puts(wd->name);
                puts(" > ");

                char buffer[256];
                gets(buffer, sizeof(buffer));

                if (streq(buffer, "clear")) {
                        clear();
                } else if (streq(buffer, "hello")) {
                        File* file = bfs_find_file(wd, "hello");

                        if (file == NULL) {
                                puts("\nProgram not found: hello.bin\n");
                        } else {
                                putc('\n');
                                bfs_exec(file);
                        }
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
                        bfs_ls(wd);
                } else if (strncmp(buffer, "mkd", 3) == 0 &&
                           (buffer[3] == ' ' || buffer[3] == '\0')) {
                        size_t index = 3;

                        if (buffer[index] == '\0') {
                                puts("\nUsage: mkd <name>\n");
                        } else {
                                index++;

                                bfs_create_folder(wd, buffer + index);
                                putc('\n');
                        }
                } else if (strncmp(buffer, "rm", 2) == 0 &&
                           (buffer[2] == ' ' || buffer[2] == '\0')) {
                        size_t index = 2;

                        if (buffer[index] == '\0') {
                                puts("\nUsage: rm <name>\n");
                        } else {
                                index++;

                                if (!bfs_remove_file(wd, buffer + index)) {
                                        puts("\nFile not found: ");
                                        puts(buffer + index);
                                        puts("\n");
                                } else {
                                        putc('\n');
                                }
                        }
                } else if (strncmp(buffer, "cd", 2) == 0 &&
                           (buffer[2] == ' ' || buffer[2] == '\0')) {
                        size_t index = 2;

                        if (buffer[index] == '\0') {
                                wd = root;
                        } else {
                                index++;

                                if (streq(buffer + index, "..")) {
                                        if (wd->parent != NULL)
                                                wd = wd->parent;
                                } else {
                                        Folder* folder = bfs_find_folder(wd, buffer + index);

                                        if (folder == NULL) {
                                                puts("\nDirectory not found: ");
                                                puts(buffer + index);
                                                puts("\n");
                                        } else {
                                                wd = folder;
                                        }
                                }
                        }

                        putc('\n');
                } else if (streq(buffer, "pwd")) {
                        puts("\n");
                        bfs_pwd(wd);
                        puts("\n");
                } else if (streq(buffer, "help")) {
                        puts("\nAvailable commands:\n");
                        puts("  clear - Clear the screen\n");
                        puts("  help  - Show this message\n");
                        puts("  hello - Execute hello.bin\n");
                        puts("  echo  - Print a message\n");
                        puts("  ls    - List files in the current directory\n");
                        puts("  pwd   - Print the current directory\n");
                        puts("  cd    - Change directory\n");
                        puts("  mkd   - Make a directory\n");
                        puts("  rm    - Remove a file\n");
                } else {
                        puts("\nUnknown command: ");
                        puts(buffer);
                        puts("\n");
                }
        }
}