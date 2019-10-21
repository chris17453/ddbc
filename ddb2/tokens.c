#include <stdint.h>
#include <stdlib.h>
#include "headers/tokens.h"



// allocates memory and assigns values for a new node, u nlinked
token_t *create_token( uint32_t   code,
                            uint16_t   type,
                            uint16_t   depth,
                            char      *data,
                            uint16_t   data_length,
                            void      *value) {
    
    // allocate memory for types in struct
    token_t *new_token=(token_t*)malloc(sizeof(token_t)); 

    //techinically its already cleared if values are given
    //memset(new_node, 0, sizeof(*new_node));

    new_token->code        =code;
    new_token->type        =type;
    new_token->depth       =depth;
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
        return haystack;
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




//struct token *new_token_list(){
//    struct token *token_list;
//
//    return token_list;
//}