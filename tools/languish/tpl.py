import os
from pprint import pprint
class tpl:
    def __init__(self,file):
        self.templates={}
        self.dir=os.path.dirname(os.path.realpath(__file__))
        self.open(os.path.join(self.dir,file))
        
        pass
    
    def add(self,template,var,data):
        if var in self.templates[template]['vars']:
            #print "adding more "+var
            self.templates[template]['vars'][var]+=data
        else:
            #print "adding "+var
            self.templates[template]['vars'][var]=data
    
    def open(self,file):
        # defaults
        func="UNK"
        template={'name':func,'vars':{},'pad':0,'content':''}
        self.templates[func]=template
        
        with open(file) as content:
            for line in content:
                clean_line=line.strip()
                clean_line=''.join([i if ord(i) < 128 else ' ' for i in clean_line])

                # skip empty lines
                if len(clean_line)<1:
                    continue
                # skip comments
                #if clean_line[0]=='#': 
                #    continue
                
                if clean_line[-1]==":":
                    func=line[0:-2]
                    template={'name':func,'vars':{},'pad':0,'content':''}
                    self.templates[func]=template
                    continue
                template['content']+=line.strip()+"\n"

    def build(self,name=None,vars=None):
        #pprint(self.templates)
        template=None
        if name==None:
            template=self.templates[0]
        else:
            template=self.templates[name]
        if vars==None:
            #print "NO vars"
            vars=template['vars']

        #print template

        output=template['content']
        #print vars
        for var in vars:
            #print "found "+var
            try:
                #print("\n// VARS: {0}-> {1} \n".format(var,vars[var] ) )
                output=output.replace('{{{0}}}'.format(var),str(vars[var]))
            except Exception as ex :
                print("Error with {0} {1}".format(var,ex))
        
        lines=output.split("\n")
        depth=0
        spacing="   "
        o=""
        fdepth=0
        for line in lines:
            line_depth=0
            function_depth=0
            for i in line:
                if i=='}': line_depth-=1
                if i=='{': line_depth+=1
                if i==')': function_depth-=1
                if i=='(': function_depth+=1

            if line_depth<0:
                depth+=line_depth
            for i in range(depth):
                o+=spacing
            if fdepth>0:
                o+="  "
            for i in range(fdepth):
                o+=" "
            o+=line.strip()+"\n"
            if line_depth>0:
                depth+=line_depth
            if function_depth>0:
                fdepth+=function_depth
            if function_depth<0:
                fdepth+=function_depth
            
        # no double enters
        o=o.replace("\n\n","\n")
        self.output=o


        return o

    def dump(self):
        print(self.output)
        pass
