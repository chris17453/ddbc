match_function:
node_t * match_{function_name}(node_t *n,const char last_method[],int depth){
    const char name[]="{function_name}";
    int start_pos=n->pos;
    n->depth+=1;
    n->function=name;
#ifdef  DEBUG_START
    debug_start(n,start_pos);
#endif
    int recursion={recurse};
    //printf("In functions match_{function_name}\n");
    
    {body}

    if ( n->OK==1 ) { 
        if (depth==0){
            printf("{function_name}           ");
            if (n->pos==-1) {
                print_sub_str(n,start_pos,n->len);
            } else {
                print_sub_str(n,start_pos,n->pos);
            }

            printf("\n");
        }
        if(recursion==1 && n->pos!=-1 && start_pos!=n->pos) {
            push(n->stack,n->pos);
            n=match_{function_name}(n,last_method,depth+1);
            if (n->OK==0) {
                n->pos=peek(n->stack);
                n->OK=1;
            }
            pop(n->stack);
        }
#ifdef  DEBUG_SUCCESS
    debug_success(n,start_pos);
#endif

    } 
#ifdef  DEBUG_FAILED
    if ( n->OK==0 ) { 
        debug_failed(n,start_pos);
    }
#endif
        
   


    n->depth-=1;
    n->last_function=name;

    return n;
}


