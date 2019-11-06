
not:
//NOT
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if (n->OK==1 ) {
        n->OK=0;
        n->pos=peek(n->stack);
    } else { 
        n->OK=1;
        n->pos+=1;
        if(n->pos>=n->len) n->pos= -1;
    }
    pop(n->stack);
}//end NOT