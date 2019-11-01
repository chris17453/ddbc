/********************************************
* Generated: 2019-11-01                    *
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
  printf("Compare %s\n", b);
  for (int i = 0; i < n->len; i++) {
    if (n->value[i] >= 'A' && n->value[i] <= 'Z') {
      d = (unsigned char) n->value[i] - (unsigned char) 'A' - (unsigned char) b[i];
    } else {
      d = (unsigned char) n->value[i] - (unsigned char) b[i];
    }
    if (d != 0)
      return d;
  }
  return 0;
}

void print_n(node_t * n)
{
  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
}

int n_OK(node_t * n)
{
  print_n(n);
  if (n->pos != -1 && n->OK == 1)
    return 1;
  return 0;
}

// Function : match_string
node_t *match_string(node_t * n)
{
  printf("In functions match_string\n");
  // or group
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);     //save position
    // begin group block
    if (n_OK(n) == 1) {
      printf("Comparing LEFT  %s\n", n->value);
      printf("Comparing RIGHT %s\n", (char *) "\"");
      if (n_OK(n) == 1 && n->len == 2 && stricmp(n, (const char *) "\"") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      push(n->stack, n->pos);   // one or more
      if (n_OK(n) == 1) {
        push(n->stack, n->pos);
        // begin group block
        if (n_OK(n) == 1) {
          //NOT
          if (n_OK(n) == 1) {
            push(n->stack, n->pos);
            printf("Comparing LEFT  %s\n", n->value);
            printf("Comparing RIGHT %s\n", (char *) "\"");
            if (n_OK(n) == 1 && n->len == 2 && stricmp(n, (const char *) "\"") == 0) {
              n->OK = 1;
              n->pos += 2;
              if (n->pos >= n->len)
                n->pos = -1;
            } else {
              n->OK = 0;
            }

            if (n->OK == 1) {
              n->OK = 0;
              n->pos = peek(n->stack);
            } else {
              n->OK = 1;
            }
            pop(n->stack);
          }                     //end NOT

        }                       // end group block

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }                       // one or more loop OK test
        pop(n->stack);
      }                         // end one or more
      if (n->pos >= peek(n->stack)) {
        n->OK = 0;
      }                         // one or more OK test
      pop(n->stack);
      printf("Comparing LEFT  %s\n", n->value);
      printf("Comparing RIGHT %s\n", (char *) "\"");
      if (n_OK(n) == 1 && n->len == 2 && stricmp(n, (const char *) "\"") == 0) {
        n->OK = 1;
        n->pos += 2;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }

    }                           // end group block
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      // begin group block
      if (n_OK(n) == 1) {
        printf("Comparing LEFT  %s\n", n->value);
        printf("Comparing RIGHT %s\n", (char *) "'");
        if (n_OK(n) == 1 && n->len == 1 && stricmp(n, (const char *) "'") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        push(n->stack, n->pos); // one or more
        if (n_OK(n) == 1) {
          push(n->stack, n->pos);
          // begin group block
          if (n_OK(n) == 1) {
            //NOT
            if (n_OK(n) == 1) {
              push(n->stack, n->pos);
              printf("Comparing LEFT  %s\n", n->value);
              printf("Comparing RIGHT %s\n", (char *) "'");
              if (n_OK(n) == 1 && n->len == 1 && stricmp(n, (const char *) "'") == 0) {
                n->OK = 1;
                n->pos += 1;
                if (n->pos >= n->len)
                  n->pos = -1;
              } else {
                n->OK = 0;
              }

              if (n->OK == 1) {
                n->OK = 0;
                n->pos = peek(n->stack);
              } else {
                n->OK = 1;
              }
              pop(n->stack);
            }                   //end NOT

          }                     // end group block

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }                     // one or more loop OK test
          pop(n->stack);
        }                       // end one or more
        if (n->pos >= peek(n->stack)) {
          n->OK = 0;
        }                       // one or more OK test
        pop(n->stack);
        printf("Comparing LEFT  %s\n", n->value);
        printf("Comparing RIGHT %s\n", (char *) "'");
        if (n_OK(n) == 1 && n->len == 1 && stricmp(n, (const char *) "'") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }

      }                         // end group block

    }
    //then that

    pop(n->stack);              //remove saved position
  }                             //end ok

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_integer
node_t *match_integer(node_t * n)
{
  printf("In functions match_integer\n");
  // or group
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);     //save position
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      if (n_OK(n) == 1) {
        n = match_unsigned_int(n);
      }                         //compare_function

    }
    //then that
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      // well this
      if (n->OK != 1) {         //if bad, retry wrapper
        n->OK = 1;
        n->pos = peek(n->stack);
        if (n_OK(n) == 1) {
          n = match_signed_int(n);
        }                       //compare_function

      }
      //then that

    }
    //then that

    pop(n->stack);              //remove saved position
  }                             //end ok

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_real
node_t *match_real(node_t * n)
{
  printf("In functions match_real\n");
  // or group
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);     //save position
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      if (n_OK(n) == 1) {
        n = match_integer(n);
      }                         //compare_function

    }
    //then that
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      // begin group block
      if (n_OK(n) == 1) {
        if (n_OK(n) == 1) {
          n = match_integer(n);
        }                       //compare_function
        printf("Comparing LEFT  %s\n", n->value);
        printf("Comparing RIGHT %s\n", (char *) ".");
        if (n_OK(n) == 1 && n->len == 1 && stricmp(n, (const char *) ".") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n);
        }                       //compare_function

      }                         // end group block

    }
    //then that
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      // begin group block
      if (n_OK(n) == 1) {
        printf("Comparing LEFT  %s\n", n->value);
        printf("Comparing RIGHT %s\n", (char *) ".");
        if (n_OK(n) == 1 && n->len == 1 && stricmp(n, (const char *) ".") == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        if (n_OK(n) == 1) {
          n = match_unsigned_int(n);
        }                       //compare_function

      }                         // end group block

    }
    //then that

    pop(n->stack);              //remove saved position
  }                             //end ok
  // begin optional block
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1) {
      n = match_exponent(n);
    }                           //compare_function

    if (n->OK == 0) {
      n->OK = 1;
      n->pos = peek(n->stack);
    }                           // weo or more loop OK test
    pop(n->stack);
  }                             // end optional block

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_alpha
node_t *match_alpha(node_t * n)
{
  printf("In functions match_alpha\n");
  push(n->stack, n->pos);       // one or more
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && ((n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z')
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
    }                           // one or more loop OK test
    pop(n->stack);
  }                             // end one or more
  if (n->pos >= peek(n->stack)) {
    n->OK = 0;
  }                             // one or more OK test
  pop(n->stack);

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_unsigned_int
node_t *match_unsigned_int(node_t * n)
{
  printf("In functions match_unsigned_int\n");
  push(n->stack, n->pos);       // one or more
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9')
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
    }                           // one or more loop OK test
    pop(n->stack);
  }                             // end one or more
  if (n->pos >= peek(n->stack)) {
    n->OK = 0;
  }                             // one or more OK test
  pop(n->stack);

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_sign
node_t *match_sign(node_t * n)
{
  printf("In functions match_sign\n");
  if (n_OK(n) == 1 && (n->value[n->pos] == '-' || n->value[n->pos] == '+')) {
    n->OK = 1;
    n->pos++;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }                             // end char

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_exponent
node_t *match_exponent(node_t * n)
{
  printf("In functions match_exponent\n");
  if (n_OK(n) == 1 && (n->value[n->pos] == 'E' || n->value[n->pos] == 'e')) {
    n->OK = 1;
    n->pos++;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }                             // end char
  if (n_OK(n) == 1) {
    n = match_integer(n);
  }                             //compare_function

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_signed_int
node_t *match_signed_int(node_t * n)
{
  printf("In functions match_signed_int\n");
  if (n_OK(n) == 1) {
    n = match_sign(n);
  }                             //compare_function
  if (n_OK(n) == 1) {
    n = match_unsigned_int(n);
  }                             //compare_function

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

// Function : match_whitespace
node_t *match_whitespace(node_t * n)
{
  printf("In functions match_whitespace\n");
  push(n->stack, n->pos);       // one or more
  if (n_OK(n) == 1) {
    push(n->stack, n->pos);
    if (n_OK(n) == 1 && (n->value[n->pos] == '\t' || n->value[n->pos] == ' ')) {
      n->OK = 1;
      n->pos++;
      if (n->pos >= n->len)
        n->pos = -1;
    } else {
      n->OK = 0;
    }                           // end char

    if (n->OK == 0) {
      n->pos = peek(n->stack);
    }                           // one or more loop OK test
    pop(n->stack);
  }                             // end one or more
  if (n->pos >= peek(n->stack)) {
    n->OK = 0;
  }                             // one or more OK test
  pop(n->stack);

  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");
  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-11-01
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
  n->OK = 1;
  n->stack = createStack(100);
  printf("POS:%d\n", n->pos);
  printf("OK:%d\n", n->OK);
  printf("--\n");

  n = match_string(n);
  if (n_OK(n) == 1)
    return n;
  n = match_integer(n);
  if (n_OK(n) == 1)
    return n;
  n = match_real(n);
  if (n_OK(n) == 1)
    return n;
  n = match_alpha(n);
  if (n_OK(n) == 1)
    return n;
  n = match_unsigned_int(n);
  if (n_OK(n) == 1)
    return n;
  n = match_sign(n);
  if (n_OK(n) == 1)
    return n;
  n = match_exponent(n);
  if (n_OK(n) == 1)
    return n;
  n = match_signed_int(n);
  if (n_OK(n) == 1)
    return n;
  n = match_whitespace(n);

  return n;
}                               // end match functions
