compare_func:
void compare_string(node_t *n,const char *  data,int length,const char * name){
    if( n_OK(n)==1 && stricmp(n,data)==0) {
        increment_n(n,length);
        n_token(n,name);
    }
    else n->OK=0; 
}

compare:
 // order {order}
 compare_string(n,(const char * ) "{compare_value}",{compare_value_length},name);


compare_method:
    //external -> {order}
    match_{function_name}(n,name,depth+1);

compare_method_self:
    //recursion -> {order}
    if(strcmp(name,last_method)==0) {
        match_{function_name}(n,name,depth+1); 
    }
