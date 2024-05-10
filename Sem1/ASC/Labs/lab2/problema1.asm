bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
; exp4 =r-t+z-1001b
segment data use32 class=data
    r db 30
    t dd 10
    z dw 20

; our code starts here
segment code use32 class=code
    start:
        ;r-t
        ;r byte->doubleword
        movzx eax, byte[r]
        sub eax, [t]
        movzx ebx, word[z]
        add eax,ebx
        sub eax, 1001b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
