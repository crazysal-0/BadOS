#include "fs.h"
#include "heap.h"
#include "stdio.h"
#include "string.h"

static Folder root;

void bfs_init(void) {
        root.name[0] = '\0';
        root.files = NULL;
        root.next = NULL;
        root.parent = NULL;
}

Folder* bfs_root(void) {
        return &root;
}

File* bfs_create_file(Folder* folder, const char* name, const char* extension) {
        File* file = malloc(sizeof(File));

        if (file == NULL)
                return NULL;

        strncpy(file->name, name, sizeof(file->name));
        strncpy(file->extension, extension, sizeof(file->extension));

        file->size = 0;
        file->contents = NULL;
        file->next = NULL;

        if (folder->files == NULL) {
                folder->files = file;
                return file;
        }

        File* current = folder->files;

        while (current->next != NULL)
                current = current->next;

        current->next = file;

        return file;
}

Folder* bfs_create_folder(Folder* parent, const char* name) {
        if (parent == NULL || name == NULL)
                return NULL;

        Folder* new_folder = (Folder*)malloc(sizeof(Folder));
        if (new_folder == NULL)
                return NULL;

        strncpy(new_folder->name, name, 16);

        new_folder->files = NULL;
        new_folder->next = NULL;

        if (parent->next == NULL) {
                parent->next = new_folder;
        } else {
                Folder* current = parent->next;
                while (current->next != NULL) {
                        current = current->next;
                }
                current->next = new_folder;
        }

        return new_folder;
}

void bfs_write_file(File* file, const char* contents) {
        size_t size = strlen(contents);

        char* data = malloc(size + 1);

        if (data == NULL)
                return;

        strcpy(data, contents);

        file->contents = data;
        file->size = size;
}

File* bfs_find_file(Folder* folder, const char* name) {
        File* current = folder->files;

        while (current != NULL) {
                if (streq(current->name, name))
                        return current;

                current = current->next;
        }

        return NULL;
}

void bfs_ls(Folder* folder) {
        if (folder == NULL)
                return;

        File* file = folder->files;
        while (file != NULL) {
                puts(file->name);

                if (file->extension != NULL && file->extension[0] != '\0') {
                        putc('.');
                        puts(file->extension);
                }

                puts(" ");
                file = file->next;
        }

        Folder* folder_ = folder->next;
        if (folder_ != NULL) {
                color_t text_color = get_text_color();
                set_text_color(LIGHT_CYAN);

                while (folder_ != NULL) {
                        puts(folder_->name);
                        putc('/');
                        puts(" ");
                        folder_ = folder_->next;
                }

                set_text_color(text_color);
        }
        putc('\n');
}

void bfs_pwd(Folder* folder) {
        if (folder->parent == NULL) {
                puts("/");
                return;
        }

        puts(folder->name);
}