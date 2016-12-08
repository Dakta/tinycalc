//
//  types.h
//  tinycalc
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#ifndef types_h
#define types_h

#include <stdio.h>

//struct Type;
//struct TypeVal;
//
typedef struct Type Type;
typedef struct TypeVal TypeVal;

struct Type {
    char* name;
    size_t size;
//    TypeVal * (* new)();
//    TypeVal * (* copy)();
//    void (* free)();
//    void (* set)();
//    void (* get)();
};

struct TypeVal {
    struct Type *type;

    void * val;
    size_t size;
};


Type * Type_new(
    char* name,
    size_t size
//    void * new,
//    void * set,
//    void * get
);


// create and destroy
TypeVal * TypeVal_new(Type * type);
TypeVal * TypeVal_copy(TypeVal * old);
void TypeVal_free(TypeVal * val);


// numeric types
extern Type * Int;
TypeVal * Int_new();
intmax_t Int_set(TypeVal * data, intmax_t val);
intmax_t Int_get(TypeVal * data);

extern Type * Double;
TypeVal * Double_new();
long double Double_set(TypeVal * data, long double val);
long double Double_get(TypeVal * data);

// string types
extern Type * String;
//TypeVal * String_new;
char* String_set(TypeVal * data, char* val);
char* String_get(TypeVal * data);


void Types_init();


#endif /* types_h */

