ORG 0x7c00 
BITS 16

start:
    cli
    cli
    cli
    cli
    cli
    cli
    mov si, message
    call print
    mov al, 0
    mov ah, 86h
    mov cx, 20
    mov dx, 40
    int 15h
    cli
    push 0X0A000
    pop es
    xor di, di
    xor ax, ax
    mov ax, 0x13
    int 0x10
    jmp payload1

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0 
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db "Hi", 0

payload1:
    
    mov ah, 0x0c
    add al, 1
    mov bh, 0x00
    add cx, 100
    add dx, -1
    int 0x10
    mov ah, 0x0c
    add al, 3
    mov bh, 0x00
    add cx, 10
    add dx, -10
    int 0x10
    mov ah, 0x0c
    add al, 1
    mov bh, 0x00
    add cx, 10
    add dx, -10
    int 0x10
    mov ah, 0x0c
    add al, 30
    mov bh, 0x00
    add cx, 10
    add dx, 10
    int 0x10
    mov ah, 0x0c
    add al, 4
    mov bh, 0x00
    add cx, 10
    add dx, 10
    int 0x10
    mov ah, 0x0c
    add al, 8
    mov bh, 0x00
    add cx, 10
    add dx, 50
    int 0x10
      mov ah, 0x0c
    add al, 1
    mov bh, 0x00
    add cx, 10
    add dx, -10
    int 0x10
    mov ah, 0x0c
    add al, 3
    mov bh, 0x00
    add cx, -10
    add dx, -10
    int 0x10
    mov ah, 0x0c
    add al, 1
    mov bh, 0x00
    add cx, 100
    add dx, -100
    int 0x10
    mov ah, 0x0c
    add al, 3
    mov bh, 0x00
    add cx, 10
    add dx, -1000
    int 0x10
    mov ah, 0x0c
    add al, 5
    mov bh, 0x00
    add cx, 10
    add dx, -10
    int 0x10
    mov ah, 0x0c
    add al, 16
    mov bh, 0x00
    add cx, 000
    add dx, 100
    int 0x10
    
    jmp payload2

payload2:
    
    mov ah, 0x0c
    add al, 1
    mov bh, 0x00
    add cx, 1000
    add dx, -100
    int 0x10
    jmp payload1

times 510 - ($-$$) db 0
dw 0XAA55

