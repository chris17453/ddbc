compare:
// order {order}
if( n_OK(n)==1 && stricmp(n,(const char * ) "{compare_value}")==0) {
    n->OK=1;
    n->pos+={compare_value_length};
    if(n->pos>=n->len) n->pos= -1;
} else {
    n->OK=0;
}

compare_method:
    //external -> {order}
    if( n_OK(n)==1 ) { n = match_{function_name}(n,name,depth+1); }

compare_method_self:
    //recursion -> {order}
    if(n_OK(n)==1  && strcmp(name,last_method)==0) {
        n = match_{function_name}(n,name,depth+1); 
    }
    //}
