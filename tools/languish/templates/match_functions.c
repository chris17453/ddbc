
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
node_t * match_function(char *d) {
    char *data=prep_sql(d);
    printf("%s",data);
    int last_pos=-1;
    node_t *  n =malloc(sizeof(node_t));
    n->value      = data;
    n->len        = strlen(data);
    n->pos        = 0;
    n->depth      = 0;
    n->OK         = 1;
    n->token_index= 0;
    n->stack      = createStack(1000);
    n->token_stack= createStack(1000);
    n->tokens       =NULL;
    n->last_token   =NULL;
 char* name="functions";

push(n->stack,n->pos);
push_token(n);
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
    pop_token(n);
#ifdef  DEBUG_FAIL
    if ( n->OK == 0) {
        printf("\nMatch not found\n");
    }    
    if (n->pos!=-1) {
        printf("String parsed until [%d] out of [%d]\n",n->pos,n->len);
    }
#endif
    printf ("\nEND MATCH\n");
    print_tokens(n->tokens);
    return n;
} // end match functions


match_functions_first_var:
    n->OK=1;
    match_{function_name}(n,name,0);
    if (n->OK==1 ) {
//#ifdef  DEBUG_SUCCESS
     printf ("GOOD {function_name}\n");  
//#endif
        continue;
}

match_functions_second_var:
    n->OK=1;
    match_{function_name}(n,name,0);
    if (n->OK==1 ) {
#ifdef  DEBUG_SUCCESS
     printf ("GOOD {function_name}\n");  
#endif
        continue;
}
