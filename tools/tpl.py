import os

class tpl:
    templates={}

    def __init__(self,file):
        self.dir=os.path.dirname(os.path.realpath(__file__))
        self.open(os.path.join(self.dir,file))
        
        pass
    
    def add_var(self,template,var,padding=0):
        self.templates[template]['variable'][var]=""
        self.templates[template]['padding'][var]=padding
        
    def add(self,template,var,data):
        padding=""
        if var in self.templates[template]['padding']:
            for i in range(self.templates[template]['padding'][var]):
                padding+=' '
        
        self.templates[template]['variable'][var]+=padding+data+"\n"
    
    def open(self,file):
        # defaults
        func="UNK"
        template={'name':func,'vars'={},'pad':0,'content':''}
        self.templates[func]=template
        
        with open(file) as content:
            for line in content:
                if line[0]=='#': 
                    continue
                if line.strip()[-1]==":":
                    func=line.split(":",1)
                    template={'name':func,'vars'={},'pad':0,'content':''}
                    self.templates[func]=template
                template['content']+=line.strip()


    def build(self,name=None):
        if name==None:
            template=self.templates[0]
        else:
            template=self.templates[name]

        output=template['content']
        for var in self.tamplate['variable']:
            output=output.replace('{{{0}}}'.format(var),template['variable'][var])
        self.output=output
        return output

    def dump(self):
        print(self.output)
        pass
