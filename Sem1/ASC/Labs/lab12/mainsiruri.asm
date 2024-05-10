bits 32

global start        

extern exit, printf            
import exit msvcrt.dll
import printf msvcrt.dll
extern concatenare

segment data use32 class=data
    s db "ana are 12 mere si 5 pere"
    len1 equ $-s
    d db "maria are 3 mere si 10 pere"
    len2 equ $-d
    result times len1+len2+1 db 0
    ;12 5 3 10 3 10 12 5
    
segment code use32 class=code public
    start:
        push dword len1
        push dword len2
        push dword result
        push dword d
        push dword s
        
        call concatenare
        
        push dword result
        call[printf]
        add esp, 4*1
        push    dword 0
        call    [exit]
