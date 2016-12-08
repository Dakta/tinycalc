//
//  main.c
//  tinycalc
//
//  Created by Dakota Schneider on 11/21/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <math.h>

#include "double_stack.h"

char seps[]   = " \t\n";

int main(int argc, char const *argv[]) {
    // initialize stack

    FILE *infile;

    if (argc == 2) {
        infile = fopen(argv[1], "r");
        if (infile == NULL) {
            printf("can's open file %s", argv[1]); exit(1);
        }
    } else {
        infile = stdin;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    char *token;
    char *saveptr; // used by strtok_r, see http://stackoverflow.com/a/15961298/362042

    DoubleStack *stack = newDoubleStack();

    while (read != -1) {
        // prompt
        fputs("TC>", stdout);
        // get input
        read = getline(&line, &len, infile);
        // what we got?

        /* While there are tokens in line */
        for (
            token = strtok_r(line, seps, &saveptr);
            token != NULL;
            token = strtok_r(NULL, seps, &saveptr)
        ) {
            // hit a comment, abort abort
            if (token[0] == '%') { break; }

            // Process Tokens

            // 1. Look up methods
            if (strcmp(token, "index") == 0) {
                // copy nth item of stack to top of stack
                push(stack, get(stack, pop(stack)));
            } else if (strcmp(token, "dup") == 0) {
                // duplicate top item of stack
                push(stack, get(stack, 0));
            } else if (strcmp(token, "exch") == 0) {
                // swap top two stack items
                double val1 = pop(stack);
                double val2 = pop(stack);
                push(stack, val1);
                push(stack, val2);
            } else if (strcmp(token, "pop") == 0) {
                // remove top stack item
                pop(stack);
            } else if (strcmp(token, "roll") == 0) {
                double count = pop(stack);
                double size  = pop(stack) - 1;
                
                // negative rolling isn't too hard
                if (count < 0) {
                    count = size + count;
                }
                
                // ugh shit? oh we can do this super cleverly!
                for (int j = 0; j < count; j++) {
                    for (int i = 0; i < size; i++) {
                        double val1 = get(stack, i);
                        double val2 = get(stack, i + 1);
                        set(stack, i, val2);
                        set(stack, i + 1, val1);
                    }
                }
            } else if (strcmp(token, "copy") == 0) {
                // duplicate top n items
                double n = pop(stack);
                for (int i = 0; i < n; i++) {
                    push(stack, get(stack, i));
                }
            } else if (strcmp(token, "add") == 0) {
                push(stack, pop(stack) * pop(stack));
            } else if (strcmp(token, "sub") == 0) {
                double val1 = pop(stack);
                double val2 = pop(stack);
                push(stack, val2 - val1);
            } else if (strcmp(token, "mul") == 0) {
                push(stack, pop(stack) * pop(stack));
            } else if (strcmp(token, "div") == 0) {
                double val1 = pop(stack);
                double val2 = pop(stack);
                push(stack, val2 / val1);
            } else if (strcmp(token, "idiv") == 0) {
                double val1 = pop(stack);
                double val2 = pop(stack);
                push(stack, floor(val2 / val1));
            } else if (strcmp(token, "mod") == 0) {
                double val1 = pop(stack);
                double val2 = pop(stack);
                push(stack, fmod(val2, val1));
            } else if (strcmp(token, "sqrt") == 0) {
                push(stack, sqrt(pop(stack)));
            } else if (strcmp(token, "sin") == 0) {
                push(stack, sin(pop(stack)));
            } else if (strcmp(token, "cos") == 0) {
                push(stack, cos(pop(stack)));
            } else if (strcmp(token, "pstack") == 0) {
                // print stack, left to right
                for (int i = stack->size - 1; i >= 0; i--) {
                    printf(" %lf", get(stack, i));
                }
                puts("");
            } else {
                // 2. Otherwise it's a value
                // 3. Can we parse it
                double num = strtod(token, NULL);
                if (errno == ERANGE) {
                    /* Could not convert. */
                } else {
                    // success!
                    push(stack, num);
                }
            }
        }
    }
    free(line);
    return 0;
}
