headers:
/********************************************
* Generated: {date_time}                    *
********************************************/
//#define DEBUG_START   1
#define DEBUG_SUCCESS 1
//#define DEBUG_FAIL    1

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
    const char  *function;
    const char  *last_function;
    char  *value;
    struct stack_t *stack;
}
node_t;


signature:
void match_{body}(node_t *n,const char *last_method,int depth);


signature2:
node_t *match_function(char * data);


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
            d = (unsigned char)tolower(c)- (unsigned char)b[i];
        } else {
            d = (unsigned char) c- (unsigned char)b[i];
        }
        if (d != 0 ) return d;
    }
    return 0;
}

void print_sub_str(node_t *n,int start,int end){
    printf("***");
    for (int i=start;i<end;i++) {
        if (n->value[i]=='\n'){
            printf("\n***",n->value[i]);
        } else {
            printf("%c",n->value[i]);
        }
    }
    printf("***");
}




void print_n(node_t *n){
    printf("POS:%d\n",n->pos);
    printf("OK:%d\n",n->OK);
    printf("--\n");

}
int n_OK(node_t *n){
    if ( n->pos!=-1 && n->OK==1 ) return 1;
    return 0;
}


void increment_n(node_t *n,int len){
    n->pos+=len; 
    if(n->pos>=n->len) n->pos= -1;
}

