#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/tokens.h"
//#include "headers/stack.h"

int tokens_UUID=0;

// allocates memory and assigns values for a new node, u nlinked
token_t *create_token(  uint32_t     code,
                        uint16_t     type,
                        uint16_t     id,
                        uint16_t     depth,
                        char        *element,
                        int          src_index,
                        char        *data,
                        uint16_t     data_length,
                        void        *value) {
    
    // allocate memory for types in struct
    token_t *new_token=(token_t*)malloc(sizeof(token_t)); 

    //techinically its already cleared if values are given
    //memset(new_node, 0, sizeof(*new_node));

    new_token->success     =0;
    new_token->code        =code;
    new_token->uuid        =tokens_UUID;
    new_token->code        =code;
    new_token->type        =type;
    new_token->id          =id;
    new_token->depth       =depth;
    new_token->src_index   =src_index;
    new_token->element     =element;
    new_token->data        =data;
    new_token->data_length =data_length;
    new_token->value       =value;
    new_token->left        =NULL;
    new_token->right       =NULL;
    tokens_UUID++;
    
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
        //printf("CONNECTING A->R to B");
        token_left->right=token_right;
    }
    if (token_right!=NULL){
        //printf("CONNECTING B->L to A");
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

/*
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
*/


void push_token(node_t *n){
    ++n->token_index;
    push(n->token_stack,n->token_index);
}

void pop_token(node_t *n){
    
    pop(n->token_stack);
}

char * sub_str_cpy(char *data,int start,int length){
    if( length<1) {
        printf("Not allocating %d",length);
        return NULL;
    }
    char *buffer=malloc(length+1);
    if (buffer==NULL){
        printf("Cannot allocate memory");
        exit(1);
    }

    memset(buffer,0,length+1);
    memcpy(buffer,&data[start],length);
    //printf("%s",buffer);
    return buffer;
}


void print_tokens(token_t *token){
    //printf("TOKENS:\n");
    
    if (token!=NULL){
        while (token!=NULL){
            if (token->data_length>0){
                for (int i=0;i<token->depth;i++) printf(" ");
                printf("[%s] %s - %d, %d\n",token->element,token->data,token->id,token->uuid);
            } else {
                for (int i=0;i<token->depth;i++) printf(" ");
                printf("^ NO DATA [%s] %s - %d, %d \n",token->element,token->data,token->id,token->uuid);
            }
            token=token->right;
        }
    } //else {
        //printf("No Tokens\n");
    //}
    //printf("<- Done\n");
}



void n_token(node_t *n,char *element){
    
    int last_pos=peek(n->stack);
    int len;
    if (n->pos==-1){
        len=n->len-last_pos;
        //printf("%d,%d,%d\n",last_pos,n->len,len);

    } else {
        len=n->pos-last_pos;
        //printf("%d,%d,%d\n",last_pos,n->pos,len);
    }
    char *buffer=sub_str_cpy(n->value,last_pos,len);
    char *name=sub_str_cpy(element,0,strlen(element));
    
    uint32_t    code       =0;
    uint16_t    type       =0;
    token_t *t=create_token(code,type,last_pos,n->depth,name,n->pos,buffer,len,NULL);
    if(n->tokens==NULL) {
        n->tokens=t;
        n->last_token=t;
    } else {
        //print_tokens(n->tokens);
        token_t *tail=n->last_token;
        //get_token_tail(n->tokens);
        //print_tokens(tail);
        
        connect_token(tail,t);
        n->last_token=t;
    }
}

void trim_token(node_t *n){
    int id=n->pos;//peek(n->token_stack);
        
    printf("\nTrimming : %d->%d",id,n->token_index);
    if(n->tokens!=NULL){
        //token_t *cur_token=n->last_token;
        token_t *cur_token=get_token_tail(n->tokens);
        token_t *last_token=NULL;
        if(cur_token!=NULL){
            //printf("\nTrimming from %d to %d\n-",cur_token->id,id);
        }
      //  print_tokens(n->tokens);
        while (cur_token!=NULL){
            //printf("\n TRIM");
            if (cur_token->id<id) {
                //n->last_token=cur_token;
                return;
            }
            //printf("\nFREEING  %d\n",cur_token->id);
            last_token=cur_token;
            //free_token(last_token);
            cur_token=previous_token(cur_token);
            if (cur_token!=NULL){
                //printf("\nPointer->  %d\n",cur_token->id);
                cur_token->right=NULL;

            } else {
                n->tokens=NULL;
                //printf("\nPointer->  NULL\n");
            }
            n->last_token=cur_token;

        }
    } //else {
        //printf("No tokens");
    //}

}


//node_t is the list of tokens and vars
//token_t is an individual component in a token list