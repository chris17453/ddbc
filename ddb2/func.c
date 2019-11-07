/********************************************
* Generated: 2019-11-06                    *
********************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "headers/stack.h"
#include "headers/func.h"
// node values are only compared if string length is the same, no need to validate
// comparitors is against a precompiled value thats already case optimised
// returns 0 for equal
int stricmp(node_t * n, const char *b)
{
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

void print_sub_str(node_t * n, int start, int end)
{
  for (int i = start; i < end; i++) {
    printf("%c", n->value[i]);
  }
}

void print_n(node_t * n)
{
  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
}

int n_OK(node_t * n)
{
  //print_n(n);
  if (n->pos != -1 && n->OK == 1)
    return 1;
  return 0;
}

void debug_start(node_t * n, int start_pos)
{
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s]-> %d - %d OK:%d, depth: %d \n", n->function, start_pos, n->pos, n->OK, n->depth);
}

void debug_success(node_t * n, int start_pos)
{
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] SUCCESS -> %d - %d OK:%d, depth: %d \n", n->function, start_pos, n->pos, n->OK, n->depth);
}

void debug_failed(node_t * n, int start_pos)
{
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] FAILED -> %d - %d OK:%d, depth: %d \n", n->function, start_pos, n->pos, n->OK, n->depth);
}

node_t *match_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_comment\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //block_comment  comment comment
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_block_comment(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //single_comment  comment comment
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_single_comment(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_block_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "block_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_block_comment\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //left_comment  block_comment block_comment
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_left_comment(n, name, depth + 1);
    }
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_right_comment(n, name, depth + 1);
          }

          if (n->OK == 1) {
            n->OK = 0;
            n->pos = peek(n->stack);
          } else {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          }
          pop(n->stack);
        }                       //end NOT

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);
    //right_comment  block_comment block_comment
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_right_comment(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("block_comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_block_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_single_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "single_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_single_comment\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //inline_comment  single_comment single_comment
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_inline_comment(n, name, depth + 1);
    }
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_end_of_line(n, name, depth + 1);
          }

          if (n->OK == 1) {
            n->OK = 0;
            n->pos = peek(n->stack);
          } else {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          }
          pop(n->stack);
        }                       //end NOT

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);
    //end_of_line  single_comment single_comment
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_end_of_line(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("single_comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_single_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_left_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "left_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_left_comment\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '/')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '*')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("left_comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_left_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_right_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "right_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_right_comment\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '*')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '/')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("right_comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_right_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_inline_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "inline_comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_inline_comment\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '-')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '-')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("inline_comment           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_inline_comment(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_select(node_t * n, const char last_method[], int depth)
{
  const char name[] = "select";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_select\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  select select
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "select") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //string
      //external -> None
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    //select_expr  select select
    //0
    //string
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_select_expr(n, name, depth + 1);
    }

  }
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name, depth + 1);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == ',')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name, depth + 1);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //select_expr  select select
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_select_expr(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name, depth + 1);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }

      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  select select
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //identifier  select select
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_identifier(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            //None  select select
            //0
            //string
            // order 0
            if (n_OK(n) == 1 && stricmp(n, (const char *) "as") == 0) {
              n->OK = 1;
              n->pos += 2;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            // dict
            //optional
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              //string
              //external -> None
              if (n_OK(n) == 1) {
                n = match_whitespace(n, name, depth + 1);
              }

              if (n->OK == 0) {
                n->OK = 1;
                n->pos = peek(n->stack);
              }
              pop(n->stack);
            }
            //identifier  select select
            //0
            //string
            //external -> 2
            if (n_OK(n) == 1) {
              n = match_identifier(n, name, depth + 1);
            }

          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        // dict
        // GROUP
        if (n_OK(n) == 1) {
          // list
          //None  select select
          //0
          //string
          // order 0
          if (n_OK(n) == 1 && stricmp(n, (const char *) "ON") == 0) {
            n->OK = 1;
            n->pos += 2;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //where_expression  select select
          //0
          //string
          //external -> 1
          if (n_OK(n) == 1) {
            n = match_where_expression(n, name, depth + 1);
          }

        }

      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("select           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_select(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 1;
  //printf("In functions match_expr\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //expr  expr expr
      //2
      //list item switch
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      //whitespace  expr expr
      //2
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  expr expr
      //2
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "OR") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //whitespace  expr expr
      //2
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //expr  expr expr
      //2
      //list item switch
      //item 4  //non index 0 recursion
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
        n = match_expr(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //expr  expr expr
        //2
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '|' ||
                              //string
                              n->value[n->pos] == '|')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //whitespace  expr expr
        //2
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //2
        //list item switch
        //item 4  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //expr  expr expr
        //2
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  expr expr
        //2
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "XOR") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //2
        //list item switch
        //item 4  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //expr  expr expr
        //2
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  expr expr
        //2
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "AND") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //2
        //list item switch
        //item 4  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //expr  expr expr
        //2
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  expr expr
        //2
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "&&") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  expr expr
        //2
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //2
        //list item switch
        //item 4  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  expr expr
        //1
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  expr expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  expr expr
        //1
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "!") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  expr expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //expr  expr expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //boolean_primary  expr expr
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_boolean_primary(n, name, depth + 1);
        }
        //None  expr expr
        //0
        //string
        // order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            //whitespace  expr expr
            //0
            //string
            //external -> 0
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //None  expr expr
            //0
            //string
            // order 1
            if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
              n->OK = 1;
              n->pos += 3;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //whitespace  expr expr
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        // GROUP
        if (n_OK(n) == 1) {
          // list
          // dict
          //OR
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
            // list
            //list item switch
            //item 0
            //string
            //external -> 0
            if (n_OK(n) == 1) {
              n = match_boolean(n, name, depth + 1);
            }
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            //list item switch
            //item+1 1
            if (n->OK == 0) {
              n->OK = 1;
              //string
              //external -> 1
              if (n_OK(n) == 1) {
                n = match_unknown(n, name, depth + 1);
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
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //boolean_primary  expr expr
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_boolean_primary(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("expr           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_expr(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_boolean_primary(node_t * n, const char last_method[], int depth)
{
  const char name[] = "boolean_primary";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 1;
  //printf("In functions match_boolean_primary\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //boolean_primary  boolean_primary boolean_primary
      //1
      //list item switch
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      //whitespace  boolean_primary boolean_primary
      //1
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  boolean_primary boolean_primary
      //1
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      // dict
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        // dict
        // GROUP
        if (n_OK(n) == 1) {
          // list
          //whitespace  boolean_primary boolean_primary
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name, depth + 1);
          }
          //None  boolean_primary boolean_primary
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }

        }

        if (n->OK == 0) {
          n->OK = 1;
          n->pos = peek(n->stack);
        }
        pop(n->stack);
      }
      //whitespace  boolean_primary boolean_primary
      //1
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //null  boolean_primary boolean_primary
      //1
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_null(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //boolean_primary  boolean_primary boolean_primary
        //1
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  boolean_primary boolean_primary
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  boolean_primary boolean_primary
        //1
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "<=>") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  boolean_primary boolean_primary
        //1
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //predicate  boolean_primary boolean_primary
        //1
        //string
        //external -> 4
        if (n_OK(n) == 1) {
          n = match_predicate(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //boolean_primary  boolean_primary boolean_primary
        //1
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  boolean_primary boolean_primary
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //comparison_operator  boolean_primary boolean_primary
        //1
        //string
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_comparison_operator(n, name, depth + 1);
        }
        //whitespace  boolean_primary boolean_primary
        //1
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //predicate  boolean_primary boolean_primary
        //1
        //string
        //external -> 4
        if (n_OK(n) == 1) {
          n = match_predicate(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //predicate  boolean_primary boolean_primary
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_predicate(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("boolean_primary           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_boolean_primary(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_where_expression(node_t * n, const char last_method[], int depth)
{
  const char name[] = "where_expression";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_where_expression\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  where_expression where_expression
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("where_expression           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_where_expression(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_predicate(node_t * n, const char last_method[], int depth)
{
  const char name[] = "predicate";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_predicate\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //bit_expr  predicate predicate
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_bit_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("predicate           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_predicate(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_bit_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "bit_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 1;
  //printf("In functions match_bit_expr\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //bit_expr  bit_expr bit_expr
      //2
      //list item switch
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      // dict
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        //string
        //external -> None
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }

        if (n->OK == 0) {
          n->OK = 1;
          n->pos = peek(n->stack);
        }
        pop(n->stack);
      }
      //operations  bit_expr bit_expr
      //2
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_operations(n, name, depth + 1);
      }
      // dict
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        //string
        //external -> None
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }

        if (n->OK == 0) {
          n->OK = 1;
          n->pos = peek(n->stack);
        }
        pop(n->stack);
      }
      //bit_expr  bit_expr bit_expr
      //2
      //list item switch
      //item 4  //non index 0 recursion
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
        n = match_bit_expr(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //simple_expr  bit_expr bit_expr
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_simple_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("bit_expr           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_bit_expr(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_operations(node_t * n, const char last_method[], int depth)
{
  const char name[] = "operations";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_operations\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '|')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '&')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '+')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '-')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '*')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '/')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  operations operations
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DIV") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  operations operations
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "MOD") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '%')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '^')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("operations           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_operations(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_complex_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "complex_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_complex_expr\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //simple_expr  complex_expr complex_expr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_simple_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("complex_expr           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_complex_expr(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_simple_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "simple_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_simple_expr\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //literal  simple_expr simple_expr
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_literal(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //identifier  simple_expr simple_expr
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_identifier(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("simple_expr           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_simple_expr(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_literal(node_t * n, const char last_method[], int depth)
{
  const char name[] = "literal";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_literal\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //hex  literal literal
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_hex(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //bit  literal literal
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //real  literal literal
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_real(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //null  literal literal
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_null(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //boolean  literal literal
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_boolean(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //string  literal literal
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("literal           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_literal(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_unknown(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unknown";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_unknown\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  unknown unknown
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "unknown") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("unknown           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_unknown(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_hex(node_t * n, const char last_method[], int depth)
{
  const char name[] = "hex";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_hex\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == 'x' ||
                          //string
                          n->value[n->pos] == 'X')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            // dict
                            (n->value[n->pos] >= '0' && n->value[n->pos] <= '9') ||
                            // dict
                            (n->value[n->pos] >= 'A' && n->value[n->pos] <= 'F') ||
                            // dict
                            (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'f')
          )) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("hex           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_hex(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_bit(node_t * n, const char last_method[], int depth)
{
  const char name[] = "bit";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_bit\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == 'b')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '0' ||
                            //string
                            n->value[n->pos] == '1')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("bit           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_bit(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_null(node_t * n, const char last_method[], int depth)
{
  const char name[] = "null";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_null\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //None  null null
      //0
      //string
      // order 0
      if (n_OK(n) == 1 && stricmp(n, (const char *) "null") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  null null
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "NULL") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("null           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_null(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_true(node_t * n, const char last_method[], int depth)
{
  const char name[] = "true";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_true\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //None  true true
      //0
      //string
      // order 0
      if (n_OK(n) == 1 && stricmp(n, (const char *) "true") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  true true
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "TRUE") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("true           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_true(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_false(node_t * n, const char last_method[], int depth)
{
  const char name[] = "false";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_false\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //None  false false
      //0
      //string
      // order 0
      if (n_OK(n) == 1 && stricmp(n, (const char *) "false") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  false false
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "FALSE") == 0) {
          n->OK = 1;
          n->pos += 5;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("false           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_false(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_boolean(node_t * n, const char last_method[], int depth)
{
  const char name[] = "boolean";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_boolean\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //true  boolean boolean
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_true(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //false  boolean boolean
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_false(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("boolean           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_boolean(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_real(node_t * n, const char last_method[], int depth)
{
  const char name[] = "real";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_real\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //integer  real real
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_integer(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '.')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //unsigned_int  real real
      //0
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_unsigned_int(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '.')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //unsigned_int  real real
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //integer  real real
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_integer(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //string
      //external -> None
      if (n_OK(n) == 1) {
        n = match_exponent(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("real           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_real(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_integer(node_t * n, const char last_method[], int depth)
{
  const char name[] = "integer";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_integer\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //signed_int  integer integer
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_signed_int(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //unsigned_int  integer integer
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("integer           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_integer(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_signed_int(node_t * n, const char last_method[], int depth)
{
  const char name[] = "signed_int";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_signed_int\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //sign  signed_int signed_int
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_sign(n, name, depth + 1);
    }
    //unsigned_int  signed_int signed_int
    //0
    //string
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("signed_int           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_signed_int(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_unsigned_int(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unsigned_int";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_unsigned_int\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            // dict
                            (n->value[n->pos] >= '0' && n->value[n->pos] <= '9')
          )) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("unsigned_int           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_unsigned_int(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_sign(node_t * n, const char last_method[], int depth)
{
  const char name[] = "sign";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_sign\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '-' ||
                          //string
                          n->value[n->pos] == '+')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("sign           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_sign(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_exponent(node_t * n, const char last_method[], int depth)
{
  const char name[] = "exponent";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_exponent\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == 'E' ||
                          //string
                          n->value[n->pos] == 'e')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //integer  exponent exponent
    //0
    //string
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("exponent           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_exponent(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_identifier(node_t * n, const char last_method[], int depth)
{
  const char name[] = "identifier";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_identifier\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            // dict
                            (n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') ||
                            // dict
                            (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z') ||
                            // dict
                            (n->value[n->pos] >= '0' && n->value[n->pos] <= '9') ||
                            //string
                            n->value[n->pos] == '$' ||
                            //string
                            n->value[n->pos] == '_')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("identifier           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_identifier(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_alpha(node_t * n, const char last_method[], int depth)
{
  const char name[] = "alpha";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_alpha\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            // dict
                            (n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') ||
                            // dict
                            (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z')
          )) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("alpha           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_alpha(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_whitespace(node_t * n, const char last_method[], int depth)
{
  const char name[] = "whitespace";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_whitespace\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '\t' ||
                            //string
                            n->value[n->pos] == ' ' ||
                            //string
                            n->value[n->pos] == '\n' ||
                            //string
                            n->value[n->pos] == '\r')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("whitespace           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_whitespace(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_single_quote_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "single_quote_string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_single_quote_string\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          if (n_OK(n) == 1 && (
                                //string
                                n->value[n->pos] == '\'')) {
            n->OK = 1;
            n->pos++;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }                     // end char

          if (n->OK == 1) {
            n->OK = 0;
            n->pos = peek(n->stack);
          } else {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          }
          pop(n->stack);
        }                       //end NOT

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("single_quote_string           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_single_quote_string(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_double_quote_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "double_quote_string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_double_quote_string\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '"')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          if (n_OK(n) == 1 && (
                                //string
                                n->value[n->pos] == '"')) {
            n->OK = 1;
            n->pos++;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }                     // end char

          if (n->OK == 1) {
            n->OK = 0;
            n->pos = peek(n->stack);
          } else {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          }
          pop(n->stack);
        }                       //end NOT

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    if (n->pos == peek(n->stack)) {
      n->OK = 0;
    } else {
      n->OK = 1;
    }
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '"')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("double_quote_string           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_double_quote_string(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "string";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_string\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //single_quote_string  string string
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_single_quote_string(n, name, depth + 1);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //double_quote_string  string string
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_double_quote_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("string           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_string(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_select_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "select_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_select_expr\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  select_expr select_expr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //string
      //external -> None
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  select_expr select_expr
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "as") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          //external -> None
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name, depth + 1);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //identifier  select_expr select_expr
        //0
        //string
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_identifier(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("select_expr           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_select_expr(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_end_of_line(node_t * n, const char last_method[], int depth)
{
  const char name[] = "end_of_line";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_end_of_line\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '\n')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '\r')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("end_of_line           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_end_of_line(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_comparison_operator(node_t * n, const char last_method[], int depth)
{
  const char name[] = "comparison_operator";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_comparison_operator\n");
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '<')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '>')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '=')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '=')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '!')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '=')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '=')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("comparison_operator           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_comparison_operator(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_not_whitespace(node_t * n, const char last_method[], int depth)
{
  const char name[] = "not_whitespace";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, start_pos);
#endif
  int recursion = 0;
  //printf("In functions match_not_whitespace\n");
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //NOT
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '\t' ||
                            //string
                            n->value[n->pos] == ' ' ||
                            //string
                            n->value[n->pos] == '\n' ||
                            //string
                            n->value[n->pos] == '\r')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char

      if (n->OK == 1) {
        n->OK = 0;
        n->pos = peek(n->stack);
      } else {
        n->OK = 1;
        n->pos += 1;
        if (n->pos >= n->len)
          n->pos = -1;
      }
      pop(n->stack);
    }                           //end NOT

  }

  if (n->OK == 1) {
    if (depth == 0) {
      printf("not_whitespace           ");
      if (n->pos == -1) {
        print_sub_str(n, start_pos, n->len);
      } else {
        print_sub_str(n, start_pos, n->pos);
      }
      printf("\n");
    }
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      push(n->stack, n->pos);
      n = match_not_whitespace(n, last_method, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-06
*      nodes: a pointer to the curent element in a linked list of nodes to search
*
*     OK: Returns a the node AFTER the curent pattern match
*              If the end of the list is reached the last node is passed
*     Failure: Returns NULL
*/
node_t *match_function(char *data)
{
  printf("In functions\n");
  node_t *n = malloc(sizeof(node_t));
  n->value = data;
  n->len = strlen(data);
  n->pos = 0;
  n->depth = 0;
  n->OK = 1;
  n->stack = createStack(1000);
  //printf("POS:%d\n",n->pos);
  //printf("OK:%d\n",n->OK);
  //printf("--\n");
  while (n->pos > -1) {

    n->OK = 1;
    n = match_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_block_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_single_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_left_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_right_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_inline_comment(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_select(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_boolean_primary(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_where_expression(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_predicate(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_bit_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_operations(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_complex_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_simple_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_literal(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_unknown(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_hex(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_bit(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_null(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_true(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_false(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_boolean(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_real(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_integer(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_signed_int(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_unsigned_int(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_sign(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_exponent(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_identifier(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_alpha(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_whitespace(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_single_quote_string(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_double_quote_string(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_string(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_select_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_end_of_line(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_comparison_operator(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_not_whitespace(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;

  }
  pop(n->stack);
  return n;
}                               // end match functions
