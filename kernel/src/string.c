#include "stdbool.h"
#include "stddef.h"

size_t strlen(const char* str) {
        size_t len = 0;

        while (str[len] != '\0')
                len++;

        return len;
}

bool streq(const char* s1, const char* s2) {
        size_t len = strlen(s1);

        if (len != strlen(s2))
                return false;

        for (size_t i = 0; i < len; i++) {
                if (s1[i] != s2[i])
                        return false;
        }

        return true;
}

int strncmp(const char* s1, const char* s2, size_t n) {
        for (size_t i = 0; i < n; i++) {
                if (s1[i] != s2[i])
                        return (unsigned char)s1[i] - (unsigned char)s2[i];

                if (s1[i] == '\0')
                        return 0;
        }

        return 0;
}

void strcpy(char* dest, const char* src) {
        while ((*dest++ = *src++))
                ;
}

void strncpy(char* dest, const char* src, size_t n) {
        size_t i = 0;

        while (i < n - 1 && src[i] != '\0') {
                dest[i] = src[i];
                i++;
        }

        dest[i] = '\0';
}