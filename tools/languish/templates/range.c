


range:
(n->value[n->pos]>='{range_1}' && n->value[n->pos]<='{range_2}')

char:
if( n_OK(n)==1 && ( 
{conditions}
) ) {
    n->OK=1;
    n->pos++; 
    if(n->pos>=n->len) n->pos= -1;
} else {     
    n->OK=0;
} // end char
