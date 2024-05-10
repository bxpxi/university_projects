bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
; (a * b + 2)/(a + 7 - c) + d +x
; FARA  semn
segment data use32 class=data
    a db 8
    b dw 2
    c db 6
    d dd 4
    x dq 1

; our code starts here
segment code use32 class=code
    start:
        movzx ax, byte[a];AX = a
        mul word[b];DX:AX = a*b
        add ax, 2; DX:AX = a*b + 2
        movzx bx, byte[a]; BX = a
        add bx, 7;BX = a + 7
        movzx cx, byte[c]; CX = c
        sub bx, cx;BX = a + 7 - c
        div bx ; (a * b + 2)/(a + 7 - c) - AX = cat, DX = rest
        movzx eax, ax; EAX = (a * b + 2)/(a + 7 - c) - catul
        add eax, dword[d]; EAX = (a * b + 2)/(a + 7 - c) + d
        mov edx, 0;EDX = 0
        add eax, dword[x]
        add edx, dword[x+4]; EDX:EAX = (a * b + 2)/(a + 7 - c) + d + x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
