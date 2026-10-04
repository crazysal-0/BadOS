#pragma once

#include "stdint.h"

typedef struct File {
        char name[16];
        char extension[8];

        uint16_t size;
        unsigned char* contents;

        struct File* next;
} File;