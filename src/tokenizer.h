/* mcc89 - src/tokenizer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "str.h"

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

enum token_type {
	TOKEN_STRING,
	TOKEN_WHITESPACE,
	/* Delimeters */
	TOKEN_PARAM_OPEN, /* ( */
	TOKEN_PARAM_CLOSE, /* ) */
	TOKEN_BRACE_OPEN,  /* { */
	TOKEN_BRACE_CLOSE, /* } */
	TOKEN_SQUARE_OPEN, /* [ */
	TOKEN_SQUARE_CLOSE, /* ] */
	TOKEN_STRING_QUOTE,  /* " */
	TOKEN_CHAR_QUOTE,   /* ' */

	TOKEN_COMMA, /* , */
	TOKEN_SEMICOLON, /* ; */
	
	TOKEN_OPERATOR,
	
	TOKEN_ENDL /* \n */
};

struct token {
	enum token_type type;
	union {
		str_t v_string;
		/* holds number of spaces/tabs */
		long v_whitespace;
		enum operator v_operator;
		long is_some;
	} content;
};

struct token_vec {
	struct token *ptr;
	unsigned long len;
	unsigned long capacity;
};

void print_operator(enum operator* operator);
void print_token(struct token* token);

struct token_vec tokenizer(char* strslice, unsigned long len);

struct token token_vec_pop(struct token_vec* self);
int token_vec_push(struct token_vec* self, struct token token);
int token_vec_reserve(struct token_vec* self, unsigned long to_reserve);
void token_vec_free(struct token_vec* self);

#endif
