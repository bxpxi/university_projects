bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; exp2 = a/b - c*d
    a db 60
    b dw 6
    c db 2
    d db 3

; our code starts here
segment code use32 class=code
    start:
        ;punem a in dx:ax
        movzx ax, byte[a]
        mov dx, 0
        ;a/b
        div word[b]
        ;mutam rezultatul a/b in dx
        mov dx, ax
        ;punem c in bl si d in cl
        mov al, byte[c]
        mov bl, byte[d]
        ;c*d
        mul bl
        ;a/b - c*d
        sub dx, ax
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
