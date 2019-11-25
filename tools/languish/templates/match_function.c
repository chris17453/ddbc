match_function:
void match_{function_name}(node_t *n,char last_method[],int depth){
    if( n_OK(n)==0) {
        return;
    }
    char *name="{function_name}";
    int start_pos=n->pos;
    n->depth+=1;
    n->function=name;
#ifdef  DEBUG_START
    debug_start(n,name,start_pos);
#endif
    
    {body}

#ifdef  DEBUG_SUCCESS
    if ( n->OK==1 ) { 
            for (int i=0;i<depth;i++) printf(" ");
            printf("[{function_name}] SUCCESS");
            if (n->pos==-1) {
                print_sub_str(n,start_pos,n->len);
            } else {
                print_sub_str(n,start_pos,n->pos);
            }
            printf("\n");
    debug_success(n,name,start_pos);
    } 
#endif

{func_recursion}

#ifdef  DEBUG_FAILED
    if ( n->OK==0 ) { 
        debug_failed(n,name,start_pos);
    }
#endif
    n->depth-=1;
    n->last_function=name;
#ifdef DEBUG_SUCCESS
    if( n->OK){
        printf("%s, %d, %d\n",name,start_pos,n->pos);
    }
#endif

}


func_recursion:
    if(n_OK(n)==1 && n->pos!=-1 && start_pos!=n->pos) { //recur
        push(n->stack,n->pos);
        push_token(n);
        match_{function_name}(n,name,depth+1);
        if (n->OK==0) {
            n->pos=pop(n->stack);
            trim_token(n);
            pop_token(n);
            n->OK=1;
        } else {
            pop(n->stack);
            pop_token(n);
        }
    }
