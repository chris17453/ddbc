
from .clean import clean_pattern

def get_var(name):
    if isinstance(name,str):
        if len(name)>1:
            if name[0]=='{' and name[-1]=='}':
                return name[1:-1]
    return None


def recursive(tokens,name):
    if isinstance(tokens,str):
        if get_var(tokens)==name:
            return 1
        else:
            return 0

    elif isinstance(tokens,dict):
        count=recursive(tokens['data'],name)
        return count
    
    elif isinstance(tokens,list):
        count=0
        for token in tokens:
            count+=recursive(token,name)
        return count


def get_padd(depth,spacer):
    padd=''
    for i in range(0,depth):
       padd=padd+spacer
    padd+="    "
    return padd

uid_int=1

def uid():
    global uid_int
    uid_int+=1
    return uid_int

def build_expression_levels(pattern,expression_depth):
    pattern=clean_pattern(pattern)
    tokens=pattern.split(" ")
    
    tokens2=[]

    index=0
    while 1:
        #1 index
        if index>=len(tokens):
            break
        token=tokens[index]
        if token=='(':
            sub_tokens=[]
            depth=0
            for sub_index in range(index,len(tokens)):
                sub_token=tokens[sub_index]
                if sub_token=='(': depth+=1 
                if sub_token==')': depth-=1 
                if depth==0:
                    sub_tokens.append(sub_token)
                    pattern2=" ".join(sub_tokens)
                    if pattern==pattern2:
                        tokens2.append(sub_tokens)    
                    else:
                        tokens2.append({'type':'group','data':build_expression_levels(pattern2[1:-1],expression_depth+1)}) 
                    index=sub_index+1
                    break
                else:
                    if token!='':
                        sub_tokens.append(sub_token)
            index+=1
            continue
        
        if token=='[':
            sub_tokens=[]
            depth=0
            for sub_index in range(index,len(tokens)):
                sub_token=tokens[sub_index]
                if sub_token=='[': depth+=1 
                if sub_token==']': depth-=1 
                if depth==0:
                    sub_tokens.append(sub_token)
                    pattern2=" ".join(sub_tokens)
                    if pattern==pattern2:
                        tokens2.append(sub_tokens)    
                    else:
                        
                        char_expressions=build_expression_levels(pattern2[1:-1],expression_depth+1)
                        tokens2.append({'type':'char','data':char_expressions}) 
                    index=sub_index+1
                    break
                else:
                    if token!='':
                        sub_tokens.append(sub_token)
            index+=1
            continue
        if token!='':
            tokens2.append(token)
        index+=1
    # end loops
    return tokens2

def gather_matches(tokens):
    functions={}
    if isinstance(tokens,list):
        for token in tokens:
            functions.update(gather_matches(token))

    elif isinstance(tokens,dict):
        functions.update(gather_matches( tokens['data']))

    elif isinstance(tokens,str):
        functions[tokens]=1

    return functions

def group_expressions(tokens,token_type=None):
    if isinstance(tokens,str):
        if token_type=="char":
            tokens=tokens.replace("\\s",' ')
            tokens=tokens.replace("\\n",'\n')
            tokens=tokens.replace("\\t",'\t')
            tokens=tokens.replace("\\",'')

        return tokens

    elif isinstance(tokens,dict):
        tokens2={'type':tokens['type'],'data':[]}
        tokens2['data']=group_expressions(tokens['data'],tokens['type'])
        return tokens2
    
    elif isinstance(tokens,list):
        tokens2=[]
        index=0
        in_or=0
        while index<len(tokens):
            
            if token_type=="char":
                if len(tokens)>index+2:
                    if tokens[index+1]=='-':
                        tokens2.append({'type':'range','data':[group_expressions(tokens[index]),group_expressions(tokens[index+2])]})
                        index+=3
                        continue
            
            if len(tokens)>index+1:
                if token_type!='char' and token_type!='range':
                    if tokens[index]=='^':
                        tokens2.append({'type':'not'     ,'data':group_expressions(tokens[index+1])})
                        index+=2
                        continue
                    if tokens[index+1]=='?':
                        tokens2.append({'type':'optional','data':group_expressions(tokens[index])})
                        index+=2
                        continue
                    if tokens[index+1]=='*':
                        tokens2.append({'type':'zero_or_more','data':group_expressions(tokens[index])})
                        index+=2
                        continue
                    if tokens[index+1]=='+':
                        tokens2.append({'type':'one_or_more','data':group_expressions(tokens[index])})
                        index+=2
                        continue

                if in_or==0 and tokens[index+1]=='|':
                    sub=[]
                    in_or=1
            if tokens[index]=='|':
                index+=1
                continue
            if in_or==1:
                sub.append(group_expressions(tokens[index],token_type))
            else:
                tokens2.append(group_expressions(tokens[index],token_type))
            if len(tokens)>index+1:
                if in_or==1 and tokens[index]!='|' and tokens[index+1]!='|':
                    tokens2.append({'type':'or','data':sub})
                    in_or=0
            index+=1
        if in_or==1:
            tokens2.append({'type':'or','data':sub})
        return tokens2


def compress_expressions(tokens):
    if isinstance(tokens,str):
        return tokens

    elif isinstance(tokens,dict):
        ## remove single groups...
        if tokens['type']=='group' and len(tokens['data'])==1:
            return tokens['data']

        ## unravel ranges from chars, remove empty chars and group chars        
        if tokens['type']=='char':
            tokens2=[]
            inner_types=[]
            for item in tokens['data']:
                if isinstance(item,str):
                    tokens2.append(item)
                if isinstance(item,dict):
                    inner_types.append(item)
            
            if len(tokens2)>0:
                inner_types.append({'type':tokens['type'],'data':tokens2})
            return inner_types
        else:
            returned_tokens=compress_expressions(tokens['data'])
            return {'type':tokens['type'],'data':returned_tokens}
    
    elif isinstance(tokens,list):
        tokens2=[]
        for item in tokens:
            returned_tokens=compress_expressions(item)
            tokens2.append(returned_tokens)
        
        return tokens2
    return "ERROR"