                                                          

zero_or_more:
//zero or more
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if(n->OK==0) { n->pos=peek(n->stack); }
    pop(n->stack);
} 

