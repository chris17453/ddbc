/********************************************
* Generated: 2019-11-05                    *
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

node_t *match_select(node_t * n, const char last_method[], int depth)
{
  const char name[] = "select";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_select\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
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
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_select_expr(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_select(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "expr";
  int recursion = 1;
  n->depth += 1;
  //printf("In functions match_expr\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //recursion -> 0
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
        n = match_expr(n, name, depth + 1);
      }
      //}
      //---?
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "OR") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //---?
      //recursion -> 2
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
        n = match_expr(n, name, depth + 1);
      }
      //}
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
//item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //recursion -> 0
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
        //}
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '|' || n->value[n->pos] == '|')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
        //recursion -> 2
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
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
//---?
//recursion -> 0
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
//---?
// order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "XOR") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//---?
//recursion -> 2
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
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
//---?
//recursion -> 0
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
//---?
// order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "AND") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//---?
//recursion -> 2
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
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
//---?
//recursion -> 0
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
//---?
// order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "&&") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//---?
//recursion -> 2
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
          n = match_expr(n, name, depth + 1);
        }
//}
      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
//item+1 5
    if (n->OK == 0) {
      n->OK = 1;
// GROUP
      if (n_OK(n) == 1) {
//---?
// order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "NOT") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//item 1  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }
      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
//item+1 6
    if (n->OK == 0) {
      n->OK = 1;
// GROUP
      if (n_OK(n) == 1) {
//---?
// order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "!") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//item 1  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_expr(n, name, depth + 1);
        }
      }
      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
//item+1 7
    if (n->OK == 0) {
      n->OK = 1;
// GROUP
      if (n_OK(n) == 1) {
//---?
//external -> 0
        if (n_OK(n) == 1) {
          n = match_boolean_primary(n, name, depth + 1);
        }
//---?
// order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
//---?
//optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
// order None
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
//---?
// GROUP
        if (n_OK(n) == 1) {
//---?
//OR
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
//item 0
//item 0
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
            if (n->OK == 0) {
              n->pos = peek(n->stack);
            }
//item+1 1
            if (n->OK == 0) {
              n->OK = 1;
//item 1
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
//item+1 8
    if (n->OK == 0) {
      n->OK = 1;
// GROUP
      if (n_OK(n) == 1) {
//---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_boolean_primary(node_t * n, const char last_method[], int depth)
{
  const char name[] = "boolean_primary";
  int recursion = 1;
  n->depth += 1;
  //printf("In functions match_boolean_primary\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //item 0  //skip if not called by self
      if (strcmp(name, last_method) != 0) {
        n->OK = 0;
      }
      //---?
      // order 1
      if (n_OK(n) == 1 && stricmp(n, (const char *) "IS") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      //---?
      //optional
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        // order None
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
      //---?
      //external -> 3
      if (n_OK(n) == 1) {
        n = match_null(n, name, depth + 1);
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
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //---?
        // order 1
        if (n_OK(n) == 1 && stricmp(n, (const char *) "<=>") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //---?
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_predicate(n, name, depth + 1);
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
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //---?
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_comparison_operator(n, name, depth + 1);
        }
        //---?
        //external -> 2
        if (n_OK(n) == 1) {
          n = match_predicate(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" boolean_primary -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_boolean_primary(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_predicate(node_t * n, const char last_method[], int depth)
{
  const char name[] = "predicate";
  int recursion = 1;
  n->depth += 1;
  //printf("In functions match_predicate\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_bit_expr(n, name, depth + 1);
    }
    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // order None
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
    //---?
    // order 2
    if (n_OK(n) == 1 && stricmp(n, (const char *) "IN") == 0) {
      n->OK = 1;
      n->pos += 2;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '(')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_expr(n, name, depth + 1);
        }
        //---?
        //one or more
        push(n->stack, n->pos);
        while (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //---?
            if (n_OK(n) == 1 && (n->value[n->pos] == ',')) {
              n->OK = 1;
              n->pos++;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }                   // end char
            //---?
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
  //---?
  // order 1
  if (n_OK(n) == 1 && stricmp(n, (const char *) "]") == 0) {
    n->OK = 1;
    n->pos += 1;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    //item 0
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // order None
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
        //---?
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "BETWEEN") == 0) {
          n->OK = 1;
          n->pos += 7;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //---?
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //---?
        // order 4
        if (n_OK(n) == 1 && stricmp(n, (const char *) "AND") == 0) {
          n->OK = 1;
          n->pos += 3;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //item 5  //non index 0 recursion
        if (n_OK(n) == 1 && strcmp(name, last_method) == 0 && n->pos > start_pos) {
          n = match_predicate(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // order None
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
        //---?
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "LIKE") == 0) {
          n->OK = 1;
          n->pos += 4;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //---?
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_simple_expr(n, name, depth + 1);
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // GROUP
          if (n_OK(n) == 1) {
            //---?
            // order 0
            if (n_OK(n) == 1 && stricmp(n, (const char *) "ESCAPE") == 0) {
              n->OK = 1;
              n->pos += 6;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }
            //---?
            //external -> 1
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
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // order None
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
        //---?
        // order 2
        if (n_OK(n) == 1 && stricmp(n, (const char *) "REGEXP") == 0) {
          n->OK = 1;
          n->pos += 6;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //---?
        //external -> 3
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit_expr(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_predicate(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_bit_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "bit_expr";
  int recursion = 1;
  n->depth += 1;
  //printf("In functions match_bit_expr\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //recursion -> 0
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
        n = match_bit_expr(n, name, depth + 1);
      }
      //}
      //---?
      //external -> 1
      if (n_OK(n) == 1) {
        n = match_operations(n, name, depth + 1);
      }
      //---?
      //recursion -> 2
      if (n_OK(n) == 1 && strcmp(name, last_method) == 0) {
        n = match_bit_expr(n, name, depth + 1);
      }
      //}
    }
    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }
//item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //item 0  //skip if not called by self
        if (strcmp(name, last_method) != 0) {
          n->OK = 0;
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
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
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '+' || n->value[n->pos] == '-')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
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
        //---?
        //external -> 4
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" bit_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_bit_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_operations(node_t * n, const char last_method[], int depth)
{
  const char name[] = "operations";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_operations\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
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
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
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
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_operations(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_complex_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "complex_expr";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_complex_expr\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_simple_expr(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_interval_expr(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_complex_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_simple_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "simple_expr";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_simple_expr\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_literal(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" simple_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_simple_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_literal(node_t * n, const char last_method[], int depth)
{
  const char name[] = "literal";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_literal\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_hex(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_bit(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_real(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_null(n, name, depth + 1);
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
        //---?
        //external -> 0
        if (n_OK(n) == 1) {
          n = match_boolean(n, name, depth + 1);
        }

      }

      if (n->OK == 0) {
        n->pos = peek(n->stack);
      }
    }
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" literal -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_literal(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEARS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEARS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_YEARS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_YEARS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_QUARTERS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUARTERS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_QUARTERS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_QUARTERS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MONTHS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTHS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MONTHS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MONTHS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_WEEKS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEKS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_WEEKS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_WEEKS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAYS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAYS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAYS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAYS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOURS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOURS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_HOURS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_HOURS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTES(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTES";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MINUTES\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MINUTES(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECONDS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECONDS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_SECONDS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_SECONDS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MICROSECONDS(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MICROSECONDS";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MICROSECONDS\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MICROSECONDS(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MICROSECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MICROSECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MICROSECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_SECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_SECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MINUTE\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MINUTE(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_HOUR\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_HOUR(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAY\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAY(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_WEEK(node_t * n, const char last_method[], int depth)
{
  const char name[] = "WEEK";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_WEEK\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_WEEKS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_WEEK(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MONTH(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MONTH";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MONTH\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_MONTHS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MONTH(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_QUARTER(node_t * n, const char last_method[], int depth)
{
  const char name[] = "QUARTER";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_QUARTER\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_QUARTERS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_QUARTER(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEAR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEAR";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_YEAR\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_YEARS(n, name, depth + 1);
    }
    //---?
    // order 1
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_YEAR(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_SECOND_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "SECOND_MICROSECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_SECOND_MICROSECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 5
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_SECOND_MICROSECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE_MICROSECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MINUTE_MICROSECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 7
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MINUTE_MICROSECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_MINUTE_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "MINUTE_SECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_MINUTE_SECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 5
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_MINUTE_SECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_MICROSECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_HOUR_MICROSECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 7
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 9
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_HOUR_MICROSECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_SECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_HOUR_SECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 5
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 7
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_HOUR_SECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_HOUR_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "HOUR_MINUTE";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_HOUR_MINUTE\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 5
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_HOUR_MINUTE(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_MICROSECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_MICROSECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAY_MICROSECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name, depth + 1);
    }
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 8
    if (n_OK(n) == 1) {
      n = match_MICROSECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 10
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAY_MICROSECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_SECOND(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_SECOND";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAY_SECOND\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name, depth + 1);
    }
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 6
    if (n_OK(n) == 1) {
      n = match_SECONDS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 8
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAY_SECOND(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_MINUTE(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_MINUTE";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAY_MINUTE\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name, depth + 1);
    }
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == ':')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 4
    if (n_OK(n) == 1) {
      n = match_MINUTES(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 6
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAY_MINUTE(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_DAY_HOUR(node_t * n, const char last_method[], int depth)
{
  const char name[] = "DAY_HOUR";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_DAY_HOUR\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_DAYS(n, name, depth + 1);
    }
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_HOURS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 4
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_DAY_HOUR(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_YEAR_MONTH(node_t * n, const char last_method[], int depth)
{
  const char name[] = "YEAR_MONTH";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_YEAR_MONTH\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_YEARS(n, name, depth + 1);
    }
    //---?
    // order 2
    if (n_OK(n) == 1 && stricmp(n, (const char *) "-") == 0) {
      n->OK = 1;
      n->pos += 1;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }
    //---?
    //external -> 3
    if (n_OK(n) == 1) {
      n = match_MONTHS(n, name, depth + 1);
    }
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    // order 5
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_YEAR_MONTH(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_interval_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "interval_expr";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_interval_expr\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      // order 0
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 7
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 8
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 9
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 10
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 11
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 12
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 13
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 14
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 15
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 16
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 17
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 18
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    //item+1 19
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_interval_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_comment\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_block_comment(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" comment -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_block_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "block_comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_block_comment\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_left_comment(n, name, depth + 1);
    }
    //---?
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
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
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_right_comment(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_block_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_single_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "single_comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_single_comment\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_inline_comment(n, name, depth + 1);
    }
    //---?
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        //NOT
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
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
    //---?
    //external -> 2
    if (n_OK(n) == 1) {
      n = match_end_of_line(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_single_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_left_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "left_comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_left_comment\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '/')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_left_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_right_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "right_comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_right_comment\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '*')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_right_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_inline_comment(node_t * n, const char last_method[], int depth)
{
  const char name[] = "inline_comment";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_inline_comment\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '-')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_inline_comment(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_unknown(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unknown";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_unknown\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" unknown -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_unknown(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_hex(node_t * n, const char last_method[], int depth)
{
  const char name[] = "hex";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_hex\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == 'x' || n->value[n->pos] == 'X')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_hex(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_bit(node_t * n, const char last_method[], int depth)
{
  const char name[] = "bit";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_bit\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '0')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == 'b')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_bit(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_null(node_t * n, const char last_method[], int depth)
{
  const char name[] = "null";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_null\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" null -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_null(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_true(node_t * n, const char last_method[], int depth)
{
  const char name[] = "true";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_true\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" true -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_true(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_false(node_t * n, const char last_method[], int depth)
{
  const char name[] = "false";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_false\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" false -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_false(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_boolean(node_t * n, const char last_method[], int depth)
{
  const char name[] = "boolean";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_boolean\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_true(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" boolean -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_boolean(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_real(node_t * n, const char last_method[], int depth)
{
  const char name[] = "real";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_real\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_integer(n, name, depth + 1);
      }
      //---?
      if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //---?
      //external -> 2
      if (n_OK(n) == 1) {
        n = match_unsigned_int(n, name, depth + 1);
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
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '.')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
        //external -> 1
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n, name, depth + 1);
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
        //---?
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
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" real -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_real(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_integer(node_t * n, const char last_method[], int depth)
{
  const char name[] = "integer";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_integer\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_signed_int(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" integer -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_integer(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_signed_int(node_t * n, const char last_method[], int depth)
{
  const char name[] = "signed_int";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_signed_int\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_sign(n, name, depth + 1);
    }
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_unsigned_int(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_signed_int(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_unsigned_int(node_t * n, const char last_method[], int depth)
{
  const char name[] = "unsigned_int";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_unsigned_int\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_unsigned_int(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_sign(node_t * n, const char last_method[], int depth)
{
  const char name[] = "sign";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_sign\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_sign(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_exponent(node_t * n, const char last_method[], int depth)
{
  const char name[] = "exponent";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_exponent\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == 'E' || n->value[n->pos] == 'e')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //external -> 1
    if (n_OK(n) == 1) {
      n = match_integer(n, name, depth + 1);
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_exponent(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_identifier(node_t * n, const char last_method[], int depth)
{
  const char name[] = "identifier";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_identifier\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_identifier(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_alpha(node_t * n, const char last_method[], int depth)
{
  const char name[] = "alpha";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_alpha\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_alpha(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_whitespace(node_t * n, const char last_method[], int depth)
{
  const char name[] = "whitespace";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_whitespace\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_whitespace(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_single_quote_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "single_quote_string";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_single_quote_string\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\'')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_single_quote_string(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_double_quote_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "double_quote_string";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_double_quote_string\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '"')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
    //one or more
    push(n->stack, n->pos);
    while (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_double_quote_string(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_string(node_t * n, const char last_method[], int depth)
{
  const char name[] = "string";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_string\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      //external -> 0
      if (n_OK(n) == 1) {
        n = match_single_quote_string(n, name, depth + 1);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" string -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_string(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_select_expr(node_t * n, const char last_method[], int depth)
{
  const char name[] = "select_expr";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_select_expr\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    //external -> 0
    if (n_OK(n) == 1) {
      n = match_expr(n, name, depth + 1);
    }
    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
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
    //---?
    //optional
    if (n_OK(n) == 1) {
      push(n->stack, n->pos);
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        // order 0
        if (n_OK(n) == 1 && stricmp(n, (const char *) "as") == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        //---?
        //optional
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
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
        //---?
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
    for (int i = 0; i < n->depth; i++)
      printf(" ");
    printf(" select_expr -> %d - %d OK:%d, depth: %d ", start_pos, n->pos, n->OK, n->depth);
    if (n->pos == -1) {
      print_sub_str(n, start_pos, n->len);
    } else {
      print_sub_str(n, start_pos, n->pos);
    }
    printf("\n");
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_select_expr(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_end_of_line(node_t * n, const char last_method[], int depth)
{
  const char name[] = "end_of_line";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_end_of_line\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
    if (n_OK(n) == 1 && (n->value[n->pos] == '\n')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_end_of_line(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_comparison_operator(node_t * n, const char last_method[], int depth)
{
  const char name[] = "comparison_operator";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_comparison_operator\n");
  int start_pos = n->pos;
  //---?
  //OR
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    //item 0
    // GROUP
    if (n_OK(n) == 1) {
      //---?
      if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
        n->OK = 1;
        n->pos++;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }                         // end char
      //---?
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
    //item+1 1
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '>')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
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
    //item+1 2
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '<')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
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
    //item+1 3
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
        if (n_OK(n) == 1 && (n->value[n->pos] == '!')) {
          n->OK = 1;
          n->pos++;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }                       // end char
        //---?
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
    //item+1 4
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 5
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    //item+1 6
    if (n->OK == 0) {
      n->OK = 1;
      // GROUP
      if (n_OK(n) == 1) {
        //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_comparison_operator(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

node_t *match_not_whitespace(node_t * n, const char last_method[], int depth)
{
  const char name[] = "not_whitespace";
  int recursion = 0;
  n->depth += 1;
  //printf("In functions match_not_whitespace\n");
  int start_pos = n->pos;
  //---?
  // GROUP
  if (n_OK(n) == 1) {
    //---?
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
    if (recursion == 1 && n->pos != -1 && start_pos != n->pos) {
      match_not_whitespace(n, last_method, depth + 1);
    }
  }
  n->depth -= 1;
  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-05
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
    n = match_YEARS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_QUARTERS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MONTHS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_WEEKS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAYS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOURS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTES(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECONDS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MICROSECONDS(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MICROSECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_WEEK(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MONTH(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_QUARTER(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_YEAR(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_SECOND_MICROSECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE_MICROSECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_MINUTE_SECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_MICROSECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_SECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_HOUR_MINUTE(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_MICROSECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_SECOND(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_MINUTE(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_DAY_HOUR(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_YEAR_MONTH(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
    n->OK = 1;
    n = match_interval_expr(n, (const char *) "functions", 0);
    if (n_OK(n) == 1 || n->pos == -1)
      continue;
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
