import datetime
from pprint import pprint
import re
from tpl import tpl
 


print("""
#include "headers/bytecode.h"
""")


def clean_pattern(pattern):
    pattern=pattern.strip()
    found=None
    new_pattern=""
    dont_break_quoted_blocks=None
    in_character_block=None
    for i in pattern:
    
        if dont_break_quoted_blocks:
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

def get_padd(depth,spacer):
    padd=''
    for i in range(0,depth):
       padd=padd+spacer
    padd+="    "
    return padd

uid_int=1
    
# '??' string
# "??" string
# {??} Ex: {digit}    
# +    Ex: [a-z]+      repeat unlimited times
# *    Ex: ([a-z]+)*   0 or more times    
# ( )  Ex: ( [a-z]+ )  group
# [ ]  Ex: [A-Za-z.]   any of these characters
# ?    Ex: {method}?   optional
# -    EX: [x-y]       range

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
        #print index
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
                        tokens2.append({'type':'char','data':build_expression_levels(pattern2[1:-1],expression_depth+1)}) 
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

    if isinstance(tokens,dict):
        for token in tokens['data']:
            functions.update(gather_matches(token))

    if isinstance(tokens,str):
        functions[tokens]=1

    return functions

def group_expressions(tokens,token_type=None):
    if isinstance(tokens,str):
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

def build(name,pattern,depth=0):
    # load data / set variables
    tokens=build_expression_levels(pattern,0)
    # pprint(tokens,indent=2)
    # print " ---"
    tokens=group_expressions(tokens)
    list_of_match_functions=gather_matches(tokens)
    # pprint(tokens,indent=2)
    
    if depth==0:
        t=tpl("templates/templates.txt")
        t.add("compare_function","function_name",name)
        t.add("compare_function","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
        t.add("compare_function","body", build_function_templates(tokens) )
        o=t.build("compare_function")
    else:
        o=build_function_templates(tokens)
    
    return o

def build_function_templates(tokens,token_type=None,depth=0):
    t="eh"
    index=0
    spacer="   "
    padd=get_padd(depth,spacer)
    in_or=0
    #print tokens
    

    o=""
    
    
    if token_type=='char':
        if isinstance(tokens,str):
            token= tokens.replace("'","\\ \'")
            t=tpl("templates/templates.txt")
            t.add("or_compare","compare_value",token)
            o+=t.build("or_compare")
            return o
    else:
        if isinstance(tokens,str):
            token= tokens.replace("'","\\ \'")
            #print token
            if  len(token)>1 and ((token[0]=='{' and  token[-1]=='}'))  :
                token=token[1:-1]

                t=tpl("templates/templates.txt")
                t.add("compare_method","function_name",token)
                o+=t.build("compare_method")

            else:
                t=tpl("templates/templates.txt")
                t.add("compare","compare_value_length",str(len(token)))
                t.add("compare","compare_value",token)
                o+=t.build("compare")
            return o
    
            
    
    
    if isinstance(tokens,list):
        if token_type=='char':
            o=[]
            for token in tokens:
                o.append(build_function_templates(token,token_type,depth).strip())
            return " || \n".join(o)
        else:
            for token in tokens:
                o+=""+build_function_templates(token,token_type,depth)
            return o

    
    if isinstance(tokens,dict):
        token=tokens
        if token['type']=='one_or_more':
            t=tpl("templates/templates.txt")
            t.add("one_or_more","body",build_function_templates(token['data'],token['type'],depth))
            o+=t.build("one_or_more")
            return o

        if token['type']=='char':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/templates.txt")
            t.add("char","conditions",build_function_templates(token['data'],token['type'],depth))
            o+=t.build("char")
            return o
        
        if token['type']=='range':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/templates.txt")
            t.add("range","range_1",tokens['data'][0])
            t.add("range","range_2",tokens['data'][1])
            o+=t.build("range")
            return o

        if token['type']=='optional':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/templates.txt")
            t.add("optional","body",build_function_templates(token['data'],token['type'],depth+1))
            t.add("optional","token_uid",opt_uid)
            o+=t.build("optional")
            return o

        if token['type']=='group':
            t=tpl("templates/templates.txt")
            t.add("group","body",build_function_templates(token['data'],token['type'],depth+1))
            o+=t.build("group")
            return o

        if token['type']=='or':
            t=tpl("templates/templates.txt")
            t.add("or","body",build_function_templates(token['data'],token['type'],depth+1))
            o+=t.build("or")
            return o
    return ""
    



#[{ 'data': [{ 'data': '-', 'type': 'one_or_more'}], 'type': 'char'}]
#[ { 'data': { 'data': ['A', '-', 'Z', 'a', '-', 'z'], 'type': 'char'},
#    'type': 'one_or_more'}]
#[ { 'data': [ { 'data': [ '"',
#                          { 'data': { 'data': ['^', '"'], 'type': 'group'},
#                            'type': 'one_or_more'},
#                          '"'],
#                'type': 'group'},
#              { 'data': [ "'",
#                          { 'data': { 'data': ['^', "'"], 'type': 'group'},
#                            'type': 'one_or_more'},
#                          "'"],
#                'type': 'group'}],
#    'type': 'or'}]
#[{ 'data': { 'data': ['0', '-', '9'], 'type': 'char'}, 'type': 'one_or_more'}]
#['{sign}', '{unsigned_int}']
#[{ 'data': ['{unsigned_int}', '{signed_int}'], 'type': 'or'}]
#[{ 'data': ['E', 'e'], 'type': 'char'}, '{integer}']
#[ { 'data': [ '{integer}',
#              { 'data': ['{integer}', '.', '{unsigned_int}'],
#                'type': 'group'},
#              { 'data': ['.', '{unsigned_int}'], 'type': 'group'}],
#    'type': 'or'},
#  { 'data': '{exponent}', 'type': 'optional'}]
#


def build_match(file):
    t=tpl("templates/templates.txt")
    functions=[]
    with open(file,"r") as content:
        for line in content:
            key,data_pattern=line.split(":",1)
            functions.append({key:data_pattern})


    for function in functions:
        for key in function:
            o=build(key,function[key])
            print(o)

    index=0
    for function in functions:
        for key in function:
            if index==0:
                fragment="\n"+t.build("match_functions_first_var",{'function_name':key})
            else:
                fragment=t.build("match_functions_second_var",{'function_name':key})
            t.add("match_functions","body",fragment)
            index+=1
    
    t.add("match_functions","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    o=t.build("match_functions")
    #print o


## TODO sub variables "acos(X)"
## TODO RANGE A-Z
## TODO ' * UNTIL '


#build_match("tools/functions.def")
build_match("tools/templates/base.def")
