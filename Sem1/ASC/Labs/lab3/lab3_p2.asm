bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;(a*b+2)/(a+7-c)+d+x
;fara semn
segment data use32 class=data
    a db
    c db
    b dw
    d dd
    x dq

; our code starts here
segment code use32 class=code
    start:
        movzx ax, byte[a]
        mul word[b]
        add eax, 2
        movzx bx, byte[a]
        add bx, 7
        sub bx, byte[c]
        div bx
        movzx eax, al
        add eax, dword[d]
        mov edx, 0
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
