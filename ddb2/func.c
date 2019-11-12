/********************************************
* Generated: 2019-11-11                    *
********************************************/
//#define DEBUG_START   1
//#define DEBUG_SUCCESS 1
//#define DEBUG_FAIL    1
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "headers/stack.h"
#include "headers/func.h"
// node values are only compared if string length is the same, no need to validate
// comparitors is against a precompiled value thats already case optimised
// returns 0 for equal
int stricmp(node_t * n, const char *b) {
  int d = 0;
  int b_len = strlen(b);
  //printf("Compare %s\n",b);
  for (int i = 0; i < b_len; i++) {
    if (n->pos + i > n->len)
      return -1;
    char c = n->value[i + n->pos];
    if (c >= 'A' && c <= 'Z') {
      d = (unsigned char) tolower(c) - (unsigned char) b[i];
    } else {
      d = (unsigned char) c - (unsigned char) b[i];
    }
    if (d != 0)
      return d;
  }
  return 0;
}
void print_sub_str(node_t * n, int start, int end) {
  printf("***");
  for (int i = start; i < end; i++) {
    if (n->value[i] == '\n') {
      printf("\n***", n->value[i]);
    } else {
      printf("%c", n->value[i]);
    }
  }
  printf("***");
}
void print_n(node_t * n) {
  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
}
int n_OK(node_t * n) {
  if (n->pos != -1 && n->OK == 1)
    return 1;
  return 0;
}
void increment_n(node_t * n, int len) {
  n->pos += len;
  if (n->pos >= n->len)
    n->pos = -1;
}
void debug_start(node_t * n, const char *name, int start_pos) {
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s]-> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
  //    printf("%s.",name);
}
void debug_success(node_t * n, const char *name, int start_pos) {
  //  printf("\n");
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] SUCCESS -> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
}
void debug_failed(node_t * n, const char *name, int start_pos) {
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] NO. -> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
}
void compare_string(node_t * n, const char *data, int length) {
  if (n_OK(n) == 1 && stricmp(n, data) == 0)
    increment_n(n, length);
  else
    n->OK = 0;
}
void optional_reset(node_t * n) {
  if (n->OK == 0) {
    n->OK = 1;
    n->pos = pop(n->stack);
  } else {
    pop(n->stack);
  }
}
void not_reset(node_t * n) {
  if (n->OK == 1) {
    n->OK = 0;
    n->pos = pop(n->stack);
  } else {
    n->OK = 1;
    pop(n->stack);
  }
}
void match_queries(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "queries";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //whitespace  queries queries
    //0
    //external -> 0
    match_whitespace(n, name, depth + 1);
    //select  queries queries
    //0
    //external -> 1
    match_select(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[queries] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_select(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "select";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //None  select select
  //0
  // order 0
  compare_string(n, (const char *) "select", 6);
  //whitespace  select select
  //0
  //external -> 1
  match_whitespace(n, name, depth + 1);
  //select_expr_list  select select
  //0
  //external -> 2
  match_select_expr_list(n, name, depth + 1);
  //whitespace  select select
  //0
  //external -> 3
  match_whitespace(n, name, depth + 1);
  // GROUP
  if (n_OK(n) == 1) {
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  select select
        //0
        // order 0
        compare_string(n, (const char *) "from", 4);
        //whitespace  select select
        //0
        //external -> 1
        match_whitespace(n, name, depth + 1);
        //identifier  select select
        //0
        //external -> 2
        match_identifier(n, name, depth + 1);
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            if (n_OK(n) == 1 && (1))
              increment_n(n, 1);
            else
              n->OK = 0;
            //identifier  select select
            //0
            //external -> 1
            match_identifier(n, name, depth + 1);

          }

          optional_reset(n);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  select select
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //None  select select
            //0
            // order 1
            compare_string(n, (const char *) "as", 2);
            //whitespace  select select
            //0
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //identifier  select select
            //0
            //external -> 3
            match_identifier(n, name, depth + 1);

          }

          optional_reset(n);
        }

      }

      optional_reset(n);
    }

  }
  //whitespace  select select
  //0
  //external -> 5
  match_whitespace(n, name, depth + 1);
  // GROUP
  if (n_OK(n) == 1) {
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  select select
        //0
        // order 0
        compare_string(n, (const char *) "where", 5);
        //one or more
        push(n->stack, n->pos);
        while (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  select select
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //expr  select select
            //0
            //external -> 1
            match_expr(n, name, depth + 1);

          }

          if (n->OK == 0)
            n->pos = pop(n->stack);
          else
            pop(n->stack);
        }
        if (n->pos == pop(n->stack)) {
          n->OK = 0;
        } else {
          n->OK = 1;
        }

      }

      optional_reset(n);
    }

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_select_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "select_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //expr  select_expr select_expr
    //0
    //external -> 0
    match_expr(n, name, depth + 1);
    //whitespace  select_expr select_expr
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  select_expr select_expr
        //0
        // order 0
        compare_string(n, (const char *) "as", 2);
        //whitespace  select_expr select_expr
        //0
        //external -> 1
        match_whitespace(n, name, depth + 1);
        //identifier  select_expr select_expr
        //0
        //external -> 2
        match_identifier(n, name, depth + 1);

      }

      optional_reset(n);
    }

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_select_expr_list(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "select_expr_list";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //select_expr  select_expr_list select_expr_list
  //0
  //external -> 0
  match_select_expr(n, name, depth + 1);
  // GROUP
  if (n_OK(n) == 1) {
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //whitespace  select_expr_list select_expr_list
        //0
        //external -> 0
        match_whitespace(n, name, depth + 1);
        if (n_OK(n) == 1 && (n->value[n->pos] == ','))
          increment_n(n, 1);
        else
          n->OK = 0;
        //whitespace  select_expr_list select_expr_list
        //0
        //external -> 2
        match_whitespace(n, name, depth + 1);
        //select_expr  select_expr_list select_expr_list
        //0
        //external -> 3
        match_select_expr(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select_expr_list] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_subquery(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "subquery";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //external -> None
      match_whitespace(n, name, depth + 1);

      optional_reset(n);
    }
    //select  subquery subquery
    //0
    //external -> 2
    match_select(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //external -> None
      match_whitespace(n, name, depth + 1);

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[subquery] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      // GROUP
      if (n_OK(n) == 1) {
        //expr  expr expr
        //2
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //external -> 1
        match_whitespace(n, name, depth + 1);
        // GROUP
        if (n_OK(n) == 1) {
          //OR
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
            //item 0
            // order 0
            compare_string(n, (const char *) "or", 2);
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            //item+1 1
            if (n->OK == 0) {
              n->OK = 1;
              // GROUP
              if (n_OK(n) == 1) {
                if (n_OK(n) == 1 && (n->value[n->pos] == '|'))
                  increment_n(n, 1);
                else
                  n->OK = 0;
                if (n_OK(n) == 1 && (n->value[n->pos] == '|'))
                  increment_n(n, 1);
                else
                  n->OK = 0;

              }

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }
            //item+1 2
            if (n->OK == 0) {
              n->OK = 1;
              // order 2
              compare_string(n, (const char *) "xor", 3);

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }
            //item+1 3
            if (n->OK == 0) {
              n->OK = 1;
              // order 3
              compare_string(n, (const char *) "and", 3);

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }
            //item+1 4
            if (n->OK == 0) {
              n->OK = 1;
              // order 4
              compare_string(n, (const char *) "&&", 2);

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }

            pop(n->stack);
          }

        }
        //whitespace  expr expr
        //2
        //external -> 3
        match_whitespace(n, name, depth + 1);
        //expr  expr expr
        //2
        //item 4  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          match_expr(n, name, depth + 1);
        }

      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //None  expr expr
        //1
        // order 0
        compare_string(n, (const char *) "not", 3);
        //whitespace  expr expr
        //1
        //external -> 1
        match_whitespace(n, name, depth + 1);
        //expr  expr expr
        //1
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //None  expr expr
        //1
        // order 0
        compare_string(n, (const char *) "!", 1);
        //whitespace  expr expr
        //1
        //external -> 1
        match_whitespace(n, name, depth + 1);
        //expr  expr expr
        //1
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //boolean_primary  expr expr
        //0
        //external -> 0
        match_boolean_primary(n, name, depth + 1);
        //whitespace  expr expr
        //0
        //external -> 1
        match_whitespace(n, name, depth + 1);
        //None  expr expr
        //0
        // order 2
        compare_string(n, (const char *) "IS", 2);
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  expr expr
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //None  expr expr
            //0
            // order 1
            compare_string(n, (const char *) "not", 3);

          }

          optional_reset(n);
        }
        //whitespace  expr expr
        //0
        //external -> 4
        match_whitespace(n, name, depth + 1);
        // GROUP
        if (n_OK(n) == 1) {
          //OR
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
            //item 0
            //external -> 0
            match_boolean(n, name, depth + 1);
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            //item+1 1
            if (n->OK == 0) {
              n->OK = 1;
              //external -> 1
              match_unknown(n, name, depth + 1);

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }

            pop(n->stack);
          }

        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 4
      match_boolean_primary(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif
  if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {    //recur
    push(n->stack, n->pos);
    match_expr(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = pop(n->stack);
      n->OK = 1;
    } else {
      pop(n->stack);
    }
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_boolean_primary(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "boolean_primary";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //boolean_primary  boolean_primary boolean_primary
      //1
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      //whitespace  boolean_primary boolean_primary
      //1
      //external -> 1
      match_whitespace(n, name, depth + 1);
      // GROUP
      if (n_OK(n) == 1) {
        //OR
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //item 0
          // GROUP
          if (n_OK(n) == 1) {
            // GROUP
            if (n_OK(n) == 1) {
              //comparison_operator  boolean_primary boolean_primary
              //0
              //external -> 0
              match_comparison_operator(n, name, depth + 1);
              //whitespace  boolean_primary boolean_primary
              //0
              //external -> 1
              match_whitespace(n, name, depth + 1);
              //predicate  boolean_primary boolean_primary
              //0
              //external -> 2
              match_predicate(n, name, depth + 1);

            }

          }
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            // GROUP
            if (n_OK(n) == 1) {
              //None  boolean_primary boolean_primary
              //0
              // order 0
              compare_string(n, (const char *) "is", 2);
              //optional
              if (n_OK(n) == 1) {
                push(n->stack, n->pos);
                // GROUP
                if (n_OK(n) == 1) {
                  //whitespace  boolean_primary boolean_primary
                  //0
                  //external -> 0
                  match_whitespace(n, name, depth + 1);
                  //None  boolean_primary boolean_primary
                  //0
                  // order 1
                  compare_string(n, (const char *) "not", 3);

                }

                optional_reset(n);
              }
              //whitespace  boolean_primary boolean_primary
              //0
              //external -> 2
              match_whitespace(n, name, depth + 1);
              //null  boolean_primary boolean_primary
              //0
              //external -> 3
              match_null(n, name, depth + 1);

            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 2
          if (n->OK == 0) {
            n->OK = 1;
            // GROUP
            if (n_OK(n) == 1) {
              //None  boolean_primary boolean_primary
              //0
              // order 0
              compare_string(n, (const char *) "<=>", 3);
              //whitespace  boolean_primary boolean_primary
              //0
              //external -> 1
              match_whitespace(n, name, depth + 1);
              //predicate  boolean_primary boolean_primary
              //0
              //external -> 2
              match_predicate(n, name, depth + 1);

            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 3
          if (n->OK == 0) {
            n->OK = 1;
            // GROUP
            if (n_OK(n) == 1) {
              //comparison_operator  boolean_primary boolean_primary
              //0
              //external -> 0
              match_comparison_operator(n, name, depth + 1);
              //whitespace  boolean_primary boolean_primary
              //0
              //external -> 1
              match_whitespace(n, name, depth + 1);
              // GROUP
              if (n_OK(n) == 1) {
                //OR
                if (n_OK(n) == 1) {
                  push(n->stack, n->pos);
                  //item 0
                  // order 0
                  compare_string(n, (const char *) "all", 3);
                  if (n->OK == 0) {
                    n->pos = peek(n->stack);
                  }
                  //item+1 1
                  if (n->OK == 0) {
                    n->OK = 1;
                    // order 1
                    compare_string(n, (const char *) "any", 3);

                    if (n->OK == 0) {
                      n->pos = peek(n->stack);
                    }
                  }

                  pop(n->stack);
                }

              }
              //whitespace  boolean_primary boolean_primary
              //0
              //external -> 3
              match_whitespace(n, name, depth + 1);
              //subquery  boolean_primary boolean_primary
              //0
              //external -> 4
              match_subquery(n, name, depth + 1);

            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }

          pop(n->stack);
        }

      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_predicate(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[boolean_primary] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif
  if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {    //recur
    push(n->stack, n->pos);
    match_boolean_primary(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = pop(n->stack);
      n->OK = 1;
    } else {
      pop(n->stack);
    }
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_predicate(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "predicate";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //bit_expr  predicate predicate
  //1
  //external -> 0
  match_bit_expr(n, name, depth + 1);
  //optional
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // GROUP
    if (n_OK(n) == 1) {
      //OR
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        //item 0
        // GROUP
        if (n_OK(n) == 1) {
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  predicate predicate
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // order None
              compare_string(n, (const char *) "not", 3);

              optional_reset(n);
            }
            //whitespace  predicate predicate
            //0
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //0
            // order 3
            compare_string(n, (const char *) "in", 2);
            //whitespace  predicate predicate
            //0
            //external -> 4
            match_whitespace(n, name, depth + 1);
            //subquery  predicate predicate
            //0
            //external -> 5
            match_subquery(n, name, depth + 1);

          }

        }
        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
        //item+1 1
        if (n->OK == 0) {
          n->OK = 1;
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  predicate predicate
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // order None
              compare_string(n, (const char *) "not", 3);

              optional_reset(n);
            }
            //whitespace  predicate predicate
            //0
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //0
            // order 3
            compare_string(n, (const char *) "in", 2);
            //whitespace  predicate predicate
            //0
            //external -> 4
            match_whitespace(n, name, depth + 1);
            if (n_OK(n) == 1 && (n->value[n->pos] == '('))
              increment_n(n, 1);
            else
              n->OK = 0;

            //expr  predicate predicate
            //0
            //external -> 6
            match_expr(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // GROUP
              if (n_OK(n) == 1) {
                //zero or more
                push(n->stack, n->OK);
                while (n_OK(n) == 1) {
                  push(n->stack, n->pos);
                  // GROUP
                  if (n_OK(n) == 1) {
                    //whitespace  predicate predicate
                    //0
                    //external -> 0
                    match_whitespace(n, name, depth + 1);
                    if (n_OK(n) == 1 && (n->value[n->pos] == ','))
                      increment_n(n, 1);
                    else
                      n->OK = 0;
                    //whitespace  predicate predicate
                    //0
                    //external -> 2
                    match_whitespace(n, name, depth + 1);
                    //expr  predicate predicate
                    //0
                    //external -> 3
                    match_expr(n, name, depth + 1);

                  }

                  if (n->OK == 0) {
                    n->pos = pop(n->stack);
                  } else
                    pop(n->stack);
                }
                n->OK = pop(n->stack);

              }

              optional_reset(n);
            }
            if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
              increment_n(n, 1);
            else
              n->OK = 0;

          }

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
        }
        //item+1 2
        if (n->OK == 0) {
          n->OK = 1;
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  predicate predicate
            //1
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // order None
              compare_string(n, (const char *) "not", 3);

              optional_reset(n);
            }
            //whitespace  predicate predicate
            //1
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //1
            // order 3
            compare_string(n, (const char *) "between", 7);
            //whitespace  predicate predicate
            //1
            //external -> 4
            match_whitespace(n, name, depth + 1);
            //bit_expr  predicate predicate
            //1
            //external -> 5
            match_bit_expr(n, name, depth + 1);
            //whitespace  predicate predicate
            //1
            //external -> 6
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //1
            // order 7
            compare_string(n, (const char *) "and", 3);
            //whitespace  predicate predicate
            //1
            //external -> 8
            match_whitespace(n, name, depth + 1);
            //predicate  predicate predicate
            //1
            //item 9  //non index 0 recursion
            if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
              match_predicate(n, name, depth + 1);
            }

          }

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
        }
        //item+1 3
        if (n->OK == 0) {
          n->OK = 1;
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  predicate predicate
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // order None
              compare_string(n, (const char *) "not", 3);

              optional_reset(n);
            }
            //whitespace  predicate predicate
            //0
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //0
            // order 3
            compare_string(n, (const char *) "like", 4);
            //whitespace  predicate predicate
            //0
            //external -> 4
            match_whitespace(n, name, depth + 1);
            //simple_expr  predicate predicate
            //0
            //external -> 5
            match_simple_expr(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // GROUP
              if (n_OK(n) == 1) {
                //whitespace  predicate predicate
                //0
                //external -> 0
                match_whitespace(n, name, depth + 1);
                //None  predicate predicate
                //0
                // order 1
                compare_string(n, (const char *) "escape", 6);
                //whitespace  predicate predicate
                //0
                //external -> 2
                match_whitespace(n, name, depth + 1);
                //simple_expr  predicate predicate
                //0
                //external -> 3
                match_simple_expr(n, name, depth + 1);

              }

              optional_reset(n);
            }

          }

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
        }
        //item+1 4
        if (n->OK == 0) {
          n->OK = 1;
          // GROUP
          if (n_OK(n) == 1) {
            //whitespace  predicate predicate
            //0
            //external -> 0
            match_whitespace(n, name, depth + 1);
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // order None
              compare_string(n, (const char *) "not", 3);

              optional_reset(n);
            }
            //whitespace  predicate predicate
            //0
            //external -> 2
            match_whitespace(n, name, depth + 1);
            //None  predicate predicate
            //0
            // order 3
            compare_string(n, (const char *) "regexp", 6);
            //whitespace  predicate predicate
            //0
            //external -> 4
            match_whitespace(n, name, depth + 1);
            //bit_expr  predicate predicate
            //0
            //external -> 5
            match_bit_expr(n, name, depth + 1);

          }

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
        }

        pop(n->stack);
      }

    }

    optional_reset(n);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[predicate] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif
  if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {    //recur
    push(n->stack, n->pos);
    match_predicate(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = pop(n->stack);
      n->OK = 1;
    } else {
      pop(n->stack);
    }
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_bit_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "bit_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //bit_expr  bit_expr bit_expr
      //2
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      //whitespace  bit_expr bit_expr
      //2
      //external -> 1
      match_whitespace(n, name, depth + 1);
      //operations  bit_expr bit_expr
      //2
      //external -> 2
      match_operations(n, name, depth + 1);
      //whitespace  bit_expr bit_expr
      //2
      //external -> 3
      match_whitespace(n, name, depth + 1);
      //bit_expr  bit_expr bit_expr
      //2
      //item 4  //non index 0 recursion
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
        match_bit_expr(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //bit_expr  bit_expr bit_expr
        //1
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  bit_expr bit_expr
        //1
        //external -> 1
        match_whitespace(n, name, depth + 1);
        if (n_OK(n) == 1 && (n->value[n->pos] == '+' || n->value[n->pos] == '-'))
          increment_n(n, 1);
        else
          n->OK = 0;
        //whitespace  bit_expr bit_expr
        //1
        //external -> 3
        match_whitespace(n, name, depth + 1);
        //interval_expr  bit_expr bit_expr
        //1
        //external -> 4
        match_interval_expr(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 2
      match_simple_expr(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bit_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif
  if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {    //recur
    push(n->stack, n->pos);
    match_bit_expr(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = pop(n->stack);
      n->OK = 1;
    } else {
      pop(n->stack);
    }
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_operations(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "operations";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    if (n_OK(n) == 1 && (n->value[n->pos] == '|'))
      increment_n(n, 1);
    else
      n->OK = 0;
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '&'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '<'))
          increment_n(n, 1);
        else
          n->OK = 0;
        if (n_OK(n) == 1 && (n->value[n->pos] == '<'))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '>'))
          increment_n(n, 1);
        else
          n->OK = 0;
        if (n_OK(n) == 1 && (n->value[n->pos] == '>'))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '+'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '-'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '*'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '/'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // order 8
      compare_string(n, (const char *) "div", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // order 9
      compare_string(n, (const char *) "mod", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '%'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '^'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[operations] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_identifier_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "identifier_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //identifier  identifier_expr identifier_expr
    //0
    //external -> 0
    match_identifier(n, name, depth + 1);
    //None  identifier_expr identifier_expr
    //0
    // order 1
    compare_string(n, (const char *) "as", 2);
    //identifier  identifier_expr identifier_expr
    //0
    //external -> 2
    match_identifier(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[identifier_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_simple_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "simple_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_literal(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_identifier(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 2
      match_subquery(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 3
      match_identifier_expr(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 4
      match_interval_expr(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[simple_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_literal(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "literal";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_hex(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_bit(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 2
      match_boolean(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 3
      match_null(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 4
      match_string(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 5
      match_real(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[literal] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_interval_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "interval_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // order 0
    compare_string(n, (const char *) "MICROSECOND", 11);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // order 1
      compare_string(n, (const char *) "SECOND", 6);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // order 2
      compare_string(n, (const char *) "MINUTE", 6);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // order 3
      compare_string(n, (const char *) "HOUR", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // order 4
      compare_string(n, (const char *) "DAY", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // order 5
      compare_string(n, (const char *) "WEEK", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // order 6
      compare_string(n, (const char *) "MONTH", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // order 7
      compare_string(n, (const char *) "QUARTER", 7);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // order 8
      compare_string(n, (const char *) "YEAR", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // order 9
      compare_string(n, (const char *) "SECOND_MICROSECOND", 18);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      // order 10
      compare_string(n, (const char *) "MINUTE_MICROSECOND", 18);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      // order 11
      compare_string(n, (const char *) "MINUTE_SECOND", 13);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      // order 12
      compare_string(n, (const char *) "HOUR_MICROSECOND", 16);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      // order 13
      compare_string(n, (const char *) "HOUR_SECOND", 11);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      // order 14
      compare_string(n, (const char *) "HOUR_MINUTE", 11);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      // order 15
      compare_string(n, (const char *) "DAY_MICROSECOND", 15);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 16
    if (n->OK == 0) {
      n->OK = 1;
      // order 16
      compare_string(n, (const char *) "DAY_SECOND", 10);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 17
    if (n->OK == 0) {
      n->OK = 1;
      // order 17
      compare_string(n, (const char *) "DAY_MINUTE", 10);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 18
    if (n->OK == 0) {
      n->OK = 1;
      // order 18
      compare_string(n, (const char *) "DAY_HOUR", 8);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 19
    if (n->OK == 0) {
      n->OK = 1;
      // order 19
      compare_string(n, (const char *) "YEAR_MONTH", 10);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[interval_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_YEARS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "YEARS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  YEARS YEARS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEARS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_QUARTERS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "QUARTERS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  QUARTERS QUARTERS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTERS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MONTHS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MONTHS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  MONTHS MONTHS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTHS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_WEEKS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "WEEKS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  WEEKS WEEKS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAYS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAYS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  DAYS DAYS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOURS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOURS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  HOURS HOURS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOURS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MINUTES(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MINUTES";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  MINUTES MINUTES
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTES] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SECONDS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SECONDS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  SECONDS SECONDS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECONDS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MICROSECONDS(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MICROSECONDS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //unsigned_int  MICROSECONDS MICROSECONDS
  //0
  //external -> 0
  match_unsigned_int(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECONDS] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MICROSECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //MICROSECONDS  MICROSECOND MICROSECOND
    //0
    //external -> 0
    match_MICROSECONDS(n, name, depth + 1);
    //whitespace  MICROSECOND MICROSECOND
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  MICROSECOND MICROSECOND
    //0
    // order 2
    compare_string(n, (const char *) "MICROSECOND", 11);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //SECONDS  SECOND SECOND
    //0
    //external -> 0
    match_SECONDS(n, name, depth + 1);
    //whitespace  SECOND SECOND
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  SECOND SECOND
    //0
    // order 2
    compare_string(n, (const char *) "SECOND", 6);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MINUTE(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //MINUTES  MINUTE MINUTE
    //0
    //external -> 0
    match_MINUTES(n, name, depth + 1);
    //whitespace  MINUTE MINUTE
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  MINUTE MINUTE
    //0
    // order 2
    compare_string(n, (const char *) "MINUTE", 6);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOUR(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOUR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //HOURS  HOUR HOUR
    //0
    //external -> 0
    match_HOURS(n, name, depth + 1);
    //whitespace  HOUR HOUR
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  HOUR HOUR
    //0
    // order 2
    compare_string(n, (const char *) "HOUR", 4);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //DAYS  DAY DAY
    //0
    //external -> 0
    match_DAYS(n, name, depth + 1);
    //whitespace  DAY DAY
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  DAY DAY
    //0
    // order 2
    compare_string(n, (const char *) "DAY", 3);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_WEEK(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "WEEK";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //WEEKS  WEEK WEEK
    //0
    //external -> 0
    match_WEEKS(n, name, depth + 1);
    //whitespace  WEEK WEEK
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  WEEK WEEK
    //0
    // order 2
    compare_string(n, (const char *) "WEEK", 4);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEK] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MONTH(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MONTH";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //MONTHS  MONTH MONTH
    //0
    //external -> 0
    match_MONTHS(n, name, depth + 1);
    //whitespace  MONTH MONTH
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  MONTH MONTH
    //0
    // order 2
    compare_string(n, (const char *) "MONTH", 5);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTH] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_QUARTER(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "QUARTER";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //QUARTERS  QUARTER QUARTER
    //0
    //external -> 0
    match_QUARTERS(n, name, depth + 1);
    //whitespace  QUARTER QUARTER
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  QUARTER QUARTER
    //0
    // order 2
    compare_string(n, (const char *) "QUARTER", 7);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTER] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_YEAR(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "YEAR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //YEARS  YEAR YEAR
    //0
    //external -> 0
    match_YEARS(n, name, depth + 1);
    //whitespace  YEAR YEAR
    //0
    //external -> 1
    match_whitespace(n, name, depth + 1);
    //None  YEAR YEAR
    //0
    // order 2
    compare_string(n, (const char *) "YEAR", 4);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SECOND_MICROSECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SECOND_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  SECOND_MICROSECOND SECOND_MICROSECOND
    //0
    //external -> 1
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (1))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MICROSECONDS  SECOND_MICROSECOND SECOND_MICROSECOND
    //0
    //external -> 3
    match_MICROSECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  SECOND_MICROSECOND SECOND_MICROSECOND
    //0
    //external -> 5
    match_whitespace(n, name, depth + 1);
    //None  SECOND_MICROSECOND SECOND_MICROSECOND
    //0
    // order 6
    compare_string(n, (const char *) "SECOND_MICROSECOND", 18);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND_MICROSECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MINUTE_MICROSECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MINUTE_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  MINUTE_MICROSECOND MINUTE_MICROSECOND
    //0
    //external -> 1
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  MINUTE_MICROSECOND MINUTE_MICROSECOND
    //0
    //external -> 3
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (1))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MICROSECONDS  MINUTE_MICROSECOND MINUTE_MICROSECOND
    //0
    //external -> 5
    match_MICROSECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  MINUTE_MICROSECOND MINUTE_MICROSECOND
    //0
    //external -> 7
    match_whitespace(n, name, depth + 1);
    //None  MINUTE_MICROSECOND MINUTE_MICROSECOND
    //0
    // order 8
    compare_string(n, (const char *) "MINUTE_MICROSECOND", 18);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_MICROSECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MINUTE_SECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MINUTE_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  MINUTE_SECOND MINUTE_SECOND
    //0
    //external -> 1
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  MINUTE_SECOND MINUTE_SECOND
    //0
    //external -> 3
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  MINUTE_SECOND MINUTE_SECOND
    //0
    //external -> 5
    match_whitespace(n, name, depth + 1);
    //None  MINUTE_SECOND MINUTE_SECOND
    //0
    // order 6
    compare_string(n, (const char *) "MINUTE_SECOND", 13);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_SECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOUR_MICROSECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOUR_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //HOURS  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    //external -> 1
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    //external -> 3
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    //external -> 5
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (1))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MICROSECONDS  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    //external -> 7
    match_MICROSECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    //external -> 9
    match_whitespace(n, name, depth + 1);
    //None  HOUR_MICROSECOND HOUR_MICROSECOND
    //0
    // order 10
    compare_string(n, (const char *) "HOUR_MICROSECOND", 16);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_MICROSECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOUR_SECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOUR_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //HOURS  HOUR_SECOND HOUR_SECOND
    //0
    //external -> 1
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  HOUR_SECOND HOUR_SECOND
    //0
    //external -> 3
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  HOUR_SECOND HOUR_SECOND
    //0
    //external -> 5
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  HOUR_SECOND HOUR_SECOND
    //0
    //external -> 7
    match_whitespace(n, name, depth + 1);
    //None  HOUR_SECOND HOUR_SECOND
    //0
    // order 8
    compare_string(n, (const char *) "HOUR_SECOND", 11);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_SECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOUR_MINUTE(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOUR_MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //HOURS  HOUR_MINUTE HOUR_MINUTE
    //0
    //external -> 1
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  HOUR_MINUTE HOUR_MINUTE
    //0
    //external -> 3
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  HOUR_MINUTE HOUR_MINUTE
    //0
    //external -> 5
    match_whitespace(n, name, depth + 1);
    //None  HOUR_MINUTE HOUR_MINUTE
    //0
    // order 6
    compare_string(n, (const char *) "HOUR_MINUTE", 11);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_MINUTE] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY_MICROSECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //DAYS  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 1
    match_DAYS(n, name, depth + 1);
    //HOURS  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 2
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 4
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 6
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (1))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MICROSECONDS  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 8
    match_MICROSECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  DAY_MICROSECOND DAY_MICROSECOND
    //0
    //external -> 10
    match_whitespace(n, name, depth + 1);
    //None  DAY_MICROSECOND DAY_MICROSECOND
    //0
    // order 11
    compare_string(n, (const char *) "DAY_MICROSECOND", 15);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_MICROSECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY_SECOND(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //DAYS  DAY_SECOND DAY_SECOND
    //0
    //external -> 1
    match_DAYS(n, name, depth + 1);
    //HOURS  DAY_SECOND DAY_SECOND
    //0
    //external -> 2
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  DAY_SECOND DAY_SECOND
    //0
    //external -> 4
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //SECONDS  DAY_SECOND DAY_SECOND
    //0
    //external -> 6
    match_SECONDS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  DAY_SECOND DAY_SECOND
    //0
    //external -> 8
    match_whitespace(n, name, depth + 1);
    //None  DAY_SECOND DAY_SECOND
    //0
    // order 9
    compare_string(n, (const char *) "DAY_SECOND", 10);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_SECOND] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY_MINUTE(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY_MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //DAYS  DAY_MINUTE DAY_MINUTE
    //0
    //external -> 1
    match_DAYS(n, name, depth + 1);
    //HOURS  DAY_MINUTE DAY_MINUTE
    //0
    //external -> 2
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ':'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //MINUTES  DAY_MINUTE DAY_MINUTE
    //0
    //external -> 4
    match_MINUTES(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  DAY_MINUTE DAY_MINUTE
    //0
    //external -> 6
    match_whitespace(n, name, depth + 1);
    //None  DAY_MINUTE DAY_MINUTE
    //0
    // order 7
    compare_string(n, (const char *) "DAY_MINUTE", 10);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_MINUTE] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY_HOUR(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY_HOUR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //DAYS  DAY_HOUR DAY_HOUR
    //0
    //external -> 1
    match_DAYS(n, name, depth + 1);
    //HOURS  DAY_HOUR DAY_HOUR
    //0
    //external -> 2
    match_HOURS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  DAY_HOUR DAY_HOUR
    //0
    //external -> 4
    match_whitespace(n, name, depth + 1);
    //None  DAY_HOUR DAY_HOUR
    //0
    // order 5
    compare_string(n, (const char *) "DAY_HOUR", 8);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_HOUR] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_YEAR_MONTH(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "YEAR_MONTH";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //YEARS  YEAR_MONTH YEAR_MONTH
    //0
    //external -> 1
    match_YEARS(n, name, depth + 1);
    //None  YEAR_MONTH YEAR_MONTH
    //0
    // order 2
    compare_string(n, (const char *) "-", 1);
    //MONTHS  YEAR_MONTH YEAR_MONTH
    //0
    //external -> 3
    match_MONTHS(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //whitespace  YEAR_MONTH YEAR_MONTH
    //0
    //external -> 5
    match_whitespace(n, name, depth + 1);
    //None  YEAR_MONTH YEAR_MONTH
    //0
    // order 6
    compare_string(n, (const char *) "YEAR_MONTH", 10);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR_MONTH] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_unknown(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "unknown";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //None  unknown unknown
  //0
  // order 0
  compare_string(n, (const char *) "unknown", 7);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unknown] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_hex(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "hex";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '0'))
    increment_n(n, 1);
  else
    n->OK = 0;
  if (n_OK(n) == 1 && (n->value[n->pos] == 'x' || n->value[n->pos] == 'X'))
    increment_n(n, 1);
  else
    n->OK = 0;
  //one or more
  push(n->stack, n->pos);
  while (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1
        && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9') || (n->value[n->pos] >= 'A' && n->value[n->pos] <= 'F')
            || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'f')))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n->OK == 0)
      n->pos = pop(n->stack);
    else
      pop(n->stack);
  }
  if (n->pos == pop(n->stack)) {
    n->OK = 0;
  } else {
    n->OK = 1;
  }

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[hex] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_bit(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "bit";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '0'))
    increment_n(n, 1);
  else
    n->OK = 0;
  if (n_OK(n) == 1 && (n->value[n->pos] == 'b'))
    increment_n(n, 1);
  else
    n->OK = 0;
  //one or more
  push(n->stack, n->pos);
  while (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && (n->value[n->pos] == '0' || n->value[n->pos] == '1'))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n->OK == 0)
      n->pos = pop(n->stack);
    else
      pop(n->stack);
  }
  if (n->pos == pop(n->stack)) {
    n->OK = 0;
  } else {
    n->OK = 1;
  }

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bit] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_null(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "null";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // order 0
    compare_string(n, (const char *) "null", 4);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // order 1
      compare_string(n, (const char *) "NULL", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[null] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_true(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "true";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // order 0
    compare_string(n, (const char *) "true", 4);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // order 1
      compare_string(n, (const char *) "TRUE", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[true] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_false(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "false";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // order 0
    compare_string(n, (const char *) "false", 5);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // order 1
      compare_string(n, (const char *) "FALSE", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[false] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_boolean(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "boolean";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_true(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_false(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[boolean] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_real(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "real";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //integer  real real
      //0
      //external -> 0
      match_integer(n, name, depth + 1);
      if (n_OK(n) == 1 && (1))
        increment_n(n, 1);
      else
        n->OK = 0;
      //unsigned_int  real real
      //0
      //external -> 2
      match_unsigned_int(n, name, depth + 1);

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (1))
          increment_n(n, 1);
        else
          n->OK = 0;
        //unsigned_int  real real
        //0
        //external -> 1
        match_unsigned_int(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //integer  real real
        //0
        //external -> 0
        match_integer(n, name, depth + 1);
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //external -> None
          match_exponent(n, name, depth + 1);

          optional_reset(n);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[real] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_integer(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "integer";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_signed_int(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_unsigned_int(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[integer] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_signed_int(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "signed_int";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //sign  signed_int signed_int
    //0
    //external -> 0
    match_sign(n, name, depth + 1);
    //unsigned_int  signed_int signed_int
    //0
    //external -> 1
    match_unsigned_int(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[signed_int] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_unsigned_int(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "unsigned_int";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //one or more
  push(n->stack, n->pos);
  while (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9')))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n->OK == 0)
      n->pos = pop(n->stack);
    else
      pop(n->stack);
  }
  if (n->pos == pop(n->stack)) {
    n->OK = 0;
  } else {
    n->OK = 1;
  }

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unsigned_int] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_sign(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "sign";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '-' || n->value[n->pos] == '+'))
    increment_n(n, 1);
  else
    n->OK = 0;

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[sign] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_exponent(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "exponent";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == 'E' || n->value[n->pos] == 'e'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //integer  exponent exponent
    //0
    //external -> 1
    match_integer(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[exponent] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_identifier(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "identifier";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //NOT
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //external -> None
    match_keywords(n, name, depth + 1);

    not_reset(n);
  }                             //end NOT
  //one or more
  push(n->stack, n->pos);
  while (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1
        && ((n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z')
            || (n->value[n->pos] >= '0' && n->value[n->pos] <= '9') || n->value[n->pos] == '$' || n->value[n->pos] == '_'))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n->OK == 0)
      n->pos = pop(n->stack);
    else
      pop(n->stack);
  }
  if (n->pos == pop(n->stack)) {
    n->OK = 0;
  } else {
    n->OK = 1;
  }

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[identifier] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_keywords(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "keywords";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // order 0
    compare_string(n, (const char *) "select", 6);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // order 1
      compare_string(n, (const char *) "from", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // order 2
      compare_string(n, (const char *) "on", 2);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // order 3
      compare_string(n, (const char *) "where", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // order 4
      compare_string(n, (const char *) "and", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // order 5
      compare_string(n, (const char *) "or", 2);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // order 6
      compare_string(n, (const char *) "xor", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // order 7
      compare_string(n, (const char *) "limit", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // order 8
      compare_string(n, (const char *) "having", 6);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // order 9
      compare_string(n, (const char *) "group", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      // order 10
      compare_string(n, (const char *) "by", 2);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      // order 11
      compare_string(n, (const char *) "order", 5);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      // order 12
      compare_string(n, (const char *) "not", 3);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      // order 13
      compare_string(n, (const char *) "in", 2);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      // order 14
      compare_string(n, (const char *) "between", 7);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      // order 15
      compare_string(n, (const char *) "like", 4);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[keywords] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_whitespace(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "whitespace";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //OR
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //item 0
          if (n_OK(n) == 1 && (n->value[n->pos] == '\t' || n->value[n->pos] == ' ' || n->value[n->pos] == '\n' || n->value[n->pos] == '\r'))
            increment_n(n, 1);
          else
            n->OK = 0;
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            //external -> 1
            match_comment(n, name, depth + 1);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }

          pop(n->stack);
        }

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[whitespace] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_string(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_single_quote_string(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_double_quote_string(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[string] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_single_quote_string(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "single_quote_string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] != '\''))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0)
        n->pos = pop(n->stack);
      else
        pop(n->stack);
    }
    if (n->pos == pop(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\''))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[single_quote_string] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_double_quote_string(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "double_quote_string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '"'))
      increment_n(n, 1);
    else
      n->OK = 0;
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] != '"'))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0)
        n->pos = pop(n->stack);
      else
        pop(n->stack);
    }
    if (n->pos == pop(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '"'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[double_quote_string] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_query_delimiter(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "query_delimiter";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == ';'))
    increment_n(n, 1);
  else
    n->OK = 0;

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[query_delimiter] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_comparison_operator(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "comparison_operator";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    if (n_OK(n) == 1 && (n->value[n->pos] == '='))
      increment_n(n, 1);
    else
      n->OK = 0;
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        // GROUP
        if (n_OK(n) == 1) {
          if (n_OK(n) == 1 && (n->value[n->pos] == '<'))
            increment_n(n, 1);
          else
            n->OK = 0;
          if (n_OK(n) == 1 && (n->value[n->pos] == '>'))
            increment_n(n, 1);
          else
            n->OK = 0;

        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        // GROUP
        if (n_OK(n) == 1) {
          if (n_OK(n) == 1 && (n->value[n->pos] == '>'))
            increment_n(n, 1);
          else
            n->OK = 0;
          if (n_OK(n) == 1 && (n->value[n->pos] == '='))
            increment_n(n, 1);
          else
            n->OK = 0;

        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        // GROUP
        if (n_OK(n) == 1) {
          if (n_OK(n) == 1 && (n->value[n->pos] == '<'))
            increment_n(n, 1);
          else
            n->OK = 0;
          if (n_OK(n) == 1 && (n->value[n->pos] == '='))
            increment_n(n, 1);
          else
            n->OK = 0;

        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        // GROUP
        if (n_OK(n) == 1) {
          if (n_OK(n) == 1 && (n->value[n->pos] == '!'))
            increment_n(n, 1);
          else
            n->OK = 0;
          if (n_OK(n) == 1 && (n->value[n->pos] == '='))
            increment_n(n, 1);
          else
            n->OK = 0;

        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '>'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      if (n_OK(n) == 1 && (n->value[n->pos] == '<'))
        increment_n(n, 1);
      else
        n->OK = 0;

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[comparison_operator] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_block_comment(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_single_comment(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_block_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "block_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //left_comment  block_comment block_comment
    //0
    //external -> 0
    match_left_comment(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //external -> None
          match_right_comment(n, name, depth + 1);

          not_reset(n);
        }                       //end NOT
        if (n_OK(n) == 1 && (1))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    //right_comment  block_comment block_comment
    //0
    //external -> 2
    match_right_comment(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[block_comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_single_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "single_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //inline_comment  single_comment single_comment
    //0
    //external -> 0
    match_inline_comment(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //external -> None
          match_end_of_line(n, name, depth + 1);

          not_reset(n);
        }                       //end NOT
        if (n_OK(n) == 1 && (1))
          increment_n(n, 1);
        else
          n->OK = 0;

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    //end_of_line  single_comment single_comment
    //0
    //external -> 2
    match_end_of_line(n, name, depth + 1);

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[single_comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_left_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "left_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '/'))
    increment_n(n, 1);
  else
    n->OK = 0;
  if (n_OK(n) == 1 && (n->value[n->pos] == '*'))
    increment_n(n, 1);
  else
    n->OK = 0;

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[left_comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_right_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "right_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '*'))
    increment_n(n, 1);
  else
    n->OK = 0;
  if (n_OK(n) == 1 && (n->value[n->pos] == '/'))
    increment_n(n, 1);
  else
    n->OK = 0;

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[right_comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_inline_comment(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "inline_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '-'))
    increment_n(n, 1);
  else
    n->OK = 0;
  if (n_OK(n) == 1 && (n->value[n->pos] == '-'))
    increment_n(n, 1);
  else
    n->OK = 0;

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[inline_comment] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_end_of_line(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "end_of_line";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  if (n_OK(n) == 1 && (n->value[n->pos] == '\n'))
    increment_n(n, 1);
  else
    n->OK = 0;
  //optional
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\r'))
      increment_n(n, 1);
    else
      n->OK = 0;

    optional_reset(n);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[end_of_line] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ABS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ABS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ABS_FUNC ABS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ABS", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  ABS_FUNC ABS_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ABS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ACOS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ACOS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ACOS_FUNC ACOS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ACOS", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  ACOS_FUNC ACOS_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ACOS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ADDDATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ADDDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ADDDATE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "INTERVAL", 8);
    //interval_expr  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //external -> 5
    match_interval_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ADDDATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ADDTIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ADDTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ADDTIME_FUNC ADDTIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ADDTIME", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    //None  ADDTIME_FUNC ADDTIME_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //expr  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //external -> 4
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ADDTIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ASCII_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ASCII_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ASCII_FUNC ASCII_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ASCII", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  ASCII_FUNC ASCII_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ASCII_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ASIN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ASIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ASIN_FUNC ASIN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ASIN", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  ASIN_FUNC ASIN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ASIN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ATAN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ATAN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ATAN_FUNC ATAN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ATAN", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  ATAN_FUNC ATAN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ATAN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ATAN2_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ATAN2_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ATAN2", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    // order 2
    compare_string(n, (const char *) "Y", 1);
    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //X  ATAN2_FUNC ATAN2_FUNC
    //0
    //external -> 4
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ATAN2_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_BIN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "BIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  BIN_FUNC BIN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "BIN", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  BIN_FUNC BIN_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[BIN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_BIT_LENGTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "BIT_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  BIT_LENGTH_FUNC BIT_LENGTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "BIT_LENGTH", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  BIT_LENGTH_FUNC BIT_LENGTH_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[BIT_LENGTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CEILING_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CEILING_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CEILING_FUNC CEILING_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CEILING", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  CEILING_FUNC CEILING_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CEILING_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CEIL_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CEIL_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CEIL_FUNC CEIL_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CEIL", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  CEIL_FUNC CEIL_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CEIL_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CHARACTER_LENGTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CHARACTER_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CHARACTER_LENGTH_FUNC CHARACTER_LENGTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CHARACTER_LENGTH", 16);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  CHARACTER_LENGTH_FUNC CHARACTER_LENGTH_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHARACTER_LENGTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CHAR_LENGTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CHAR_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CHAR_LENGTH_FUNC CHAR_LENGTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CHAR_LENGTH", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  CHAR_LENGTH_FUNC CHAR_LENGTH_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHAR_LENGTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CHAR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CHAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CHAR_FUNC CHAR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CHAR", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  CHAR_FUNC CHAR_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  CHAR_FUNC CHAR_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //N  CHAR_FUNC CHAR_FUNC
        //0
        //external -> 1
        match_N(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  CHAR_FUNC CHAR_FUNC
        //0
        // order 0
        compare_string(n, (const char *) "USING", 5);
        //charset_name  CHAR_FUNC CHAR_FUNC
        //0
        //external -> 1
        match_charset_name(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHAR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CONCAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CONCAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CONCAT_FUNC CONCAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CONCAT", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  CONCAT_FUNC CONCAT_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  CONCAT_FUNC CONCAT_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //string  CONCAT_FUNC CONCAT_FUNC
        //0
        //external -> 1
        match_string(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONCAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CONCAT_WS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CONCAT_WS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CONCAT_WS_FUNC CONCAT_WS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CONCAT_WS", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //separator  CONCAT_WS_FUNC CONCAT_WS_FUNC
    //0
    //external -> 2
    match_separator(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  CONCAT_WS_FUNC CONCAT_WS_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //string  CONCAT_WS_FUNC CONCAT_WS_FUNC
        //0
        //external -> 1
        match_string(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONCAT_WS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CONVERT_TZ_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CONVERT_TZ_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CONVERT_TZ", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //dt  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //external -> 2
    match_dt(n, name, depth + 1);
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //from_tz  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //external -> 4
    match_from_tz(n, name, depth + 1);
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //to_tz  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //external -> 6
    match_to_tz(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONVERT_TZ_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CONV_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CONV_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CONV_FUNC CONV_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CONV", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  CONV_FUNC CONV_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    //None  CONV_FUNC CONV_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //from_base  CONV_FUNC CONV_FUNC
    //0
    //external -> 4
    match_from_base(n, name, depth + 1);
    //None  CONV_FUNC CONV_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //to_base  CONV_FUNC CONV_FUNC
    //0
    //external -> 6
    match_to_base(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONV_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_COS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "COS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  COS_FUNC COS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "COS", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  COS_FUNC COS_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[COS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_COT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "COT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  COT_FUNC COT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "COT", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  COT_FUNC COT_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[COT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CRC32_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CRC32_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CRC32_FUNC CRC32_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CRC32", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  CRC32_FUNC CRC32_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CRC32_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CURDATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CURDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CURDATE_FUNC CURDATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CURDATE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURDATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CURRENT_DATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CURRENT_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CURRENT_DATE_FUNC CURRENT_DATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CURRENT_DATE", 12);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_DATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CURRENT_TIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CURRENT_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CURRENT_TIME_FUNC CURRENT_TIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CURRENT_TIME", 12);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  CURRENT_TIME_FUNC CURRENT_TIME_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_TIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CURRENT_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CURRENT_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CURRENT_TIMESTAMP_FUNC CURRENT_TIMESTAMP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CURRENT_TIMESTAMP", 17);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  CURRENT_TIMESTAMP_FUNC CURRENT_TIMESTAMP_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_TIMESTAMP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_CURTIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "CURTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  CURTIME_FUNC CURTIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "CURTIME", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  CURTIME_FUNC CURTIME_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURTIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DATE_ADD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DATE_ADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DATE_ADD", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "INTERVAL", 8);
    //interval_expr  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //external -> 5
    match_interval_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_ADD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DATEDIFF_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DATEDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DATEDIFF", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    //None  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //expr  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //external -> 4
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATEDIFF_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DATE_FUNC DATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DATE", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  DATE_FUNC DATE_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DATE_FORMAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DATE_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DATE_FORMAT", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //None  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //format  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //external -> 4
    match_format(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_FORMAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DATE_SUB_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DATE_SUB_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DATE_SUB", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "INTERVAL", 8);
    //interval_expr  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //external -> 5
    match_interval_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_SUB_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAY_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DAY_FUNC DAY_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DAY", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DAY_FUNC DAY_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAYNAME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAYNAME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DAYNAME_FUNC DAYNAME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DAYNAME", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DAYNAME_FUNC DAYNAME_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYNAME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAYOFMONTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAYOFMONTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DAYOFMONTH_FUNC DAYOFMONTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DAYOFMONTH", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DAYOFMONTH_FUNC DAYOFMONTH_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFMONTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAYOFWEEK_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAYOFWEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DAYOFWEEK_FUNC DAYOFWEEK_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DAYOFWEEK", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DAYOFWEEK_FUNC DAYOFWEEK_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFWEEK_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DAYOFYEAR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DAYOFYEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DAYOFYEAR_FUNC DAYOFYEAR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DAYOFYEAR", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  DAYOFYEAR_FUNC DAYOFYEAR_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFYEAR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_DEGREES_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "DEGREES_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  DEGREES_FUNC DEGREES_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "DEGREES", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  DEGREES_FUNC DEGREES_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DEGREES_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ELT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ELT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ELT_FUNC ELT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ELT", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  ELT_FUNC ELT_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  ELT_FUNC ELT_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //string  ELT_FUNC ELT_FUNC
        //0
        //external -> 1
        match_string(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ELT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_EXPORT_SET_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "EXPORT_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "EXPORT_SET", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //bits  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //external -> 2
    match_bits(n, name, depth + 1);
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //on  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //external -> 4
    match_on(n, name, depth + 1);
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //off  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //external -> 6
    match_off(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //separator  EXPORT_SET_FUNC EXPORT_SET_FUNC
        //0
        //external -> 1
        match_separator(n, name, depth + 1);
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
            //0
            // order 0
            compare_string(n, (const char *) ",", 1);
            //number_of_bits  EXPORT_SET_FUNC EXPORT_SET_FUNC
            //0
            //external -> 1
            match_number_of_bits(n, name, depth + 1);

          }

          optional_reset(n);
        }

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXPORT_SET_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_EXP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "EXP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  EXP_FUNC EXP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "EXP", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  EXP_FUNC EXP_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_EXTRACT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "EXTRACT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  EXTRACT_FUNC EXTRACT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "EXTRACT", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //unit  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //external -> 2
    match_unit(n, name, depth + 1);
    //None  EXTRACT_FUNC EXTRACT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) "FROM", 4);
    //date  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //external -> 4
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXTRACT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FIELD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FIELD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FIELD_FUNC FIELD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FIELD", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  FIELD_FUNC FIELD_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  FIELD_FUNC FIELD_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //string  FIELD_FUNC FIELD_FUNC
        //0
        //external -> 1
        match_string(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FIELD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FIND_IN_SET_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FIND_IN_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FIND_IN_SET", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //strlist  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //external -> 4
    match_strlist(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FIND_IN_SET_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FLOOR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FLOOR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FLOOR_FUNC FLOOR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FLOOR", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  FLOOR_FUNC FLOOR_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FLOOR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FORMAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FORMAT_FUNC FORMAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FORMAT", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  FORMAT_FUNC FORMAT_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    //None  FORMAT_FUNC FORMAT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //D  FORMAT_FUNC FORMAT_FUNC
    //0
    //external -> 4
    match_D(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  FORMAT_FUNC FORMAT_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //locale  FORMAT_FUNC FORMAT_FUNC
        //0
        //external -> 1
        match_locale(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FORMAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FROM_BASE64_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FROM_BASE64_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FROM_BASE64_FUNC FROM_BASE64_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FROM_BASE64", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  FROM_BASE64_FUNC FROM_BASE64_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_BASE64_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FROM_DAYS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FROM_DAYS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FROM_DAYS_FUNC FROM_DAYS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FROM_DAYS", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  FROM_DAYS_FUNC FROM_DAYS_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_DAYS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_FROM_UNIXTIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "FROM_UNIXTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "FROM_UNIXTIME", 13);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //unix_timestamp  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
    //0
    //external -> 2
    match_unix_timestamp(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //format  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
        //0
        //external -> 1
        match_format(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_UNIXTIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_GET_FORMAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "GET_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  GET_FORMAT_FUNC GET_FORMAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "GET_FORMAT", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //OR
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //item 0
          // order 0
          compare_string(n, (const char *) "DATE", 4);
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            // order 1
            compare_string(n, (const char *) "TIME", 4);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 2
          if (n->OK == 0) {
            n->OK = 1;
            // order 2
            compare_string(n, (const char *) "DATETIME", 8);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }

          pop(n->stack);
        }

      }

      optional_reset(n);
    }
    //None  GET_FORMAT_FUNC GET_FORMAT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //OR
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //item 0
          // order 0
          compare_string(n, (const char *) "EUR", 3);
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            // order 1
            compare_string(n, (const char *) "USA", 3);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 2
          if (n->OK == 0) {
            n->OK = 1;
            // order 2
            compare_string(n, (const char *) "JIS", 3);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 3
          if (n->OK == 0) {
            n->OK = 1;
            // order 3
            compare_string(n, (const char *) "ISO", 3);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //item+1 4
          if (n->OK == 0) {
            n->OK = 1;
            // order 4
            compare_string(n, (const char *) "INTERNAL", 8);

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }

          pop(n->stack);
        }

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[GET_FORMAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HEX_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  HEX_FUNC HEX_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "HEX", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //OR
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //item 0
      //external -> 0
      match_string(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      //item+1 1
      if (n->OK == 0) {
        n->OK = 1;
        //external -> 1
        match_N(n, name, depth + 1);

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HEX_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_HOUR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "HOUR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  HOUR_FUNC HOUR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "HOUR", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //time  HOUR_FUNC HOUR_FUNC
    //0
    //external -> 2
    match_time(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_INSERT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "INSERT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  INSERT_FUNC INSERT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "INSERT", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  INSERT_FUNC INSERT_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  INSERT_FUNC INSERT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //pos  INSERT_FUNC INSERT_FUNC
    //0
    //external -> 4
    match_pos(n, name, depth + 1);
    //None  INSERT_FUNC INSERT_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //len  INSERT_FUNC INSERT_FUNC
    //0
    //external -> 6
    match_len(n, name, depth + 1);
    //None  INSERT_FUNC INSERT_FUNC
    //0
    // order 7
    compare_string(n, (const char *) ",", 1);
    //newstr  INSERT_FUNC INSERT_FUNC
    //0
    //external -> 8
    match_newstr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[INSERT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_INSTR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "INSTR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  INSTR_FUNC INSTR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "INSTR", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  INSTR_FUNC INSTR_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  INSTR_FUNC INSTR_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //substr  INSTR_FUNC INSTR_FUNC
    //0
    //external -> 4
    match_substr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[INSTR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LAST_DAY_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LAST_DAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LAST_DAY_FUNC LAST_DAY_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LAST_DAY", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  LAST_DAY_FUNC LAST_DAY_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LAST_DAY_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LCASE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LCASE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LCASE_FUNC LCASE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LCASE", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LCASE_FUNC LCASE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LCASE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LEFT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LEFT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LEFT_FUNC LEFT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LEFT", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LEFT_FUNC LEFT_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  LEFT_FUNC LEFT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //len  LEFT_FUNC LEFT_FUNC
    //0
    //external -> 4
    match_len(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LEFT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LENGTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LENGTH_FUNC LENGTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LENGTH", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LENGTH_FUNC LENGTH_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LENGTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LN_FUNC LN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LN", 2);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  LN_FUNC LN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOAD_FILE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOAD_FILE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOAD_FILE_FUNC LOAD_FILE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOAD_FILE", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //file_name  LOAD_FILE_FUNC LOAD_FILE_FUNC
    //0
    //external -> 2
    match_file_name(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOAD_FILE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOCALTIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOCALTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOCALTIME_FUNC LOCALTIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOCALTIME", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  LOCALTIME_FUNC LOCALTIME_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCALTIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOCALTIMESTAMP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOCALTIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOCALTIMESTAMP_FUNC LOCALTIMESTAMP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOCALTIMESTAMP", 14);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  LOCALTIMESTAMP_FUNC LOCALTIMESTAMP_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCALTIMESTAMP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOCATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOCATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOCATE_FUNC LOCATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOCATE", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //substr  LOCATE_FUNC LOCATE_FUNC
    //0
    //external -> 2
    match_substr(n, name, depth + 1);
    //None  LOCATE_FUNC LOCATE_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //string  LOCATE_FUNC LOCATE_FUNC
    //0
    //external -> 4
    match_string(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  LOCATE_FUNC LOCATE_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //pos  LOCATE_FUNC LOCATE_FUNC
        //0
        //external -> 1
        match_pos(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOG10_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOG10_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOG10_FUNC LOG10_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOG10", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  LOG10_FUNC LOG10_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG10_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOG2_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOG2_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOG2_FUNC LOG2_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOG2", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  LOG2_FUNC LOG2_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG2_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOG_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOG_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOG_FUNC LOG_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOG", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //B  LOG_FUNC LOG_FUNC
        //0
        //external -> 0
        match_B(n, name, depth + 1);

      }

      optional_reset(n);
    }
    //None  LOG_FUNC LOG_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //X  LOG_FUNC LOG_FUNC
    //0
    //external -> 4
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LOWER_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LOWER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LOWER_FUNC LOWER_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LOWER", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LOWER_FUNC LOWER_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOWER_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LPAD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LPAD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LPAD_FUNC LPAD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LPAD", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LPAD_FUNC LPAD_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  LPAD_FUNC LPAD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //len  LPAD_FUNC LPAD_FUNC
    //0
    //external -> 4
    match_len(n, name, depth + 1);
    //None  LPAD_FUNC LPAD_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //padstr  LPAD_FUNC LPAD_FUNC
    //0
    //external -> 6
    match_padstr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LPAD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_LTRIM_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "LTRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  LTRIM_FUNC LTRIM_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "LTRIM", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  LTRIM_FUNC LTRIM_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LTRIM_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MAKEDATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MAKEDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MAKEDATE", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //year  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //external -> 2
    match_year(n, name, depth + 1);
    //None  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //dayofyear  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //external -> 4
    match_dayofyear(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKEDATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MAKE_SET_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MAKE_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MAKE_SET_FUNC MAKE_SET_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MAKE_SET", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //bits  MAKE_SET_FUNC MAKE_SET_FUNC
    //0
    //external -> 2
    match_bits(n, name, depth + 1);
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  MAKE_SET_FUNC MAKE_SET_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //string  MAKE_SET_FUNC MAKE_SET_FUNC
        //0
        //external -> 1
        match_string(n, name, depth + 1);

      }

      if (n->OK == 0) {
        n->pos = pop(n->stack);
      } else
        pop(n->stack);
    }
    n->OK = pop(n->stack);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKE_SET_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MAKETIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MAKETIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MAKETIME", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //hour  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //external -> 2
    match_hour(n, name, depth + 1);
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //minute  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //external -> 4
    match_minute(n, name, depth + 1);
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //second  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //external -> 6
    match_second(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKETIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MICROSECOND_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MICROSECOND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MICROSECOND_FUNC MICROSECOND_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MICROSECOND", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  MICROSECOND_FUNC MICROSECOND_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECOND_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MID_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MID_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MID_FUNC MID_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MID", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  MID_FUNC MID_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  MID_FUNC MID_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //pos  MID_FUNC MID_FUNC
    //0
    //external -> 4
    match_pos(n, name, depth + 1);
    //None  MID_FUNC MID_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //len  MID_FUNC MID_FUNC
    //0
    //external -> 6
    match_len(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MID_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MINUTE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MINUTE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MINUTE_FUNC MINUTE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MINUTE", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //time  MINUTE_FUNC MINUTE_FUNC
    //0
    //external -> 2
    match_time(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MOD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MOD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MOD_FUNC MOD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MOD", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  MOD_FUNC MOD_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    //None  MOD_FUNC MOD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  MOD_FUNC MOD_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "M", 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MOD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MONTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MONTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MONTH_FUNC MONTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MONTH", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  MONTH_FUNC MONTH_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_MONTHNAME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "MONTHNAME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  MONTHNAME_FUNC MONTHNAME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "MONTHNAME", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  MONTHNAME_FUNC MONTHNAME_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTHNAME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_NOW_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "NOW_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  NOW_FUNC NOW_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "NOW", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  NOW_FUNC NOW_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[NOW_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_OCTET_LENGTH_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "OCTET_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  OCTET_LENGTH_FUNC OCTET_LENGTH_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "OCTET_LENGTH", 12);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  OCTET_LENGTH_FUNC OCTET_LENGTH_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[OCTET_LENGTH_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_OCT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "OCT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  OCT_FUNC OCT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "OCT", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  OCT_FUNC OCT_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[OCT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ORD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ORD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ORD_FUNC ORD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ORD", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  ORD_FUNC ORD_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ORD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_PERIOD_ADD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "PERIOD_ADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "PERIOD_ADD", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    // order 2
    compare_string(n, (const char *) "P", 1);
    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //N  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    //external -> 4
    match_N(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PERIOD_ADD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_PERIOD_DIFF_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "PERIOD_DIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "PERIOD_DIFF", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    // order 2
    compare_string(n, (const char *) "P1", 2);
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "P2", 2);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PERIOD_DIFF_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_PI_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "PI_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  PI_FUNC PI_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "PI", 2);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PI_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_POSITION_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "POSITION_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  POSITION_FUNC POSITION_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "POSITION", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //substr  POSITION_FUNC POSITION_FUNC
    //0
    //external -> 2
    match_substr(n, name, depth + 1);
    //None  POSITION_FUNC POSITION_FUNC
    //0
    // order 3
    compare_string(n, (const char *) "IN", 2);
    //string  POSITION_FUNC POSITION_FUNC
    //0
    //external -> 4
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POSITION_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_POWER_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "POWER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  POWER_FUNC POWER_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "POWER", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  POWER_FUNC POWER_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    //None  POWER_FUNC POWER_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  POWER_FUNC POWER_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "Y", 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POWER_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_POW_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "POW_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  POW_FUNC POW_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "POW", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  POW_FUNC POW_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    //None  POW_FUNC POW_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //None  POW_FUNC POW_FUNC
    //0
    // order 4
    compare_string(n, (const char *) "Y", 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POW_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_QUARTER_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "QUARTER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  QUARTER_FUNC QUARTER_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "QUARTER", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  QUARTER_FUNC QUARTER_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTER_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_QUOTE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "QUOTE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  QUOTE_FUNC QUOTE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "QUOTE", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  QUOTE_FUNC QUOTE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUOTE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_RADIANS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "RADIANS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  RADIANS_FUNC RADIANS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "RADIANS", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  RADIANS_FUNC RADIANS_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RADIANS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_RAND_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "RAND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  RAND_FUNC RAND_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "RAND", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //N  RAND_FUNC RAND_FUNC
        //0
        //external -> 0
        match_N(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RAND_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_REPEAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "REPEAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  REPEAT_FUNC REPEAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "REPEAT", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  REPEAT_FUNC REPEAT_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  REPEAT_FUNC REPEAT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //count  REPEAT_FUNC REPEAT_FUNC
    //0
    //external -> 4
    match_count(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REPEAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_REPLACE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "REPLACE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "REPLACE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  REPLACE_FUNC REPLACE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //from_str  REPLACE_FUNC REPLACE_FUNC
    //0
    //external -> 4
    match_from_str(n, name, depth + 1);
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //to_str  REPLACE_FUNC REPLACE_FUNC
    //0
    //external -> 6
    match_to_str(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REPLACE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_REVERSE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "REVERSE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  REVERSE_FUNC REVERSE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "REVERSE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  REVERSE_FUNC REVERSE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REVERSE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_RIGHT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "RIGHT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  RIGHT_FUNC RIGHT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "RIGHT", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  RIGHT_FUNC RIGHT_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  RIGHT_FUNC RIGHT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //len  RIGHT_FUNC RIGHT_FUNC
    //0
    //external -> 4
    match_len(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RIGHT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_ROUND_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "ROUND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  ROUND_FUNC ROUND_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "ROUND", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  ROUND_FUNC ROUND_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  ROUND_FUNC ROUND_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //D  ROUND_FUNC ROUND_FUNC
        //0
        //external -> 1
        match_D(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ROUND_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_RPAD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "RPAD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  RPAD_FUNC RPAD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "RPAD", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  RPAD_FUNC RPAD_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  RPAD_FUNC RPAD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //len  RPAD_FUNC RPAD_FUNC
    //0
    //external -> 4
    match_len(n, name, depth + 1);
    //None  RPAD_FUNC RPAD_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //padstr  RPAD_FUNC RPAD_FUNC
    //0
    //external -> 6
    match_padstr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RPAD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_RTRIM_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "RTRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  RTRIM_FUNC RTRIM_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "RTRIM", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  RTRIM_FUNC RTRIM_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RTRIM_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SECOND_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SECOND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SECOND_FUNC SECOND_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SECOND", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //time  SECOND_FUNC SECOND_FUNC
    //0
    //external -> 2
    match_time(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SEC_TO_TIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SEC_TO_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SEC_TO_TIME_FUNC SEC_TO_TIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SEC_TO_TIME", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //seconds  SEC_TO_TIME_FUNC SEC_TO_TIME_FUNC
    //0
    //external -> 2
    match_seconds(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SEC_TO_TIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SIGN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SIGN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SIGN_FUNC SIGN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SIGN", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  SIGN_FUNC SIGN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SIGN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SIN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SIN_FUNC SIN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SIN", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  SIN_FUNC SIN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SIN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SOUNDEX_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SOUNDEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SOUNDEX_FUNC SOUNDEX_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SOUNDEX", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  SOUNDEX_FUNC SOUNDEX_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SOUNDEX_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SPACE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SPACE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SPACE_FUNC SPACE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SPACE", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //N  SPACE_FUNC SPACE_FUNC
    //0
    //external -> 2
    match_N(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SPACE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SQRT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SQRT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SQRT_FUNC SQRT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SQRT", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  SQRT_FUNC SQRT_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SQRT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_STR_TO_DATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "STR_TO_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "STR_TO_DATE", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //format  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //external -> 4
    match_format(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[STR_TO_DATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SUBDATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SUBDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SUBDATE_FUNC SUBDATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SUBDATE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //OR
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //item 0
      // GROUP
      if (n_OK(n) == 1) {
        //date  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //external -> 0
        match_date(n, name, depth + 1);
        //None  SUBDATE_FUNC SUBDATE_FUNC
        //0
        // order 1
        compare_string(n, (const char *) ",", 1);
        //None  SUBDATE_FUNC SUBDATE_FUNC
        //0
        // order 2
        compare_string(n, (const char *) "INTERVAL", 8);
        //interval_expr  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //external -> 3
        match_interval_expr(n, name, depth + 1);

      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      //item+1 1
      if (n->OK == 0) {
        n->OK = 1;
        // GROUP
        if (n_OK(n) == 1) {
          //expr  SUBDATE_FUNC SUBDATE_FUNC
          //0
          //external -> 0
          match_expr(n, name, depth + 1);
          //None  SUBDATE_FUNC SUBDATE_FUNC
          //0
          // order 1
          compare_string(n, (const char *) ",", 1);
          //days  SUBDATE_FUNC SUBDATE_FUNC
          //0
          //external -> 2
          match_days(n, name, depth + 1);

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBDATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SUBSTRING_INDEX_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SUBSTRING_INDEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SUBSTRING_INDEX", 15);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //delim  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //external -> 4
    match_delim(n, name, depth + 1);
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //count  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //external -> 6
    match_count(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTRING_INDEX_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SUBSTRING_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SUBSTRING_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SUBSTRING_FUNC SUBSTRING_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SUBSTRING", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //OR
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //item 0
      // GROUP
      if (n_OK(n) == 1) {
        //string  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        //external -> 0
        match_string(n, name, depth + 1);
        //None  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        // order 1
        compare_string(n, (const char *) ",", 1);
        //pos  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        //external -> 2
        match_pos(n, name, depth + 1);

      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      //item+1 1
      if (n->OK == 0) {
        n->OK = 1;
        // GROUP
        if (n_OK(n) == 1) {
          //string  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //external -> 0
          match_string(n, name, depth + 1);
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          // order 1
          compare_string(n, (const char *) "FROM", 4);
          //pos  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //external -> 2
          match_pos(n, name, depth + 1);

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }
      //item+1 2
      if (n->OK == 0) {
        n->OK = 1;
        // GROUP
        if (n_OK(n) == 1) {
          //string  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //external -> 0
          match_string(n, name, depth + 1);
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          // order 1
          compare_string(n, (const char *) ",", 1);
          //pos  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //external -> 2
          match_pos(n, name, depth + 1);
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          // order 3
          compare_string(n, (const char *) ",", 1);
          //len  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //external -> 4
          match_len(n, name, depth + 1);

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTRING_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SUBSTR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SUBSTR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SUBSTR_FUNC SUBSTR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SUBSTR", 6);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //OR
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //item 0
      // GROUP
      if (n_OK(n) == 1) {
        //string  SUBSTR_FUNC SUBSTR_FUNC
        //0
        //external -> 0
        match_string(n, name, depth + 1);
        //None  SUBSTR_FUNC SUBSTR_FUNC
        //0
        // order 1
        compare_string(n, (const char *) ",", 1);
        //pos  SUBSTR_FUNC SUBSTR_FUNC
        //0
        //external -> 2
        match_pos(n, name, depth + 1);

      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      //item+1 1
      if (n->OK == 0) {
        n->OK = 1;
        // GROUP
        if (n_OK(n) == 1) {
          //string  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //external -> 0
          match_string(n, name, depth + 1);
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          // order 1
          compare_string(n, (const char *) "FROM", 4);
          //pos  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //external -> 2
          match_pos(n, name, depth + 1);

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }
      //item+1 2
      if (n->OK == 0) {
        n->OK = 1;
        // GROUP
        if (n_OK(n) == 1) {
          //string  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //external -> 0
          match_string(n, name, depth + 1);
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          // order 1
          compare_string(n, (const char *) ",", 1);
          //pos  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //external -> 2
          match_pos(n, name, depth + 1);
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          // order 3
          compare_string(n, (const char *) ",", 1);
          //len  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //external -> 4
          match_len(n, name, depth + 1);

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SUBTIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SUBTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SUBTIME_FUNC SUBTIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SUBTIME", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    //None  SUBTIME_FUNC SUBTIME_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //expr  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //external -> 4
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBTIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_SYSDATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "SYSDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  SYSDATE_FUNC SYSDATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "SYSDATE", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  SYSDATE_FUNC SYSDATE_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SYSDATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TAN_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TAN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TAN_FUNC TAN_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TAN", 3);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  TAN_FUNC TAN_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TAN_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIMEDIFF_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIMEDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIMEDIFF", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    //None  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //expr  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //external -> 4
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMEDIFF_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIME_FUNC TIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIME", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  TIME_FUNC TIME_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIME_FORMAT_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIME_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIME_FORMAT", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //time  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //external -> 2
    match_time(n, name, depth + 1);
    //None  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //format  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //external -> 4
    match_format(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_FORMAT_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIMESTAMPADD_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIMESTAMPADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIMESTAMPADD", 12);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //unit  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //external -> 2
    match_unit(n, name, depth + 1);
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //interval  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //external -> 4
    match_interval(n, name, depth + 1);
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //datetime_expr  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //external -> 6
    match_datetime_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMPADD_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIMESTAMPDIFF_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIMESTAMPDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIMESTAMPDIFF", 13);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //unit  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //external -> 2
    match_unit(n, name, depth + 1);
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    // order 3
    compare_string(n, (const char *) ",", 1);
    //datetime_expr  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //external -> 4
    match_datetime_expr(n, name, depth + 1);
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    // order 5
    compare_string(n, (const char *) ",", 1);
    //datetime_expr  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //external -> 6
    match_datetime_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMPDIFF_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIMESTAMP_FUNC TIMESTAMP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIMESTAMP", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  TIMESTAMP_FUNC TIMESTAMP_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  TIMESTAMP_FUNC TIMESTAMP_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //expr  TIMESTAMP_FUNC TIMESTAMP_FUNC
        //0
        //external -> 1
        match_expr(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TIME_TO_SEC_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TIME_TO_SEC_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TIME_TO_SEC_FUNC TIME_TO_SEC_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TIME_TO_SEC", 11);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //time  TIME_TO_SEC_FUNC TIME_TO_SEC_FUNC
    //0
    //external -> 2
    match_time(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_TO_SEC_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TO_BASE64_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TO_BASE64_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TO_BASE64_FUNC TO_BASE64_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TO_BASE64", 9);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  TO_BASE64_FUNC TO_BASE64_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_BASE64_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TO_DAYS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TO_DAYS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TO_DAYS_FUNC TO_DAYS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TO_DAYS", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  TO_DAYS_FUNC TO_DAYS_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_DAYS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TO_SECONDS_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TO_SECONDS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TO_SECONDS_FUNC TO_SECONDS_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TO_SECONDS", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //expr  TO_SECONDS_FUNC TO_SECONDS_FUNC
    //0
    //external -> 2
    match_expr(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_SECONDS_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TRIM_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TRIM_FUNC TRIM_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TRIM", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //OR
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              //item 0
              // order 0
              compare_string(n, (const char *) "BOTH", 4);
              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
              //item+1 1
              if (n->OK == 0) {
                n->OK = 1;
                // order 1
                compare_string(n, (const char *) "LEADING", 7);

                if (n->OK == 0) {
                  n->pos = peek(n->stack);
                }
              }
              //item+1 2
              if (n->OK == 0) {
                n->OK = 1;
                // order 2
                compare_string(n, (const char *) "TRAILING", 8);

                if (n->OK == 0) {
                  n->pos = peek(n->stack);
                }
              }

              pop(n->stack);
            }

          }

          optional_reset(n);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // order None
          compare_string(n, (const char *) "{remstr", 7);


          optional_reset(n);
        }
        //None  TRIM_FUNC TRIM_FUNC
        //0
        // order 2
        compare_string(n, (const char *) "}", 1);
        //None  TRIM_FUNC TRIM_FUNC
        //0
        // order 3
        compare_string(n, (const char *) "FROM", 4);

      }

      optional_reset(n);
    }
    //string  TRIM_FUNC TRIM_FUNC
    //0
    //external -> 3
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TRIM_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_TRUNCATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "TRUNCATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  TRUNCATE_FUNC TRUNCATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "TRUNCATE", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //X  TRUNCATE_FUNC TRUNCATE_FUNC
    //0
    //external -> 2
    match_X(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  TRUNCATE_FUNC TRUNCATE_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //D  TRUNCATE_FUNC TRUNCATE_FUNC
        //0
        //external -> 1
        match_D(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TRUNCATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UCASE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UCASE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UCASE_FUNC UCASE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UCASE", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  UCASE_FUNC UCASE_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UCASE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UNHEX_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UNHEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UNHEX_FUNC UNHEX_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UNHEX", 5);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //string  UNHEX_FUNC UNHEX_FUNC
    //0
    //external -> 2
    match_string(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UNHEX_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UNIX_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UNIX_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UNIX_TIMESTAMP_FUNC UNIX_TIMESTAMP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UNIX_TIMESTAMP", 14);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // order None
      compare_string(n, (const char *) "{date", 5);


      optional_reset(n);
    }
    //None  UNIX_TIMESTAMP_FUNC UNIX_TIMESTAMP_FUNC
    //0
    // order 3
    compare_string(n, (const char *) "}", 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UNIX_TIMESTAMP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UTC_DATE_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UTC_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UTC_DATE_FUNC UTC_DATE_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UTC_DATE", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_DATE_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UTC_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UTC_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UTC_TIMESTAMP_FUNC UTC_TIMESTAMP_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UTC_TIMESTAMP", 13);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  UTC_TIMESTAMP_FUNC UTC_TIMESTAMP_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_TIMESTAMP_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_UTC_TIME_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "UTC_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  UTC_TIME_FUNC UTC_TIME_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "UTC_TIME", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //fsp  UTC_TIME_FUNC UTC_TIME_FUNC
        //0
        //external -> 0
        match_fsp(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_TIME_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_WEEK_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "WEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  WEEK_FUNC WEEK_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "WEEK", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  WEEK_FUNC WEEK_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  WEEK_FUNC WEEK_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //mode  WEEK_FUNC WEEK_FUNC
        //0
        //external -> 1
        match_mode(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEK_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_WEEKDAY_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "WEEKDAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  WEEKDAY_FUNC WEEKDAY_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "WEEKDAY", 7);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  WEEKDAY_FUNC WEEKDAY_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKDAY_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_WEEKOFYEAR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "WEEKOFYEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  WEEKOFYEAR_FUNC WEEKOFYEAR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "WEEKOFYEAR", 10);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  WEEKOFYEAR_FUNC WEEKOFYEAR_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKOFYEAR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_YEAR_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "YEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  YEAR_FUNC YEAR_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "YEAR", 4);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  YEAR_FUNC YEAR_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_YEARWEEK_FUNC(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "YEARWEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // GROUP
  if (n_OK(n) == 1) {
    //None  YEARWEEK_FUNC YEARWEEK_FUNC
    //0
    // order 0
    compare_string(n, (const char *) "YEARWEEK", 8);
    if (n_OK(n) == 1 && (n->value[n->pos] == '('))
      increment_n(n, 1);
    else
      n->OK = 0;

    //date  YEARWEEK_FUNC YEARWEEK_FUNC
    //0
    //external -> 2
    match_date(n, name, depth + 1);
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //None  YEARWEEK_FUNC YEARWEEK_FUNC
        //0
        // order 0
        compare_string(n, (const char *) ",", 1);
        //mode  YEARWEEK_FUNC YEARWEEK_FUNC
        //0
        //external -> 1
        match_mode(n, name, depth + 1);

      }

      optional_reset(n);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ')'))
      increment_n(n, 1);
    else
      n->OK = 0;

  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEARWEEK_FUNC] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_functions(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "functions";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //external -> 0
    match_ABS_FUNC(n, name, depth + 1);
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 1
      match_ACOS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 2
      match_ADDDATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 3
      match_ADDTIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 4
      match_ASCII_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 5
      match_ASIN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 6
      match_ATAN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 7
      match_ATAN2_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 8
      match_BIN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 9
      match_BIT_LENGTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 10
      match_CEILING_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 11
      match_CEIL_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 12
      match_CHARACTER_LENGTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 13
      match_CHAR_LENGTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 14
      match_CHAR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 15
      match_CONCAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 16
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 16
      match_CONCAT_WS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 17
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 17
      match_CONVERT_TZ_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 18
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 18
      match_CONV_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 19
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 19
      match_COS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 20
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 20
      match_COT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 21
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 21
      match_CRC32_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 22
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 22
      match_CURDATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 23
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 23
      match_CURRENT_DATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 24
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 24
      match_CURRENT_TIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 25
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 25
      match_CURRENT_TIMESTAMP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 26
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 26
      match_CURTIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 27
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 27
      match_DATE_ADD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 28
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 28
      match_DATEDIFF_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 29
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 29
      match_DATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 30
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 30
      match_DATE_FORMAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 31
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 31
      match_DATE_SUB_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 32
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 32
      match_DAY_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 33
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 33
      match_DAYNAME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 34
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 34
      match_DAYOFMONTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 35
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 35
      match_DAYOFWEEK_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 36
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 36
      match_DAYOFYEAR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 37
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 37
      match_DEGREES_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 38
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 38
      match_ELT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 39
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 39
      match_EXPORT_SET_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 40
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 40
      match_EXP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 41
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 41
      match_EXTRACT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 42
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 42
      match_FIELD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 43
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 43
      match_FIND_IN_SET_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 44
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 44
      match_FLOOR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 45
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 45
      match_FORMAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 46
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 46
      match_FORMAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 47
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 47
      match_FROM_BASE64_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 48
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 48
      match_FROM_DAYS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 49
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 49
      match_FROM_UNIXTIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 50
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 50
      match_GET_FORMAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 51
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 51
      match_HEX_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 52
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 52
      match_HOUR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 53
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 53
      match_INSERT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 54
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 54
      match_INSTR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 55
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 55
      match_LAST_DAY_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 56
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 56
      match_LCASE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 57
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 57
      match_LEFT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 58
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 58
      match_LENGTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 59
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 59
      match_LN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 60
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 60
      match_LOAD_FILE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 61
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 61
      match_LOCALTIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 62
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 62
      match_LOCALTIMESTAMP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 63
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 63
      match_LOCATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 64
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 64
      match_LOG10_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 65
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 65
      match_LOG2_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 66
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 66
      match_LOG_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 67
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 67
      match_LOWER_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 68
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 68
      match_LPAD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 69
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 69
      match_LTRIM_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 70
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 70
      match_MAKEDATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 71
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 71
      match_MAKE_SET_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 72
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 72
      match_MAKETIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 73
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 73
      match_MICROSECOND_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 74
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 74
      match_MID_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 75
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 75
      match_MINUTE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 76
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 76
      match_MOD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 77
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 77
      match_MONTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 78
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 78
      match_MONTHNAME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 79
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 79
      match_NOW_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 80
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 80
      match_OCTET_LENGTH_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 81
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 81
      match_OCT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 82
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 82
      match_ORD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 83
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 83
      match_PERIOD_ADD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 84
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 84
      match_PERIOD_DIFF_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 85
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 85
      match_PI_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 86
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 86
      match_POSITION_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 87
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 87
      match_POWER_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 88
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 88
      match_POW_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 89
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 89
      match_QUARTER_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 90
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 90
      match_QUOTE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 91
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 91
      match_RADIANS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 92
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 92
      match_RAND_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 93
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 93
      match_REPEAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 94
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 94
      match_REPLACE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 95
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 95
      match_REVERSE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 96
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 96
      match_RIGHT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 97
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 97
      match_ROUND_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 98
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 98
      match_RPAD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 99
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 99
      match_RTRIM_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 100
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 100
      match_SECOND_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 101
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 101
      match_SEC_TO_TIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 102
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 102
      match_SIGN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 103
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 103
      match_SIN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 104
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 104
      match_SOUNDEX_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 105
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 105
      match_SPACE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 106
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 106
      match_SQRT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 107
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 107
      match_STR_TO_DATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 108
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 108
      match_SUBDATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 109
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 109
      match_SUBSTRING_INDEX_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 110
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 110
      match_SUBSTRING_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 111
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 111
      match_SUBSTR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 112
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 112
      match_SUBTIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 113
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 113
      match_SYSDATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 114
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 114
      match_TAN_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 115
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 115
      match_TIMEDIFF_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 116
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 116
      match_TIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 117
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 117
      match_TIME_FORMAT_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 118
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 118
      match_TIMESTAMPADD_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 119
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 119
      match_TIMESTAMPDIFF_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 120
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 120
      match_TIMESTAMP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 121
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 121
      match_TIME_TO_SEC_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 122
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 122
      match_TO_BASE64_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 123
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 123
      match_TO_DAYS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 124
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 124
      match_TO_SECONDS_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 125
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 125
      match_TRIM_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 126
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 126
      match_TRUNCATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 127
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 127
      match_UCASE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 128
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 128
      match_UNHEX_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 129
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 129
      match_UNIX_TIMESTAMP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 130
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 130
      match_UTC_DATE_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 131
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 131
      match_UTC_TIMESTAMP_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 132
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 132
      match_UTC_TIME_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 133
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 133
      match_WEEK_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 134
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 134
      match_WEEKDAY_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 135
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 135
      match_WEEKOFYEAR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 136
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 136
      match_YEAR_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 137
    if (n->OK == 0) {
      n->OK = 1;
      //external -> 137
      match_YEARWEEK_FUNC(n, name, depth + 1);

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[functions] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_B(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "B";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //bit  B B
  //0
  //external -> 0
  match_bit(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[B] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_bits(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "bits";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  bits bits
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bits] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_charset_name(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "charset_name";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  charset_name charset_name
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[charset_name] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_count(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "count";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  count count
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[count] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_D(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "D";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //real  D D
  //0
  //external -> 0
  match_real(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[D] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_date(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "date";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  date date
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[date] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_datetime_expr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "datetime_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  datetime_expr datetime_expr
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[datetime_expr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_dayofyear(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "dayofyear";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  dayofyear dayofyear
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[dayofyear] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_days(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "days";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  days days
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[days] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_delim(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "delim";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  delim delim
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[delim] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_dt(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "dt";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  dt dt
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[dt] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_file_name(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "file_name";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  file_name file_name
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[file_name] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_format(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "format";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  format format
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[format] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_from_base(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "from_base";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  from_base from_base
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_base] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_from_str(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "from_str";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  from_str from_str
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_str] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_from_tz(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "from_tz";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  from_tz from_tz
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_tz] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_fsp(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "fsp";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  fsp fsp
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[fsp] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_hour(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "hour";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  hour hour
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[hour] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_interval(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "interval";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  interval interval
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[interval] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_len(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "len";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  len len
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[len] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_locale(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "locale";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  locale locale
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[locale] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_M(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "M";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  M M
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[M] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_minute(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "minute";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  minute minute
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[minute] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_mode(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "mode";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  mode mode
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[mode] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_N(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "N";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  N N
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[N] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_newstr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "newstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  newstr newstr
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[newstr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_N_or_S(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "N_or_S";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  N_or_S N_or_S
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[N_or_S] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_number_of_bits(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "number_of_bits";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  number_of_bits number_of_bits
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[number_of_bits] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_off(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "off";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  off off
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[off] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_on(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "on";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  on on
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[on] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_P(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "P";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  P P
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[P] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_padstr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "padstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  padstr padstr
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[padstr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_pos(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "pos";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  pos pos
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[pos] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_remstr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "remstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  remstr remstr
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[remstr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_second(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "second";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  second second
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[second] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_seconds(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "seconds";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  seconds seconds
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[seconds] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_separator(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "separator";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  separator separator
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[separator] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_strlist(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "strlist";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  strlist strlist
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[strlist] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_substr(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "substr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  substr substr
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[substr] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_time(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "time";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  time time
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[time] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_to_base(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "to_base";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  to_base to_base
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_base] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_to_str(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "to_str";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  to_str to_str
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_str] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_to_tz(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "to_tz";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  to_tz to_tz
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_tz] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_unit(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "unit";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //expr  unit unit
  //0
  //external -> 0
  match_expr(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unit] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_unix_timestamp(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "unix_timestamp";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //integer  unix_timestamp unix_timestamp
  //0
  //external -> 0
  match_integer(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unix_timestamp] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_X(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "X";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //integer  X X
  //0
  //external -> 0
  match_integer(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[X] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_Y(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "Y";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //integer  Y Y
  //0
  //external -> 0
  match_integer(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[Y] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_year(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "year";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //integer  year year
  //0
  //external -> 0
  match_integer(n, name, depth + 1);

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[year] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}
void match_catch_all(node_t * n, const char last_method[], int depth) {
  if (n_OK(n) == 0) {
    return;
  }
  const char name[] = "catch_all";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  //NOT
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\t' || n->value[n->pos] == ' ' || n->value[n->pos] == '\n' || n->value[n->pos] == '\r'))
      increment_n(n, 1);
    else
      n->OK = 0;

    not_reset(n);
  }                             //end NOT

#ifdef  DEBUG_SUCCESS
  if (n->OK == 1) {
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[catch_all] SUCCESS");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    debug_success(n, name, start_pos);
  }
#endif

#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  if (n->OK) {
    printf("%s, %d, %d\n", name, start_pos, n->pos);
  }
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-11
*      nodes: a pointer to the curent element in a linked list of nodes to search
*
*     OK: Returns a the node AFTER the curent pattern match
*              If the end of the list is reached the last node is passed
*     Failure: Returns NULL
*/
node_t *match_function(char *data) {
  int last_pos = -1;
  node_t *n = malloc(sizeof(node_t));
  n->value = data;
  n->len = strlen(data);
  n->pos = 0;
  n->depth = 0;
  n->OK = 1;
  n->stack = createStack(1000);
  const char *name = "functions";
  push(n->stack, n->pos);
  while (n->pos > -1) {
    if (last_pos == n->pos) {
      break;
    }
    last_pos = n->pos;

    n->OK = 1;
    match_queries(n, name, 0);
#ifdef  DEBUG_SUCCESS
    if (n_OK(n) == 1) {
      printf("GOOD queries\n");
    }
#endif
    n->OK = 1;
    match_expr(n, name, 0);
#ifdef  DEBUG_SUCCESS
    if (n_OK(n) == 1) {
      printf("GOOD expr\n");
    }
#endif
    n->OK = 1;
    match_whitespace(n, name, 0);
#ifdef  DEBUG_SUCCESS
    if (n_OK(n) == 1) {
      printf("GOOD whitespace\n");
    }
#endif
    n->OK = 1;
    match_query_delimiter(n, name, 0);
#ifdef  DEBUG_SUCCESS
    if (n_OK(n) == 1) {
      printf("GOOD query_delimiter\n");
    }
#endif

    if (n->OK == 0) {
      break;
    }
  }
  pop(n->stack);
#ifdef  DEBUG_FAIL
  if (n->OK == 0) {
    printf("\nMatch not found\n");
  }
  if (n->pos != -1) {
    printf("String parsed until [%d] out of [%d]\n", n->pos, n->len);
  }
#endif
  return n;
}                               // end match functions
