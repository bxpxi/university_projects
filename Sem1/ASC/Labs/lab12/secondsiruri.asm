bits 32

segment code use32 class=code public

global concatenare
    concatenare:
        mov esi, [esp+4]
        mov edi, [esp+12]
        mov ecx, [esp+20]
        cld
        repeta:
            lodsb
            cmp al, '0'
            jb fals
            cmp al, '9'
            ja fals
            stosb
            fals:
        loop repeta
        
        mov esi, [esp+8]
        mov ecx, [esp+16]
        cld
        repeta2:
            lodsb
            cmp al, '0'
            jb fals2
            cmp al, '9'
            ja fals2
            stosb
            fals2:
        loop repeta2
        
        mov esi, [esp+8]
        mov ecx, [esp+16]
        cld
        repeta3:
            lodsb
            cmp al, '0'
            jb fals3
            cmp al, '9'
            ja fals3
            stosb
            fals3:
        loop repeta3
        
        mov esi, [esp+4]
        mov ecx, [esp+20]
        cld
        repeta4:
            lodsb
            cmp al, '0'
            jb fals4
            cmp al, '9'
            ja fals4
            stosb
            fals4:
        loop repeta4
        
        ret 4*9
        
