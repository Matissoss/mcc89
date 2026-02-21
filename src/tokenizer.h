/* mcc89 - src/tokenizer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "str.h"
#include "operator.h"

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

    /* \\ */
    TOKEN_BACKSLASH,

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

void token_print(struct token* token);

struct token_vec tokenizer(char* strslice, unsigned long len);
unsigned long token_as_str_len(struct token* token);

struct token token_vec_pop(struct token_vec* self);
int token_vec_push(struct token_vec* self, struct token token);
int token_vec_reserve(struct token_vec* self, unsigned long to_reserve);
void token_vec_free(struct token_vec* self);

#endif
