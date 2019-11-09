/********************************************
* Generated: 2019-11-09                    *
********************************************/
//#define DEBUG_START   1
#define DEBUG_SUCCESS 1
//#define DEBUG_FAIL    1
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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

void debug_start(node_t * n, const char *name, int start_pos)
{
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s]-> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
  //    printf("%s.",name);
}

void debug_success(node_t * n, const char *name, int start_pos)
{
  //  printf("\n");
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] SUCCESS -> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
}

void debug_failed(node_t * n, const char *name, int start_pos)
{
  for (int i = 0; i < n->depth; i++)
    printf(" ");
  printf(" [%s] NO. -> %d - %d OK:%d, depth: %d \n", name, start_pos, n->pos, n->OK, n->depth);
}

node_t *match_queries(node_t * n, const char last_method[], int depth)
{
  const char name[] = "queries";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  //select  queries queries
  //0
  //string
  //external -> 0
  if (n_OK(n) == 1) {
    n = match_select(n, name, depth + 1);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[queries] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  //whitespace  select select
  //0
  //string
  //external -> 1
  if (n_OK(n) == 1) {
    n = match_whitespace(n, name, depth + 1);
  }
  //select_expr_list  select select
  //0
  //string
  //external -> 2
  if (n_OK(n) == 1) {
    n = match_select_expr_list(n, name, depth + 1);
  }
  //whitespace  select select
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "from") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  select select
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //identifier  select select
        //0
        //string
        //external -> 2
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
            }                   // end char
            //identifier  select select
            //0
            //string
            //external -> 1
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
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            //whitespace  select select
            //0
            //string
            //external -> 0
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //None  select select
            //0
            //string
            // order 1
            if (n_OK(n) == 1 && stricmp(n, (const char *) "as") == 0) {
              n->OK = 1;
              n->pos += 2;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            //whitespace  select select
            //0
            //string
            //external -> 2
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //identifier  select select
            //0
            //string
            //external -> 3
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

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }
  //whitespace  select select
  //0
  //string
  //external -> 5
  if (n_OK(n) == 1) {
    n = match_whitespace(n, name, depth + 1);
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "where") == 0) {
          n->OK = 1;
          n->pos += 5;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
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
            //whitespace  select select
            //0
            //string
            //external -> 0
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //expr  select select
            //0
            //string
            //external -> 1
            if (n_OK(n) == 1) {
              n = match_expr(n, name, depth + 1);
            }

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

      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //whitespace  select_expr select_expr
    //0
    //string
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_whitespace(n, name, depth + 1);
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
        //whitespace  select_expr select_expr
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select_expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_select_expr_list(node_t * n, const char last_method[], int depth)
{
  const char name[] = "select_expr_list";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  //select_expr  select_expr_list select_expr_list
  //0
  //string
  //external -> 0
  if (n_OK(n) == 1) {
    n = match_select_expr(n, name, depth + 1);
  }
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //whitespace  select_expr_list select_expr_list
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
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
        //whitespace  select_expr_list select_expr_list
        //0
        //string
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //select_expr  select_expr_list select_expr_list
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_select_expr(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[select_expr_list] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_subquery(node_t * n, const char last_method[], int depth)
{
  const char name[] = "subquery";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //whitespace  subquery subquery
    //0
    //string
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_whitespace(n, name, depth + 1);
    }
    //select  subquery subquery
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_select(n, name, depth + 1);
    }
    //whitespace  subquery subquery
    //0
    //string
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_whitespace(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[subquery] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      if (n_OK(n) == 1 && stricmp(n, (const char *) "or") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "xor") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "and") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
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
        //whitespace  expr expr
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  expr expr
        //0
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
            if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
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
        //external -> 4
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
      //string
      //external -> 8
      if (n_OK(n) == 1) {
        n = match_boolean_primary(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }
    if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {  //recur
      push(n->stack, n->pos);
      n = match_expr(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "is") == 0) {
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
            if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
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
    //item+1 3
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
            // order 0
            if (n_OK(n) == 1 && stricmp(n, (const char *) "all") == 0) {
              n->OK = 1;
              n->pos += 3;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            //list item switch
            //item+1 1
            if (n->OK == 0) {
              n->OK = 1;
              //string
              // order 1
              if (n_OK(n) == 1 && stricmp(n, (const char *) "any") == 0) {
                n->OK = 1;
                n->pos += 3;
                if (n->pos >= n->len)
                  n->pos = -1;
              } else {
                n->OK = 0;
              }

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
            }

            pop(n->stack);
          }

        }
        //whitespace  boolean_primary boolean_primary
        //1
        //string
        //external -> 5
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //subquery  boolean_primary boolean_primary
        //1
        //string
        //external -> 6
        if (n_OK(n) == 1) {
          n = match_subquery(n, name, depth + 1);
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
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_predicate(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[boolean_primary] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }
    if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {  //recur
      push(n->stack, n->pos);
      n = match_boolean_primary(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  //expr  where_expression where_expression
  //0
  //string
  //external -> 0
  if (n_OK(n) == 1) {
    n = match_expr(n, name, depth + 1);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[where_expression] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      //bit_expr  predicate predicate
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_bit_expr(n, name, depth + 1);
      }
      //whitespace  predicate predicate
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      // dict
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        //string
        // order None
        if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

        if (n->OK == 0) {
          n->OK = 1;
          n->pos = peek(n->stack);
        }
        pop(n->stack);
      }
      //whitespace  predicate predicate
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  predicate predicate
      //0
      //string
      // order 4
      if (n_OK(n) == 1 && stricmp(n, (const char *) "in") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //whitespace  predicate predicate
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //subquery  predicate predicate
      //0
      //string
      //external -> 6
      if (n_OK(n) == 1) {
        n = match_subquery(n, name, depth + 1);
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
        //bit_expr  predicate predicate
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          // order None
          if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  predicate predicate
        //0
        //string
        // order 4
        if (n_OK(n) == 1 && stricmp(n, (const char *) "in") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 5
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '(')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char

        //expr  predicate predicate
        //0
        //string
        //external -> 7
        if (n_OK(n) == 1) {
          n = match_expr(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            // dict
            //zero or more
            push(n->stack, n->OK);
            while (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // dict
              // GROUP
              if (n_OK(n) == 1) {
                // list
                //whitespace  predicate predicate
                //0
                //string
                //external -> 0
                if (n_OK(n) == 1) {
                  n = match_whitespace(n, name, depth + 1);
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
                }               // end char
                //whitespace  predicate predicate
                //0
                //string
                //external -> 2
                if (n_OK(n) == 1) {
                  n = match_whitespace(n, name, depth + 1);
                }
                //expr  predicate predicate
                //0
                //string
                //external -> 3
                if (n_OK(n) == 1) {
                  n = match_expr(n, name, depth + 1);
                }

              }

              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
              pop(n->stack);
            }
            n->OK = peek(n->stack);
            pop(n->stack);

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
                              n->value[n->pos] == ')')) {
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
        //bit_expr  predicate predicate
        //1
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //whitespace  predicate predicate
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          // order None
          if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //whitespace  predicate predicate
        //1
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  predicate predicate
        //1
        //string
        // order 4
        if (n_OK(n) == 1 && stricmp(n, (const char *) "between") == 0) {
          n->OK = 1;
          n->pos += 7;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  predicate predicate
        //1
        //string
        //external -> 5
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //bit_expr  predicate predicate
        //1
        //string
        //external -> 6
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //whitespace  predicate predicate
        //1
        //string
        //external -> 7
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  predicate predicate
        //1
        //string
        // order 8
        if (n_OK(n) == 1 && stricmp(n, (const char *) "and") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  predicate predicate
        //1
        //string
        //external -> 9
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //predicate  predicate predicate
        //1
        //list item switch
        //item 10  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
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
        //bit_expr  predicate predicate
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          // order None
          if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  predicate predicate
        //0
        //string
        // order 4
        if (n_OK(n) == 1 && stricmp(n, (const char *) "like") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 5
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  predicate predicate
        //0
        //string
        //external -> 6
        if (n_OK(n) == 1) {
          n = match_simple_expr(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            //whitespace  predicate predicate
            //0
            //string
            //external -> 0
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //None  predicate predicate
            //0
            //string
            // order 1
            if (n_OK(n) == 1 && stricmp(n, (const char *) "escape") == 0) {
              n->OK = 1;
              n->pos += 6;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            //whitespace  predicate predicate
            //0
            //string
            //external -> 2
            if (n_OK(n) == 1) {
              n = match_whitespace(n, name, depth + 1);
            }
            //simple_expr  predicate predicate
            //0
            //string
            //external -> 3
            if (n_OK(n) == 1) {
              n = match_simple_expr(n, name, depth + 1);
            }

          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
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
        //bit_expr  predicate predicate
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          // order None
          if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //None  predicate predicate
        //0
        //string
        // order 4
        if (n_OK(n) == 1 && stricmp(n, (const char *) "regexp") == 0) {
          n->OK = 1;
          n->pos += 6;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //whitespace  predicate predicate
        //0
        //string
        //external -> 5
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //bit_expr  predicate predicate
        //0
        //string
        //external -> 6
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
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
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_bit_expr(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[predicate] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }
    if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {  //recur
      push(n->stack, n->pos);
      n = match_predicate(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      //whitespace  bit_expr bit_expr
      //2
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //operations  bit_expr bit_expr
      //2
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_operations(n, name, depth + 1);
      }
      //whitespace  bit_expr bit_expr
      //2
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
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
        //bit_expr  bit_expr bit_expr
        //1
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  bit_expr bit_expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '+' ||
                              //string
                              n->value[n->pos] == '-')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //whitespace  bit_expr bit_expr
        //1
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //interval_expr  bit_expr bit_expr
        //1
        //string
        //external -> 4
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name, depth + 1);
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
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_simple_expr(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bit_expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }
    if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {  //recur
      push(n->stack, n->pos);
      n = match_bit_expr(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
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
    }                           // end char
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
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
      }                         // end char

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
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '+')) {
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
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
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
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
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
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
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
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 8
      if (n_OK(n) == 1 && stricmp(n, (const char *) "div") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 9
      if (n_OK(n) == 1 && stricmp(n, (const char *) "mod") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
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
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == '%')) {
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
    }
    //list item switch
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
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
      }                         // end char

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[operations] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      n = match_literal(n, name, depth + 1);
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
        n = match_identifier(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_subquery(n, name, depth + 1);
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
        //simple_expr  simple_expr simple_expr
        //2
        //list item switch
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //whitespace  simple_expr simple_expr
        //2
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
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
        }                       // end char
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
        }                       // end char
        //whitespace  simple_expr simple_expr
        //2
        //string
        //external -> 4
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  simple_expr simple_expr
        //2
        //list item switch
        //item 5  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_simple_expr(n, name, depth + 1);
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
        //whitespace  simple_expr simple_expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  simple_expr simple_expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_simple_expr(n, name, depth + 1);
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
        //whitespace  simple_expr simple_expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  simple_expr simple_expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_simple_expr(n, name, depth + 1);
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
        // dict
        if (n_OK(n) == 1 && (
                              //string
                              n->value[n->pos] == '~')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //whitespace  simple_expr simple_expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  simple_expr simple_expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_simple_expr(n, name, depth + 1);
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
        //whitespace  simple_expr simple_expr
        //1
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_whitespace(n, name, depth + 1);
        }
        //simple_expr  simple_expr simple_expr
        //1
        //list item switch
        //item 2  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_simple_expr(n, name, depth + 1);
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
      //string
      //external -> 8
      if (n_OK(n) == 1) {
        n = match_interval_expr(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[simple_expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }
    if (n_OK(n) == 1 && n->pos != -1 && start_pos != n->pos) {  //recur
      push(n->stack, n->pos);
      n = match_simple_expr(n, name, depth + 1);
      if (n->OK == 0) {
        n->pos = peek(n->stack);
        n->OK = 1;
      }
      pop(n->stack);
    }
#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      n = match_hex(n, name, depth + 1);
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
        n = match_bit(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_real(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_null(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_boolean(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_string(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[literal] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_interval_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "interval_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND") == 0) {
        n->OK = 1;
        n->pos += 6;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE") == 0) {
        n->OK = 1;
        n->pos += 6;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 3
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 4
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 5
      if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEK") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTH") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 7
      if (n_OK(n) == 1 && stricmp(n, (const char *) "QUARTER") == 0) {
        n->OK = 1;
        n->pos += 7;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 8
      if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 9
      if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 18;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 10
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 18;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 11
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_SECOND") == 0) {
        n->OK = 1;
        n->pos += 13;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 12
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 16;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 13
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_SECOND") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 14
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MINUTE") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 15
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 15;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 16
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 16
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_SECOND") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 17
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 17
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MINUTE") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 18
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 18
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_HOUR") == 0) {
        n->OK = 1;
        n->pos += 8;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 19
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 19
      if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR_MONTH") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[interval_expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_YEARS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEARS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  YEARS YEARS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEARS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_QUARTERS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUARTERS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  QUARTERS QUARTERS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTERS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MONTHS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTHS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  MONTHS MONTHS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTHS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_WEEKS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEKS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  WEEKS WEEKS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAYS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  DAYS DAYS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOURS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOURS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  HOURS HOURS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOURS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MINUTES(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTES";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  MINUTES MINUTES
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTES] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SECONDS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECONDS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  SECONDS SECONDS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECONDS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MICROSECONDS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MICROSECONDS";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //unsigned_int  MICROSECONDS MICROSECONDS
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECONDS] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //MICROSECONDS  MICROSECOND MICROSECOND
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_MICROSECONDS(n, name, depth + 1);
      }
      //whitespace  MICROSECOND MICROSECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  MICROSECOND MICROSECOND
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //SECONDS  SECOND SECOND
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
      }
      //whitespace  SECOND SECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  SECOND SECOND
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND") == 0) {
        n->OK = 1;
        n->pos += 6;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //MINUTES  MINUTE MINUTE
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      //whitespace  MINUTE MINUTE
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  MINUTE MINUTE
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE") == 0) {
        n->OK = 1;
        n->pos += 6;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOUR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //HOURS  HOUR HOUR
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      //whitespace  HOUR HOUR
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  HOUR HOUR
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //DAYS  DAY DAY
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_DAYS(n, name, depth + 1);
      }
      //whitespace  DAY DAY
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  DAY DAY
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_WEEK(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEK";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //WEEKS  WEEK WEEK
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_WEEKS(n, name, depth + 1);
      }
      //whitespace  WEEK WEEK
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  WEEK WEEK
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEK") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEK] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MONTH(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTH";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //MONTHS  MONTH MONTH
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_MONTHS(n, name, depth + 1);
      }
      //whitespace  MONTH MONTH
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  MONTH MONTH
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTH") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTH] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_QUARTER(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUARTER";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //QUARTERS  QUARTER QUARTER
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_QUARTERS(n, name, depth + 1);
      }
      //whitespace  QUARTER QUARTER
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  QUARTER QUARTER
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "QUARTER") == 0) {
        n->OK = 1;
        n->pos += 7;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTER] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_YEAR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEAR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    // dict
    // GROUP
    if (n_OK(n) == 1) {
      // list
      //YEARS  YEAR YEAR
      //0
      //string
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_YEARS(n, name, depth + 1);
      }
      //whitespace  YEAR YEAR
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  YEAR YEAR
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SECOND_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECOND_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //SECONDS  SECOND_MICROSECOND SECOND_MICROSECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
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
      //MICROSECONDS  SECOND_MICROSECOND SECOND_MICROSECOND
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_MICROSECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  SECOND_MICROSECOND SECOND_MICROSECOND
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  SECOND_MICROSECOND SECOND_MICROSECOND
      //0
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 18;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND_MICROSECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MINUTE_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //MINUTES  MINUTE_MICROSECOND MINUTE_MICROSECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  MINUTE_MICROSECOND MINUTE_MICROSECOND
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
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
      //MICROSECONDS  MINUTE_MICROSECOND MINUTE_MICROSECOND
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_MICROSECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  MINUTE_MICROSECOND MINUTE_MICROSECOND
      //0
      //string
      //external -> 7
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  MINUTE_MICROSECOND MINUTE_MICROSECOND
      //0
      //string
      // order 8
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 18;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_MICROSECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MINUTE_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //MINUTES  MINUTE_SECOND MINUTE_SECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  MINUTE_SECOND MINUTE_SECOND
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  MINUTE_SECOND MINUTE_SECOND
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  MINUTE_SECOND MINUTE_SECOND
      //0
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_SECOND") == 0) {
        n->OK = 1;
        n->pos += 13;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_SECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOUR_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //HOURS  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
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
      //MICROSECONDS  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      //external -> 7
      if (n_OK(n) == 1) {
        n = match_MICROSECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      //external -> 9
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  HOUR_MICROSECOND HOUR_MICROSECOND
      //0
      //string
      // order 10
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 16;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_MICROSECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOUR_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //HOURS  HOUR_SECOND HOUR_SECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  HOUR_SECOND HOUR_SECOND
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  HOUR_SECOND HOUR_SECOND
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  HOUR_SECOND HOUR_SECOND
      //0
      //string
      //external -> 7
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  HOUR_SECOND HOUR_SECOND
      //0
      //string
      // order 8
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_SECOND") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_SECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOUR_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //HOURS  HOUR_MINUTE HOUR_MINUTE
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  HOUR_MINUTE HOUR_MINUTE
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  HOUR_MINUTE HOUR_MINUTE
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  HOUR_MINUTE HOUR_MINUTE
      //0
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MINUTE") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_MINUTE] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_MICROSECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //DAYS  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_DAYS(n, name, depth + 1);
      }
      //HOURS  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 6
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
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
      //MICROSECONDS  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 8
      if (n_OK(n) == 1) {
        n = match_MICROSECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      //external -> 10
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  DAY_MICROSECOND DAY_MICROSECOND
      //0
      //string
      // order 11
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 15;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_MICROSECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_SECOND";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //DAYS  DAY_SECOND DAY_SECOND
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_DAYS(n, name, depth + 1);
      }
      //HOURS  DAY_SECOND DAY_SECOND
      //0
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  DAY_SECOND DAY_SECOND
      //0
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //SECONDS  DAY_SECOND DAY_SECOND
      //0
      //string
      //external -> 6
      if (n_OK(n) == 1) {
        n = match_SECONDS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  DAY_SECOND DAY_SECOND
      //0
      //string
      //external -> 8
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  DAY_SECOND DAY_SECOND
      //0
      //string
      // order 9
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_SECOND") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_SECOND] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_MINUTE";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //DAYS  DAY_MINUTE DAY_MINUTE
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_DAYS(n, name, depth + 1);
      }
      //HOURS  DAY_MINUTE DAY_MINUTE
      //0
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
      // dict
      if (n_OK(n) == 1 && (
                            //string
                            n->value[n->pos] == ':')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //MINUTES  DAY_MINUTE DAY_MINUTE
      //0
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_MINUTES(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  DAY_MINUTE DAY_MINUTE
      //0
      //string
      //external -> 6
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  DAY_MINUTE DAY_MINUTE
      //0
      //string
      // order 7
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MINUTE") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_MINUTE] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY_HOUR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_HOUR";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //DAYS  DAY_HOUR DAY_HOUR
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_DAYS(n, name, depth + 1);
      }
      //HOURS  DAY_HOUR DAY_HOUR
      //0
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_HOURS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  DAY_HOUR DAY_HOUR
      //0
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  DAY_HOUR DAY_HOUR
      //0
      //string
      // order 5
      if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_HOUR") == 0) {
        n->OK = 1;
        n->pos += 8;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_HOUR] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_YEAR_MONTH(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEAR_MONTH";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
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
      }                         // end char
      //YEARS  YEAR_MONTH YEAR_MONTH
      //0
      //string
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_YEARS(n, name, depth + 1);
      }
      //None  YEAR_MONTH YEAR_MONTH
      //0
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "-") == 0) {
        n->OK = 1;
        n->pos += 1;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //MONTHS  YEAR_MONTH YEAR_MONTH
      //0
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_MONTHS(n, name, depth + 1);
      }
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
      }                         // end char
      //whitespace  YEAR_MONTH YEAR_MONTH
      //0
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name, depth + 1);
      }
      //None  YEAR_MONTH YEAR_MONTH
      //0
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR_MONTH") == 0) {
        n->OK = 1;
        n->pos += 10;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR_MONTH] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unknown] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
  }                             // end char
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
    }                           // end char

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

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[hex] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
  }                             // end char
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
    }                           // end char

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

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bit] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
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
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "NULL") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[null] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
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
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "TRUE") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[true] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
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
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "FALSE") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[false] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      n = match_true(n, name, depth + 1);
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
        n = match_false(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[boolean] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_integer(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
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

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[real] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      n = match_signed_int(n, name, depth + 1);
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
        n = match_unsigned_int(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[integer] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[signed_int] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    }                           // end char

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

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unsigned_int] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[sign] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[exponent] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
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
        n = match_keywords(n, name, depth + 1);
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
    }                           //end NOT
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[identifier] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_keywords(node_t * n, const char last_method[], int depth)
{
  const char name[] = "keywords";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "from") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //list item switch
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "select") == 0) {
        n->OK = 1;
        n->pos += 6;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 2
      if (n_OK(n) == 1 && stricmp(n, (const char *) "where") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 3
      if (n_OK(n) == 1 && stricmp(n, (const char *) "on") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 4
      if (n_OK(n) == 1 && stricmp(n, (const char *) "and") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 5
      if (n_OK(n) == 1 && stricmp(n, (const char *) "or") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 6
      if (n_OK(n) == 1 && stricmp(n, (const char *) "xor") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 7
      if (n_OK(n) == 1 && stricmp(n, (const char *) "not") == 0) {
        n->OK = 1;
        n->pos += 3;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 8
      if (n_OK(n) == 1 && stricmp(n, (const char *) "in") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 9
      if (n_OK(n) == 1 && stricmp(n, (const char *) "between") == 0) {
        n->OK = 1;
        n->pos += 7;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      //string
      // order 10
      if (n_OK(n) == 1 && stricmp(n, (const char *) "like") == 0) {
        n->OK = 1;
        n->pos += 4;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[keywords] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //zero or more
  push(n->stack, n->OK);
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
    }                           // end char

    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    pop(n->stack);
  }
  n->OK = peek(n->stack);
  pop(n->stack);

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[whitespace] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
      n = match_single_quote_string(n, name, depth + 1);
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
        n = match_double_quote_string(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[string] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[single_quote_string] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[double_quote_string] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    // list
    //list item switch
    //item 0
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
    }                           // end char
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
          }                     // end char
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
          }                     // end char

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
          }                     // end char
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
          }                     // end char

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
          }                     // end char
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
          }                     // end char

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
          }                     // end char
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
          }                     // end char

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

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
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

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[comparison_operator] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "comment";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
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
      n = match_block_comment(n, name, depth + 1);
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
        n = match_single_comment(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[block_comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[single_comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
  }                             // end char

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[left_comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
  }                             // end char

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[right_comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
  }                             // end char

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[inline_comment] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
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
  debug_start(n, name, start_pos);
#endif
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
  }                             // end char
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
    }                           // end char

    if (n->OK == 0) {
      n->OK = 1;
      n->pos = peek(n->stack);
    }
    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[end_of_line] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ABS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ABS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ABS_FUNC ABS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ABS") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  ABS_FUNC ABS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ABS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ACOS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ACOS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ACOS_FUNC ACOS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ACOS") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  ACOS_FUNC ACOS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ACOS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ADDDATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ADDDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ADDDATE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "INTERVAL") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //interval_expr  ADDDATE_FUNC ADDDATE_FUNC
    //0
    //string
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_interval_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ADDDATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ADDTIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ADDTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ADDTIME") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    //None  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //expr  ADDTIME_FUNC ADDTIME_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ADDTIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ASCII_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ASCII_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ASCII_FUNC ASCII_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ASCII") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  ASCII_FUNC ASCII_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ASCII_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ASIN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ASIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ASIN_FUNC ASIN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ASIN") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  ASIN_FUNC ASIN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ASIN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ATAN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ATAN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ATAN_FUNC ATAN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ATAN") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  ATAN_FUNC ATAN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ATAN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ATAN2_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ATAN2_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ATAN2") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    //string
    // order 2
    if (n_OK(n) == 1 && stricmp(n, (const char *) "Y") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  ATAN2_FUNC ATAN2_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //X  ATAN2_FUNC ATAN2_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ATAN2_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_BIN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "BIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  BIN_FUNC BIN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "BIN") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  BIN_FUNC BIN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[BIN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_BIT_LENGTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "BIT_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  BIT_LENGTH_FUNC BIT_LENGTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "BIT_LENGTH") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  BIT_LENGTH_FUNC BIT_LENGTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[BIT_LENGTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CEILING_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CEILING_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CEILING_FUNC CEILING_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CEILING") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  CEILING_FUNC CEILING_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CEILING_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CEIL_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CEIL_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CEIL_FUNC CEIL_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CEIL") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  CEIL_FUNC CEIL_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CEIL_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CHARACTER_LENGTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CHARACTER_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CHARACTER_LENGTH_FUNC CHARACTER_LENGTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CHARACTER_LENGTH") == 0) {
      n->OK = 1;
      n->pos += 16;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  CHARACTER_LENGTH_FUNC CHARACTER_LENGTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHARACTER_LENGTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CHAR_LENGTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CHAR_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CHAR_LENGTH_FUNC CHAR_LENGTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CHAR_LENGTH") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  CHAR_LENGTH_FUNC CHAR_LENGTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHAR_LENGTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CHAR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CHAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CHAR_FUNC CHAR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CHAR") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  CHAR_FUNC CHAR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  CHAR_FUNC CHAR_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //N  CHAR_FUNC CHAR_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_N(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  CHAR_FUNC CHAR_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "USING") == 0) {
          n->OK = 1;
          n->pos += 5;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //charset_name  CHAR_FUNC CHAR_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_charset_name(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CHAR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CONCAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CONCAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CONCAT_FUNC CONCAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CONCAT") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  CONCAT_FUNC CONCAT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  CONCAT_FUNC CONCAT_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //string  CONCAT_FUNC CONCAT_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONCAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CONCAT_WS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CONCAT_WS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CONCAT_WS_FUNC CONCAT_WS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CONCAT_WS") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //separator  CONCAT_WS_FUNC CONCAT_WS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_separator(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  CONCAT_WS_FUNC CONCAT_WS_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //string  CONCAT_WS_FUNC CONCAT_WS_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONCAT_WS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CONVERT_TZ_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CONVERT_TZ_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CONVERT_TZ") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //dt  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_dt(n, name, depth + 1);
    }
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //from_tz  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_from_tz(n, name, depth + 1);
    }
    //None  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //to_tz  CONVERT_TZ_FUNC CONVERT_TZ_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_to_tz(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONVERT_TZ_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CONV_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CONV_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CONV_FUNC CONV_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CONV") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  CONV_FUNC CONV_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    //None  CONV_FUNC CONV_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //from_base  CONV_FUNC CONV_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_from_base(n, name, depth + 1);
    }
    //None  CONV_FUNC CONV_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //to_base  CONV_FUNC CONV_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_to_base(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CONV_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_COS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "COS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  COS_FUNC COS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "COS") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  COS_FUNC COS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[COS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_COT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "COT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  COT_FUNC COT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "COT") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  COT_FUNC COT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[COT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CRC32_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CRC32_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CRC32_FUNC CRC32_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CRC32") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  CRC32_FUNC CRC32_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CRC32_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CURDATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CURDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CURDATE_FUNC CURDATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CURDATE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURDATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CURRENT_DATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CURRENT_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CURRENT_DATE_FUNC CURRENT_DATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CURRENT_DATE") == 0) {
      n->OK = 1;
      n->pos += 12;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_DATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CURRENT_TIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CURRENT_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CURRENT_TIME_FUNC CURRENT_TIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CURRENT_TIME") == 0) {
      n->OK = 1;
      n->pos += 12;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  CURRENT_TIME_FUNC CURRENT_TIME_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_TIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CURRENT_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CURRENT_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CURRENT_TIMESTAMP_FUNC CURRENT_TIMESTAMP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CURRENT_TIMESTAMP") == 0) {
      n->OK = 1;
      n->pos += 17;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  CURRENT_TIMESTAMP_FUNC CURRENT_TIMESTAMP_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURRENT_TIMESTAMP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_CURTIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "CURTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  CURTIME_FUNC CURTIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "CURTIME") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  CURTIME_FUNC CURTIME_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[CURTIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DATE_ADD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DATE_ADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DATE_ADD") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "INTERVAL") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //interval_expr  DATE_ADD_FUNC DATE_ADD_FUNC
    //0
    //string
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_interval_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_ADD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DATEDIFF_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DATEDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DATEDIFF") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    //None  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //expr  DATEDIFF_FUNC DATEDIFF_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATEDIFF_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DATE_FUNC DATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DATE") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  DATE_FUNC DATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DATE_FORMAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DATE_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DATE_FORMAT") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    //None  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //format  DATE_FORMAT_FUNC DATE_FORMAT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_format(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_FORMAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DATE_SUB_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DATE_SUB_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DATE_SUB") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "INTERVAL") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //interval_expr  DATE_SUB_FUNC DATE_SUB_FUNC
    //0
    //string
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_interval_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DATE_SUB_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAY_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DAY_FUNC DAY_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DAY_FUNC DAY_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAY_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAYNAME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYNAME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DAYNAME_FUNC DAYNAME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAYNAME") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DAYNAME_FUNC DAYNAME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYNAME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAYOFMONTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYOFMONTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DAYOFMONTH_FUNC DAYOFMONTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAYOFMONTH") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DAYOFMONTH_FUNC DAYOFMONTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFMONTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAYOFWEEK_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYOFWEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DAYOFWEEK_FUNC DAYOFWEEK_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAYOFWEEK") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DAYOFWEEK_FUNC DAYOFWEEK_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFWEEK_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DAYOFYEAR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYOFYEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DAYOFYEAR_FUNC DAYOFYEAR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAYOFYEAR") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  DAYOFYEAR_FUNC DAYOFYEAR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DAYOFYEAR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_DEGREES_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DEGREES_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  DEGREES_FUNC DEGREES_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DEGREES") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  DEGREES_FUNC DEGREES_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[DEGREES_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ELT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ELT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ELT_FUNC ELT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ELT") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  ELT_FUNC ELT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  ELT_FUNC ELT_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //string  ELT_FUNC ELT_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ELT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_EXPORT_SET_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "EXPORT_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "EXPORT_SET") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //bits  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_bits(n, name, depth + 1);
    }
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //on  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_on(n, name, depth + 1);
    }
    //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //off  EXPORT_SET_FUNC EXPORT_SET_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_off(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //separator  EXPORT_SET_FUNC EXPORT_SET_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_separator(n, name, depth + 1);
        }
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // dict
          // GROUP
          if (n_OK(n) == 1) {
            // list
            //None  EXPORT_SET_FUNC EXPORT_SET_FUNC
            //0
            //string
            // order 0
            if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
              n->OK = 1;
              n->pos += 1;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            //number_of_bits  EXPORT_SET_FUNC EXPORT_SET_FUNC
            //0
            //string
            //external -> 1
            if (n_OK(n) == 1) {
              n = match_number_of_bits(n, name, depth + 1);
            }

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
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXPORT_SET_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_EXP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "EXP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  EXP_FUNC EXP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "EXP") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  EXP_FUNC EXP_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_EXTRACT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "EXTRACT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "EXTRACT") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //unit  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_unit(n, name, depth + 1);
    }
    //None  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //date  EXTRACT_FUNC EXTRACT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[EXTRACT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FIELD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FIELD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FIELD_FUNC FIELD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FIELD") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  FIELD_FUNC FIELD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  FIELD_FUNC FIELD_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //string  FIELD_FUNC FIELD_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FIELD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FIND_IN_SET_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FIND_IN_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FIND_IN_SET") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //strlist  FIND_IN_SET_FUNC FIND_IN_SET_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_strlist(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FIND_IN_SET_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FLOOR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FLOOR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FLOOR_FUNC FLOOR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FLOOR") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  FLOOR_FUNC FLOOR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FLOOR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FORMAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FORMAT_FUNC FORMAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FORMAT") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  FORMAT_FUNC FORMAT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    //None  FORMAT_FUNC FORMAT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //D  FORMAT_FUNC FORMAT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_D(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  FORMAT_FUNC FORMAT_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //locale  FORMAT_FUNC FORMAT_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_locale(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FORMAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FROM_BASE64_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FROM_BASE64_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FROM_BASE64_FUNC FROM_BASE64_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM_BASE64") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  FROM_BASE64_FUNC FROM_BASE64_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_BASE64_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FROM_DAYS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FROM_DAYS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FROM_DAYS_FUNC FROM_DAYS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM_DAYS") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  FROM_DAYS_FUNC FROM_DAYS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_DAYS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_FROM_UNIXTIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "FROM_UNIXTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM_UNIXTIME") == 0) {
      n->OK = 1;
      n->pos += 13;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //unix_timestamp  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_unix_timestamp(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //format  FROM_UNIXTIME_FUNC FROM_UNIXTIME_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_format(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[FROM_UNIXTIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_GET_FORMAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "GET_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  GET_FORMAT_FUNC GET_FORMAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "GET_FORMAT") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
          // order 0
          if (n_OK(n) == 1 && stricmp(n, (const char *) "DATE") == 0) {
            n->OK = 1;
            n->pos += 4;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //list item switch
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 1
            if (n_OK(n) == 1 && stricmp(n, (const char *) "TIME") == 0) {
              n->OK = 1;
              n->pos += 4;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //list item switch
          //item+1 2
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 2
            if (n_OK(n) == 1 && stricmp(n, (const char *) "DATETIME") == 0) {
              n->OK = 1;
              n->pos += 8;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
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
    //None  GET_FORMAT_FUNC GET_FORMAT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
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
        // dict
        //OR
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // list
          //list item switch
          //item 0
          //string
          // order 0
          if (n_OK(n) == 1 && stricmp(n, (const char *) "EUR") == 0) {
            n->OK = 1;
            n->pos += 3;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }
          //list item switch
          //item+1 1
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 1
            if (n_OK(n) == 1 && stricmp(n, (const char *) "USA") == 0) {
              n->OK = 1;
              n->pos += 3;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //list item switch
          //item+1 2
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 2
            if (n_OK(n) == 1 && stricmp(n, (const char *) "JIS") == 0) {
              n->OK = 1;
              n->pos += 3;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //list item switch
          //item+1 3
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 3
            if (n_OK(n) == 1 && stricmp(n, (const char *) "ISO") == 0) {
              n->OK = 1;
              n->pos += 3;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
          }
          //list item switch
          //item+1 4
          if (n->OK == 0) {
            n->OK = 1;
            //string
            // order 4
            if (n_OK(n) == 1 && stricmp(n, (const char *) "INTERNAL") == 0) {
              n->OK = 1;
              n->pos += 8;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
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
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[GET_FORMAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HEX_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  HEX_FUNC HEX_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HEX") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

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
        n = match_string(n, name, depth + 1);
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
          n = match_N(n, name, depth + 1);
        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HEX_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_HOUR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  HOUR_FUNC HOUR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //time  HOUR_FUNC HOUR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_time(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[HOUR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_INSERT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "INSERT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  INSERT_FUNC INSERT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "INSERT") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  INSERT_FUNC INSERT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  INSERT_FUNC INSERT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //pos  INSERT_FUNC INSERT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_pos(n, name, depth + 1);
    }
    //None  INSERT_FUNC INSERT_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  INSERT_FUNC INSERT_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    //None  INSERT_FUNC INSERT_FUNC
    //0
    //string
    // order 7
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //newstr  INSERT_FUNC INSERT_FUNC
    //0
    //string
    //external -> 8
    if (n_OK(n) == 1) {
      n = match_newstr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[INSERT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_INSTR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "INSTR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  INSTR_FUNC INSTR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "INSTR") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  INSTR_FUNC INSTR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  INSTR_FUNC INSTR_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //substr  INSTR_FUNC INSTR_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_substr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[INSTR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LAST_DAY_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LAST_DAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LAST_DAY_FUNC LAST_DAY_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LAST_DAY") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  LAST_DAY_FUNC LAST_DAY_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LAST_DAY_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LCASE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LCASE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LCASE_FUNC LCASE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LCASE") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LCASE_FUNC LCASE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LCASE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LEFT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LEFT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LEFT_FUNC LEFT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LEFT") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LEFT_FUNC LEFT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  LEFT_FUNC LEFT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  LEFT_FUNC LEFT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LEFT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LENGTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LENGTH_FUNC LENGTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LENGTH") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LENGTH_FUNC LENGTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LENGTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LN_FUNC LN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LN") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  LN_FUNC LN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOAD_FILE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOAD_FILE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOAD_FILE_FUNC LOAD_FILE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOAD_FILE") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //file_name  LOAD_FILE_FUNC LOAD_FILE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_file_name(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOAD_FILE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOCALTIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOCALTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOCALTIME_FUNC LOCALTIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOCALTIME") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  LOCALTIME_FUNC LOCALTIME_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCALTIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOCALTIMESTAMP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOCALTIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOCALTIMESTAMP_FUNC LOCALTIMESTAMP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOCALTIMESTAMP") == 0) {
      n->OK = 1;
      n->pos += 14;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  LOCALTIMESTAMP_FUNC LOCALTIMESTAMP_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCALTIMESTAMP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOCATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOCATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOCATE_FUNC LOCATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOCATE") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //substr  LOCATE_FUNC LOCATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_substr(n, name, depth + 1);
    }
    //None  LOCATE_FUNC LOCATE_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //string  LOCATE_FUNC LOCATE_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  LOCATE_FUNC LOCATE_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //pos  LOCATE_FUNC LOCATE_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_pos(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOCATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOG10_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOG10_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOG10_FUNC LOG10_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOG10") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  LOG10_FUNC LOG10_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG10_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOG2_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOG2_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOG2_FUNC LOG2_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOG2") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  LOG2_FUNC LOG2_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG2_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOG_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOG_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOG_FUNC LOG_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOG") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //B  LOG_FUNC LOG_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_B(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    //None  LOG_FUNC LOG_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //X  LOG_FUNC LOG_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOG_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LOWER_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LOWER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LOWER_FUNC LOWER_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LOWER") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LOWER_FUNC LOWER_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LOWER_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LPAD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LPAD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LPAD_FUNC LPAD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LPAD") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LPAD_FUNC LPAD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  LPAD_FUNC LPAD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  LPAD_FUNC LPAD_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    //None  LPAD_FUNC LPAD_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //padstr  LPAD_FUNC LPAD_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_padstr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LPAD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_LTRIM_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "LTRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  LTRIM_FUNC LTRIM_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "LTRIM") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  LTRIM_FUNC LTRIM_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[LTRIM_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MAKEDATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MAKEDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MAKEDATE") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //year  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_year(n, name, depth + 1);
    }
    //None  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //dayofyear  MAKEDATE_FUNC MAKEDATE_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_dayofyear(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKEDATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MAKE_SET_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MAKE_SET_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MAKE_SET_FUNC MAKE_SET_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MAKE_SET") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //bits  MAKE_SET_FUNC MAKE_SET_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_bits(n, name, depth + 1);
    }
    // dict
    //zero or more
    push(n->stack, n->OK);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  MAKE_SET_FUNC MAKE_SET_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //string  MAKE_SET_FUNC MAKE_SET_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    n->OK = peek(n->stack);
    pop(n->stack);
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKE_SET_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MAKETIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MAKETIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MAKETIME") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //hour  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_hour(n, name, depth + 1);
    }
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //minute  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_minute(n, name, depth + 1);
    }
    //None  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //second  MAKETIME_FUNC MAKETIME_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_second(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MAKETIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MICROSECOND_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MICROSECOND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MICROSECOND_FUNC MICROSECOND_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  MICROSECOND_FUNC MICROSECOND_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MICROSECOND_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MID_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MID_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MID_FUNC MID_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MID") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  MID_FUNC MID_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  MID_FUNC MID_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //pos  MID_FUNC MID_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_pos(n, name, depth + 1);
    }
    //None  MID_FUNC MID_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  MID_FUNC MID_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MID_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MINUTE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MINUTE_FUNC MINUTE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //time  MINUTE_FUNC MINUTE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_time(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MINUTE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MOD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MOD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MOD_FUNC MOD_FUNC
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
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  MOD_FUNC MOD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    //None  MOD_FUNC MOD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  MOD_FUNC MOD_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "M") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MOD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MONTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MONTH_FUNC MONTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTH") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  MONTH_FUNC MONTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_MONTHNAME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTHNAME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  MONTHNAME_FUNC MONTHNAME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTHNAME") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  MONTHNAME_FUNC MONTHNAME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[MONTHNAME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_NOW_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "NOW_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  NOW_FUNC NOW_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "NOW") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  NOW_FUNC NOW_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[NOW_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_OCTET_LENGTH_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "OCTET_LENGTH_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  OCTET_LENGTH_FUNC OCTET_LENGTH_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "OCTET_LENGTH") == 0) {
      n->OK = 1;
      n->pos += 12;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  OCTET_LENGTH_FUNC OCTET_LENGTH_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[OCTET_LENGTH_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_OCT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "OCT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  OCT_FUNC OCT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "OCT") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  OCT_FUNC OCT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[OCT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ORD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ORD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ORD_FUNC ORD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ORD") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  ORD_FUNC ORD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ORD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_PERIOD_ADD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "PERIOD_ADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "PERIOD_ADD") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    //string
    // order 2
    if (n_OK(n) == 1 && stricmp(n, (const char *) "P") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //N  PERIOD_ADD_FUNC PERIOD_ADD_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PERIOD_ADD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_PERIOD_DIFF_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "PERIOD_DIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "PERIOD_DIFF") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    //string
    // order 2
    if (n_OK(n) == 1 && stricmp(n, (const char *) "P1") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  PERIOD_DIFF_FUNC PERIOD_DIFF_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "P2") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PERIOD_DIFF_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_PI_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "PI_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  PI_FUNC PI_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "PI") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[PI_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_POSITION_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "POSITION_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  POSITION_FUNC POSITION_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "POSITION") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //substr  POSITION_FUNC POSITION_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_substr(n, name, depth + 1);
    }
    //None  POSITION_FUNC POSITION_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) "IN") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //string  POSITION_FUNC POSITION_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POSITION_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_POWER_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "POWER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  POWER_FUNC POWER_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "POWER") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  POWER_FUNC POWER_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    //None  POWER_FUNC POWER_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  POWER_FUNC POWER_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "Y") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POWER_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_POW_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "POW_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  POW_FUNC POW_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "POW") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  POW_FUNC POW_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    //None  POW_FUNC POW_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //None  POW_FUNC POW_FUNC
    //0
    //string
    // order 4
    if (n_OK(n) == 1 && stricmp(n, (const char *) "Y") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[POW_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_QUARTER_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUARTER_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  QUARTER_FUNC QUARTER_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "QUARTER") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  QUARTER_FUNC QUARTER_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUARTER_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_QUOTE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUOTE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  QUOTE_FUNC QUOTE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "QUOTE") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  QUOTE_FUNC QUOTE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[QUOTE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_RADIANS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "RADIANS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  RADIANS_FUNC RADIANS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "RADIANS") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  RADIANS_FUNC RADIANS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RADIANS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_RAND_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "RAND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  RAND_FUNC RAND_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "RAND") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //N  RAND_FUNC RAND_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_N(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RAND_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_REPEAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "REPEAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  REPEAT_FUNC REPEAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "REPEAT") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  REPEAT_FUNC REPEAT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  REPEAT_FUNC REPEAT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //count  REPEAT_FUNC REPEAT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_count(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REPEAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_REPLACE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "REPLACE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "REPLACE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //from_str  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_from_str(n, name, depth + 1);
    }
    //None  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //to_str  REPLACE_FUNC REPLACE_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_to_str(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REPLACE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_REVERSE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "REVERSE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  REVERSE_FUNC REVERSE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "REVERSE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  REVERSE_FUNC REVERSE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[REVERSE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_RIGHT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "RIGHT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  RIGHT_FUNC RIGHT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "RIGHT") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  RIGHT_FUNC RIGHT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  RIGHT_FUNC RIGHT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  RIGHT_FUNC RIGHT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RIGHT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_ROUND_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "ROUND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  ROUND_FUNC ROUND_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "ROUND") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  ROUND_FUNC ROUND_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  ROUND_FUNC ROUND_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //D  ROUND_FUNC ROUND_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_D(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[ROUND_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_RPAD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "RPAD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  RPAD_FUNC RPAD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "RPAD") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  RPAD_FUNC RPAD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  RPAD_FUNC RPAD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //len  RPAD_FUNC RPAD_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_len(n, name, depth + 1);
    }
    //None  RPAD_FUNC RPAD_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //padstr  RPAD_FUNC RPAD_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_padstr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RPAD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_RTRIM_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "RTRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  RTRIM_FUNC RTRIM_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "RTRIM") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  RTRIM_FUNC RTRIM_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[RTRIM_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SECOND_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECOND_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SECOND_FUNC SECOND_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //time  SECOND_FUNC SECOND_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_time(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SECOND_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SEC_TO_TIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SEC_TO_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SEC_TO_TIME_FUNC SEC_TO_TIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SEC_TO_TIME") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //seconds  SEC_TO_TIME_FUNC SEC_TO_TIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_seconds(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SEC_TO_TIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SIGN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SIGN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SIGN_FUNC SIGN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SIGN") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  SIGN_FUNC SIGN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SIGN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SIN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SIN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SIN_FUNC SIN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SIN") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  SIN_FUNC SIN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SIN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SOUNDEX_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SOUNDEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SOUNDEX_FUNC SOUNDEX_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SOUNDEX") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  SOUNDEX_FUNC SOUNDEX_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SOUNDEX_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SPACE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SPACE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SPACE_FUNC SPACE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SPACE") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //N  SPACE_FUNC SPACE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_N(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SPACE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SQRT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SQRT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SQRT_FUNC SQRT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SQRT") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  SQRT_FUNC SQRT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SQRT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_STR_TO_DATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "STR_TO_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "STR_TO_DATE") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //format  STR_TO_DATE_FUNC STR_TO_DATE_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_format(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[STR_TO_DATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SUBDATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SUBDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SUBDATE_FUNC SUBDATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SUBDATE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

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
        //date  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_date(n, name, depth + 1);
        }
        //None  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //string
        // order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //None  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "INTERVAL") == 0) {
          n->OK = 1;
          n->pos += 8;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //interval_expr  SUBDATE_FUNC SUBDATE_FUNC
        //0
        //string
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name, depth + 1);
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
          //expr  SUBDATE_FUNC SUBDATE_FUNC
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_expr(n, name, depth + 1);
          }
          //None  SUBDATE_FUNC SUBDATE_FUNC
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //days  SUBDATE_FUNC SUBDATE_FUNC
          //0
          //string
          //external -> 2
          if (n_OK(n) == 1) {
            n = match_days(n, name, depth + 1);
          }

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBDATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SUBSTRING_INDEX_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SUBSTRING_INDEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SUBSTRING_INDEX") == 0) {
      n->OK = 1;
      n->pos += 15;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //delim  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_delim(n, name, depth + 1);
    }
    //None  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //count  SUBSTRING_INDEX_FUNC SUBSTRING_INDEX_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_count(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTRING_INDEX_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SUBSTRING_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SUBSTRING_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SUBSTRING_FUNC SUBSTRING_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SUBSTRING") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

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
        //string  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }
        //None  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        //string
        // order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //pos  SUBSTRING_FUNC SUBSTRING_FUNC
        //0
        //string
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_pos(n, name, depth + 1);
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
          //string  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_string(n, name, depth + 1);
          }
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM") == 0) {
            n->OK = 1;
            n->pos += 4;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //pos  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          //external -> 2
          if (n_OK(n) == 1) {
            n = match_pos(n, name, depth + 1);
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
          //string  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_string(n, name, depth + 1);
          }
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //pos  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          //external -> 2
          if (n_OK(n) == 1) {
            n = match_pos(n, name, depth + 1);
          }
          //None  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          // order 3
          if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //len  SUBSTRING_FUNC SUBSTRING_FUNC
          //0
          //string
          //external -> 4
          if (n_OK(n) == 1) {
            n = match_len(n, name, depth + 1);
          }

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTRING_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SUBSTR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SUBSTR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SUBSTR_FUNC SUBSTR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SUBSTR") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

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
        //string  SUBSTR_FUNC SUBSTR_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_string(n, name, depth + 1);
        }
        //None  SUBSTR_FUNC SUBSTR_FUNC
        //0
        //string
        // order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //pos  SUBSTR_FUNC SUBSTR_FUNC
        //0
        //string
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_pos(n, name, depth + 1);
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
          //string  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_string(n, name, depth + 1);
          }
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM") == 0) {
            n->OK = 1;
            n->pos += 4;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //pos  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          //external -> 2
          if (n_OK(n) == 1) {
            n = match_pos(n, name, depth + 1);
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
          //string  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          //external -> 0
          if (n_OK(n) == 1) {
            n = match_string(n, name, depth + 1);
          }
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          // order 1
          if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //pos  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          //external -> 2
          if (n_OK(n) == 1) {
            n = match_pos(n, name, depth + 1);
          }
          //None  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          // order 3
          if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
            n->OK = 1;
            n->pos += 1;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }
          //len  SUBSTR_FUNC SUBSTR_FUNC
          //0
          //string
          //external -> 4
          if (n_OK(n) == 1) {
            n = match_len(n, name, depth + 1);
          }

        }

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }
      }

      pop(n->stack);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBSTR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SUBTIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SUBTIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SUBTIME") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    //None  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //expr  SUBTIME_FUNC SUBTIME_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SUBTIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_SYSDATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SYSDATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  SYSDATE_FUNC SYSDATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SYSDATE") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  SYSDATE_FUNC SYSDATE_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[SYSDATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TAN_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TAN_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TAN_FUNC TAN_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TAN") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  TAN_FUNC TAN_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TAN_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIMEDIFF_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIMEDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIMEDIFF") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    //None  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //expr  TIMEDIFF_FUNC TIMEDIFF_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMEDIFF_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIME_FUNC TIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIME") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  TIME_FUNC TIME_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIME_FORMAT_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIME_FORMAT_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIME_FORMAT") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //time  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_time(n, name, depth + 1);
    }
    //None  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //format  TIME_FORMAT_FUNC TIME_FORMAT_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_format(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_FORMAT_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIMESTAMPADD_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIMESTAMPADD_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIMESTAMPADD") == 0) {
      n->OK = 1;
      n->pos += 12;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //unit  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_unit(n, name, depth + 1);
    }
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //interval  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_interval(n, name, depth + 1);
    }
    //None  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //datetime_expr  TIMESTAMPADD_FUNC TIMESTAMPADD_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_datetime_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMPADD_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIMESTAMPDIFF_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIMESTAMPDIFF_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIMESTAMPDIFF") == 0) {
      n->OK = 1;
      n->pos += 13;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //unit  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_unit(n, name, depth + 1);
    }
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //datetime_expr  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_datetime_expr(n, name, depth + 1);
    }
    //None  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    // order 5
    if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //datetime_expr  TIMESTAMPDIFF_FUNC TIMESTAMPDIFF_FUNC
    //0
    //string
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_datetime_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMPDIFF_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIMESTAMP_FUNC TIMESTAMP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIMESTAMP") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  TIMESTAMP_FUNC TIMESTAMP_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  TIMESTAMP_FUNC TIMESTAMP_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //expr  TIMESTAMP_FUNC TIMESTAMP_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_expr(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIMESTAMP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TIME_TO_SEC_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TIME_TO_SEC_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TIME_TO_SEC_FUNC TIME_TO_SEC_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TIME_TO_SEC") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //time  TIME_TO_SEC_FUNC TIME_TO_SEC_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_time(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TIME_TO_SEC_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TO_BASE64_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TO_BASE64_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TO_BASE64_FUNC TO_BASE64_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TO_BASE64") == 0) {
      n->OK = 1;
      n->pos += 9;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  TO_BASE64_FUNC TO_BASE64_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_BASE64_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TO_DAYS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TO_DAYS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TO_DAYS_FUNC TO_DAYS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TO_DAYS") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  TO_DAYS_FUNC TO_DAYS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_DAYS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TO_SECONDS_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TO_SECONDS_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TO_SECONDS_FUNC TO_SECONDS_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TO_SECONDS") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //expr  TO_SECONDS_FUNC TO_SECONDS_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TO_SECONDS_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TRIM_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TRIM_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TRIM_FUNC TRIM_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TRIM") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
            //OR
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              // list
              //list item switch
              //item 0
              //string
              // order 0
              if (n_OK(n) == 1 && stricmp(n, (const char *) "BOTH") == 0) {
                n->OK = 1;
                n->pos += 4;
                if (n->pos >= n->len)
                  n->pos = -1;
              } else {
                n->OK = 0;
              }
              if (n->OK == 0) {
                n->pos = peek(n->stack);
              }
              //list item switch
              //item+1 1
              if (n->OK == 0) {
                n->OK = 1;
                //string
                // order 1
                if (n_OK(n) == 1 && stricmp(n, (const char *) "LEADING") == 0) {
                  n->OK = 1;
                  n->pos += 7;
                  if (n->pos >= n->len)
                    n->pos = -1;
                } else {
                  n->OK = 0;
                }

                if (n->OK == 0) {
                  n->pos = peek(n->stack);
                }
              }
              //list item switch
              //item+1 2
              if (n->OK == 0) {
                n->OK = 1;
                //string
                // order 2
                if (n_OK(n) == 1 && stricmp(n, (const char *) "TRAILING") == 0) {
                  n->OK = 1;
                  n->pos += 8;
                  if (n->pos >= n->len)
                    n->pos = -1;
                } else {
                  n->OK = 0;
                }

                if (n->OK == 0) {
                  n->pos = peek(n->stack);
                }
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
        // dict
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //string
          // order None
          if (n_OK(n) == 1 && stricmp(n, (const char *) "{remstr") == 0) {
            n->OK = 1;
            n->pos += 7;
            if (n->pos >= n->len)
              n->pos = -1;
          } else {
            n->OK = 0;
          }


          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //None  TRIM_FUNC TRIM_FUNC
        //0
        //string
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "}") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //None  TRIM_FUNC TRIM_FUNC
        //0
        //string
        // order 3
        if (n_OK(n) == 1 && stricmp(n, (const char *) "FROM") == 0) {
          n->OK = 1;
          n->pos += 4;
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
    //string  TRIM_FUNC TRIM_FUNC
    //0
    //string
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TRIM_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_TRUNCATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "TRUNCATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  TRUNCATE_FUNC TRUNCATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "TRUNCATE") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //X  TRUNCATE_FUNC TRUNCATE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_X(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  TRUNCATE_FUNC TRUNCATE_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //D  TRUNCATE_FUNC TRUNCATE_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_D(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[TRUNCATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UCASE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UCASE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UCASE_FUNC UCASE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UCASE") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  UCASE_FUNC UCASE_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UCASE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UNHEX_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UNHEX_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UNHEX_FUNC UNHEX_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UNHEX") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //string  UNHEX_FUNC UNHEX_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_string(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UNHEX_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UNIX_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UNIX_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UNIX_TIMESTAMP_FUNC UNIX_TIMESTAMP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UNIX_TIMESTAMP") == 0) {
      n->OK = 1;
      n->pos += 14;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      //string
      // order None
      if (n_OK(n) == 1 && stricmp(n, (const char *) "{date") == 0) {
        n->OK = 1;
        n->pos += 5;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }


      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    //None  UNIX_TIMESTAMP_FUNC UNIX_TIMESTAMP_FUNC
    //0
    //string
    // order 3
    if (n_OK(n) == 1 && stricmp(n, (const char *) "}") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UNIX_TIMESTAMP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UTC_DATE_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UTC_DATE_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UTC_DATE_FUNC UTC_DATE_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UTC_DATE") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_DATE_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UTC_TIMESTAMP_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UTC_TIMESTAMP_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UTC_TIMESTAMP_FUNC UTC_TIMESTAMP_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UTC_TIMESTAMP") == 0) {
      n->OK = 1;
      n->pos += 13;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  UTC_TIMESTAMP_FUNC UTC_TIMESTAMP_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_TIMESTAMP_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_UTC_TIME_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "UTC_TIME_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  UTC_TIME_FUNC UTC_TIME_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "UTC_TIME") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
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
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //fsp  UTC_TIME_FUNC UTC_TIME_FUNC
        //0
        //string
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_fsp(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[UTC_TIME_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_WEEK_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  WEEK_FUNC WEEK_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEK") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  WEEK_FUNC WEEK_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  WEEK_FUNC WEEK_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //mode  WEEK_FUNC WEEK_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_mode(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEK_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_WEEKDAY_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEKDAY_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  WEEKDAY_FUNC WEEKDAY_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEKDAY") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  WEEKDAY_FUNC WEEKDAY_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKDAY_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_WEEKOFYEAR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEKOFYEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  WEEKOFYEAR_FUNC WEEKOFYEAR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEKOFYEAR") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  WEEKOFYEAR_FUNC WEEKOFYEAR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[WEEKOFYEAR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_YEAR_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEAR_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  YEAR_FUNC YEAR_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  YEAR_FUNC YEAR_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEAR_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_YEARWEEK_FUNC(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEARWEEK_FUNC";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //None  YEARWEEK_FUNC YEARWEEK_FUNC
    //0
    //string
    // order 0
    if (n_OK(n) == 1 && stricmp(n, (const char *) "YEARWEEK") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    // dict
    if (n_OK(n) == 1 && (
                          //string
                          n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //date  YEARWEEK_FUNC YEARWEEK_FUNC
    //0
    //string
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_date(n, name, depth + 1);
    }
    // dict
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // dict
      // GROUP
      if (n_OK(n) == 1) {
        // list
        //None  YEARWEEK_FUNC YEARWEEK_FUNC
        //0
        //string
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) ",") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //mode  YEARWEEK_FUNC YEARWEEK_FUNC
        //0
        //string
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_mode(n, name, depth + 1);
        }

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
                          n->value[n->pos] == ')')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[YEARWEEK_FUNC] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_functions(node_t * n, const char last_method[], int depth)
{
  const char name[] = "functions";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
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
      n = match_ABS_FUNC(n, name, depth + 1);
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
        n = match_ACOS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_ADDDATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_ADDTIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 4
      if (n_OK(n) == 1) {
        n = match_ASCII_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 5
      if (n_OK(n) == 1) {
        n = match_ASIN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 6
      if (n_OK(n) == 1) {
        n = match_ATAN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 7
      if (n_OK(n) == 1) {
        n = match_ATAN2_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 8
      if (n_OK(n) == 1) {
        n = match_BIN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 9
      if (n_OK(n) == 1) {
        n = match_BIT_LENGTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 10
      if (n_OK(n) == 1) {
        n = match_CEILING_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 11
      if (n_OK(n) == 1) {
        n = match_CEIL_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 12
      if (n_OK(n) == 1) {
        n = match_CHARACTER_LENGTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 13
      if (n_OK(n) == 1) {
        n = match_CHAR_LENGTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 14
      if (n_OK(n) == 1) {
        n = match_CHAR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 15
      if (n_OK(n) == 1) {
        n = match_CONCAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 16
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 16
      if (n_OK(n) == 1) {
        n = match_CONCAT_WS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 17
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 17
      if (n_OK(n) == 1) {
        n = match_CONVERT_TZ_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 18
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 18
      if (n_OK(n) == 1) {
        n = match_CONV_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 19
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 19
      if (n_OK(n) == 1) {
        n = match_COS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 20
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 20
      if (n_OK(n) == 1) {
        n = match_COT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 21
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 21
      if (n_OK(n) == 1) {
        n = match_CRC32_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 22
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 22
      if (n_OK(n) == 1) {
        n = match_CURDATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 23
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 23
      if (n_OK(n) == 1) {
        n = match_CURRENT_DATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 24
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 24
      if (n_OK(n) == 1) {
        n = match_CURRENT_TIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 25
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 25
      if (n_OK(n) == 1) {
        n = match_CURRENT_TIMESTAMP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 26
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 26
      if (n_OK(n) == 1) {
        n = match_CURTIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 27
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 27
      if (n_OK(n) == 1) {
        n = match_DATE_ADD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 28
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 28
      if (n_OK(n) == 1) {
        n = match_DATEDIFF_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 29
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 29
      if (n_OK(n) == 1) {
        n = match_DATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 30
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 30
      if (n_OK(n) == 1) {
        n = match_DATE_FORMAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 31
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 31
      if (n_OK(n) == 1) {
        n = match_DATE_SUB_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 32
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 32
      if (n_OK(n) == 1) {
        n = match_DAY_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 33
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 33
      if (n_OK(n) == 1) {
        n = match_DAYNAME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 34
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 34
      if (n_OK(n) == 1) {
        n = match_DAYOFMONTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 35
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 35
      if (n_OK(n) == 1) {
        n = match_DAYOFWEEK_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 36
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 36
      if (n_OK(n) == 1) {
        n = match_DAYOFYEAR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 37
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 37
      if (n_OK(n) == 1) {
        n = match_DEGREES_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 38
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 38
      if (n_OK(n) == 1) {
        n = match_ELT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 39
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 39
      if (n_OK(n) == 1) {
        n = match_EXPORT_SET_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 40
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 40
      if (n_OK(n) == 1) {
        n = match_EXP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 41
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 41
      if (n_OK(n) == 1) {
        n = match_EXTRACT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 42
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 42
      if (n_OK(n) == 1) {
        n = match_FIELD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 43
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 43
      if (n_OK(n) == 1) {
        n = match_FIND_IN_SET_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 44
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 44
      if (n_OK(n) == 1) {
        n = match_FLOOR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 45
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 45
      if (n_OK(n) == 1) {
        n = match_FORMAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 46
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 46
      if (n_OK(n) == 1) {
        n = match_FORMAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 47
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 47
      if (n_OK(n) == 1) {
        n = match_FROM_BASE64_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 48
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 48
      if (n_OK(n) == 1) {
        n = match_FROM_DAYS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 49
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 49
      if (n_OK(n) == 1) {
        n = match_FROM_UNIXTIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 50
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 50
      if (n_OK(n) == 1) {
        n = match_GET_FORMAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 51
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 51
      if (n_OK(n) == 1) {
        n = match_HEX_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 52
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 52
      if (n_OK(n) == 1) {
        n = match_HOUR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 53
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 53
      if (n_OK(n) == 1) {
        n = match_INSERT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 54
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 54
      if (n_OK(n) == 1) {
        n = match_INSTR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 55
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 55
      if (n_OK(n) == 1) {
        n = match_LAST_DAY_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 56
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 56
      if (n_OK(n) == 1) {
        n = match_LCASE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 57
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 57
      if (n_OK(n) == 1) {
        n = match_LEFT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 58
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 58
      if (n_OK(n) == 1) {
        n = match_LENGTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 59
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 59
      if (n_OK(n) == 1) {
        n = match_LN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 60
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 60
      if (n_OK(n) == 1) {
        n = match_LOAD_FILE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 61
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 61
      if (n_OK(n) == 1) {
        n = match_LOCALTIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 62
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 62
      if (n_OK(n) == 1) {
        n = match_LOCALTIMESTAMP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 63
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 63
      if (n_OK(n) == 1) {
        n = match_LOCATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 64
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 64
      if (n_OK(n) == 1) {
        n = match_LOG10_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 65
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 65
      if (n_OK(n) == 1) {
        n = match_LOG2_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 66
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 66
      if (n_OK(n) == 1) {
        n = match_LOG_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 67
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 67
      if (n_OK(n) == 1) {
        n = match_LOWER_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 68
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 68
      if (n_OK(n) == 1) {
        n = match_LPAD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 69
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 69
      if (n_OK(n) == 1) {
        n = match_LTRIM_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 70
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 70
      if (n_OK(n) == 1) {
        n = match_MAKEDATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 71
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 71
      if (n_OK(n) == 1) {
        n = match_MAKE_SET_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 72
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 72
      if (n_OK(n) == 1) {
        n = match_MAKETIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 73
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 73
      if (n_OK(n) == 1) {
        n = match_MICROSECOND_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 74
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 74
      if (n_OK(n) == 1) {
        n = match_MID_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 75
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 75
      if (n_OK(n) == 1) {
        n = match_MINUTE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 76
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 76
      if (n_OK(n) == 1) {
        n = match_MOD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 77
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 77
      if (n_OK(n) == 1) {
        n = match_MONTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 78
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 78
      if (n_OK(n) == 1) {
        n = match_MONTHNAME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 79
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 79
      if (n_OK(n) == 1) {
        n = match_NOW_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 80
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 80
      if (n_OK(n) == 1) {
        n = match_OCTET_LENGTH_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 81
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 81
      if (n_OK(n) == 1) {
        n = match_OCT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 82
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 82
      if (n_OK(n) == 1) {
        n = match_ORD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 83
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 83
      if (n_OK(n) == 1) {
        n = match_PERIOD_ADD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 84
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 84
      if (n_OK(n) == 1) {
        n = match_PERIOD_DIFF_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 85
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 85
      if (n_OK(n) == 1) {
        n = match_PI_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 86
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 86
      if (n_OK(n) == 1) {
        n = match_POSITION_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 87
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 87
      if (n_OK(n) == 1) {
        n = match_POWER_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 88
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 88
      if (n_OK(n) == 1) {
        n = match_POW_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 89
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 89
      if (n_OK(n) == 1) {
        n = match_QUARTER_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 90
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 90
      if (n_OK(n) == 1) {
        n = match_QUOTE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 91
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 91
      if (n_OK(n) == 1) {
        n = match_RADIANS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 92
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 92
      if (n_OK(n) == 1) {
        n = match_RAND_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 93
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 93
      if (n_OK(n) == 1) {
        n = match_REPEAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 94
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 94
      if (n_OK(n) == 1) {
        n = match_REPLACE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 95
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 95
      if (n_OK(n) == 1) {
        n = match_REVERSE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 96
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 96
      if (n_OK(n) == 1) {
        n = match_RIGHT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 97
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 97
      if (n_OK(n) == 1) {
        n = match_ROUND_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 98
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 98
      if (n_OK(n) == 1) {
        n = match_RPAD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 99
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 99
      if (n_OK(n) == 1) {
        n = match_RTRIM_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 100
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 100
      if (n_OK(n) == 1) {
        n = match_SECOND_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 101
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 101
      if (n_OK(n) == 1) {
        n = match_SEC_TO_TIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 102
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 102
      if (n_OK(n) == 1) {
        n = match_SIGN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 103
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 103
      if (n_OK(n) == 1) {
        n = match_SIN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 104
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 104
      if (n_OK(n) == 1) {
        n = match_SOUNDEX_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 105
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 105
      if (n_OK(n) == 1) {
        n = match_SPACE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 106
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 106
      if (n_OK(n) == 1) {
        n = match_SQRT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 107
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 107
      if (n_OK(n) == 1) {
        n = match_STR_TO_DATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 108
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 108
      if (n_OK(n) == 1) {
        n = match_SUBDATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 109
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 109
      if (n_OK(n) == 1) {
        n = match_SUBSTRING_INDEX_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 110
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 110
      if (n_OK(n) == 1) {
        n = match_SUBSTRING_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 111
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 111
      if (n_OK(n) == 1) {
        n = match_SUBSTR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 112
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 112
      if (n_OK(n) == 1) {
        n = match_SUBTIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 113
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 113
      if (n_OK(n) == 1) {
        n = match_SYSDATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 114
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 114
      if (n_OK(n) == 1) {
        n = match_TAN_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 115
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 115
      if (n_OK(n) == 1) {
        n = match_TIMEDIFF_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 116
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 116
      if (n_OK(n) == 1) {
        n = match_TIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 117
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 117
      if (n_OK(n) == 1) {
        n = match_TIME_FORMAT_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 118
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 118
      if (n_OK(n) == 1) {
        n = match_TIMESTAMPADD_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 119
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 119
      if (n_OK(n) == 1) {
        n = match_TIMESTAMPDIFF_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 120
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 120
      if (n_OK(n) == 1) {
        n = match_TIMESTAMP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 121
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 121
      if (n_OK(n) == 1) {
        n = match_TIME_TO_SEC_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 122
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 122
      if (n_OK(n) == 1) {
        n = match_TO_BASE64_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 123
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 123
      if (n_OK(n) == 1) {
        n = match_TO_DAYS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 124
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 124
      if (n_OK(n) == 1) {
        n = match_TO_SECONDS_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 125
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 125
      if (n_OK(n) == 1) {
        n = match_TRIM_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 126
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 126
      if (n_OK(n) == 1) {
        n = match_TRUNCATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 127
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 127
      if (n_OK(n) == 1) {
        n = match_UCASE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 128
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 128
      if (n_OK(n) == 1) {
        n = match_UNHEX_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 129
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 129
      if (n_OK(n) == 1) {
        n = match_UNIX_TIMESTAMP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 130
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 130
      if (n_OK(n) == 1) {
        n = match_UTC_DATE_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 131
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 131
      if (n_OK(n) == 1) {
        n = match_UTC_TIMESTAMP_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 132
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 132
      if (n_OK(n) == 1) {
        n = match_UTC_TIME_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 133
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 133
      if (n_OK(n) == 1) {
        n = match_WEEK_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 134
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 134
      if (n_OK(n) == 1) {
        n = match_WEEKDAY_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 135
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 135
      if (n_OK(n) == 1) {
        n = match_WEEKOFYEAR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 136
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 136
      if (n_OK(n) == 1) {
        n = match_YEAR_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //list item switch
    //item+1 137
    if (n->OK == 0) {
      n->OK = 1;
      //string
      //external -> 137
      if (n_OK(n) == 1) {
        n = match_YEARWEEK_FUNC(n, name, depth + 1);
      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[functions] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_B(node_t * n, const char last_method[], int depth)
{
  const char name[] = "B";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //bit  B B
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_bit(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[B] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_bits(node_t * n, const char last_method[], int depth)
{
  const char name[] = "bits";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  bits bits
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[bits] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_charset_name(node_t * n, const char last_method[], int depth)
{
  const char name[] = "charset_name";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  charset_name charset_name
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[charset_name] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_count(node_t * n, const char last_method[], int depth)
{
  const char name[] = "count";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  count count
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[count] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_D(node_t * n, const char last_method[], int depth)
{
  const char name[] = "D";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //real  D D
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_real(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[D] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_date(node_t * n, const char last_method[], int depth)
{
  const char name[] = "date";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  date date
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[date] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_datetime_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "datetime_expr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  datetime_expr datetime_expr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[datetime_expr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_dayofyear(node_t * n, const char last_method[], int depth)
{
  const char name[] = "dayofyear";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  dayofyear dayofyear
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[dayofyear] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_days(node_t * n, const char last_method[], int depth)
{
  const char name[] = "days";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  days days
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[days] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_delim(node_t * n, const char last_method[], int depth)
{
  const char name[] = "delim";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  delim delim
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[delim] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_dt(node_t * n, const char last_method[], int depth)
{
  const char name[] = "dt";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  dt dt
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[dt] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_file_name(node_t * n, const char last_method[], int depth)
{
  const char name[] = "file_name";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  file_name file_name
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[file_name] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_format(node_t * n, const char last_method[], int depth)
{
  const char name[] = "format";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  format format
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[format] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_from_base(node_t * n, const char last_method[], int depth)
{
  const char name[] = "from_base";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  from_base from_base
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_base] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_from_str(node_t * n, const char last_method[], int depth)
{
  const char name[] = "from_str";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  from_str from_str
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_str] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_from_tz(node_t * n, const char last_method[], int depth)
{
  const char name[] = "from_tz";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  from_tz from_tz
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[from_tz] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_fsp(node_t * n, const char last_method[], int depth)
{
  const char name[] = "fsp";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  fsp fsp
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[fsp] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_hour(node_t * n, const char last_method[], int depth)
{
  const char name[] = "hour";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  hour hour
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[hour] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_interval(node_t * n, const char last_method[], int depth)
{
  const char name[] = "interval";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  interval interval
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[interval] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_len(node_t * n, const char last_method[], int depth)
{
  const char name[] = "len";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  len len
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[len] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_locale(node_t * n, const char last_method[], int depth)
{
  const char name[] = "locale";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  locale locale
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[locale] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_M(node_t * n, const char last_method[], int depth)
{
  const char name[] = "M";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  M M
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[M] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_minute(node_t * n, const char last_method[], int depth)
{
  const char name[] = "minute";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  minute minute
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[minute] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_mode(node_t * n, const char last_method[], int depth)
{
  const char name[] = "mode";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  mode mode
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[mode] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_N(node_t * n, const char last_method[], int depth)
{
  const char name[] = "N";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  N N
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[N] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_newstr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "newstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  newstr newstr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[newstr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_N_or_S(node_t * n, const char last_method[], int depth)
{
  const char name[] = "N_or_S";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  N_or_S N_or_S
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[N_or_S] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_number_of_bits(node_t * n, const char last_method[], int depth)
{
  const char name[] = "number_of_bits";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  number_of_bits number_of_bits
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[number_of_bits] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_off(node_t * n, const char last_method[], int depth)
{
  const char name[] = "off";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  off off
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[off] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_on(node_t * n, const char last_method[], int depth)
{
  const char name[] = "on";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  on on
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[on] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_P(node_t * n, const char last_method[], int depth)
{
  const char name[] = "P";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  P P
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[P] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_padstr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "padstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  padstr padstr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[padstr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_pos(node_t * n, const char last_method[], int depth)
{
  const char name[] = "pos";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  pos pos
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[pos] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_remstr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "remstr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  remstr remstr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[remstr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_second(node_t * n, const char last_method[], int depth)
{
  const char name[] = "second";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  second second
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[second] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_seconds(node_t * n, const char last_method[], int depth)
{
  const char name[] = "seconds";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  seconds seconds
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[seconds] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_separator(node_t * n, const char last_method[], int depth)
{
  const char name[] = "separator";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  separator separator
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[separator] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_strlist(node_t * n, const char last_method[], int depth)
{
  const char name[] = "strlist";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  strlist strlist
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[strlist] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_substr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "substr";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  substr substr
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[substr] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_time(node_t * n, const char last_method[], int depth)
{
  const char name[] = "time";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  time time
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[time] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_to_base(node_t * n, const char last_method[], int depth)
{
  const char name[] = "to_base";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  to_base to_base
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_base] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_to_str(node_t * n, const char last_method[], int depth)
{
  const char name[] = "to_str";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  to_str to_str
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_str] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_to_tz(node_t * n, const char last_method[], int depth)
{
  const char name[] = "to_tz";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  to_tz to_tz
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[to_tz] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_unit(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unit";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //expr  unit unit
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unit] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_unix_timestamp(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unix_timestamp";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //integer  unix_timestamp unix_timestamp
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[unix_timestamp] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_X(node_t * n, const char last_method[], int depth)
{
  const char name[] = "X";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //integer  X X
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[X] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_Y(node_t * n, const char last_method[], int depth)
{
  const char name[] = "Y";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //integer  Y Y
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[Y] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_year(node_t * n, const char last_method[], int depth)
{
  const char name[] = "year";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
  // list
  // dict
  // GROUP
  if (n_OK(n) == 1) {
    // list
    //integer  year year
    //0
    //string
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
    }

  }

  if (n->OK == 1) {
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[year] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

node_t *match_catch_all(node_t * n, const char last_method[], int depth)
{
  const char name[] = "catch_all";
  int start_pos = n->pos;
  n->depth += 1;
  n->function = name;
#ifdef  DEBUG_START
  debug_start(n, name, start_pos);
#endif
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
    //if (depth==0){
    for (int i = 0; i < depth; i++)
      printf(" ");
    printf("[catch_all] ");
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    // }

#ifdef  DEBUG_SUCCESS
    debug_success(n, name, start_pos);
#endif
  }
#ifdef  DEBUG_FAILED
  if (n->OK == 0) {
    debug_failed(n, name, start_pos);
  }
#endif
  n->depth -= 1;
  n->last_function = name;
  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-09
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
    n = match_queries(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_catch_all(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;

    if (n->OK == 0) {
      printf("Match not found");
      break;
    }
  }
  pop(n->stack);
  return n;
}                               // end match functions
