match_function:
node_t * match_{function_name}(node_t *n,const char last_method[],int depth){
    const char name[]="{function_name}";
    int start_pos=n->pos;
    n->depth+=1;
    n->function=name;
#ifdef  DEBUG_START
    debug_start(n,name,start_pos);
#endif
    
    {body}

    if ( n->OK==1 ) { 
        //if (depth==0){
            for (int i=0;i<depth;i++) printf(" ");
            printf("[{function_name}] ");
            if (n->pos==-1) {
                print_sub_str(n,start_pos,n->len);
            } else {
                print_sub_str(n,start_pos,n->pos);
            }
            printf("\n");
       // }
{func_recursion}
#ifdef  DEBUG_SUCCESS
    debug_success(n,name,start_pos);
#endif

    } 
#ifdef  DEBUG_FAILED
    if ( n->OK==0 ) { 
        debug_failed(n,name,start_pos);
    }
#endif
        

    n->depth-=1;
    n->last_function=name;

    return n;
}


func_recursion:
    if(n_OK(n)==1 && n->pos!=-1 && start_pos!=n->pos) { //recur
        push(n->stack,n->pos);
        n=match_{function_name}(n,name,depth+1);
        if (n->OK==0) {
            n->pos=peek(n->stack);
            n->OK=1;
        }
        pop(n->stack);
    }
