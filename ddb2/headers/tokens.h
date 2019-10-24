#include <stdint.h>



// token element in bytecode list
typedef struct token_t{
    uint32_t        code;         // the byte code used for comparison
    uint16_t        type;         // string,literal,delimiter,operator,function,reserverd,keyword
    uint16_t        depth;
    char           *data;         // string value
    uint16_t        data_length;  // data length
    void           *value;        //value of token ? Just-in-case
    
    struct token_t  *left;         // previous node
    struct token_t  *right;        // next node
} token_t;


// signatures
token_t  * create_token(uint32_t code,uint16_t type,uint16_t depth,char *data,uint16_t data_length,void *value);
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
int        token_cmp_range(token_t *token,char* match1,char* match2);

