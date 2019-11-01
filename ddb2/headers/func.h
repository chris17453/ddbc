// this holds the string you are tokenizing
typedef struct node_t {
  int len;
  int pos;
  int OK;
  char *value;
  struct stack_t *stack;
} node_t;
node_t *match_string(node_t * n);
node_t *match_integer(node_t * n);
node_t *match_real(node_t * n);
node_t *match_alpha(node_t * n);
node_t *match_unsigned_int(node_t * n);
node_t *match_sign(node_t * n);
node_t *match_exponent(node_t * n);
node_t *match_signed_int(node_t * n);
node_t *match_whitespace(node_t * n);
node_t *match_function(char *data);
