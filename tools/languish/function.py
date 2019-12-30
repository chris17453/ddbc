import datetime
from pprint import pprint
from .tokenizer import group_expressions, gather_matches, build_expression_levels, recursive, get_var, uid
from .tpl import tpl

UUID=1

def build_DEFINES(name,pattern,depth=0):
    global UUID
    # load data / set variables
    tokens=build_expression_levels(pattern,0)
    # pprint(tokens,indent=2)
    # print " ---"
    
    tokens=group_expressions(tokens)
    #print({'name':name,'data':tokens})    
    return gather_matches(tokens)

def build_expressions(name,pattern,depth=0):
    global UUID
    tokens=build_expression_levels(pattern,0)
    tokens=group_expressions(tokens)
    # pprint(tokens,indent=2)
    return tokens


def build(name,pattern,depth=0):
    global UUID
    # load data / set variables
    tokens=build_expression_levels(pattern,0)
    # pprint(tokens,indent=2)
    # print " ---"
    
    tokens=group_expressions(tokens)
    
    list_of_match_functions=gather_matches(tokens)
    

    #pprint(tokens,indent=2)

    o="\n"
    t=tpl("templates/match_function.c")
    t.add("match_function","function_name",name)
    t.add("match_function","uid",UUID)
    t.add("match_function","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    t.add("match_function","body", build_function_templates(tokens,name=name) )

    if recursive(tokens,name)!=0:
        t.add("func_recursion","function_name",name)
        o2=t.build("func_recursion")
        t.add("match_function","func_recursion", o2 )
    else:
        t.add("match_function","func_recursion", "" )

    
    o=t.build("match_function")
    
    return o



def build_string(tokens,token_type=None,depth=0,name=None,order=None):
    o=""
    if token_type=='char':
        token= tokens.replace("'","\\\'")
        t=tpl("templates/or.c")

        if token==".":
            o+='1' 
        else:

            if token=="\s":
                token=" "
            if token=="\|":
                token="|"
            if token=="\(":
                token="("
            if token=="\)":
                token=")"
            if token=="\.":
                token="."
            if token=="\^":
                token="^"
            t.add("or_compare","compare_value",token)
            o+=t.build("or_compare")
        return o
    token= tokens.replace("'","\\\'")
    token= tokens.replace("\"","\\\"")
    if token_type=='or':
        t=tpl("templates/or.c")
        t.add("or_list_item1","body",o)
        o+=t.build("or_list_item1")
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
        o+=t.build(template_name)
        return o
    else:
        t=tpl("templates/compare.c")
        t.add("compare","order",order)
        t.add("compare","compare_value_length",str(len(token)))
        t.add("compare","compare_value",token)
        o+=t.build("compare")
        return o
    
    return "unknown STRING"

def list_item(token,token_type=None,depth=0,name=None,order=None,recurse=None):
    global UUID
    o=""
    UUID+=1
    if recurse==None:
        if order==0:
            t=tpl("templates/or.c")
            t.add("or_list_item1","uid",UUID)
            t.add("or_list_item1","order",order)
            t.add("or_list_item1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("or_list_item1")
        else:
            t=tpl("templates/or.c")
            t.add("or_list_item+1","uid",UUID)
            t.add("or_list_item+1","order",order)
            t.add("or_list_item+1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("or_list_item+1")
    else:
        if  order==0:
            t=tpl("templates/or.c")
            t.add("recursive_self","uid",UUID)
            t.add("recursive_self","order",order)
            t.add("recursive_self","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("recursive_self")
        else:
            t=tpl("templates/or.c")
            t.add("recursive_self+1","uid",UUID)
            t.add("recursive_self+1","function_name",name)
            t.add("recursive_self+1","order",order)
            t.add("recursive_self+1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("recursive_self+1")    
    return o            

def build_list(tokens,token_type=None,depth=0,name=None,order=None):
    global UUID
    name2=name
    o=""
    if name!=None:
        if name[0]=='{':
            name2=name[1:-1]

    if token_type=='char':
        o2=[]
        build_next=None
        for token in tokens:
            if build_next:
                build_next=None
                token= token.replace("'","\\\'")
                if token=="\s":
                    token=" "
                if token=="\|":
                    token="|"
                if token=="\(":
                    token="("
                if token=="\)":
                    token=")"
                if token=="\.":
                    token="."
                if token=="\^":
                    token="^"
                t=tpl("templates/or.c")
                t.add("not_compare","compare_value",token)
                o2.append(t.build("not_compare"))
        
            if token=="^":
                build_next=True
                continue

        o2=" && ".join(o2)


        o=[]
        skip_next=None
        for token in tokens:
            if skip_next:
                skip_next=None
                continue
            if token=="^":
                skip_next=True
                continue
            o.append(build_function_templates(token,token_type,depth,name=name).strip())
       
        if len(o2)>0 and len(o)>0:
            return "({0} && ({1})) ". format(o2," || ".join(o))
        if len(o2)>0:
            return o2
        if len(o)>0:
            return " || ".join(o)
    elif token_type=='or':
        index=0
        tokens2=[]
        
        for token in tokens:
            o+=list_item(token,token_type=None,depth=0,name=name,order=index,recurse=None)
            index+=1
        return o
    else:

        index=0
        if tokens==None:
            return ""
        for token in tokens:
            if isinstance(token,str):
                compare_name=get_var(token)
                o+="//"+str(compare_name)+" "+ " " +str(name)+ " " + str(name2) +"\n"
                o+="//"+str(recursive(tokens,name2))+"\n"
                if compare_name==name and  recursive(tokens,name2)>0:
                    o+=list_item(token,token_type=None,depth=0,name=name,order=index,recurse=True)
                else:
                    o+=build_function_templates(token,token_type,depth,name=name,order=index)
            else:
                o+=build_function_templates(token,token_type,depth,name=name,order=index)
            index+=1
        return o

    return "Unknown LIST"

def build_dict(tokens,token_type=None,depth=0,name=None,order=None):
    global UUID
    o=""
    token=tokens
    UUID+=1

    if token['type']=='zero_or_more':
        t=tpl("templates/zero_or_more.c")
        t.add("zero_or_more","uid",UUID)
        t.add("zero_or_more","body",build_function_templates(token['data'],token['type'],depth,name=name))
        o+=t.build("zero_or_more")
        return o

    if token['type']=='one_or_more':
        t=tpl("templates/one_or_more.c")
        t.add("one_or_more","uid",UUID)
        t.add("one_or_more","body",build_function_templates(token['data'],token['type'],depth,name=name))
        o+=t.build("one_or_more")
        return o

    if token['type']=='char':
        opt_uid="opt_temp_{0}".format(uid())
        t=tpl("templates/char.c")
        t.add("char","uid",UUID)
        t.add("char","conditions",build_function_templates(token['data'],token['type'],depth,name=name))
        o+=t.build("char")
        return o
    
    if token['type']=='range':
        opt_uid="opt_temp_{0}".format(uid())
        t=tpl("templates/range.c")
        t.add("range","uid",UUID)
        t.add("range","range_1",tokens['data'][0])
        t.add("range","range_2",tokens['data'][1])
        o+=t.build("range")
        return o

    if token['type']=='optional':
        opt_uid="opt_temp_{0}".format(uid())
        t=tpl("templates/optional.c")
        t.add("optional","uid",UUID)
        t.add("optional","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
        t.add("optional","token_uid",opt_uid)
        o+=t.build("optional")
        return o

    if token['type']=='group':
        t=tpl("templates/group.c")
        t.add("group","uid",UUID)
        t.add("group","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
        o+=t.build("group")
        return o

    if token['type']=='or':
        t=tpl("templates/or.c")
        t.add("or","uid",UUID)
        t.add("or","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
        o+=t.build("or")
        return o

    if token['type']=='not':
        t=tpl("templates/not.c")
        t.add("not","uid",UUID)
        t.add("not","body",build_function_templates(token['data'],token['type'],depth+1,name=name))
        o+=t.build("not")
        return o
    return "Unknown DICT:" +str(tokens)

def build_function_templates(tokens,token_type=None,depth=0,name=None,order=None):
    if isinstance(tokens,str):
        return build_string(tokens,token_type,depth,name,order)
    elif isinstance(tokens,list):
        return build_list(tokens,token_type,depth,name,order)
    elif isinstance(tokens,dict):
        return build_dict(tokens,token_type,depth,name,order)
    
    return "UNKNOWN TEMPLATE"
    
