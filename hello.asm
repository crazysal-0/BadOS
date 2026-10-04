bits 16

start:
        mov ax, 0xb800
        mov es, ax

        mov byte [es:0], 'H'
        mov byte [es:1], 0x0a

        mov byte [es:2], 'e'
        mov byte [es:3], 0x0a

        mov byte [es:4], 'l'
        mov byte [es:5], 0x0a

        mov byte [es:6], 'l'
        mov byte [es:7], 0x0a

        mov byte [es:8], 'o'
        mov byte [es:9], 0x0a

        ret