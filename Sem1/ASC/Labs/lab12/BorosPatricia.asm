bits 32 

global start        

extern exit, printf, scanf               
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll    


segment data use32 class=data
    a dd 0
    b dd 0
    format1 db "a=",0
    format2 db "b=",0
    readformat1 db "%d",0
    readformat2 db "%x",0
    printformat db "%d",0

segment code use32 class=code
    start:
        ;printf(format1)
        push dword format1
        call [printf]
        add esp, 4*1
        
        ;scanf(readformat1, a)
        push dword a
        push dword readformat1
        call [scanf]
        add esp, 4*2
        
        ;printf(format2)
        push dword format2
        call [printf]
        add esp, 4*1
        
        ;scanf(readformat2, b)
        push dword b
        push dword readformat2
        call [scanf]
        add esp, 4*2
        
        ;exp = a*(-3)/b
        mov eax, [a]
        mov ebx, -3
        imul ebx
        cdq
        idiv dword[b]
      
        ;printf(printformat, eax)
        push eax
        push dword printformat
        call [printf]
        add esp, 4*2
        
        push    dword 0      
        call    [exit]       
