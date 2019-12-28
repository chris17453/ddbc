group:
// GROUP
if( n_OK(n)==1 ) {
    push(n->stack,n->pos);
    push_token(n);


    {body}
    
    if(n->OK==1){
        char group_name[100];
        memset(group_name,0,100);
        int r=sprintf(group_name,"GROUP %s",name);
      //  printf ("[%s] is a string %d chars long\n",group_name,r);
      //  n_token(n,group_name);
    } 


    pop(n->stack);
    pop_token(n);
}


