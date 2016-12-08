//
//  types.c
//  tinycalc
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include "types.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


Type * Int = NULL;

Type * Double = NULL;

Type * String = NULL;


Type * Type_new(
    char* name,
    size_t size
//    void * new,
//    void * set,
//    void * get
) {
    Type * type = malloc(sizeof(Type));

    type->name = strdup(name);
    type->size = size;
//    type->new = new;
//    type->copy = TypeVal_copy;
//    type->free = TypeVal_free;
//    type->set = set;
//    type->get = get;
    
    return type;
}

TypeVal * TypeVal_new(Type * type) {
    TypeVal * val = malloc(sizeof(TypeVal));

    val->type = type;
    val->size = val->type->size;
    val->val = malloc(val->size);
    
    return val;
}

TypeVal * TypeVal_copy(TypeVal * old) {
    TypeVal * new = malloc(sizeof(TypeVal));
    new->type = old->type;
    
    new->size = old->size;
    new->val = malloc(new->size);
    memcpy(new->val, old->val, new->size);
    
    return new;
}

void TypeVal_free(TypeVal * val) {
    free(val->val);
    free(val);
}


bool isNumberType(TypeVal * data) {
    return (
        data->type == Int ||
        data->type == Double
    );
}

TypeVal * Int_new() {
    return TypeVal_new(Int);
}

intmax_t Int_set(TypeVal * data, intmax_t val) {
    if (data->type == Int) {
        *((intmax_t *)data->val) = val;
    } else if (data->type == Double) {
        *((long double *) data->val) = (long double) val;
    } else if (data->type == String) {
        // clean up
        free(data->val);
        // how big?
        data->size = snprintf(NULL, 0, "%jd", val);
        data->val = malloc(data->size+1);
        // stringify
        sprintf((char *) data->val, "%jd", val);
    }
    return val;
}

intmax_t Int_get(TypeVal * data) {
    intmax_t val;
    
    if (data->type == Int) {
        val = *((intmax_t *) data->val);
    } else if (data->type == Double) {
        val = (long double) floor(*((long double *) data->val));
    } else if (data->type == String) {
        // todo
    }
    
    return val;
}

TypeVal * Double_new() {
    return TypeVal_new(Double);
}

long double Double_set(TypeVal * data, long double val) {
    if (data->type == Int) {
        *((intmax_t *) data->val) = (intmax_t) floor(val);
    } else if (data->type == Double) {
        *((long double *) data->val) = val;
    } else if (data->type == String) {
        // clean up
        free(data->val);
        // how big?
        data->size = snprintf(NULL, 0, "%Lf", val);
        data->val = malloc(data->size+1);
        // stringify
        sprintf((char *) data->val, "%Lf", val);
    }
    return val;
}

long double Double_get(TypeVal * data) {
    long double val;
    
    if (data->type == Int) {
        val = (long double) *((intmax_t *) data->val);
    } else if (data->type == Double) {
        val = *((long double *) data->val);
    } else if (data->type == String) {
        // todo
    }
    
    return val;
}

//TypeVal * String_new() {
//    return TypeVal_new(String);
//}

char* String_set(TypeVal * data, char* val) {
    if (data->type == Int) {
        // what
    } else if (data->type == Double) {
        // what
    } else if (data->type == String) {
        // clean up
        free(data->val);
        // how big?
        data->size = sizeof(val);
        data->val = strdup(val);
    }
    return val;
}

char* String_get(TypeVal * data) {
    char* val;

    if (data->type == Int) {
        // how big?
        size_t size = snprintf(NULL, 0, "%jd", *((intmax_t *) data->val));
        val = malloc(size+1);
        // stringify
        sprintf((char *) val, "%jd", *((intmax_t *)data->val));
    } else if (data->type == Double) {
        // how big?
        size_t size = snprintf(NULL, 0, "%Lf", *((long double *) data->val));
        val = malloc(size+1);
        // stringify
        sprintf((char *) val, "%Lf", *((long double *) data->val));
    } else if (data->type == String) {
        val = strdup((char *) data->val);
    }
    
    return val;
}


void Types_init() {
    if (Int == NULL) {
        Int = Type_new(
            "Integer",
            sizeof(intmax_t)
//            &Int_new,
//            &Int_new,
//            &Int_get
        );
    }
    if (Double == NULL) {
        Double = Type_new(
            "Double",
            sizeof(long double)
//            &Double_new,
//            &Double_set,
//            &Double_get
        );
    }
    if (String == NULL) {
        String = Type_new(
            "String",
            (size_t) 0
//            &String_new,
//            &String_set,
//            &String_get
        );
    }
}

