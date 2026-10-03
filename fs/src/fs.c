#include "fs.h"
#include "heap.h"
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
        (void)parent;
        (void)name;

        return NULL;
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
        File* file = folder->files;

        while (file != NULL) {
                puts(file->name);

                if (file->extension[0] != '\0') {
                        puts(".");
                        puts(file->extension);
                }

                puts("\n");

                file = file->next;
        }
}

void bfs_pwd(Folder* folder) {
        if (folder->parent == NULL) {
                puts("/");
                return;
        }

        puts(folder->name);
}