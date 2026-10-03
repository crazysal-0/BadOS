#pragma once

#include "file.h"

typedef struct Folder {
        char name[16];

        File* files;
        struct Folder* next;
        struct Folder* parent;
} Folder;