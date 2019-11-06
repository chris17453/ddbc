
one_or_more:
//one or more
push(n->stack,n->pos);
while( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if(n->OK==0) { n->pos=peek(n->stack); } 
    pop(n->stack);
}
if(n->pos==peek(n->stack)){ 
    n->OK=0; 
} else {
    n->OK=1; 
}
pop(n->stack);