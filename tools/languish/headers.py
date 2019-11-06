from .tpl import tpl
from .definitions import load_definitions

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

