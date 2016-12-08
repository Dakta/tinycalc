//
//  stack.c
//  tinycalc
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include "stack.h"


#include <stdlib.h>


Stack * newStack() {
    Stack * stack= malloc(sizeof(StackNode));
    if (!stack) return NULL;
    
    stack->size = 0;
    stack->top = NULL;
    
    return stack;
}

StackNode * push(Stack * stack, TypeVal * val) {
    StackNode * node = malloc(sizeof(StackNode));
    if (!node) return NULL;
    
    node->val = TypeVal_copy(val);
    node->prev = stack->top;
    
    stack->top = node;
    
    stack->size++;
    
    return node;
}

TypeVal * pop(Stack * stack) {
    if (stack->top != NULL) {
        TypeVal * val = stack->top->val;
        StackNode * prev = stack->top->prev;
        free(stack->top);
        stack->top = prev;
        
        stack->size--;
        return val;
        
    } else {
        // error condition, empty stack
    }
    return 0;
}

TypeVal * get(Stack * stack, intmax_t idx) {
    // stack overflow?
    if (idx >= stack->size) { return NULL; }
    
    // otherwise
    StackNode * node = stack->top;
    for (int i = 0; i < idx; i++) {
        node = node->prev;
    }
    return TypeVal_copy(node->val);
}


TypeVal * set(Stack * stack, intmax_t idx, TypeVal * val) {
    // stack overflow?
    if (idx >= stack->size) { return NULL; }
    
    // otherwise
    StackNode * node = stack->top;
    for (int i = 0; i < idx; i++) {
        node = node->prev;
    }
    
    return node->val = TypeVal_copy(val);
}

