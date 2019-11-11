
not:
//NOT
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    {body}
    not_reset(n);
}//end NOT


not_reset:
void not_reset(node_t *n){
    if (n->OK==1 ) {
        n->OK=0;
        n->pos=pop(n->stack);
    } else { 
        n->OK=1;
        increment_n(n,1);
        pop(n->stack);
    }
}