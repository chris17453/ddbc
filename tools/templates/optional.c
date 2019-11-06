


optional:
//optional
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if(n->OK==0) { 
        n->OK=1; 
        n->pos=peek(n->stack); 
    }
    pop(n->stack);
}
