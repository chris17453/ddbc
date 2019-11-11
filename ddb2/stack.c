// C program for array implementation of stack 
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include "headers/stack.h"
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
stack_t* createStack(unsigned capacity) { 
     stack_t* stack = ( stack_t*)malloc(sizeof( stack_t)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    //printf("stack created\n"); 
    return stack; 
} 
  
//  stack_t is full when top is equal to the last index 
int isFull(stack_t* stack) { 
    return stack->top == stack->capacity - 1; 
} 
  
//  stack_t is empty when top is equal to -1 
int isEmpty(stack_t* stack) { 
    return stack->top == -1; 
} 
  
// Function to add an item to stack.  It increases top by 1 
void push(stack_t* stack, int item) { 
    if (stack->top == stack->capacity - 1)  {
        printf("stack full\n"); 
        return; 
    }
    stack->array[++stack->top] = item; 
    //printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
int pop(stack_t* stack) { 
    if (stack->top == -1) {
        printf("stack empty\n"); 
        return INT_MIN; 
    }
    int item=stack->array[stack->top--]; 
    //printf("%d popped from stack\n", item); 
    return item;
} 
  
// Function to return the top from stack without removing it 
int peek(stack_t* stack){ 
    if (stack->top == -1) {
        printf("stack empty\n"); 
        return INT_MIN; 
    }
    return stack->array[stack->top]; 
} 

//struct  stack_t* stack = createStack(100); 
