#pragma once

#include "stdint.h"

#define outb(port, value) __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port))

#define inb(port)                                                                                  \
        ({                                                                                         \
                uint8_t value;                                                                     \
                __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));                         \
                value;                                                                             \
        })

#define VGA_CURSOR_DISABLE()                                                                       \
        __asm__ volatile("movb $0x0A, %al\n"                                                       \
                         "movw $0x3D4, %dx\n"                                                      \
                         "outb %al, %dx\n"                                                         \
                         "movb $0x20, %al\n"                                                       \
                         "movw $0x3D5, %dx\n"                                                      \
                         "outb %al, %dx\n")\
