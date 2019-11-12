                                                          

zero_or_more:
//zero or more

push(n->stack,n->OK);
    while( n_OK(n)==1 ) {
        push(n->stack,n->pos);
        {body}
        n_token(n);
        if(n->OK==0) { n->pos=pop(n->stack);} 
        else pop(n->stack);
    }
n->OK=pop(n->stack);