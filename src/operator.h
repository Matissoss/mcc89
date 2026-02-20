/* mcc89 - src/operator.h
 * made by matyz
 * licensed under MPL 2.0
 */

#include "str.h"

#ifndef OPERATOR_H
#define OPERATOR_H

enum operator {
    OP_NONE,
	OP_ASSIGN, /* = */
	OP_LT, /* < */
	OP_GT, /* > */
	OP_EQ, /* == */
	OP_LTE, /* <= */
	OP_GTE, /* >= */
	
	OP_XOR, /* ^ */
	OP_ADD, /* + */
	OP_SUB, /* - */
	OP_MUL, /* * */
	OP_DIV, /* / */
	OP_MOD, /* % */
	OP_AND, /* & */
	OP_OR,  /* | */
	OP_NEG, /* ! */
    OP_LSH, /* << */
    OP_RSH, /* >> */
	
	OP_XORASSIGN, /* ^= */
	OP_ADDASSIGN, /* += */
	OP_SUBASSIGN, /* -= */
	OP_MULASSIGN, /* *= */
	OP_DIVASSIGN, /* /= */
	OP_MODASSIGN, /* %= */
	OP_ANDASSIGN, /* &= */
	OP_ORASSIGN,  /* |= */
	OP_NEGASSIGN, /* != */
    OP_LSHASSIGN, /* <<= */
    OP_RSHASSIGN, /* >>= */
	OP_ARROW,     /* -> */
	OP_CMP_AND,   /* && */
	OP_CMP_OR,    /* || */
	
	/* misc operators */
	OP_DOT, /* . */
	OP_QM, /* ? */
	OP_COLON /* : */
};

unsigned char operator_as_str_len(enum operator self);
void operator_print(enum operator* operator);
enum operator operator_from_str(str_t slice);

#endif
