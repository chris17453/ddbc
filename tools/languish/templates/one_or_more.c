
one_or_more:
//one or more
push(n->stack,n->pos);
while( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if(n->OK==0) n->pos=pop(n->stack); 
    else pop(n->stack);
}
if(n->pos==pop(n->stack)){ 
    n->OK=0; 
} else {
    n->OK=1; 
}
