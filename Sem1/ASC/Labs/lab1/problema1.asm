bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; exp1 = a+b+27-c
    a dw 2
    b dd 3
    c db 10

; our code starts here
segment code use32 class=code
    start:
        ; punem a in eax, 16 biti -> 32 biti, eax=a 
        movzx eax,word[a]
        ; eax=a+b
        add eax, dword[b]
        ; eax=a+b+27
        add eax, 11011b
        ;punem c in ebx, 8 biti -> 32 biti, ebx=c
        movzx ebx, byte[c]
        ;eax=a+b+27-c
        sub eax, ebx
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
