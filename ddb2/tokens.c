#include <stdint.h>
#include <stdlib.h>
#include "headers/tokens.h"



// allocates memory and assigns values for a new node, u nlinked
token_t *create_token(  uint32_t   code,
                        uint16_t   type,
                        uint16_t   id,
                        uint16_t   depth,
                        char      *element,
                        int        src_index,
                        char      *data,
                        uint16_t   data_length,
                        void      *value) {
    
    // allocate memory for types in struct
    token_t *new_token=(token_t*)malloc(sizeof(token_t)); 

    //techinically its already cleared if values are given
    //memset(new_node, 0, sizeof(*new_node));

    new_token->code        =code;
    new_token->type        =type;
    new_token->id          =id;
    new_token->depth       =depth;
    new_token->src_index   =src_index;
    new_token->element     =element;
    new_token->data        =data;
    new_token->data_length =data_length;
    new_token->value       =value;
    return new_token;
}

// releases memory for a given node
void free_token(token_t *token) {
    free((*(token_t *)token).data);
    free((*(token_t *)token).value);
    free(token);
}

// return head element of token list
token_t *get_token_head(token_t *haystack){
    while (haystack->left!=NULL) {
         haystack=haystack->left; 
    }
    return haystack;
}

// return tail element of token list
token_t *get_token_tail(token_t *haystack){
    while (haystack->right!=NULL) {
         haystack=haystack->right; 
    }
    return haystack;
}

// return next element of token list
token_t *next_token(token_t *haystack){
    if (haystack->right==NULL){
        return haystack;
    }
    return haystack->right;
}

// return previous element of token list
token_t *previous_token(token_t *haystack){
    if (haystack->left==NULL){
        return NULL;
    }
    return haystack->left;
}

//Connect 2 tokens as immedate siblings
void connect_token(token_t *token_left,token_t *token_right){
    if (token_left!=NULL){
        token_left->right=token_right;
    }
    if (token_right!=NULL){
        token_right->left=token_left;
    }
}

// insert a token after another
void insert_token_after(token_t *token_left,token_t *token_insert){
    token_t *token_right=token_left->right;
    connect_token(token_left,token_insert);
    connect_token(token_insert,token_right);
}

// insert a token before another 
void insert_token_before(token_t *token_right,token_t *token_insert){
    token_t *token_left=token_right->left;
    connect_token(token_left,token_insert);
    connect_token(token_insert,token_right);
}

// insert a token before another 
void append_token(token_t *token_list,token_t *token_insert){
    connect_token(token_list,token_insert);
}

// insert a token before another 
int token_cmp(token_t *token,char* match){
    int needle_len=strlen(match);
    if (token->data_length!=needle_len) return NULL;
    
    for(int i=0;i<token->data_length;i++){
        if (token->data[i]!=match[i]){
            return NULL;
        }
    }
    return 1;
}


void push_token(node_t *n){
    ++n->token_index;
    push(n->token_stack,n->token_index);
}

void pop_token(node_t *n){
    pop(n->token_stack);
}

char * sub_str_cpy(char *data,int start,int length){
    char *buffer=malloc(length);
    if (buffer==NULL){
        printf("Cannoit allocate memory");
        exit(1);
    }

    memcopy(buffer,data[start],length);

    return buffer;
}

void n_token(node_t *n,const char *element){
    int last_pos=peek(n->stack);
    int len=n->pos-last_pos;
    char *buffer=sub_str_cpy(n->data,last_pos,len);
    
    uint32_t   code       =0;
    uint16_t   type       =0;
    uint16_t   depth      =n->depth;
    char      *element    =element;
    int        src_index  =n->pos;
    int        id         =id;
    char      *data       =buffer;
    uint16_t   data_length=len;
    void      *value      =NULL;
        
    token_t *t=create_token(code,type,id,depth,element,src_index,data,data_length,value);
    if(n->tokens==NULL) {
        n->tokens=t;
    } else {
        token_t *tail=get_token_tail(n->tokens);
        connect_token(tail,t);
    }
}

void trim_token(node_t *n){
    int pos=peek(n->token_stack);
    printf("Trimming : %d->%d",pos,n->token_index)
    if(n->tokens!=NULL){
        token_t *cur_token=n->tokens;
        if (cur_token->id!=id) {
            cur_token=next_token(cur_token);
        }
        
    } else {
        printf("No tokens");
    }

}