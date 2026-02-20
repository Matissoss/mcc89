#ifndef MSTR_H
#define MSTR_H

#include <stdio.h>

typedef struct str {
    char* ptr;
    unsigned long len;
} str_t;

int str_t_print(str_t* self);

#endif
