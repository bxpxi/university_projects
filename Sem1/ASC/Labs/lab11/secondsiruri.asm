bits 32

segment data use32 class=data
    cifre db '0123456789'
    
segment code use32 class=code
    global concatenare
    concatenare:
        
        mov esi, [esp+4] ; esi = offset-ul sirului s1
        mov edi, [esp+12] ; edi = offset-ul sirului s3
        mov ecx, [esp+20] ; ecx = len1
        
        cld
        
        repeta:
            lodsb
            push ecx
            push esi
            mov ecx,10
            mov esi,cifre
            mov bl, al
            repeta1:
                lodsb
                cmp bl,al
                je final_repeta1
            loop repeta1
            final_repeta1:
                pop esi
                pop ecx 
                stosb
        loop repeta
        
        mov esi, [esp+8] ; esi = offset-ul sirului s2
        mov ecx, [esp+16] ; ecx = len2
        
        cld
        
        repeta2:
            lodsb
            push ecx
            push esi
            mov ecx,10
            mov esi,cifre
            mov bl, al
            repeta3:
                lodsb
                cmp bl,al
                je final_repeta3
            loop repeta3
            final_repeta3:
                pop esi
                pop ecx 
                stosb
        loop repeta2
        
    ret 4*5
        
        
        