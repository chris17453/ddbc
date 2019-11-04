/********************************************
* Generated: 2019-11-03                    *
********************************************/
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
      d = (unsigned char) c - (unsigned char) 'A' - (unsigned char) b[i];
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

node_t *match_select(node_t * n, const char last_method[])
{
  const char name[] = "select";
  n->depth += 1;
  //printf("In functions match_select\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && stricmp(n, (const char *) "select") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }
  // GROUP
  if (n_OK(n) == 1) {
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //other
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_select_expr(n, name);
    }

  }
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && stricmp(n, (const char *) "$") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        if (n_OK(n) == 1 && (n->value[n->pos] == ',')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //other
        if (n_OK(n) == 1) {
          n = match_select_expr(n, name);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
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

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" select -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_expr(node_t * n, const char last_method[])
{
  const char name[] = "expr";
  n->depth += 1;
  //printf("In functions match_expr\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //self
      if (strcmp(name, last_method) == 0) {
        if (n_OK(n) == 1 && start_pos != n->pos) {
          n = match_expr(n, name);
        }
      }
      if (n_OK(n) == 1 && stricmp(n, (const char *) "OR") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //self
      if (strcmp(name, last_method) == 0) {
        if (n_OK(n) == 1 && start_pos != n->pos) {
          n = match_expr(n, name);
        }
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }
        if (n_OK(n) == 1 && (n->value[n->pos] == '|' || n->value[n->pos] == '|')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "XOR") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "AND") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "&&") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "!") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_expr(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_boolean_primary(n, name);
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
        // GROUP
        if (n_OK(n) == 1) {
          //OR
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
            //item
            //item
            //other
            if (n_OK(n) == 1) {
              n = match_boolean(n, name);
            }
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            //item+1
            if (n->OK == 0) {
              n->OK = 1;
              //item
              //other
              if (n_OK(n) == 1) {
                n = match_unknown(n, name);
              }
              if (n->OK == 0) {
                n->pos = peek(n->stack);
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_boolean_primary(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_boolean_primary(node_t * n, const char last_method[])
{
  const char name[] = "boolean_primary";
  n->depth += 1;
  //printf("In functions match_boolean_primary\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //self
      if (strcmp(name, last_method) == 0) {
        if (n_OK(n) == 1 && start_pos != n->pos) {
          n = match_boolean_primary(n, name);
        }
      }
      if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
      //other
      if (n_OK(n) == 1) {
        n = match_null(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_boolean_primary(n, name);
          }
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "<=>") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //other
        if (n_OK(n) == 1) {
          n = match_predicate(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_boolean_primary(n, name);
          }
        }
        //other
        if (n_OK(n) == 1) {
          n = match_comparison_operator(n, name);
        }
        //other
        if (n_OK(n) == 1) {
          n = match_predicate(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_predicate(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" boolean_primary -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_predicate(node_t * n, const char last_method[])
{
  const char name[] = "predicate";
  n->depth += 1;
  //printf("In functions match_predicate\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_bit_expr(n, name);
    }
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
    if (n_OK(n) == 1 && stricmp(n, (const char *) "IN") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_expr(n, name);
        }
        //one or more
        push(n->stack, n->pos);
        while (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            if (n_OK(n) == 1 && (n->value[n->pos] == ',')) {
              n->OK = 1;
              n->pos++;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }                   // end char
            //other
            if (n_OK(n) == 1) {
              n = match_expr(n, name);
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

  if (n_OK(n) == 1 && stricmp(n, (const char *) "]") == 0) {
    n->OK = 1;
    n->pos += 1;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    //item
    if (n_OK(n) == 1 && stricmp(n, (const char *) ")") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "BETWEEN") == 0) {
          n->OK = 1;
          n->pos += 7;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }
        if (n_OK(n) == 1 && stricmp(n, (const char *) "AND") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_predicate(n, name);
          }
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "LIKE") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //other
        if (n_OK(n) == 1) {
          n = match_simple_expr(n, name);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            if (n_OK(n) == 1 && stricmp(n, (const char *) "ESCAPE") == 0) {
              n->OK = 1;
              n->pos += 6;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            //other
            if (n_OK(n) == 1) {
              n = match_simple_expr(n, name);
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
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
        if (n_OK(n) == 1 && stricmp(n, (const char *) "REGEXP") == 0) {
          n->OK = 1;
          n->pos += 6;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" predicate -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_bit_expr(node_t * n, const char last_method[])
{
  const char name[] = "bit_expr";
  n->depth += 1;
  //printf("In functions match_bit_expr\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //self
      if (strcmp(name, last_method) == 0) {
        if (n_OK(n) == 1 && start_pos != n->pos) {
          n = match_bit_expr(n, name);
        }
      }
      //other
      if (n_OK(n) == 1) {
        n = match_operations(n, name);
      }
      //self
      if (strcmp(name, last_method) == 0) {
        if (n_OK(n) == 1 && start_pos != n->pos) {
          n = match_bit_expr(n, name);
        }
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //self
        if (strcmp(name, last_method) == 0) {
          if (n_OK(n) == 1 && start_pos != n->pos) {
            n = match_bit_expr(n, name);
          }
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        if (n_OK(n) == 1 && (n->value[n->pos] == '+' || n->value[n->pos] == '-')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //other
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_simple_expr(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" bit_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_operations(node_t * n, const char last_method[])
{
  const char name[] = "operations";
  n->depth += 1;
  //printf("In functions match_operations\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      if (n_OK(n) == 1 && (n->value[n->pos] == '|')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '&')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '+')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '-')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '*')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '/')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '%')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '^')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" operations -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_complex_expr(node_t * n, const char last_method[])
{
  const char name[] = "complex_expr";
  n->depth += 1;
  //printf("In functions match_complex_expr\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_simple_expr(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" complex_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_simple_expr(node_t * n, const char last_method[])
{
  const char name[] = "simple_expr";
  n->depth += 1;
  //printf("In functions match_simple_expr\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_literal(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_identifier(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" simple_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_literal(node_t * n, const char last_method[])
{
  const char name[] = "literal";
  n->depth += 1;
  //printf("In functions match_literal\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_hex(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_bit(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_real(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_null(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_boolean(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_string(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" literal -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEARS(node_t * n, const char last_method[])
{
  const char name[] = "YEARS";
  n->depth += 1;
  //printf("In functions match_YEARS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" YEARS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_QUARTERS(node_t * n, const char last_method[])
{
  const char name[] = "QUARTERS";
  n->depth += 1;
  //printf("In functions match_QUARTERS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" QUARTERS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MONTHS(node_t * n, const char last_method[])
{
  const char name[] = "MONTHS";
  n->depth += 1;
  //printf("In functions match_MONTHS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MONTHS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_WEEKS(node_t * n, const char last_method[])
{
  const char name[] = "WEEKS";
  n->depth += 1;
  //printf("In functions match_WEEKS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" WEEKS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAYS(node_t * n, const char last_method[])
{
  const char name[] = "DAYS";
  n->depth += 1;
  //printf("In functions match_DAYS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAYS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOURS(node_t * n, const char last_method[])
{
  const char name[] = "HOURS";
  n->depth += 1;
  //printf("In functions match_HOURS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" HOURS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTES(node_t * n, const char last_method[])
{
  const char name[] = "MINUTES";
  n->depth += 1;
  //printf("In functions match_MINUTES\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MINUTES -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECONDS(node_t * n, const char last_method[])
{
  const char name[] = "SECONDS";
  n->depth += 1;
  //printf("In functions match_SECONDS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" SECONDS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MICROSECONDS(node_t * n, const char last_method[])
{
  const char name[] = "MICROSECONDS";
  n->depth += 1;
  //printf("In functions match_MICROSECONDS\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MICROSECONDS -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MICROSECOND(node_t * n, const char last_method[])
{
  const char name[] = "MICROSECOND";
  n->depth += 1;
  //printf("In functions match_MICROSECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MICROSECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECOND(node_t * n, const char last_method[])
{
  const char name[] = "SECOND";
  n->depth += 1;
  //printf("In functions match_SECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" SECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE(node_t * n, const char last_method[])
{
  const char name[] = "MINUTE";
  n->depth += 1;
  //printf("In functions match_MINUTE\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE") == 0) {
      n->OK = 1;
      n->pos += 6;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MINUTE -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR(node_t * n, const char last_method[])
{
  const char name[] = "HOUR";
  n->depth += 1;
  //printf("In functions match_HOUR\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" HOUR -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY(node_t * n, const char last_method[])
{
  const char name[] = "DAY";
  n->depth += 1;
  //printf("In functions match_DAY\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY") == 0) {
      n->OK = 1;
      n->pos += 3;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAY -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_WEEK(node_t * n, const char last_method[])
{
  const char name[] = "WEEK";
  n->depth += 1;
  //printf("In functions match_WEEK\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_WEEKS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEK") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" WEEK -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MONTH(node_t * n, const char last_method[])
{
  const char name[] = "MONTH";
  n->depth += 1;
  //printf("In functions match_MONTH\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_MONTHS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTH") == 0) {
      n->OK = 1;
      n->pos += 5;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MONTH -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_QUARTER(node_t * n, const char last_method[])
{
  const char name[] = "QUARTER";
  n->depth += 1;
  //printf("In functions match_QUARTER\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_QUARTERS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "QUARTER") == 0) {
      n->OK = 1;
      n->pos += 7;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" QUARTER -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEAR(node_t * n, const char last_method[])
{
  const char name[] = "YEAR";
  n->depth += 1;
  //printf("In functions match_YEAR\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_YEARS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR") == 0) {
      n->OK = 1;
      n->pos += 4;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" YEAR -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECOND_MICROSECOND(node_t * n, const char last_method[])
{
  const char name[] = "SECOND_MICROSECOND";
  n->depth += 1;
  //printf("In functions match_SECOND_MICROSECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND_MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 18;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" SECOND_MICROSECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE_MICROSECOND(node_t * n, const char last_method[])
{
  const char name[] = "MINUTE_MICROSECOND";
  n->depth += 1;
  //printf("In functions match_MINUTE_MICROSECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 18;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MINUTE_MICROSECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE_SECOND(node_t * n, const char last_method[])
{
  const char name[] = "MINUTE_SECOND";
  n->depth += 1;
  //printf("In functions match_MINUTE_SECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_SECOND") == 0) {
      n->OK = 1;
      n->pos += 13;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" MINUTE_SECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_MICROSECOND(node_t * n, const char last_method[])
{
  const char name[] = "HOUR_MICROSECOND";
  n->depth += 1;
  //printf("In functions match_HOUR_MICROSECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 16;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" HOUR_MICROSECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_SECOND(node_t * n, const char last_method[])
{
  const char name[] = "HOUR_SECOND";
  n->depth += 1;
  //printf("In functions match_HOUR_SECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_SECOND") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" HOUR_SECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_MINUTE(node_t * n, const char last_method[])
{
  const char name[] = "HOUR_MINUTE";
  n->depth += 1;
  //printf("In functions match_HOUR_MINUTE\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MINUTE") == 0) {
      n->OK = 1;
      n->pos += 11;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" HOUR_MINUTE -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_MICROSECOND(node_t * n, const char last_method[])
{
  const char name[] = "DAY_MICROSECOND";
  n->depth += 1;
  //printf("In functions match_DAY_MICROSECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MICROSECOND") == 0) {
      n->OK = 1;
      n->pos += 15;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAY_MICROSECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_SECOND(node_t * n, const char last_method[])
{
  const char name[] = "DAY_SECOND";
  n->depth += 1;
  //printf("In functions match_DAY_SECOND\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_SECOND") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAY_SECOND -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_MINUTE(node_t * n, const char last_method[])
{
  const char name[] = "DAY_MINUTE";
  n->depth += 1;
  //printf("In functions match_DAY_MINUTE\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MINUTE") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAY_MINUTE -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_HOUR(node_t * n, const char last_method[])
{
  const char name[] = "DAY_HOUR";
  n->depth += 1;
  //printf("In functions match_DAY_HOUR\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_HOUR") == 0) {
      n->OK = 1;
      n->pos += 8;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" DAY_HOUR -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEAR_MONTH(node_t * n, const char last_method[])
{
  const char name[] = "YEAR_MONTH";
  n->depth += 1;
  //printf("In functions match_YEAR_MONTH\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_YEARS(n, name);
    }
    if (n_OK(n) == 1 && stricmp(n, (const char *) "-") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //other
    if (n_OK(n) == 1) {
      n = match_MONTHS(n, name);
    }
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR_MONTH") == 0) {
      n->OK = 1;
      n->pos += 10;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" YEAR_MONTH -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_interval_expr(node_t * n, const char last_method[])
{
  const char name[] = "interval_expr";
  n->depth += 1;
  //printf("In functions match_interval_expr\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      if (n_OK(n) == 1 && stricmp(n, (const char *) "MICROSECOND") == 0) {
        n->OK = 1;
        n->pos += 11;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND") == 0) {
          n->OK = 1;
          n->pos += 6;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE") == 0) {
          n->OK = 1;
          n->pos += 6;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR") == 0) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY") == 0) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "WEEK") == 0) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "MONTH") == 0) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "QUARTER") == 0) {
          n->OK = 1;
          n->pos += 7;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR") == 0) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "SECOND_MICROSECOND") == 0) {
          n->OK = 1;
          n->pos += 18;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_MICROSECOND") == 0) {
          n->OK = 1;
          n->pos += 18;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "MINUTE_SECOND") == 0) {
          n->OK = 1;
          n->pos += 13;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MICROSECOND") == 0) {
          n->OK = 1;
          n->pos += 16;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_SECOND") == 0) {
          n->OK = 1;
          n->pos += 11;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "HOUR_MINUTE") == 0) {
          n->OK = 1;
          n->pos += 11;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MICROSECOND") == 0) {
          n->OK = 1;
          n->pos += 15;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_SECOND") == 0) {
          n->OK = 1;
          n->pos += 10;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_MINUTE") == 0) {
          n->OK = 1;
          n->pos += 10;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "DAY_HOUR") == 0) {
          n->OK = 1;
          n->pos += 8;
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "YEAR_MONTH") == 0) {
          n->OK = 1;
          n->pos += 10;
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" interval_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_comment(node_t * n, const char last_method[])
{
  const char name[] = "comment";
  n->depth += 1;
  //printf("In functions match_comment\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_block_comment(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_single_comment(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_block_comment(node_t * n, const char last_method[])
{
  const char name[] = "block_comment";
  n->depth += 1;
  //printf("In functions match_block_comment\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_left_comment(n, name);
    }
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_right_comment(n, name);
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
    //other
    if (n_OK(n) == 1) {
      n = match_right_comment(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" block_comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_single_comment(node_t * n, const char last_method[])
{
  const char name[] = "single_comment";
  n->depth += 1;
  //printf("In functions match_single_comment\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_inline_comment(n, name);
    }
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_end_of_line(n, name);
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
    //other
    if (n_OK(n) == 1) {
      n = match_end_of_line(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" single_comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_left_comment(node_t * n, const char last_method[])
{
  const char name[] = "left_comment";
  n->depth += 1;
  //printf("In functions match_left_comment\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '/')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && (n->value[n->pos] == '*')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" left_comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_right_comment(node_t * n, const char last_method[])
{
  const char name[] = "right_comment";
  n->depth += 1;
  //printf("In functions match_right_comment\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '*')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && (n->value[n->pos] == '/')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" right_comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_inline_comment(node_t * n, const char last_method[])
{
  const char name[] = "inline_comment";
  n->depth += 1;
  //printf("In functions match_inline_comment\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '-')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && (n->value[n->pos] == '-')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" inline_comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_unknown(node_t * n, const char last_method[])
{
  const char name[] = "unknown";
  n->depth += 1;
  //printf("In functions match_unknown\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" unknown -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_hex(node_t * n, const char last_method[])
{
  const char name[] = "hex";
  n->depth += 1;
  //printf("In functions match_hex\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && (n->value[n->pos] == 'x' || n->value[n->pos] == 'X')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9') ||
                           (n->value[n->pos] >= 'A' && n->value[n->pos] <= 'F') || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'f')
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" hex -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_bit(node_t * n, const char last_method[])
{
  const char name[] = "bit";
  n->depth += 1;
  //printf("In functions match_bit\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    if (n_OK(n) == 1 && (n->value[n->pos] == 'b')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && (n->value[n->pos] == '0' || n->value[n->pos] == '1')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" bit -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_null(node_t * n, const char last_method[])
{
  const char name[] = "null";
  n->depth += 1;
  //printf("In functions match_null\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" null -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_true(node_t * n, const char last_method[])
{
  const char name[] = "true";
  n->depth += 1;
  //printf("In functions match_true\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" true -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_false(node_t * n, const char last_method[])
{
  const char name[] = "false";
  n->depth += 1;
  //printf("In functions match_false\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" false -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_boolean(node_t * n, const char last_method[])
{
  const char name[] = "boolean";
  n->depth += 1;
  //printf("In functions match_boolean\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_true(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_false(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" boolean -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_real(node_t * n, const char last_method[])
{
  const char name[] = "real";
  n->depth += 1;
  //printf("In functions match_real\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_integer(n, name);
      }
      if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //other
      if (n_OK(n) == 1) {
        n = match_unsigned_int(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //other
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_integer(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }
  // GROUP
  if (n_OK(n) == 1) {
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //other
      if (n_OK(n) == 1) {
        n = match_exponent(n, name);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" real -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_integer(node_t * n, const char last_method[])
{
  const char name[] = "integer";
  n->depth += 1;
  //printf("In functions match_integer\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_signed_int(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" integer -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_signed_int(node_t * n, const char last_method[])
{
  const char name[] = "signed_int";
  n->depth += 1;
  //printf("In functions match_signed_int\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_sign(n, name);
    }
    //other
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" signed_int -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_unsigned_int(node_t * n, const char last_method[])
{
  const char name[] = "unsigned_int";
  n->depth += 1;
  //printf("In functions match_unsigned_int\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9')
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" unsigned_int -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_sign(node_t * n, const char last_method[])
{
  const char name[] = "sign";
  n->depth += 1;
  //printf("In functions match_sign\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '-' || n->value[n->pos] == '+')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" sign -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_exponent(node_t * n, const char last_method[])
{
  const char name[] = "exponent";
  n->depth += 1;
  //printf("In functions match_exponent\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == 'E' || n->value[n->pos] == 'e')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //other
    if (n_OK(n) == 1) {
      n = match_integer(n, name);
    }

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" exponent -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_identifier(node_t * n, const char last_method[])
{
  const char name[] = "identifier";
  n->depth += 1;
  //printf("In functions match_identifier\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && ((n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') ||
                           (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z') ||
                           (n->value[n->pos] >= '0' && n->value[n->pos] <= '9') || n->value[n->pos] == '$' || n->value[n->pos] == '_')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" identifier -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_alpha(node_t * n, const char last_method[])
{
  const char name[] = "alpha";
  n->depth += 1;
  //printf("In functions match_alpha\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && ((n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z')
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" alpha -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_whitespace(node_t * n, const char last_method[])
{
  const char name[] = "whitespace";
  n->depth += 1;
  //printf("In functions match_whitespace\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && (n->value[n->pos] == '\t' || n->value[n->pos] == ' ' || n->value[n->pos] == '\n' || n->value[n->pos] == '\r')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" whitespace -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_single_quote_string(node_t * n, const char last_method[])
{
  const char name[] = "single_quote_string";
  n->depth += 1;
  //printf("In functions match_single_quote_string\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
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
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" single_quote_string -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_double_quote_string(node_t * n, const char last_method[])
{
  const char name[] = "double_quote_string";
  n->depth += 1;
  //printf("In functions match_double_quote_string\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '"')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          if (n_OK(n) == 1 && (n->value[n->pos] == '"')) {
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
    if (n_OK(n) == 1 && (n->value[n->pos] == '"')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" double_quote_string -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_string(node_t * n, const char last_method[])
{
  const char name[] = "string";
  n->depth += 1;
  //printf("In functions match_string\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      //other
      if (n_OK(n) == 1) {
        n = match_single_quote_string(n, name);
      }

    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //other
        if (n_OK(n) == 1) {
          n = match_double_quote_string(n, name);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }

    pop(n->stack);
  }

  if (n->OK == 1) {
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" string -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_select_expr(node_t * n, const char last_method[])
{
  const char name[] = "select_expr";
  n->depth += 1;
  //printf("In functions match_select_expr\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //other
    if (n_OK(n) == 1) {
      n = match_expr(n, name);
    }
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      //other
      if (n_OK(n) == 1) {
        n = match_whitespace(n, name);
      }

      if (n->OK == 0) {
        n->OK = 1;
        n->pos = peek(n->stack);
      }
      pop(n->stack);
    }
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && stricmp(n, (const char *) "as") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          //other
          if (n_OK(n) == 1) {
            n = match_whitespace(n, name);
          }

          if (n->OK == 0) {
            n->OK = 1;
            n->pos = peek(n->stack);
          }
          pop(n->stack);
        }
        //other
        if (n_OK(n) == 1) {
          n = match_identifier(n, name);
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" select_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_end_of_line(node_t * n, const char last_method[])
{
  const char name[] = "end_of_line";
  n->depth += 1;
  //printf("In functions match_end_of_line\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    if (n_OK(n) == 1 && (n->value[n->pos] == '\n')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && (n->value[n->pos] == '\r')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" end_of_line -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_comparison_operator(node_t * n, const char last_method[])
{
  const char name[] = "comparison_operator";
  n->depth += 1;
  //printf("In functions match_comparison_operator\n");
  int start_pos = n->pos;
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item
    // GROUP
    if (n_OK(n) == 1) {
      if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        if (n_OK(n) == 1 && (n->value[n->pos] == '=')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        if (n_OK(n) == 1 && (n->value[n->pos] == '=')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '!')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        if (n_OK(n) == 1 && (n->value[n->pos] == '=')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
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
    //item+1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1 && (n->value[n->pos] == '=')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" comparison_operator -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

node_t *match_not_whitespace(node_t * n, const char last_method[])
{
  const char name[] = "not_whitespace";
  n->depth += 1;
  //printf("In functions match_not_whitespace\n");
  int start_pos = n->pos;
  // GROUP
  if (n_OK(n) == 1) {
    //NOT
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      if (n_OK(n) == 1 && (n->value[n->pos] == '\t' || n->value[n->pos] == ' ' || n->value[n->pos] == '\n' || n->value[n->pos] == '\r')) {
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" not_whitespace -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
  }
  n->depth -= 1;
  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-03
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
    n = match_select(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_boolean_primary(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_predicate(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_bit_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_operations(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_complex_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_simple_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_literal(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_YEARS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_QUARTERS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MONTHS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_WEEKS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAYS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOURS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTES(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECONDS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MICROSECONDS(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MICROSECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_WEEK(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MONTH(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_QUARTER(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_YEAR(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECOND_MICROSECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE_MICROSECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE_SECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_MICROSECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_SECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_MINUTE(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_MICROSECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_SECOND(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_MINUTE(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_HOUR(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_YEAR_MONTH(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_interval_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_block_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_single_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_left_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_right_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_inline_comment(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_unknown(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_hex(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_bit(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_null(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_true(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_false(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_boolean(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_real(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_integer(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_signed_int(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_unsigned_int(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_sign(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_exponent(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_identifier(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_alpha(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_whitespace(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_single_quote_string(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_double_quote_string(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_string(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_select_expr(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_end_of_line(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_comparison_operator(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_not_whitespace(n, (const char *) "functions");
    if (n_OK(n) == 1 || n->pos == -1)
      continue;

  }
  pop(n->stack);
  return n;
}                               // end match functions
