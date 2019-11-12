


range:
(n->value[n->pos]>='{range_1}' && n->value[n->pos]<='{range_2}')

char:
if( n_OK(n)==1 && ( {conditions} ) )   {
    increment_m(n,1);
    n_token(n);
} else {
    n->OK=0;
}
 // end char