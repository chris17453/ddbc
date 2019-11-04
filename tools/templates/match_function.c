match_function:
node_t * match_{function_name}(node_t *n,const char last_method[],int depth){
    const char name[]="{function_name}";
    int recursion={recurse};
    n->depth+=1;
    //printf("In functions match_{function_name}\n");
    int start_pos=n->pos;
    
    {body}

    if ( n->OK==1 ) { 
        for( int i=0;i<n->depth;i++) printf(" ");
            printf(" {function_name} -> %d - %d OK:%d, depth: %d ",start_pos,n->pos,n->OK,n->depth); 
            if (n->pos==-1) {
                print_sub_str(n,start_pos,n->len);
            } else {
                print_sub_str(n,start_pos,n->pos);
            }
        printf("\n");
        if(recursion==1 && n->pos!=-1 && start_pos!=n->pos) {
            match_{function_name}(n,last_method,depth+1);
        }
    }
    n->depth-=1;

    return n;
}
