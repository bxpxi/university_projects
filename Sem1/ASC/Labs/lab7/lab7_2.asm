bits 32 

global start        

extern exit, fopen, fprintf, fclose, fread, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    fisier db "file.txt", 0
    access_mode db "r", 0
    descriptor dd -1
    vocale db 'aeiouAEIOU',0
    caracter db 0
    len equ 100
    text times (len + 1) db 0
    mesajafisare db 'Numarul de vocale este: %d', 0

; 1.Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de vocale si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.
segment code use32 class=code
    start:
        push dword access_mode   
        push dword fisier
        call [fopen]
        add esp, 4*2  
        
        mov [descriptor], eax  
        cmp eax, 0
        je final
        
        push dword [descriptor]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4 
        
        mov ecx,eax 
        mov esi,text
        cld
        mov edx,0
        repeta:
            lodsb
            push ecx
            push esi
            mov ecx,10
            mov esi,vocale
            mov bl, al
            inc edx
            repeta1:
                lodsb
                cmp bl,al
                je final_repeta1
            loop repeta1
            dec edx
            final_repeta1:
                pop esi
                pop ecx              
        loop repeta
        
        push edx
        push dword mesajafisare
        call [printf]
        add esp, 4*2
        
        push dword [descriptor]
        call [fclose]
        add esp, 4


        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
