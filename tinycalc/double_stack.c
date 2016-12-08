//
//  double_stack.c
//  tinycalc
//
//  Created by Dakota Schneider on 11/30/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include "double_stack.h"

#include <stdlib.h>


DoubleStack * newDoubleStack() {
  DoubleStack * stack = malloc(sizeof(DoubleStackNode));
  if (!stack) return NULL;
  
  stack->size = 0;
  stack->top = NULL;
  
  return stack;
}

DoubleStackNode * push(DoubleStack * stack, double val) {
  DoubleStackNode * node = malloc(sizeof(DoubleStackNode));
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

double pop(DoubleStack * stack) {
  if (stack->top != NULL) {
    double val = stack->top->val;
    DoubleStackNode * prev = stack->top->prev;
    free(stack->top);
    stack->top = prev;
    
    stack->size--;
    return val;
    
  }
  // error condition, empty stack
  return 0;
}

double get(DoubleStack * stack, int idx) {
  // stack overflow?
  if (idx >= stack->size) { return 0; }
  
  // otherwise
  DoubleStackNode * node = stack->top;
  for (int i = 0; i < idx; i++) {
    node = node->prev;
  }
  return node->val;
}


void set(DoubleStack * stack, int idx, double val) {
  // stack overflow?
  if (idx >= stack->size) { return; }
  
  // otherwise
  DoubleStackNode * node = stack->top;
  for (int i = 0; i < idx; i++) {
    node = node->prev;
  }
  
  node->val = val;
}

