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
#include <stdlib.h>

//#include "headers/stack.h"
//#include "headers/func.h"
#include "headers/tokens.h"


node_t:

// this holds the string you are tokenizing
typedef struct node_t{
    int    len;
    int    pos;
    int    OK;
    int    depth;
    int             token_index;
    char           *function;
    char           *last_function;
    char           *value;
    struct stack_t *token_stack;
    struct stack_t *stack;
    struct token_t *tokens;
    struct token_t *last_token;
}
node_t;



signature:
void match_{body}(node_t *n,char *last_method,int depth);


signature2:
node_t *match_function(char * data);


stricmp:


// node values are only compared if string length is the same, no need to validate
// comparitors is against a precompiled value thats already case optimised
// returns 0 for equal
int stricmp(node_t *n, char * b){
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

char * substr(node_t *n,int start,int stop){
    int buffer_len=stop-start+1;
    char * buffer=malloc(buffer_len);
    if(buffer==NULL) {
        printf("Cannot allocate memory for substring copy.");
        exit(1);
    }
    memset(buffer,0,buffer_len);

    for (int i=start;i<stop;i++) {
        buffer[i-start]=n->value[i];
    }
    return buffer;
}

void print_sub_str(node_t *n,int start,int end){
    printf("***");
    for (int i=start;i<end;i++) {
        if (n->value[i]=='\n'){
            printf("\n***");
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
    if( n->pos!=-1 ) {
        n->pos+=len; 
        if(n->pos>=n->len) n->pos= -1;
    }
}

#define ZONE_PLAIN_TEXT    1            
#define ZONE_STRING_BLOCK  2            
#define ZONE_COMMENT_BLOCK 3            
#define ZONE_COMMENT_LINE  4            
#define TOKEN_SEPARATOR    0

char* prep_sql(char* query_str){
    int  string_length   = strlen(query_str)+1;
    int  mem_size        = string_length*sizeof(char);
    char *temp=(char *)malloc(mem_size);
    
    char character       = 0;
    char last_character  = 0;
    
    int zone              = ZONE_PLAIN_TEXT;
    int zone_identifier   = 0;
    int start_index       = 0;
    int end_index         = 0;
    int start_set         = 0;
    int new_string_length = 0;
    int index=0;
    
    memset(temp,0,mem_size);
    memcpy(temp,query_str,string_length);


    for (uint32_t i=0;i<mem_size;i++){
        last_character=character;
        character=temp[i];                                                                                                  //assign current character to c, strlength ends at null, so no value will have a 0
        
        switch(zone){
            case ZONE_STRING_BLOCK:     if (zone_identifier == character) {                                          //ending a string block, the match is the previouslt set block identifier
                                            zone            = ZONE_PLAIN_TEXT;
                                            zone_identifier = 0;
                                        }            
                                        break;

            case ZONE_PLAIN_TEXT:       if( character == '\'' || character == '"' || character == '`')  {
                                            zone            = ZONE_STRING_BLOCK;
                                            zone_identifier = character;
                                            break;
                                        } 
                                        if (last_character == '/' && character == '*') {
                                            temp[i-1] = TOKEN_SEPARATOR;
                                            temp[i]   = TOKEN_SEPARATOR;
                                            zone      = ZONE_COMMENT_BLOCK;
                                            break;
                                        } 
                                        if (last_character == '-' && character == '-') {
                                            temp[i-1] = TOKEN_SEPARATOR;
                                            temp[i]   = TOKEN_SEPARATOR;
                                            zone      = ZONE_COMMENT_LINE;
                                            break;
                                        }     
                                        if (character == '\r' ||  character == '\n' || character == ' ' || character == '\t') temp[i] = TOKEN_SEPARATOR;        //remove whitespace
                                        break;

            case ZONE_COMMENT_BLOCK:    if(last_character == '*' && character == '/')  zone = ZONE_PLAIN_TEXT;
                                        temp[i] = TOKEN_SEPARATOR;
                                        break;
            case ZONE_COMMENT_LINE:     if (character == '\n')  zone = ZONE_PLAIN_TEXT;
                                        temp[i] = TOKEN_SEPARATOR;
                                        break;
            

        }//end zone switch
        if (start_set==0){              //this is the first printable character
            if (temp[i]!=TOKEN_SEPARATOR){
                start_set=1;
                start_index=i;
            }
        }

        if (temp[i]!=TOKEN_SEPARATOR){      //increase length f string if valid. move end index
            end_index=i+1;
        }
    }//end for    
    // at the end of this loop
    // start_index = the first printable character
    // end_index = the last printable character
    // tmp = string with lots of 0's for stuff we want to delete


    //remove convert seperators to single spaces, calculate new string length
    int in_whitespace=0;
    new_string_length=0;

    for (uint32_t i=start_index;i<=end_index;i++) {
        if (temp[i]==0) {
            if(in_whitespace==0 ){
                temp[i]=' ';
                ++new_string_length;
                in_whitespace=1;
            }
        } else {
                ++new_string_length;
                in_whitespace=0;
        }
    }//end for

    //allocate the length of the string + 1 character for the null terminator
    int data_size=(new_string_length+10)*sizeof(char);
    char *data=(char *)malloc(data_size);
    memset(data,0,data_size);
    //copy the string into its permant location, without seperators
    index=0;
    for (uint32_t i=0;i<mem_size;i++) {
        if (temp[i]!=0){
            data[index]=temp[i];
            ++index;
        }
    }//end for
    data[index]=0;  // add null terminator to the end of the string
    free(temp);     // release the temp memory we used for copying and editing
    return data;    //return the cleansed string
}
