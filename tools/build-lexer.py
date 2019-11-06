import argparse
import os
import sys
import datetime
from pprint import pprint
import re
from tpl import tpl



def clean_pattern(pattern):
    pattern=pattern.strip()
    found=None
    new_pattern=""
    dont_break_quoted_blocks=None
    in_character_block=None
    escaped=None
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



def build(name,pattern,depth=0):
    # load data / set variables
    tokens=build_expression_levels(pattern,0)
    # pprint(tokens,indent=2)
    # print " ---"
    tokens=group_expressions(tokens)
    list_of_match_functions=gather_matches(tokens)
    #pprint(tokens,indent=2)
    o="\n"
    if depth==0:
        t=tpl("templates/match_function.c")
        t.add("match_function","function_name",name)
        if recursive(tokens,name)==0:
            t.add("match_function","recurse",0)
        else:
            t.add("match_function","recurse",1)
        t.add("match_function","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
        t.add("match_function","body", build_function_templates(tokens,name=name) )
        o=t.build("match_function")
    
    return o




def build_function_templates(tokens,token_type=None,depth=0,name=None,order=None):
    t="eh"
    index=0
    spacer="   "
    padd=get_padd(depth,spacer)
    in_or=0
    name2=name
    if name!=None:
        if name[0]=='{':
            name2=name[1:-1]
        
    o=""

    if isinstance(tokens,str):
        if token_type=='char':
            token= tokens.replace("'","\\\'")
            t=tpl("templates/or.c")
            if token=="\s":
                token=" "
            if token=="\|":
                token="|"
            if token=="\(":
                token="("
            if token=="\)":
                token=")"
            t.add("or_compare","compare_value",token)
            o=t.build("or_compare")
            return o
        token= tokens.replace("'","\\\'")
        token= tokens.replace("\"","\\\"")
        if token_type=='or':
            t=tpl("templates/or.c")
            t.add("or_list_item1","body",o)
            o=t.build("or_list_item1")
            return o

        #print token
        if  len(token)>1 and ((token[0]=='{' and  token[-1]=='}')):
            token=token[1:-1]
            t=tpl("templates/compare.c")
            if token==name:
                template_name="compare_method_self"
            else:
                template_name="compare_method"
            t.add(template_name,"order",order)
            t.add(template_name,"function_name",token)
            o=t.build(template_name)
            return o
        else:
            t=tpl("templates/compare.c")
            t.add("compare","order",order)
            t.add("compare","compare_value_length",str(len(token)))
            t.add("compare","compare_value",token)
            o=t.build("compare")
            return o

    if isinstance(tokens,list):
        if token_type=='char':
            o=[]
            for token in tokens:
                o.append(build_function_templates(token,token_type,depth,name=name).strip())
            return " || \n".join(o)
        elif token_type=='or':
            index=0
            tokens2=[]
         
            for token in tokens:
                if index==0:
                    t=tpl("templates/or.c")
                    t.add("or_list_item1","order",index)
                    t.add("or_list_item1","body",build_function_templates(token,token_type,depth,name=name,order=index))
                    o+=t.build("or_list_item1")
                else:
                    t=tpl("templates/or.c")
                    t.add("or_list_item+1","order",index)
                    t.add("or_list_item+1","body",build_function_templates(token,token_type,depth,name=name,order=index))
                    o+=t.build("or_list_item+1")
                index+=1

            return o
        else:
            index=0
            if tokens==None:
                return ""
            for token in tokens:
                compare_name=get_var(token)
               #print token,name,index
                if compare_name!=None and compare_name==name2 and  recursive(tokens,name2)==1:
                    #print token,name,index
                    if  index==0:
                        t=tpl("templates/or.c")
                        t.add("recursive_self","order",index)
                        t.add("recursive_self","body",build_function_templates(token,token_type,depth,name=name,order=index))
                        o+=t.build("recursive_self")
                    else:
                        t=tpl("templates/or.c")
                        t.add("recursive_self+1","order",index)
                        t.add("recursive_self+1","body",build_function_templates(token,token_type,depth,name=name,order=index))
                        o+=t.build("recursive_self+1")
                else:
                    o+="//---?\n"+build_function_templates(token,token_type,depth,name=name,order=index)
                index+=1
            return o

    
    if isinstance(tokens,dict):
        token=tokens
        if token['type']=='one_or_more':
            t=tpl("templates/one_or_more.c")
            t.add("one_or_more","body",build_function_templates(token['data'],token['type'],depth,name=name))
            o+=t.build("one_or_more")
            return o

        if token['type']=='char':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/char.c")
            t.add("char","conditions",build_function_templates(token['data'],token['type'],depth,name=name))
            o+=t.build("char")
            return o
        
        if token['type']=='range':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/range.c")
            t.add("range","range_1",tokens['data'][0])
            t.add("range","range_2",tokens['data'][1])
            o+=t.build("range")
            return o

        if token['type']=='optional':
            opt_uid="opt_temp_{0}".format(uid())
            t=tpl("templates/optional.c")
            t.add("optional","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
            t.add("optional","token_uid",opt_uid)
            o+=t.build("optional")
            return o

        if token['type']=='group':
            t=tpl("templates/group.c")
            t.add("group","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
            o+=t.build("group")
            return o

        if token['type']=='or':
            t=tpl("templates/or.c")
            t.add("or","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
            o+=t.build("or")
            return o

        if token['type']=='not':
            t=tpl("templates/not.c")
            t.add("not","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
            o+=t.build("not")
            return o

    return ""
    
def load_definitions(file):
    functions=[]
    data_pattern=None

    with open(file,"r") as content:
        for line in content:

            data_line=line.strip()
            if data_line == '---': 
                break
     
            if data_line.isspace() or data_line==None or len(data_line)==0:
                continue
            if data_line[0]=='#':
                continue
            if ':' in data_line:
                if data_pattern:
                    functions.append({key:data_pattern})
                key,data_pattern=data_line.split(":",1)
                data_pattern=data_pattern.strip()+" "
                if data_pattern[0]=='|':
                    if data_pattern[1:].isspace()==False:
                        data_pattern="| ("+data_pattern[1:] + ") "
                    else: 
                        data_pattern=""
                else:
                    if data_pattern.isspace()==False:
                        data_pattern="( "+data_pattern + " )"
                    else: 
                        data_pattern=""


            else:
                data_line=data_line.strip()
                if data_line[0]=='|':
                    if data_line.isspace()==False:
                        data_line="| ( "+data_line[1:] + " ) "
                    else:
                        data_line=""
                else:
                    if data_line.isspace()==False:
                        data_line="( "+data_line + " ) "
                    else:
                        data_line=""

                data_pattern += data_line

    if data_pattern:
        functions.append({key:data_pattern})
    
    #print functions
    return functions

def build_match(file):
    o=""
    t=tpl("templates/match_functions.c")
    t.add("headers","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    o+=t.build("headers")
    o+=t.build("stricmp")
    
    functions=load_definitions(file)
    

    for function in functions:
        for key in function:
            o+=build(key,function[key])

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
    o+=t.build("match_functions")
    print o

def build_headers(file):
    functions=load_definitions(file)
    
    o=""
    
    t=tpl("templates/headers.c")
    o+=t.build("node_t")
    
    for function in functions:
        for key in function:
            t=tpl("templates/headers.c")
            t.add("signature","body",key)
            o+=t.build("signature")

    t=tpl("templates/headers.c")
    t.add("signature","body",key)
    o+=t.build("signature2")

    print o


if __name__=='__main__':
    parser = argparse.ArgumentParser("expressonator", usage='%(prog)s [options]', description="""create a c file for expression consumption""", epilog="")
    parser.add_argument('-i', help='return headers', action='store_true')
    args = parser.parse_args()
    template="tools/templates/base.def"
    if args.i:
        build_headers(template)
    else:
        build_match(template)
