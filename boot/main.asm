[bits 16]

section .text

global _start
extern main

_start:
	; clean out segments
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov sp, 0x7c00

	call main

.hang:
	hlt
	jmp .hang