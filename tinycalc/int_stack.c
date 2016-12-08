//
// int_stack.c
// tinycalc
//
// Created by Dakota Schneider on 11/21/16.
// Copyright © 2016 Code From Above. All rights reserved.
//

#include "int_stack.h"

#include <stdlib.h>


IntStack * newIntStack() {
     IntStack * stack= malloc(sizeof(IntStackNode));
     if (!stack) return NULL;
     
     stack->size = 0;
     stack->top = NULL;
    
     return stack;
}

IntStackNode * push(IntStack * stack, int val) {
     IntStackNode * node = malloc(sizeof(IntStackNode));
     if (!node) return NULL;
     
     node->val = val;
     node->next = NULL;
     node->prev = stack->top;
    
     if (stack->top == NULL) {
          stack->top = node;
     } else {
          stack->top->next = node;
          stack->top = node;
     }
     
     stack->size++;
     
     return node;
}

int pop(IntStack * stack) {
    if (stack->top != NULL) {
        int val = stack->top->val;
        IntStackNode * prev = stack->top->prev;
        free(stack->top);
        stack->top = prev;

        stack->size--;
        return val;

    }
    // error condition, empty stack
    return 0;
}

int get(IntStack * stack, int idx) {
     // stack overflow?
     if (idx >= stack->size) { return NULL; }
     
     // otherwise
     IntStackNode * node = stack->top;
     for (int i = 0; i < idx; i++) {
          node = node->prev;
     }
     return node->val;
}


int set(IntStack * stack, int idx, int val) {
    // stack overflow?
    if (idx >= stack->size) { return NULL; }
    
    // otherwise
    IntStackNode * node = stack->top;
    for (int i = 0; i < idx; i++) {
        node = node->prev;
    }
    
    return node->val = val;
}

