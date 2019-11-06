headers:
/********************************************
* Generated: {date_time}                    *
********************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "headers/stack.h"
#include "headers/func.h"


node_t:

// this holds the string you are tokenizing
typedef struct node_t{
    int    len;
    int    pos;
    int    OK;
    int    depth;
    const char  *last_function;
    char  *value;
    struct stack_t *stack;
}
node_t;


signature:
node_t * match_{body}(node_t *n,const char *last_method,int depth);


signature2:
node_t *match_function(char * data);
