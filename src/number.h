/* mcc89 - src/number.h
 * made by matyz
 * licensed under MPL 2.0
 */

#ifndef MCC89_NUMBER_H
#define MCC89_NUMBER_H

#include "str.h"

enum number_type {
	N_NONE,

    N_F64,
	N_F32,
	
	N_U64,
	N_U32,
	N_U16,
	N_U8,
	
	N_I64,
	N_I32,
	N_I16,
	N_I8
};

struct number {
	enum number_type type;
	union {
		double v_f64;
		float v_f32;
		unsigned long v_u64;
		unsigned int v_u32;
		unsigned short v_u16;
		unsigned char v_u8;
		long v_i64;
		int v_i32;
		short v_i16;
		char v_i8;
	} content;
};

enum number_error {
    NERROR_NUMBER_TOO_LARGE,
    NERROR_INVALID_DIGIT
};

struct number_result {
    unsigned char is_ok;
    union {
        enum number_error v_error;
        struct number v_number;
    } content;
};

struct number number_from_str(str_t str);
int number_print(struct number self);

struct nubmer_result number_from_oct(str_t str, unsigned char is_minus);
struct number_result number_from_hex(str_t str, unsigned char is_minus);
struct number_result number_from_bin(str_t str, unsigned char is_minus);
struct number_result number_float_from_str(str_t str, unsigned char is_minus);

char number_digit_from_hex_char(char hexd);

#endif
