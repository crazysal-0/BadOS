#pragma once

#include "stdbool.h"
#include "stddef.h"

size_t strlen(const char* str);
bool streq(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
void strcpy(char* dest, const char* src);
void strncpy(char* dest, const char* src, size_t n);
void* memcpy(void* destination, const void* source, size_t size);
