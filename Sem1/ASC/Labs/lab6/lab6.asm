bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Dandu-se un sir de cuvinte, sa se calculeze cel mai lung subsir de cuvinte ordonate crescator din acest sir.
    s dw 1, 2, 3, 4, 5, 1, 2, 3
    ls equ ($-s)/2
    d times ls dw 0 
    len_max db 0 ; se retine lungimea maxima a subsirului cel mai lung subsir de cuvinte ordonate crescator
    sir_max dw 0 ; se retine adresa de inceput a celui mai lung subsir de cuvinte ordonate crescator 
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls-1 ; ecx = len - 1
        jecxz final ; aceasta eticheta ne asigura ca nu vom avea un loop infinit
        mov esi, s ; esi = adresa de inceput a primului cuvant din sirul s
        mov edi, s+2 ; edi = adresa de inceput a celui de al doilea cuvant din sirul s
        mov eax, s ; eax = adresa de inceput a sirului s
        mov [sir_max], eax ; sir_max = adresa de inceput a sirului s
        mov bl, 1 ; contor pentru subsirul crescator
        mov edx, s ; edx = adresa de inceput a sirului s
        comp:
            cmpsw ; cmp [DS:ESI], [ES:EDI]
            ja mai_mic ; daca subsirul nu e crescator
            inc bl ; creste lungimea curenta a subsirului crescator
            cmp bl, [len_max] ; verificam daca subsirul este de lungime maxima
            jb mai_mic ; cazul in care subsirul nu e de lungime maxima
            mov [len_max], bl ; retinem in len_max lungimea subsirului daca acesta e de lungime maxima
            mov [sir_max], edx ; retinem in sir_max adresa de inceput a subsirului de lungime maxima
            jmp continua
            mai_mic: ; caz in care incepem un nou subsir
                mov bl, 1 ; noul subsir are un element
                mov edx, esi ; edx = adresa de inceput a noului subsir
            continua:
        loop comp
        movzx ecx, byte[len_max] ; ecx =len_max
        mov esi, [sir_max] ; esi = sir_max
        mov edi, d ; edi = d
        load:
            movsw ; d = sir_max
        loop load
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
