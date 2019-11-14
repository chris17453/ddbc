                                                          

zero_or_more:
//zero or more

if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    push_token(n);
    while( n_OK(n)==1 ) {
        push(n->stack,n->pos);
        push_token(n);
        {body}
        if(n->OK==0) { 
            n->pos=pop(n->stack);
            trim_token(n);
            pop_token(n);
        } 
        else {
            pop(n->stack);
            pop_token(n);
        }
    }
    n->OK=1; 
    pop(n->stack);
    pop_token(n);
}
