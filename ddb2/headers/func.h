// this holds the string you are tokenizing
typedef struct node_t {
  int len;
  int pos;
  int OK;
  int depth;
  int token_index;
  char *function;
  char *last_function;
  char *value;
  struct stack_t *token_stack;
  struct stack_t *stack;
  struct token_t *tokens;
  struct token_t *last_token;
} node_t;
void match_queries(node_t * n, char *last_method, int depth);
void match_select(node_t * n, char *last_method, int depth);
void match_select_expr(node_t * n, char *last_method, int depth);
void match_select_expr_list(node_t * n, char *last_method, int depth);
void match_subquery(node_t * n, char *last_method, int depth);
void match_expr(node_t * n, char *last_method, int depth);
void match_boolean_primary(node_t * n, char *last_method, int depth);
void match_predicate(node_t * n, char *last_method, int depth);
void match_bit_expr(node_t * n, char *last_method, int depth);
void match_operations(node_t * n, char *last_method, int depth);
void match_identifier_expr(node_t * n, char *last_method, int depth);
void match_simple_expr(node_t * n, char *last_method, int depth);
void match_literal(node_t * n, char *last_method, int depth);
void match_whitespace(node_t * n, char *last_method, int depth);
void match_unknown(node_t * n, char *last_method, int depth);
void match_hex(node_t * n, char *last_method, int depth);
void match_bit(node_t * n, char *last_method, int depth);
void match_null(node_t * n, char *last_method, int depth);
void match_true(node_t * n, char *last_method, int depth);
void match_false(node_t * n, char *last_method, int depth);
void match_boolean(node_t * n, char *last_method, int depth);
void match_integer(node_t * n, char *last_method, int depth);
void match_signed_int(node_t * n, char *last_method, int depth);
void match_unsigned_int(node_t * n, char *last_method, int depth);
void match_real(node_t * n, char *last_method, int depth);
void match_sign(node_t * n, char *last_method, int depth);
void match_exponent(node_t * n, char *last_method, int depth);
void match_identifier(node_t * n, char *last_method, int depth);
void match_keywords(node_t * n, char *last_method, int depth);
void match_string(node_t * n, char *last_method, int depth);
void match_single_quote_string(node_t * n, char *last_method, int depth);
void match_double_quote_string(node_t * n, char *last_method, int depth);
void match_query_delimiter(node_t * n, char *last_method, int depth);
void match_comparison_operator(node_t * n, char *last_method, int depth);
void match_comment(node_t * n, char *last_method, int depth);
void match_block_comment(node_t * n, char *last_method, int depth);
void match_single_comment(node_t * n, char *last_method, int depth);
void match_left_comment(node_t * n, char *last_method, int depth);
void match_right_comment(node_t * n, char *last_method, int depth);
void match_inline_comment(node_t * n, char *last_method, int depth);
void match_end_of_line(node_t * n, char *last_method, int depth);
void match_catch_all(node_t * n, char *last_method, int depth);
node_t *match_function(char *data);
