//
//  double_stack.h
//  tinycalc
//
//  Created by Dakota Schneider on 11/30/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#ifndef double_stack_h
#define double_stack_h

#include <stdio.h>

#endif /* double_stack_h */

typedef struct DoubleStackNode {
  double val;
  struct DoubleStackNode * prev;
  struct DoubleStackNode * next;
} DoubleStackNode;

typedef struct DoubleStack {
  int size;
  struct DoubleStackNode * top;
  struct DoubleStackNode * bottom;
} DoubleStack;


DoubleStack * newDoubleStack();

void pushl(double val);

void popl(int * reg);

double get(DoubleStack * stack, int idx);

void set(DoubleStack * stack, int idx, double val);


// TODO: hide these
DoubleStackNode * push(DoubleStack * stack, double val);
double pop(DoubleStack * stack);
