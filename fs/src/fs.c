#include "fs.h"
#include "heap.h"
#include "stdio.h"
#include "string.h"

static Folder root;

void fs_init(void) {
        root.name[0] = '\0';
        root.files = NULL;
        root.next = NULL;
        root.parent = NULL;
}

Folder* fs_root(void) {
        return &root;
}

File* fs_create_file(Folder* folder, const char* name, const char* extension) {
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

Folder* fs_find_folder(Folder* folder, const char* name) {
        if (folder == NULL || name == NULL)
                return NULL;

        Folder* current = folder->next;

        while (current != NULL) {
                if (streq(current->name, name))
                        return current;

                current = current->next;
        }

        return NULL;
}

bool fs_remove_folder(Folder* parent, const char* name) {
        if (parent == NULL || name == NULL)
                return false;

        Folder* current = parent->next;
        Folder* previous = NULL;

        while (current != NULL) {
                if (streq(current->name, name)) {
                        if (current->files != NULL)
                                return false;

                        if (previous == NULL)
                                parent->next = current->next;
                        else
                                previous->next = current->next;

                        return true;
                }

                previous = current;
                current = current->next;
        }

        return false;
}

bool fs_remove_file(Folder* folder, const char* name) {
        if (folder == NULL || name == NULL)
                return false;

        File* current = folder->files;
        File* previous = NULL;

        while (current != NULL) {
                if (streq(current->name, name)) {
                        if (previous == NULL)
                                folder->files = current->next;
                        else
                                previous->next = current->next;

                        return true;
                }

                previous = current;
                current = current->next;
        }

        return false;
}

Folder* fs_create_folder(Folder* parent, const char* name) {
        if (parent == NULL || name == NULL)
                return NULL;

        Folder* new_folder = malloc(sizeof(Folder));

        if (new_folder == NULL)
                return NULL;

        strncpy(new_folder->name, name, sizeof(new_folder->name));

        new_folder->files = NULL;
        new_folder->next = NULL;
        new_folder->parent = parent;

        if (parent->next == NULL) {
                parent->next = new_folder;
        } else {
                Folder* current = parent->next;

                while (current->next != NULL)
                        current = current->next;

                current->next = new_folder;
        }

        return new_folder;
}

File* fs_find_file(Folder* folder, const char* name) {
        if (folder == NULL || name == NULL)
                return NULL;

        File* current = folder->files;

        while (current != NULL) {
                if (streq(current->name, name))
                        return current;

                current = current->next;
        }

        return NULL;
}

void fs_ls(Folder* folder) {
        if (folder == NULL)
                return;

        File* file = folder->files;

        while (file != NULL) {
                puts(file->name);

                if (file->extension[0] != '\0') {
                        putc('.');
                        puts(file->extension);
                }

                puts(" ");
                file = file->next;
        }

        Folder* folder_ = folder->next;

        if (folder_ != NULL) {
                Color text_color = get_text_color();

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

void fs_pwd(Folder* folder) {
        if (folder->parent == NULL) {
                puts("/");
                return;
        }

        puts(folder->name);
}

void fs_exec(File* file) {
        if (file == NULL || file->contents == NULL)
                return;

        void (*program)(void) = (void (*)(void))file->contents;

        program();
}

void fs_write_file(File* file, const void* contents, size_t size) {
        unsigned char* data = malloc(size);

        if (data == NULL)
                return;

        memcpy(data, contents, size);

        file->contents = data;
        file->size = size;
}
