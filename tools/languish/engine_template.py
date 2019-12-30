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
            print('#define EXP_{0:25}   0x{1:04X}'.format(key[1:-1],matches[key]))

    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            safe_key=get_safe_name(key)
            print('#define STR_{0:25}   0x{1:04X}'.format(safe_key,matches[key]))

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
            func_t='TYP_CHR'
            func_index=0xFF01
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
            func_t='TYP_STR'
            func_index=0xFF09
        elif func_t=="ZERO_OR_MORE" : 
            func_t='TYP_ZOM'
            func_index=0xFF0A




        else:
            print ("---"+func_t+"---")       


        if USE_HUMAN_INDEXES==None:
            o.append("0x{0:04X}".format(func_index ) )
            if isinstance(func['data'],dict):
                o.append("0x{0:04X}".format(1) )    
            else:
                o.append("0x{0:04X}".format(len(func['data']) ) )
        else:
            o.append("{0}".format(func_t ) )
            if isinstance(func['data'],dict):
                o.append("0x{0:04X}".format(1) )    
            else:
                o.append("0x{0:04X}".format(len(func['data']) ) )

        
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
            o.append("0x{0:04X}".format(num ) )
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
        { 'key' : "'" ,   'safe_key' : "SINGLE_QUOTE",},
        { 'key' : '"' ,   'safe_key' : "DOUBLE_QUOTE",},
        { 'key' : '_' ,   'safe_key' : "UNDERSCORE",},
        { 'key' : '.' ,   'safe_key' : "PERIOD",},
        { 'key' : '&' ,   'safe_key' : "LOGICAL_AND",},
        { 'key' : '=' ,   'safe_key' : "EQUALS",},
        { 'key' : ';' ,   'safe_key' : "SEMICOLON",},
        { 'key' : ',' ,   'safe_key' : "COMMA",},
        { 'key' : '+' ,   'safe_key' : "PLUS",},
        { 'key' : '-' ,   'safe_key' : "MINUS",},
        { 'key' : '<' ,   'safe_key' : "LT",},
        { 'key' : '>' ,   'safe_key' : "GT",},
        { 'key' : '*' ,   'safe_key' : "TIMES",},
        { 'key' : '/' ,   'safe_key' : "DIVIDE",},
        { 'key' : '%' ,   'safe_key' : "MODULUS",},
        { 'key' : '~' ,   'safe_key' : "TILDE",},
        { 'key' : ':' ,   'safe_key' : "COLON",},
        { 'key' : '{' ,   'safe_key' : "LEFT_BRACKET",},
        { 'key' : '}' ,   'safe_key' : "RIGHT_BRACKET",},
        { 'key' : '!' ,   'safe_key' : "NEGATE",},
        { 'key' : '$' ,   'safe_key' : "DOLLAR_SIGN",},
        { 'key' : '#' ,   'safe_key' : "POUND_SIGN",},
        { 'key' : '@' ,   'safe_key' : "AT_SIGN",},
        { 'key' : '^' ,   'safe_key' : "NOT",},

        { 'key' : "\\n",   'safe_key' : "NEW_LINE",},
        { 'key' : "\\r",   'safe_key' : "LINE_RETURN",},
        { 'key' : "\\t",   'safe_key' : "TAB",},
        { 'key' : "\s",   'safe_key' : "SPACE",},
        { 'key' : '\(',   'safe_key' : "LEFT_PAREN",},
        { 'key' : '\^',   'safe_key' : "NOT",},
        { 'key' : '\)',   'safe_key' : "RIGHT_PAREN",},
        { 'key' : '\|',   'safe_key' : "LOGICAL_OR",},
        { 'key' : '&&',   'safe_key' : "SHORT_CIRCUIT_AND",},
        { 'key' : '<=>',  'safe_key' : "NULL_EQUAL",},
        ]
    if mode=="NAME":
        for token in tokens:
            if token['key']==key:
                if is_exp:
                    return "{{{0}}}".format(token['safe_key'])
                return token['safe_key']
    else:
        for token in tokens:
            if token['safe_key']==key:
                if is_exp:
                    return "{{{0}}}".format(token['key'])
                return token['key']
    
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
                        o+="\nuint16_t PATTERN_0x{0:04X}[0x{1:04X}] = {{ 0x{4:04X}, {2} }};    //{3}".format(matches[key],len(byte_arr)+1,byte_str,key, len(byte_arr))
                        break;
            if found==None:
                print ("// ERR{0}".format(key))
    

    for key in matches:
        if key[0]!='{' or key[-1]!='}':
            safe_key=key
            safe_key=safe_key.replace("\\","")
            
            chars=[]
            for c in safe_key:
                chars.append("0x{0:2}".format(ord(c)) )
            

            if len(safe_key)>1:
                safe_key=safe_key.replace("\"","\\\"")
                
                
                o+="\nuint16_t PATTERN_0x{0:04X}[0x{1:04X}]={{ 0x{5:04X}, TYP_STR, 0x{3:04X}, {2} }};    //{4}".format(matches[key],len(chars)+3,",".join(chars) ,len(chars),safe_key,len(chars)+2)
            else:
                safe_key=safe_key.replace("\'","\\\'")
                safe_key=safe_key.replace("\n","\\n")
                o+="\nuint16_t PATTERN_0x{0:04X}[0x{1:04X}]={{ 0x{5:04X}, TYP_CHR, 0x{3:04X}, {2} }};    //{4}".format(matches[key],len(chars)+3,",".join(chars),len(chars),safe_key ,len(chars)+2)


    
    patterns=[]
    for i in range(0,len(matches)):
        patterns.append("PATTERN_0x{0:04X}".format(i))
    o+= "\n\n// ********************"
    o+= "\n\nuint16_t *pattern[{0}]={{ {1} }};".format(len(matches),",".join(patterns) )

    print (o)


