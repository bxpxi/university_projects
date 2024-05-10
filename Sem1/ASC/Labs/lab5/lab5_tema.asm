bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1
    b db 0
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        mov bl,[a]
        mov [b], bl
        ror byte[b], 3 ; se obtine b prin rotirea la dreapta a lui a cu 3 biti
        movzx eax, byte[b] ; EAX = 00000000 00000000 00000000 a2a1a0a7a6a5a4a3
        shl eax, 24 ;  EAX = a2a1a0a7a6a5a4a3  00000000 00000000 00000000
        or dword[c], eax ; c  = a2a1a0a7a6a5a4a3  00000000 00000000 00000000
        movzx eax, byte[a] ; EAX = 00000000 00000000 00000000 a7a6a5a4a3a2a1a0
        shl eax, 16 ; EAX = 00000000 a7a6a5a4a3a2a1a0 00000000 00000000
        or dword[c], eax ; c = a2a1a0a7a6a5a4a3 a7a6a5a4a3a2a1a0 00000000 00000000
        or dword[c], 00000000000000000000000011111111b ; c = a2a1a0a7a6a5a4a3 a7a6a5a4a3a2a1a0 00000000 11111111
        mov ecx, [c]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
