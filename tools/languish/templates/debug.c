debug:

void debug_start(node_t *n,int start_pos){
    for( int i=0;i<n->depth;i++) printf(" ");
    printf(" [%s]-> %d - %d OK:%d, depth: %d \n",n->function,start_pos,n->pos,n->OK,n->depth); 
}

void debug_success(node_t *n,int start_pos){
    for( int i=0;i<n->depth;i++) printf(" ");
    printf(" [%s] SUCCESS -> %d - %d OK:%d, depth: %d \n",n->function,start_pos,n->pos,n->OK,n->depth); 
}

void debug_failed(node_t *n,int start_pos){
    for( int i=0;i<n->depth;i++) printf(" ");
    printf(" [%s] FAILED -> %d - %d OK:%d, depth: %d \n",n->function,start_pos,n->pos,n->OK,n->depth); 
}