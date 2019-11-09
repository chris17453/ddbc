import datetime;
from .tpl import tpl
from .definitions import load_definitions
from .function import build

def build_functions(template_dir):
    o=""
    t=tpl("templates/headers.c")
    t.add("headers","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    o+=t.build("headers")
    
    o+=t.build("stricmp")

    t=tpl("templates/debug.c")
    o+=t.build("debug")
        
    t=tpl("templates/match_functions.c")

    functions=load_definitions(template_dir)
    
    #print functions
    #exit(0)
    for function in functions:
        for key in function:
            o+=build(key,function[key])

    index=0
    
    for function in functions:

        for key in function:
            if key!='queries' and key!='catch_all':
                continue
            
            if index==0:
                fragment="\n"+t.build("match_functions_first_var",{'function_name':key})
            else:
                fragment=t.build("match_functions_second_var",{'function_name':key})
            t.add("match_functions","body",fragment)
            index+=1
    
    t.add("match_functions","date_time",str(datetime.datetime.now().strftime("%Y-%m-%d")  ) )
    o+=t.build("match_functions")
    print o


