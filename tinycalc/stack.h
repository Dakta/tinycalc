//
//  stack.h
//  tinycalc
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>

#include "types.h"


typedef struct StackNode {
    TypeVal * val;
    struct StackNode * prev;
} StackNode;

typedef struct Stack {
    int size;
    struct StackNode * top;
} Stack;

Stack * newStack();

TypeVal * get(Stack * stack, intmax_t idx);

TypeVal * set(Stack * stack, intmax_t idx, TypeVal * val);

StackNode * push(Stack * stack, TypeVal * val);

TypeVal * pop(Stack * stack);

#endif /* stack_h */
