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

