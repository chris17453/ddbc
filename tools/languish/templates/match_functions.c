
match_functions:
/*
 * Function: match_functions
 * -----------------------------
 *   Generated: {date_time}
 *      nodes: a pointer to the curent element in a linked list of nodes to search
 * 
 *     OK: Returns a the node AFTER the curent pattern match
 *              If the end of the list is reached the last node is passed
 *     Failure: Returns NULL
 */
node_t * match_function(char *data) {
    printf("In functions\n");
    int last_pos=-1;
    node_t * n=malloc(sizeof(node_t));
    n->value=data;
    n->len=strlen(data);
    n->pos=0;
    n->depth=0;
    n->OK=1;
    n->stack=createStack(1000);
const char* name="functions";

push(n->stack,n->pos);
while (n->pos>-1){
    if (last_pos==n->pos) {
        break;
    }
    last_pos=n->pos;
{body}

    if ( n->OK == 0) {
        break;
    }    
    
}
    pop(n->stack);
    if ( n->OK == 0) {
        printf("\nMatch not found\n");
    }    
    if (n->pos!=-1) {
        printf("String parsed until [%d] out of [%d]\n",n->pos,n->len);
    }
    return n;
} // end match functions


match_functions_first_var:
    n->OK=1;
    match_{function_name}(n,name,0);
    if (n_OK(n)==1 ) { printf ("GOOD {function_name}\n");  }

match_functions_second_var:
    n->OK=1;
    match_{function_name}(n,name,0);
    if (n_OK(n)==1 ) { printf ("GOOD {function_name}\n");  }
