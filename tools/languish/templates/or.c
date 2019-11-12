or:
//OR
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    push_token(n);
    {body}
    
    if(n->OK==0){
        trim_token(n);
    } 

    pop(n->stack);
    pop_token(n);
}


recursive_self:
//item {order}  //skip if not called by self
if (strcmp(name,last_method)!=0 ) {
    n->OK=0;
}

recursive_self+1:
//item {order}  //non index 0 recursion
if (n_OK(n)==1 && strcmp(name,last_method)==0 && n->pos>start_pos) {
    match_{function_name}(n,name,depth+1); 
}


or_list_item1:
//item {order} 
{body}
if (n->OK==0) {
    n->pos=peek(n->stack); 
    trim_token(n);
}

or_list_item+1:
//item+1 {order}
if (n->OK==0 ) {
    n->OK=1;
    {body}
    if (n->OK==0) {
        n->pos=peek(n->stack); 
        trim_token(n);
    }
} 

or_compare:
 n->value[n->pos]=='{compare_value}'

not_compare:
 n->value[n->pos]!='{compare_value}'
