#include "str.h"

int str_t_print(str_t* self) {
    int i, printed = 0;
    for (i = 0; i < self->len; i++) {
        printed += printf("%c", self->ptr[i]);
    }
    return printed;
}
