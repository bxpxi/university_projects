bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;adunari si scaderi, interpretari cu semn
;problema 24
;exp = (a+b+c)-d+(b-c)
segment data use32 class=data
    a db 1
    b dw 3
    c dd 2
    d dq 4

; our code starts here
segment code use32 class=code
    start:
        movsx eax, byte[a];eax=a
        movsx ebx, word[b];ebx=b
        add eax, ebx;eax=eax+ebx=a+b
        mov ebx, dword[c];ebx=c
        add eax,ebx;eax=eax+ebx=a+b+c
        cdq;edx:eax=a+b+c
        sub eax, [d] 
        sbb edx, [d+4];edx:eax=(a+b+c)-d
        movsx ebx, word[b];ebx=b
        sub ebx, dword[c];ebx=b-c
        mov ecx, eax;ecx=eax
        mov eax, ebx;eax=ebx
        mov ebx, edx;ebx=edx
        cdq
        add eax, ecx
        add edx, ebx;edx:eax=(a+b+c)-d+(b-c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
