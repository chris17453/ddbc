#include <stdint.h>
#include "func.h"
#include "stack.h"


// token element in bytecode list
typedef struct token_t{
    uint32_t        code;         // the byte code used for comparison
    uint16_t        type;         // string,literal,delimiter,operator,function,reserverd,keyword
    uint16_t        id;           // incremental ID for trimming 
    uint16_t        depth;        // pattern matching depth, sub elements and recursion
    char           *element;      // name function/element type
    int             src_index;    // src location in original string
    char           *data;         // string value
    uint16_t        data_length;  // data length
    void           *value;        // value of token ? Just-in-case
    
    struct token_t  *left;         // previous node
    struct token_t  *right;        // next node
} token_t;


// signatures
token_t  * create_token( uint32_t   code,
                        uint16_t    type,
                        uint16_t    id,
                        uint16_t    depth,
                        char       *element,
                        int         src_index,
                        char       *data,
                        uint16_t    data_length,
                        void       *value);
void       free_token(token_t *token);
token_t *  next_token(token_t *token);
token_t *  previous_token(token_t *token);
token_t *  get_token_head(token_t *haystack);
token_t *  get_token_tail(token_t *haystack);
void       connect_token(token_t *token_left,token_t *token_right);
void       insert_token_after(token_t *token_left,token_t *token_insert);
void       insert_token_before(token_t *token_right,token_t *token_insert);
void       append_token(token_t *token_list,token_t *token_insert);
int        token_cmp(token_t *token,char* match);
void       push_token(node_t *n);
void       pop_token(node_t *n);
void       print_tokens(token_t *token);
char       * sub_str_cpy(char *data,int start,int length);
void       n_token(node_t *n,char *element);
void       trim_token(node_t *n);

