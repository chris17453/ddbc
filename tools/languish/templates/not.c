
not:
//NOT
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    push_token(n);
    {body}
    not_reset(n);
}//end NOT


not_reset:
void not_reset(node_t *n){
    if (n->OK==1 ) {
        n->OK=0;
        n->pos=pop(n->stack);
        trim_token();
        pop_token();
    } else { 
        n->OK=1;
        pop(n->stack);
        pop_token();
    }
}