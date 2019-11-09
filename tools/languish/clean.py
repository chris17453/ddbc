

def clean_pattern(pattern):
    pattern=pattern.strip()
    found=None
    new_pattern=""
    dont_break_quoted_blocks=None
    in_character_block=None
    escaped=None
    pattern= ''.join([i if ord(i) < 128 else ' ' for i in pattern])

    for i in pattern:
    
        if dont_break_quoted_blocks==True:
                if found:
                    new_pattern+=i
                    if i==found:
                        found=None
                    continue
                if i=="'":
                    found="'"
                elif i=='"':
                    found='"'
                if found:
                    new_pattern+=i
                    continue
        
        if escaped==None and  i=='\\':
            escaped=True
            new_pattern+=" "+i
            continue
        
        if escaped==True:
            escaped=None
            new_pattern+=i+" "
            continue
        
        
        if i=='[':
            in_character_block=True
        if in_character_block==True:
            new_pattern+=" "+i+" "
            if i==']':
                in_character_block=None
            continue


        if found == None:
            if  i in ("|","(",")","[","]",",","-","^","+","*",".","?"):
                new_pattern+=" "+i+" "
            else:
                new_pattern+=i
        else:
            new_pattern+=i
    #print new_pattern
    return new_pattern
