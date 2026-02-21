/* mcc89 - src/number.c
 * made by matyz
 * licensed under MPL 2.0
 */

#include "number.h"

struct number number_from_str(str_t str) {
    struct number toreturn = {0};
    /* TODO */
    return toreturn;
}

int number_print(struct number self) {
    switch (self.type) {
        case N_NONE: printf("NULL");
        case N_F32:
            printf("Float(%f)", self.content.v_f32);
            break;
        case N_F64:
            printf("Double(%lf)", self.content.v_f64);
            break;
        case N_U64:
            printf("U64(%ld)", self.content.v_u64);
            break;
        case N_U32:
            printf("U32(%u)", self.content.v_u32);
            break;
        case N_U16:
            printf("U16(%u)", self.content.v_u16);
            break;
        case N_U8:
            printf("U8(%u)", self.content.v_u8);
            break;
        case N_I64:
            printf("I64(%ld)", self.content.v_i64);
            break;
        case N_I32:
            printf("I32(%d)", self.content.v_i32);
            break;
        case N_I16:
            printf("I16(%d)", self.content.v_i16);
            break;
        case N_I8:
            printf("I8(%d)", self.content.v_i8);
            break;
    }
    return 0;
}
