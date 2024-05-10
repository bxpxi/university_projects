bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf, getchar, fprintf           
import exit msvcrt.dll    
import fopen msvcrt.dll                        
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import getchar msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)

;Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de vocale si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date

segment data use32 class=data
    nume_fisier db "file.txt", 0; numele fisierului care va fi creat
    mod_acces db "r", 0          ; modul de deschidere a fisierului - 
                                 ; r - pentru scriere. fisierul trebuie sa existe 
    len equ 100                  ; numarul maxim de elemente citite din fisier.                            
    text times (len+1) db 0      ; sirul in care se va citi textul din fisier (dimensiune len+1 explicata mai sus)
    descriptor_fis dd -1         ; variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    format db "Am citit %d vocale din fisier.", 0  ; formatul - utilizat pentru afisarea textului citit din fisier
                                 ; %s reprezinta un sir de caractere
    vocale db "aeiouAEIOU", 0
    lvocale equ $-vocale
    contor dd 0

; our code starts here
segment code use32 class=code
    start:
        ; apelam fopen pentru a deschide fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        ; citim textul in fisierul deschis folosind functia fread
        ; eax = fread(text, 1, len, descriptor_fis)
        push dword [descriptor_fis]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4                 ; dupa apelul functiei fread EAX contine numarul de caractere citite din fisier
        
        
        mov ecx, eax
        mov esi, 0;text
        mov edi, 0;vocale
        mov ebp, 0;rezultat
        repeta_text:
            mov al, [text+esi]
            push ecx
            mov ecx, lvocale
            repeta_vocale:
                mov bl, [vocale+edi]
                cmp al, bl
                je numara
                jne nu_numara
                numara:
                    inc dword[contor]
                nu_numara:
                    inc edi
            loop repeta_vocale
            inc esi
            pop ecx
        loop repeta_text
        
        push dword [contor]
        push dword format
        push dword [descriptor_fis]
        call[fprintf]
        add esp, 4*3
        
        
        ; apelam functia fclose pentru a inchide fisierul
        ; fclose(descriptor_fis)
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
      final:
        
        ; exit(0)
        push    dword 0      
        call    [exit]       
