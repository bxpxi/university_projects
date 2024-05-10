bits 32 

global start        

extern exit, printf, concatenare               
import exit msvcrt.dll    
import printf msvcrt.dll
                          

segment data use32 class=data
    s1 db 'abc234df6q'
    len1 equ $-s1
    s2 db 'jdbve875jbd90'
    len2 equ $-s2
    s3 times len1+len2+1 db 0

; Se dau doua siruri continand caractere. Sa se calculeze si sa se afiseze rezultatul concatenarii tuturor caracterelor tip cifra zecimala din cel de-al doilea sir dupa cele din primul sir si invers, rezultatul concatenarii primului sir dupa al doilea.

segment code use32 class=code
    start:
        ; punem parametrii pe stiva
        push dword len1
        push dword len2
        push s3
        push s2
        push s1
        
        call concatenare
        
        push dword s3
        call [printf]
        add esp, 4*1
    
        push    dword 0      
        call    [exit]       
