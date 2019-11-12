
one_or_more:
//one or more
push(n->stack,n->pos);
push_token(n);
while( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    if(n->OK==0) {
        n->pos=pop(n->stack); 
        trim_token(n);
        pop_token(n);
    } else {
        pop(n->stack);
        pop_token(n);
    }
}
if(n->pos==pop(n->stack)){ 
    n->OK=0; 
    trim_token(n);
} else {
    n->OK=1; 
}
pop_token(n);
