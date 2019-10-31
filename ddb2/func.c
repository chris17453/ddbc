/********************************************
* Generated: 2019-10-31                    *
********************************************/
#include <stdio.h>
#include "headers/stack.h"
#include "headers/func.h"
// node values are only compared if string length is the same, no need to validate
// comparitors is against a precompiled value thats already case optimised
// returns 0 for equal
int stricmp(node_t * n, char const *b)
{
  int d = 0;
  for (int i = 0; i < n->len; i++) {
    d = tolower(node[i]) - b[i];
    if (d != 0)
      return d;
  }
  return 0;
}

// Function : match_string
node_t *match_string(node_t * n)
{
  // or group
  if (n->pos != -1 && n->OK == 1) {
    push(n->stack, n->pos);     //save position
    // begin group block
    if (n->pos != -1 && n->OK == 1) {
      if (n->pos != -1 && n->OK == 1 && n->len == 1 && strcmpi(n, '"') == 0) {
        n->OK = 1;
        n->pos += 1;
        if (n->pos >= n->len)
          n->pos = -1;
      } else {
        n->OK = 0;
      }
      push(n->stack, n->pos);   // one or more
      if (n->pos != -1 && n->OK == 1) {
        push(n->stack, n->pos);
        // begin group block
        if (n->pos != -1 && n->OK == 1) {
          //NOT
          if (n->pos != -1 && n->OK == 1) {
            push(n->stack, n->pos);
            if (n->pos != -1 && n->OK == 1 && n->len == 1 && strcmpi(n, '"') == 0) {
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
          }                     //end NOT

        }                       // end group block

        if (n->OK == 0) {
          n->pos = peek(n->stack);
        }                       // one or more loop OK test
        pop(n->stack);
      }                         // end one or more
      if (n->pos >== peek(n->stack)) {
        n->OK = 0;
      }                         // one or more OK test
      pop(n->stack);
      if (n->pos != -1 && n->OK == 1 && n->len == 1 && strcmpi(n, '"') == 0) {
        n->OK = 1;
        n->pos += 1;
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
      if (n->pos != -1 && n->OK == 1) {
        if (n->pos != -1 && n->OK == 1 && n->len == 2 && strcmpi(n, '\'') == 0) {
          n->OK = 1;
          n->pos += 2;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        push(n->stack, n->pos); // one or more
        if (n->pos != -1 && n->OK == 1) {
          push(n->stack, n->pos);
          // begin group block
          if (n->pos != -1 && n->OK == 1) {
            //NOT
            if (n->pos != -1 && n->OK == 1) {
              push(n->stack, n->pos);
              if (n->pos != -1 && n->OK == 1 && n->len == 2 && strcmpi(n, '\'') == 0) {
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
            }                   //end NOT

          }                     // end group block

          if (n->OK == 0) {
            n->pos = peek(n->stack);
          }                     // one or more loop OK test
          pop(n->stack);
        }                       // end one or more
        if (n->pos >== peek(n->stack)) {
          n->OK = 0;
        }                       // one or more OK test
        pop(n->stack);
        if (n->pos != -1 && n->OK == 1 && n->len == 2 && strcmpi(n, '\'') == 0) {
          n->OK = 1;
          n->pos += 2;
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

  return n;
}

// Function : match_integer
node_t *match_integer(node_t * n)
{
  // or group
  if (n->pos != -1 && n->OK == 1) {
    push(n->stack, n->pos);     //save position
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      if (n->pos != -1 && n->OK == 1) {
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
        if (n->pos != -1 && n->OK == 1) {
          n = match_signed_int(n);
        }                       //compare_function

      }
      //then that

    }
    //then that

    pop(n->stack);              //remove saved position
  }                             //end ok

  return n;
}

// Function : match_real
node_t *match_real(node_t * n)
{
  // or group
  if (n->pos != -1 && n->OK == 1) {
    push(n->stack, n->pos);     //save position
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      if (n->pos != -1 && n->OK == 1) {
        n = match_integer(n);
      }                         //compare_function

    }
    //then that
    // well this
    if (n->OK != 1) {           //if bad, retry wrapper
      n->OK = 1;
      n->pos = peek(n->stack);
      // begin group block
      if (n->pos != -1 && n->OK == 1) {
        if (n->pos != -1 && n->OK == 1) {
          n = match_integer(n);
        }                       //compare_function
        if (n->pos != -1 && n->OK == 1 && n->len == 1 && strcmpi(n, '.') == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        if (n->pos != -1 && n->OK == 1) {
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
      if (n->pos != -1 && n->OK == 1) {
        if (n->pos != -1 && n->OK == 1 && n->len == 1 && strcmpi(n, '.') == 0) {
          n->OK = 1;
          n->pos += 1;
          if (n->pos >= n->len)
            n->pos = -1;
        } else {
          n->OK = 0;
        }
        if (n->pos != -1 && n->OK == 1) {
          n = match_unsigned_int(n);
        }                       //compare_function

      }                         // end group block

    }
    //then that

    pop(n->stack);              //remove saved position
  }                             //end ok
  // begin optional block
  if (node = !NULL) {
    node_t * {
    node_uid}
    = node;
    if (n->pos != -1 && n->OK == 1) {
      n = match_exponent(n);
    }                           //compare_function

    if (node == NULL)
      node = { node_uid };
  }                             // end optional block

  return n;
}

// Function : match_alpha
node_t *match_alpha(node_t * n)
{
  push(n->stack, n->pos);       // one or more
  if (n->pos != -1 && n->OK == 1) {
    push(n->stack, n->pos);
    if (n->pos != -1 && n->OK == 1 && ((n->value[n->pos] >= 'A' && n->value[n->pos] <= 'Z') || (n->value[n->pos] >= 'a' && n->value[n->pos] <= 'z')
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
  if (n->pos >== peek(n->stack)) {
    n->OK = 0;
  }                             // one or more OK test
  pop(n->stack);

  return n;
}

// Function : match_unsigned_int
node_t *match_unsigned_int(node_t * n)
{
  push(n->stack, n->pos);       // one or more
  if (n->pos != -1 && n->OK == 1) {
    push(n->stack, n->pos);
    if (n->pos != -1 && n->OK == 1 && ((n->value[n->pos] >= '0' && n->value[n->pos] <= '9')
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
  if (n->pos >== peek(n->stack)) {
    n->OK = 0;
  }                             // one or more OK test
  pop(n->stack);

  return n;
}

// Function : match_sign
node_t *match_sign(node_t * n)
{
  if (n->pos != -1 && n->OK == 1 && (n->value[n->pos] == '-' || n->value[n->pos] == '+')) {
    n->OK = 1;
    n->pos++;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }                             // end char

  return n;
}

// Function : match_exponent
node_t *match_exponent(node_t * n)
{
  if (n->pos != -1 && n->OK == 1 && (n->value[n->pos] == 'E' || n->value[n->pos] == 'e')) {
    n->OK = 1;
    n->pos++;
    if (n->pos >= n->len)
      n->pos = -1;
  } else {
    n->OK = 0;
  }                             // end char
  if (n->pos != -1 && n->OK == 1) {
    n = match_integer(n);
  }                             //compare_function

  return n;
}

// Function : match_signed_int
node_t *match_signed_int(node_t * n)
{
  if (n->pos != -1 && n->OK == 1) {
    n = match_sign(n);
  }                             //compare_function
  if (n->pos != -1 && n->OK == 1) {
    n = match_unsigned_int(n);
  }                             //compare_function

  return n;
}

/*
* Function: match_functions
* -----------------------------
*   Generated: 2019-10-31
*      nodes: a pointer to the curent element in a linked list of nodes to search
*
*     OK: Returns a the node AFTER the curent pattern match
*              If the end of the list is reached the last node is passed
*     Failure: Returns NULL
*/
node_t *match_function(char *data)
{
  node_t *n = malloc(sizeof(node_t));
  n->value = data;
  n->len = strlen(data);
  n->pos = 0;
  n->stack = createStack(100);

  n = match_string(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_integer(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_real(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_alpha(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_unsigned_int(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_sign(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_exponent(nodes);
  if (n.pos != -1 && n->OK = 1)
    return node;
  n = match_signed_int(nodes);

  return n;
}                               // end match functions
