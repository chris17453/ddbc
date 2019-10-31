#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 

// A structure to represent a stack 
typedef struct { 
    int top; 
    unsigned capacity; 
    int* array; 
}  stack_t; 
  
stack_t *  createStack (unsigned capacity);
int        isFull      (stack_t* stack);
int        isEmpty     (stack_t* stack);
void       push        (stack_t* stack, int item);
int        pop         (stack_t* stack);
int        peek        (stack_t* stack);

