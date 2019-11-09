                                                          

zero_or_more:
//zero or more

push(n->stack,n->OK);
    while( n_OK(n)==1 ) {
        push(n->stack,n->pos);
        {body}
        if(n->OK==0) { n->pos=peek(n->stack); } 
        pop(n->stack);
    }
    n->OK=peek(n->stack);
pop(n->stack);