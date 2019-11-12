


optional:
//optional
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    push_token(n);
    {body}
    optional_reset(n);
}

optional_reset:
void optional_reset(node_t *n){
    if(n->OK==0) { 
        n->OK=1; 
        n->pos=pop(n->stack);
        trim_token(n);
        pop_token(n);
    } else {
        pop(n->stack);
        pop_token(n);
    }
}