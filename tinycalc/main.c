//
//  main.c
//  tinycalc
//
//  Created by Dakota Schneider on 11/21/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <inttypes.h>

//#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "types.h"
#include "stack.h"


char seps[] = " \t\n";

int main(int argc, char const *argv[]) {
    // gotta get set up
    Types_init();

    FILE *infile;
    
    if (argc == 2) {
        infile = fopen(argv[1], "r");
        if (infile == NULL) {
            printf("can't open file %s", argv[1]); exit(1);
        }
    } else {
        infile = stdin;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    
    char *token;
    char *saveptr; // used by strtok_r, see http://stackoverflow.com/a/15961298/362042
    
    Stack *stack = newStack();
    
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
            
//            puts(token);
            
            // Process Tokens
            
            // 1. Look up methods
            if (strcmp(token, "index") == 0) {
                // copy nth item of stack to top of stack
                // TODO type safety check
                push(stack, get(stack, Int_get(pop(stack))));
            } else if (strcmp(token, "dup") == 0) {
                // duplicate top item of stack
                push(stack, get(stack, 0));
            } else if (strcmp(token, "exch") == 0) {
                // swap top two stack items
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                
                push(stack, val1);
                push(stack, val2);
                
                TypeVal_free(val1);
                TypeVal_free(val2);
            } else if (strcmp(token, "pop") == 0) {
                // remove top stack item
                pop(stack);
            } else if (strcmp(token, "roll") == 0) {
                // TODO type safety check
                intmax_t count = Int_get(pop(stack));
                intmax_t size  = Int_get(pop(stack));
                
                // negative rolling isn't too hard
                if (count < 0) {
                    count = size + count;
                }
                
                // ugh shit? oh we can do this super cleverly!
                for (int j = 0; j < count; j++) {
                    for (int i = 0; i < size - 1; i++) {
                        TypeVal * val1 = get(stack, i);
                        TypeVal * val2 = get(stack, i + 1);
                        
                        set(stack, i, val2);
                        set(stack, i + 1, val1);
                        
                        TypeVal_free(val1);
                        TypeVal_free(val2);
                    }
                }
            } else if (strcmp(token, "copy") == 0) {
                // duplicate top n items
                intmax_t n = Int_get(pop(stack));
                for (intmax_t i = 0; i < n; i++) {
                    push(stack, get(stack, n - 1));
                }
            } else if (strcmp(token, "cvi") == 0) {
                // convert to integer
                
                TypeVal * val1 = pop(stack);
                TypeVal * result = TypeVal_new(Int);
                Int_set(result, Int_get(val1));
                
                push(stack, result);
                
                TypeVal_free(val1);
                TypeVal_free(result);
            } else if (strcmp(token, "add") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                if (val1->type == Int &&
                    val2->type == Int
                ) {
                    result = TypeVal_new(Int);
                    Int_set(result, Int_get(val1) + Int_get(val2));
                } else {
                    result = TypeVal_new(Double);
                    Double_set(result, Double_get(val1) + Double_get(val2));
                }
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "sub") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                if (val1->type == Int &&
                    val2->type == Int
                ) {
                    result = TypeVal_new(Int);
                    Int_set(result, Int_get(val2) - Int_get(val1));
                } else {
                    result = TypeVal_new(Double);
                    Double_set(result, Double_get(val2) - Double_get(val1));
                }
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "mul") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                if (val1->type == Int &&
                    val2->type == Int
                ) {
                    result = TypeVal_new(Int);
                    Int_set(result, Int_get(val1) * Int_get(val2));
                } else {
                    result = TypeVal_new(Double);
                    Double_set(result, Double_get(val1) * Double_get(val2));
                }
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "div") == 0) {
                // regular divion always produces a float
                
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                
                TypeVal * result = TypeVal_new(Double);
                Double_set(result, Double_get(val2) / Double_get(val1));
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "idiv") == 0) {
                // special integer division convenience method
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                result = TypeVal_new(Int);
                Int_set(result, Int_get(val2) / Int_get(val1));
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "mod") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * val2 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                if (val1->type == Int &&
                    val2->type == Int
                ) {
                    result = TypeVal_new(Int);
                    Int_set(result, Int_get(val2) % Int_get(val1));
                } else {
                    result = TypeVal_new(Double);
                    Double_set(result, fmod(Double_get(val2), Double_get(val1)));
                }
                push(stack, result);

                // clean up
                TypeVal_free(val1);
                TypeVal_free(val2);
                TypeVal_free(result);
            } else if (strcmp(token, "sqrt") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
//                if (val1->type == Int) {
//                    result = TypeVal_new(Int);
//                    Int_set(result, sqrt(Int_get(val1)));
//                } else {
                result = TypeVal_new(Double);
                Double_set(result, sqrt(Double_get(val1)));
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(result);
            } else if (strcmp(token, "sin") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                result = TypeVal_new(Double);
                Double_set(result, sin(Double_get(val1)));
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(result);
            } else if (strcmp(token, "cos") == 0) {
                TypeVal * val1 = pop(stack);
                TypeVal * result;
                
                // TODO numeric type safety check
                
                result = TypeVal_new(Double);
                Double_set(result, cos(Double_get(val1)));
                push(stack, result);
                
                // clean up
                TypeVal_free(val1);
                TypeVal_free(result);
            } else if (strcmp(token, "pstack") == 0) {
                // print stack, left to right
                for (intmax_t i = stack->size - 1; i >= 0; i--) {
                    printf(" %s", String_get(get(stack, i)));
                }
                puts("");
            } else {
                // 2. Otherwise it's a value
    
                TypeVal * val = NULL;
                
                // check if it's a symbol
                
                // Try to parse int
                // the Most Proper Way(tm): https://www.securecoding.cert.org/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number#ERR34-C.Detecterrorswhenconvertingastringtoanumber-CompliantSolution(strtol())
                
                char *end = NULL;
                errno = 0;
                
                intmax_t intnum = strtoimax(token, &end, 10);

                if (end == token) {
                    fprintf(stderr, "%s: not a decimal number\n", token);
                } else if ('\0' != *end) {
                    fprintf(stderr, "%s: extra characters at end of input: %s\nAssuming float type\n", token, end);
                    
                    // try to parse float
                    end = NULL;
                    errno = 0;
                    
                    long double floatnum = strtold(token, &end);
                    
                    if (end == token) {
                        fprintf(stderr, "%s: not a decimal number\n", token);
                    } else if ('\0' != *end) {
                        fprintf(stderr, "%s: extra characters at end of input: %s\nInvalid type\n", token, end);
                    } else if ((floatnum == LDBL_MIN || floatnum == LDBL_MAX) && ERANGE == errno) {
                        fprintf(stderr, "%s: out of range of type long double\n", token);
                    } else {
                        // valid long double
                        val = TypeVal_new(Double);
                        Double_set(val, floatnum);
                        push(stack, val);
                        TypeVal_free(val);
                    }
                    
                } else if ((intnum == INTMAX_MIN || intnum == INTMAX_MAX) && ERANGE == errno) {
                    fprintf(stderr, "%s: out of range of type intmax_t\n", token);
                } else {
                    // valid intmax_t
                    val = TypeVal_new(Int);
                    Int_set(val, intnum);
                    push(stack, val);
                    TypeVal_free(val);
                }
                
                // clean up
            }

            
            
                
                
//                // 3. Can we parse it
//                long double num = strtod(token, NULL);
//                if (errno == ERANGE) {
//                    /* Could not convert. */
//                } else {
//                    // success!
//                    TypeVal * val = TypeVal_new(Double);
//                    Double_set(val, num);
//                    push(stack, val);
//                    TypeVal_free(val);
//                }
//            }

//            // print stack for debugging
//            for (int i = stack->size - 1; i >= 0; i--) {
//                printf(" %s", String_get(get(stack, i)));
//            }
//            puts("");

        }
    }
    free(line);
    return 0;
}
