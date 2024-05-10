bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;27/ (a+b) - c*data
    a db 2
    b dw 3
    c db 1
    d dw 5

; our code starts here
segment code use32 class=code
    start:
        ; a+b
        ;a de la byte sa devina word
        movzx ax,byte[a]
        add ax,[b] ; ax=a+b
        ;transferam continutul din bx pt ca ax sa ramana pt impartire
        mov ax,bx
        ;bx=a+b
        ;27/bx
        ;27 -> dx:ax
        mov ax,27
        mov dx,0
        div bx ;dx:ax/bx= ax cat, dx rest, ignoram restul impartirii
        ;ax-c*d
        ;word-byte*word
        ;transfer ax in bx
        mov bx,ax
        ;bx=27/(a+b)
        ;c*d
        ;c cde la byte la word
        movzx ax,byte[c]
        mul word[d];dx:ax=c*d
        ;27/(a+b)-c*d
        ;bx-dx:ax
        ;word->dword
        ;combinatie de registri pe 16:16
        ;cx:bx = 1 dword = 32 biti
        mov cx,0
        ;cx:bx
        ;dx:bx
        sub bx,ax
        sbb 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
