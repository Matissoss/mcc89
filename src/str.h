#ifndef MSTR_H
#define MSTR_H

#include <stdio.h>

typedef struct str {
    char* ptr;
    unsigned long len;
} str_t;

int str_t_print(str_t* self);

/*
int str_t_eq(str_t *lhs, str_t* rhs) {
    int i;
    if (lhs->len != rhs->len) return 0;
    for (i = 0; i < lhs->len; i++) {
        if (lhs->ptr[i] != rhs->ptr[i]) {
            return 0;
        }
    }
    return 1;
}
*/

#endif
