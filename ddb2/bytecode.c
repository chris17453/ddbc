#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "headers/bytecode.h"
//#include "headers/tokens.h"

/*
char * reserved[42]={
                "AND",
                "AS",
                "ASC",
                "BEGIN",
                "BETWEEN",
                "BY",
                "CASE",
                "DELETE",
                "DESC",
                "DUPLICATE",
                "END",
                "EXISTS",
                "FILE",
                "FROM",
                "FULL",
                "GROUP",
                "HAVING",
                "IDENTITY",
                "IF",
                "IN",
                "INNER",
                "INSERT",
                "INTO",
                "JOIN",
                "KEY",
                "LEFT",
                "NOT",
                "NULL",
                "ON",
                "OR",
                "ORDER",
                "OUTER",
                "RIGHT",
                "ROLLBACK",
                "SELECT",
                "SET",
                "TABLE",
                "THEN",
                "UNION",
                "VALUES",
                "WHEN",
                "WHERE"
};

*/




void print_tokens(token_t *token){
    printf("TOKENS:\n");
    
    if (token!=NULL){
        while (token!=NULL){
            printf(" %s - %d\n",token->data,token->type);
            token=token->right;
        }
    } else {
        printf("No Tokens\n");
    }
    printf("<- Done\n");
}



void error_exit(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

char *string_duplicate(const char *str){
    char *new_str = strdup(str);
    if(new_str == NULL)
        error_exit("Failed to create a copy of a string.");
    return new_str;
}


void add_fragment(token_t **tokens,char * query_string,unsigned int index,unsigned int length,BYTECODE_TYPE bc_type){
    //allocate memory for fragment string
    if (length==0){
        return;
    }
    
    unsigned int data_length=(unsigned int)sizeof(char)*length;
    
    char *data=(char *)malloc(data_length);

    //copy it to the new place
    memcpy(data,&query_string[index], data_length); 

    //copy it to the new place
    uint32_t code  = 1;
    uint16_t depth = 1;
    
    token_t *token=create_token(code,(uint16_t)bc_type,depth,data,data_length,NULL);
    if (*tokens==NULL){                                                                               //no list. just make this element the head
        *tokens=token;
    } else {                                                                                        //well there is a list lets append
        token_t *token_end=get_token_tail(*tokens);
        append_token(token_end,token);
    }
}


// prep_sql(char* query_str)
//   this clones the string, and zero's out :
//   - windows line endings, tabs, spaces
//   - block comments
//   - single line comments
//   - replaces whitespace spans with single whitespace
//   - trims the string
//   returns cleaned string
// TODO:  SPEED IT UP
char* prep_sql(char* query_str){
    int str_len = strlen(query_str);        
    char c    =0;
    char block=0;
    char last_character =0;
    int in_comment=0;
    int index=0;
    int mem_size=(strlen(query_str)+1)*sizeof(char);
    char *temp=(char *)malloc(mem_size);
    memcpy(temp,query_str,mem_size);
    int do_pass1=1;  //windows line endings, spaces,tabs
    int do_pass2=1;  //block comments
    int do_pass3=1;  //single line comments
    int do_pass4=1;  //insert place holders
    int do_pass5=1;  //whitespace spans
    int do_pass6=1;  //trim whitespace
    
    if(do_pass1==1){
        //ROUND 1, strip windows line endings , spaces and tabs
        for(int i=0;i<str_len;i++){
            c=temp[i];
            if (block==0 &&  (c=='\'' || c== '"' || c== '`') ) block=c;
            else if (block==c) block=0;
            
            if (block==0){
                if (c=='\r') temp[i]=0;
                else if (c==' ') temp[i]=0;
                else if (c=='\t') temp[i]=0;
            }
        }//end loop 1
    }
    if(do_pass2==1){
        //Pass 2 Strip block comments
        c=0;
        in_comment=0;
        for (uint32_t i=0;i<str_len;i++){
            last_character=c;
            c=temp[i];                                                        //assign current character to c
            
            if (in_comment==0){
                if (block==0 &&  (c=='\'' || c== '"' || c== '`') ) block=c;
                else if (block==c) block=0;
            }

            if (block==0){
                if (in_comment==0){
                    if (last_character=='/' && c=='*') {
                        temp[i-1]=0;
                        in_comment=1;
                    }
                } 
                if (in_comment==1) {
                    temp[i]=0;
                    if (last_character=='*' && c=='/') {
                        in_comment=0;
                    }
                }
            }
        }//end loop 2
    }
    if(do_pass3==1){
        // Pass 3 strip single line comments
        c=0;
        in_comment=0;
        for (uint32_t i=0;i<str_len;i++){
            last_character=c;
            c=temp[i];                                                        //assign current character to c

            if (in_comment==0){
                if (block==0 &&  (c=='\'' || c== '"' || c== '`') ) block=c;
                else if (block==c) block=0;
            }
            if (block==0){
                if (in_comment==0){
                    if (last_character=='-' && c=='-') {
                        temp[i-1]=0;
                        in_comment=1;
                    }
                } 
                if (in_comment==1) {
                    temp[i]=0;
                    if (c=='\n') {
                        in_comment=0;
                    }
                }
            }
        }//end loop 3
    }
    if(do_pass4==1){
        // Pass 4.. for everything that was stripped out, add a single whitespace
        // this prevent seperate tokens/words joining due to the omission
        int in_whitespace=0;
        for (uint32_t i=0;i<mem_size;i++) {
            if (temp[i]!=0) {
                in_whitespace=0;
                continue;
            }
            if (in_whitespace==0 && temp[i]==0) {
                temp[i]=' ';
                in_whitespace=1;
            }
        }
    }
    if (do_pass5==1){
       // Pass 5.. remove whitespace spans >1
        int in_span=0;
        for (uint32_t i=0;i<mem_size;i++) {
            
            if (temp[i]==' ' || temp[i]==0 || temp[i]=='\n') {
                in_span+=1;
                if (in_span>1) temp[i]=0;
            } else {
                in_span=0;
            }
            
        }

    }
    if (do_pass6==1){
       // Pass 6.. trim whitespace
        //at this point all the spaces and tabs have beeen removed, but place holders have been reinserted.
        //trim end
        for (uint32_t i=mem_size-1;i!=0;i--) {
            if (temp[i]=='\n') temp[i]=0;
            else if (temp[i]==' ') temp[i]=0;
            else if (temp[i]!=0) break;
        }
        //trim start
        for (uint32_t i=0;i<mem_size;i++) {
            //temp[i]=38;
            if (temp[i]=='\n') temp[i]=0;
            else if (temp[i]==' ') temp[i]=0;
            else if (temp[i]!=0) break;
        }

    }

    str_len=0;
    for (uint32_t i=0;i<mem_size;i++) if (temp[i]!=0) str_len++;
    char *data=(char *)malloc(str_len*sizeof(char)+1);
    
    index=0;
    for (uint32_t i=0;i<mem_size;i++) {
        if (temp[i]!=0){
            data[index]=temp[i];
            index++;
        }
    }
    free(temp);
    data[index]=0;
    return data;
}

token_t * bytecode(char *query_str){
        token_t   *tokens            = NULL; 
        int              fragment_index     = 0;
        int              fragment_length    = 0;
        int              str_len            = 0;        
        int              is_literal         = 0;                                   //flag to track if this is a numeric litteral
        int              is_block           = 0;                                   //flag to track if this is a quoted block
        char             block_character    = 0;                                   //flag to track curent block endcap
        char             c                  = 0;                                   //local data variable for curent chartacter
        uint16_t         fragment_type      = 0;
        uint16_t         push_fragment      = 0;
        //LOOP TO Tokenize data into a linked list

        char *temp=prep_sql(query_str);
        
        query_str=temp;
        str_len=strlen(query_str);

        for (uint32_t i=0;i<str_len;i++){
            c=query_str[i];                                                        //assign current character to c
            if (fragment_length==0){
                is_literal=1;
            } 


            // are we quoted block? no
            if (is_block==0){
                

                if (c=='\'' || c== '"' || c== '`'){
                    if (is_literal==1)  fragment_type=LITERAL;
                    else                fragment_type=UNKNOWN;
                    add_fragment(&tokens,query_str,fragment_index,fragment_length,10);     //we just changed fragments, add the old one
                    is_block        =1;
                    block_character =c;
                    fragment_length =1;
                    fragment_index  =i;
                    continue;
                } else { 
                    if (is_literal==1 && ( (c>='A' && c<='Z') || (c>='a' && c<='z')) ) {
                        if(fragment_length==0){
                        is_literal=2;
                        }
                    }
                    
                    if (c<=32) {
                        push_fragment=WHITESPACE;                                             //its a non printable character
                    } else if (is_literal==1 && (c<'0' || c>'9')) {   //
                        push_fragment=UNKNOWN;
                    }
                    else if (is_literal==2 && (c<'A' || c>'Z') && (c<'a' || c>'z')) {   // && c!='_' && c!='$' && (c<'0' || c>'9')
                        push_fragment=UNKNOWN;
                    }

                    if (push_fragment!=0) {
                        if (is_literal==1)  fragment_type=LITERAL;
                        else                fragment_type=UNKNOWN;

                        add_fragment(&tokens,query_str,fragment_index,fragment_length,fragment_type);     //we just changed fragments, add the old one
                        add_fragment(&tokens,query_str,i,1,push_fragment);                                
                    
                        push_fragment   =0;
                        is_block        =0;
                        block_character =0;
                        fragment_length =0;
                        fragment_index  =i+1;
                        continue;
                    }// end if push fragment
                    
                    fragment_length+=1;
                    continue;                                     //fragment just got longer broham
                }    
            } 
            
            // are we quoted block? yes
            if (is_block==1){
                fragment_length+=1;                                            //fragment just got longer broham
                if (c==block_character){
                    is_block        =0;
                    block_character =0;
                    add_fragment(&tokens,query_str,fragment_index,fragment_length,STRING);
                    fragment_length =0;                                          //we just ended and added a block, next character is the start index
                    fragment_index  =i+1;
                } //end if c==block_character
            }//end if quoted block
        } //end string loop per character

        //catch all for unprocessed end token
        if (is_literal==1)  fragment_type=LITERAL;
        else                fragment_type=UNKNOWN;
        add_fragment(&tokens,query_str,fragment_index,fragment_length,fragment_type);
    





    printf("NUMBERS FOUND\n");
    token_t *tokens_ptr=tokens;
    token_t *next_token;
    while(tokens_ptr!=NULL) {
        next_token=number(tokens_ptr);
        if (next_token==NULL){
            tokens_ptr=tokens_ptr->right;
        } else{
            //printf("GOOD POINTER");
            tokens_ptr=next_token;
        }
    }
    printf("END NUMBERS FOUND\n");
    


    return tokens;                                                              //exit with the list of tokens
}//end function




token_t * dot(token_t *tokens){
    // dot: 
    //  '.'
    if(tokens->data_length!=1) return NULL;                                //signs are only 1 character
    if(tokens->data[0]=='.') return next_token(tokens);
    return NULL;
}

token_t * alpha_E(token_t *tokens){
    // alpha_e:
    //  'E'
    if(tokens->data_length!=1) return NULL;                                //signs are only 1 character
    if(tokens->data[0]=='E') return next_token(tokens);
    return NULL;
}

token_t * alpha(token_t *tokens){
    // alpha:
    // A-Z | a-z
    int len=tokens->data_length;
    if(len==0) return NULL;                                                
    for(int i=0;i<len;i++){
        if ((tokens->data[i]<'A' || tokens->data[i]>'Z') && (tokens->data[i]<'a' || tokens->data[i]>'z')) return NULL;      //it anything is not a digit bail
    }
    return next_token(tokens);
}

token_t * sign(token_t *tokens){
    // sign:
    //  '-' | '+'
    if(tokens->data_length!=1) return NULL;                                //signs are only 1 character
    if(tokens->data[0]=='-' || tokens->data[0]=='+') return next_token(tokens);
    return NULL;
}

token_t * unsigned_integer(token_t *tokens){
    // unsigned_int:
    //  [0-9]+
    int len=tokens->data_length;
    if(len==0) return NULL;                                               //if nothing is here.. its not a number
    //if(alpha(previous_token(tokens))!=NULL) return NULL;                  //previous token cant be alpha
    //if(alpha(next_token(tokens))!=NULL) return NULL;                      //next token cant be alpha
    for(int i=0;i<len;i++){
        if (tokens->data[i]<'0' || tokens->data[i]>'9') return NULL;      //it anything is not a digit bail
    }
    return next_token(tokens);                                            //only way to get here is everything is a digit. return true
}

token_t * signed_integer(token_t *tokens){
    // signed_int:
    //  sign & int
    token_t *token;
    token=sign(tokens);
    if (token!=NULL) {
        token=unsigned_integer(token);
    } 
    return token;
}

// handles signed or unsigned integers
token_t * integer(token_t *tokens){
    // int:
    //  unsigned_int | signed_int
    token_t *token;
    token=signed_integer(tokens);
    if (token==NULL ) token=unsigned_integer(tokens);
    return token;                                            //only way to get here is everything is a digit. return true
}



token_t * number(token_t *tokens){
    // number:
    //  [int] |  [int & dot & unsigned_int] |  dot & unsigned_int
    //  [alpha_e & int]
    token_t *token;
    token_t *token_holder;
    
    token=dot(tokens);
    if (token!=NULL ) token=unsigned_integer(token);
    
    if (token==NULL ){
        token=integer(tokens);
        if (token!=NULL ) token=dot(token);
        if (token!=NULL ) token=unsigned_integer(token);
    }
    
    if (token==NULL ){
        token=integer(tokens);
    }

    if (token!=NULL){

        token_holder=token;
        token=alpha_E(token);
        if (token!=NULL ) token=integer(token);

        if (token==NULL) {
            token=token_holder;
        }

        printf(" \n");
        if (token!=NULL){
            printf("\nFOUND -> ");
            while(tokens!=token){
                printf("%s",tokens->data);
                tokens=tokens->right;
            }
        }
    }

    return token;
}



