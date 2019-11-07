import datetime
from .tokenizer import group_expressions, gather_matches, build_expression_levels, recursive, get_var, uid
from .tpl import tpl

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



def build_string(tokens,token_type=None,depth=0,name=None,order=None):
    o="//string\n"
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
    o="//list item switch\n"
    if recurse==None:
        if order==0:
            t=tpl("templates/or.c")
            t.add("or_list_item1","order",order)
            t.add("or_list_item1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("or_list_item1")
        else:
            t=tpl("templates/or.c")
            t.add("or_list_item+1","order",order)
            t.add("or_list_item+1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("or_list_item+1")
    else:
        if  order==0:
            t=tpl("templates/or.c")
            t.add("recursive_self","order",order)
            t.add("recursive_self","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("recursive_self")
        else:
            t=tpl("templates/or.c")
            t.add("recursive_self+1","order",order)
            t.add("recursive_self+1","body",build_function_templates(token,token_type,depth,name=name,order=order))
            o+=t.build("recursive_self+1")    
    return o            

def build_list(tokens,token_type=None,depth=0,name=None,order=None):
    name2=name
    o="// list\n"
    if name!=None:
        if name[0]=='{':
            name2=name[1:-1]

    if token_type=='char':
        o=[]
        for token in tokens:
            o.append(build_function_templates(token,token_type,depth,name=name).strip())
        return " || \n".join(o)
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

    return "Unknowen LIST"

def build_dict(tokens,token_type=None,depth=0,name=None,order=None):
    o="// dict\n"
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
    return "Unknown DICT"

def build_function_templates(tokens,token_type=None,depth=0,name=None,order=None):
    if isinstance(tokens,str):
        return build_string(tokens,token_type,depth,name,order)
    elif isinstance(tokens,list):
        return build_list(tokens,token_type,depth,name,order)
    elif isinstance(tokens,dict):
        return build_dict(tokens,token_type,depth,name,order)
    
    return "UNKNOWN TEMPLATE"
    
