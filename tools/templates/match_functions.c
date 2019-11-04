headers:
/********************************************
* Generated: {date_time}                    *
********************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "headers/stack.h"
#include "headers/func.h"

stricmp:


// node values are only compared if string length is the same, no need to validate
// comparitors is against a precompiled value thats already case optimised
// returns 0 for equal
int stricmp(node_t *n, const char * b){
    int d=0;
    int b_len=strlen(b);
    //printf("Compare %s\n",b);
    for (int i=0;i<b_len;i++) {
        if (n->pos+i>n->len) return -1;
        char c=n->value[i+n->pos];

        if (c>='A' && c<='Z'){
            d = (unsigned char) c-(unsigned char)'A'- (unsigned char)b[i];
        } else {
            d = (unsigned char) c- (unsigned char)b[i];
        }
        if (d != 0 ) return d;
    }
    return 0;
}

void print_sub_str(node_t *n,int start,int end){
    for (int i=start;i<end;i++) {
        printf("%c",n->value[i]);
    }
}




void print_n(node_t *n){
    printf("POS:%d\n",n->pos);
    printf("OK:%d\n",n->OK);
    printf("--\n");

}
int n_OK(node_t *n){
    //print_n(n);
    if ( n->pos!=-1 && n->OK==1 ) return 1;
    return 0;
}


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
    
}
    pop(n->stack);
    return n;
} // end match functions


match_functions_first_var:
    n->OK=1;
    n=match_{function_name}(n,(const char* )"functions");
    if (n_OK(n)==1 || n->pos==-1 ) continue; 

match_functions_second_var:
    n->OK=1;
    n=match_{function_name}(n,(const char *)"functions");
    if (n_OK(n)==1  || n->pos==-1 ) continue; 
