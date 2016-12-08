//
//  int_stack.h
//  tinycalc
//
//  Created by Dakota Schneider on 11/21/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#ifndef int_stack_h
#define int_stack_h

#include <stdio.h>

#endif /* int_stack_h */


typedef struct IntStackNode {
  int val;
  struct IntStackNode * prev;
  struct IntStackNode * next;
} IntStackNode;

typedef struct IntStack {
  int size;
  struct IntStackNode * top;
  struct IntStackNode * bottom;
} IntStack;


IntStack * newIntStack();

void pushl(int val);

void popl(int * reg);

int get(IntStack * stack, int idx);

int set(IntStack * stack, int idx, int val);


// TODO: hide these
IntStackNode * push(IntStack * stack, int val);
int pop(IntStack * stack);
