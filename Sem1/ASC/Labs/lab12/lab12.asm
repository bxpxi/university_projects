bits 32
global _concatenare
segment code public code use32
_concatenare:

    a dd 0
    b dd 0 
    result dd 0
segment code public code use32
    _concatenare:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp+8]
        mov [a], eax
        
        mov eax, [ebp+12]
        mov [b], eax
        
        mov eax, [ebp+16]
        mov [result], eax
        
        mov esi, [a]
        mov edi, [result]
        cld
        repeta:
            lodsb
            cmp al,0
            je final
            cmp al, '0'
            jb fals
            cmp al, '9'
            ja fals
            stosb
            fals:   
            jmp repeta
        final:
        
        mov esi, [b]
        cld
        repeta2:
            lodsb
            cmp al,0
            je final2
            cmp al, '0'
            jb fals2
            cmp al, '9'
            ja fals2
            stosb
            fals2:
            jmp repeta22
        final2:
        mov esp, ebp
        pop ebp
    ret
