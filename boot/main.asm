[bits 16]

section .boot

global _start
extern main

_start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00

	mov [boot_drive], dl

	mov si, disk_packet
	mov dl, [boot_drive]
	mov ah, 0x42
	int 0x13
	jc .hang

	call main

.hang:
	hlt
	jmp .hang

boot_drive:
	db 0

disk_packet:
	db 0x10
	db 0
	dw 2
	dw 0x7e00
	dw 0
	dq 1