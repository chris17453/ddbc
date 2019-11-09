
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
    node_t * n=malloc(sizeof(node_t));
    n->value=data;
    n->len=strlen(data);
    n->pos=0;
    n->depth=0;
    n->OK=1;
    n->stack=createStack(1000);

//printf("POS:%d\n",n->pos);
//printf("OK:%d\n",n->OK);
//printf("--\n");
while (n->pos>-1){
{body}

    if ( n->OK == 0) {
        printf("Match not found");
        break;
    }
    
}
    pop(n->stack);
    return n;
} // end match functions


match_functions_first_var:
    n->OK=1;
    n=match_{function_name}(n,(const char* )"functions",0);
    if (n_OK(n)==1 || n->pos==-1 ) continue; 

match_functions_second_var:
    n->OK=1;
    n=match_{function_name}(n,(const char *)"functions",0);
    if (n_OK(n)==1  || n->pos==-1 ) continue; 
