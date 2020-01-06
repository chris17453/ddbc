import datetime;
from pprint import pprint
from .tpl import tpl
from .definitions import load_definitions
from .function import build, build_DEFINES, build_expressions
USE_HUMAN_INDEXES=True

def build_defines(template_dir):
    res=get_matches(template_dir)
    matches=res['matches']
    functions=res['functions']
    
    #pprint(functions,indent=2)
    print("#include <stdint.h>")

    for key in matches:
        if key[0]=='{' and key[-1]=='}':
            print('#define EXP_{0:25}   0x{1:03X}'.format(key[1:-1],matches[key]))

    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            safe_key=get_safe_name(key)
            safe_value=matches[key]
            print('#define STR_{0:25}   0x{1:03X}'.format(safe_key,safe_value))

    print("\nconst char *debug_str [{0}];\n".format(len(matches)))
    print("\n\nuint16_t *pattern[{0}];".format(len(matches)))

            
def functobytecode(func,matches):
    o=[]
    if isinstance(func,list):
        for item in func:
            o+=functobytecode(item,matches)
    elif isinstance(func,dict):
        func_t=func['type'].upper()


        func_index=0
        if   func_t=="CHAR"         : 
            func_t='TYP_GRP'
            func_index=0xFF02
        elif func_t=="GROUP"        : 
            func_t='TYP_GRP'
            func_index=0xFF02
        elif func_t=="NEGATE"       : 
            func_t='TYP_NEG'
            func_index=0xFF03
        elif func_t=="NOT"          : 
            func_t='TYP_NOT'
            func_index=0xFF04
        elif func_t=="ONE_OR_MORE"  : 
            func_t='TYP_OOM'
            func_index=0xFF05
        elif func_t=="OPTIONAL"     : 
            func_t='TYP_OPT'
            func_index=0xFF06
        elif func_t=="OR"           : 
            func_t='TYP_OR'
            func_index=0xFF07
        elif func_t=="RANGE"        : 
            func_t='TYP_RNG'
            func_index=0xFF08
        elif func_t=="STR"          : 
            func_t='TYP_GRP'
            func_index=0xFF02
        elif func_t=="ZERO_OR_MORE" : 
            func_t='TYP_ZOM'
            func_index=0xFF0A
        elif func_t=="EXP" : 
            func_t='TYP_EXP'
            func_index=0xFF0B
        else:
            print ("---"+func_t+"---")       


        if len(func['data'])==1 and func_t=="TYP_GRP":
            dont_parse=True;
        else:
            dont_parse=None
        #dont_parse=None
        if dont_parse==None:
            if USE_HUMAN_INDEXES==None:
                o.append("0x{0:03X}".format(func_index ) )
                if isinstance(func['data'],dict):
                    o.append("0x{0:03X}".format(1) )    
                else:
                    o.append("0x{0:03X}".format(len(func['data']) ) )
            else:
                o.append("{0}".format(func_t ) )
                if len(func['data'])==0:
                    print(func);
                if isinstance(func['data'],dict):
                    o.append("0x{0:03X}".format(1) )    
                else:
                    o.append("0x{0:03X}".format(len(func['data']) ) )

      
        o+=functobytecode(func['data'],matches)
    else:
        safe_key=get_safe_name(func)
        if '^' in safe_key:
            print("{0},{1}".format(safe_key,func) )
        if safe_key in matches:
            num=matches[safe_key]
        else:
            num=0
            print ("++++"+safe_key+'+++')

        if USE_HUMAN_INDEXES==None:
            o.append("0x{0:03X}".format(num ) )
        else:
            if func[0]=='{' and func[-1]=='}':
                o.append("EXP_{0}".format(safe_key[1:-1] ) )
            else:
                o.append("STR_{0}".format(safe_key ) )
    
    return o


def get_safe_name(key):
    return get_safe(key,"NAME")

def get_safe_value(key):
    return get_safe(key,"VALUE")

def get_safe(key,mode="NAME"):
    
    is_exp=None
    if key[0]=='{' and key[-1]=='}':
        key=key[1:-1]
        is_exp=True

    tokens=[            
        { 'key' : "'" ,   'value' : "'" ,  'safe_key' : "SINGLE_QUOTE",},
        { 'key' : '"' ,   'value' : '"' ,  'safe_key' : "DOUBLE_QUOTE",},
        { 'key' : '_' ,   'value' : '_' ,  'safe_key' : "UNDERSCORE",},
        { 'key' : '.' ,   'value' : '.' ,  'safe_key' : "PERIOD",},
        { 'key' : '&' ,   'value' : '&' ,  'safe_key' : "LOGICAL_AND",},
        { 'key' : '=' ,   'value' : '=' ,  'safe_key' : "EQUALS",},
        { 'key' : ';' ,   'value' : ';' ,  'safe_key' : "SEMICOLON",},
        { 'key' : ',' ,   'value' : ',' ,  'safe_key' : "COMMA",},
        { 'key' : '+' ,   'value' : '+' ,  'safe_key' : "PLUS",},
        { 'key' : '-' ,   'value' : '-' ,  'safe_key' : "MINUS",},
        { 'key' : '<' ,   'value' : '<' ,  'safe_key' : "LT",},
        { 'key' : '>' ,   'value' : '>' ,  'safe_key' : "GT",},
        { 'key' : '*' ,   'value' : '*' ,  'safe_key' : "TIMES",},
        { 'key' : '/' ,   'value' : '/' ,  'safe_key' : "DIVIDE",},
        { 'key' : '%' ,   'value' : '%' ,  'safe_key' : "MODULUS",},
        { 'key' : '~' ,   'value' : '~' ,  'safe_key' : "TILDE",},
        { 'key' : ':' ,   'value' : ':' ,  'safe_key' : "COLON",},
        { 'key' : '{' ,   'value' : '{' ,  'safe_key' : "LEFT_BRACKET",},
        { 'key' : '}' ,   'value' : '}' ,  'safe_key' : "RIGHT_BRACKET",},
        { 'key' : '!' ,   'value' : '!' ,  'safe_key' : "NEGATE",},
        { 'key' : '$' ,   'value' : '$' ,  'safe_key' : "DOLLAR_SIGN",},
        { 'key' : '#' ,   'value' : '#' ,  'safe_key' : "POUND_SIGN",},
        { 'key' : '@' ,   'value' : '@' ,  'safe_key' : "AT_SIGN",},
        { 'key' : '\^' ,  'value' : '^' ,  'safe_key' : "NOT",},
        { 'key' : "\n",   'value' : "\n",  'safe_key' : "NEW_LINE",},
        { 'key' : "\r",   'value' : "\r",  'safe_key' : "LINE_RETURN",},
        { 'key' : "\t",   'value' : "\t",  'safe_key' : "TAB",},
        { 'key' : " ",    'value' : " ",   'safe_key' : "SPACE",},
        { 'key' : '(',    'value' : '(',   'safe_key' : "LEFT_PAREN",},
        { 'key' : '^',    'value' : '^',   'safe_key' : "NOT",},
        { 'key' : ')',    'value' : ')',   'safe_key' : "RIGHT_PAREN",},
        { 'key' : '|',    'value' : '|',   'safe_key' : "LOGICAL_OR",},
        { 'key' : '&&',   'value' : '&&',  'safe_key' : "SHORT_CIRCUIT_AND",},
        { 'key' : '<=>',  'value' : '<=>', 'safe_key' : "NULL_EQUAL",},
        ]
    if mode=="NAME":
        for token in tokens:
            if token['key']==key:
                if is_exp:
                    return "{{{0}}}".format(token['safe_key'])
                return token['safe_key']
    if mode=="SAFE_KEY":
        for token in tokens:
            if token['safe_key']==key:
                if is_exp:
                    return "{{{0}}}".format(token['key'])
                return token['key']
    if mode=="VALUE":
        for token in tokens:
            if token['safe_key']==key:
                if is_exp:
                    return "{{{0}}}".format(token['value'])
                return token['value']
    
    if is_exp:
        return "{{{0}}}".format(key.upper())
    return key.upper()


def get_matches(template_dir):
    functions=load_definitions(template_dir)
    matches={}
    for function in functions:
        for key in function:
            new_matches=build_DEFINES(key,function[key])
            if isinstance(new_matches,str):
                new_matches=[new_matches]
            matches["{{{0}}}".format(get_safe_name(key)) ]=1
            func=build_expressions(key,function[key])
            for key2 in new_matches:
                matches[get_safe_name(key2)]=1
            
    index=0;
    for key in matches:
        if key[0]=='{' and key[-1]=='}':
            matches[key]=index
            index+=1

    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            matches[key]=index
            index+=1
    return {'functions':functions,'matches':matches}


def build_engine(template_dir):
    o=""
    t=tpl("templates/headers.c")
    t.add("engine_headers","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    o+=t.build("engine_headers")
    
    res=get_matches(template_dir)
    matches=res['matches']
    functions=res['functions']
    
    #print_defines(matches)
    #pprint(matches,indent=2)

    # expression matches
    for key in matches:
        if key[0]=='{' and key[-1]=='}':
            found=None

            for function in functions:
                for key2 in function:
                    #print ("//{0} {1} ",key,get_safe_name("{{{0}}}".format(key2)) )
                    if key=="{{{0}}}".format(get_safe_name(key2)):
                        found=True
                        func=build_expressions(key2,function[key2])
                        #pprint(func,indent=2)
                        byte_arr=functobytecode(func,matches)
                        byte_str=",".join(byte_arr)
                        o+="\nuint16_t PATTERN_0x{0:03X}[0x{1:03X}] = {{ 0x{4:03X}, {2} }};    //{3}".format(matches[key],len(byte_arr)+1,byte_str,key, len(byte_arr))
                        break;
            if found==None:
                print ("// ERR{0}".format(key))
    
    # string matches
    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            safe_key=key
            #safe_key=get_safe_value(key)
            safe_value=get_safe_value(key)
            #safe_key=safe_key.replace("\\","")
            
            chars=[]
            for c in safe_value:
                chars.append("0x{0:02X}".format(ord(c)) )
            

            if len(safe_value)>1:
                #safe_key=safe_key.replace("\"","\\\"")
                
                
                o+="\nuint16_t PATTERN_0x{0:03X}[0x{1:03X}]={{ 0x{5:03X}, TYP_STR, 0x{3:03X}, {2} }};    //{4}".format(matches[key],len(chars)+3,",".join(chars) ,len(chars),safe_key,len(chars)+2)
            else:
                #//safe_key=safe_key.replace("\'","\\\'")
                #safe_key=safe_key.replace("\n","\\n")
                o+="\nuint16_t PATTERN_0x{0:03X}[0x{1:03X}]={{ 0x{5:03X}, TYP_CHR, 0x{3:03X}, {2} }};    //{4}".format(matches[key],len(chars)+3,",".join(chars),len(chars),safe_key ,len(chars)+2)


    # groupings array
    patterns=[]
    for i in range(0,len(matches)):
        patterns.append("PATTERN_0x{0:03X}".format(i))
    o+= "\n\n// ********************"
    o+= "\n\nuint16_t *pattern[{0}]={{ {1} }};".format(len(matches),",".join(patterns) )


    debug_str=[]
    for key in matches:
        if key[0]=='{' and key[-1]=='}':
            debug_str.append('"{0}"'.format(key[1:-1]))

    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            safe_key=get_safe_name(key)
            debug_str.append('"{0}"'.format(safe_key))

    o+="\nconst char *debug_str [{0}] ={{ {1} }};\n\n".format(len(debug_str),",".join(debug_str))

    print (o)


