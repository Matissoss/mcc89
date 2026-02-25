/* mcc89 - src/number.c
 * made by matyz
 * licensed under MPL 2.0
 */

#include "number.h"

struct number_result number_from_bin(str_t str, unsigned char is_minus) {
    struct number_result toret;
    unsigned long n = 0;
    int i;
    for (i = 0; i < str.len; i++) {
        if (str.ptr[i] == '0') {
            if (n & 1 << (sizeof(n) - 1)) {
                toret.content.v_error = NERROR_NUMBER_TOO_LARGE;
                toret.is_ok = 0;
                return toret;
            } else {
                n <<= 1;
            }
        }
        else if (str.ptr[i] == '1') {
            if (n & 1 << (sizeof(n) - 1)) {
                toret.content.v_error = NERROR_NUMBER_TOO_LARGE;
                toret.is_ok = 0;
                return toret;
            }
            n |= 1;
            n <<= 1;
        } else {
            toret.content.v_error = NERROR_INVALID_DIGIT;
            toret.is_ok = 0;
            return toret;
        }
    }
    if (is_minus) {
        n = (long) -n;
    }
    if (n <= 255) {
        toret.content.v_number.type = is_minus ? N_I8 : N_U8;
    } else if (n <= (2 << 16) - 1) {
        toret.content.v_number.type = is_minus ? N_I16 : N_U16;
    } else if (n <= (2ul << 32) - 1) {
        toret.content.v_number.type = is_minus ? N_I32 : N_U32;
    } else {
        toret.content.v_number.type = is_minus ? N_I64 : N_U64;
    }
    toret.content.v_number.content.v_u64 = n;
    toret.is_ok = 1;
    return toret;
}

struct number number_from_str(str_t str) {
    struct number toreturn = {0};
    /* TODO */
    if (str.len >= 2 && str.ptr[0] == '0') {
        if (str.ptr[1] == 'x') {

        } else if (str.ptr[1] == 'b') {

        } else if (str.ptr[1] == 'o') {

        }
    }
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
