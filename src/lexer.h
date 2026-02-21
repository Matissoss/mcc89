/* mcc89 - src/lexer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#ifndef LEXER_H
#define LEXER_H

#include "str.h"
#include "tokenizer.h"
#include "number.h"

enum keyword {
    K_NONE,
	K_IF,
	K_WHILE,
	K_FOR,
	K_ELSE,
	K_RETURN
};

enum lexer_token_type {
	/* SMALL TOKENS*/
	/* if, for, while, do, else, return */
	LT_KEYWORD,
	/* "these", "are", "strings" */
	LT_STRING,
	/* 'c', 'h', 'a', 'r' */
	LT_CHAR,
	/* 256, 0xFF, 0o42, 0b1011 */
	LT_NUMBER,
	/* these are labels */
	LT_LABEL,
	
	LT_COMMA,
	LT_OPERATOR,	
	
	/* COLLECTION TOKENS */
	LT_PARAM_CLOSURE,
	LT_BRACKET_CLOSURE,
	LT_SQUARE_CLOSURE,
	LT_EXPRESSION
};

struct lexer_token_vec {
	struct lexer_token* ptr;
	unsigned long len;
	unsigned long capacity;
};

struct lexer_token {
	enum lexer_token_type type;
	union {
		struct lexer_token_vec v_collection;
		struct lexer_token_vec v_sq_closure;
		struct lexer_token_vec v_pa_closure;
		struct lexer_token_vec v_bk_closure;
		
		enum operator v_operator;
		struct number v_number;
		str_t v_label;
		str_t v_string;
        char v_char;
		enum keyword v_keyword;
		
		long is_some;
	} content;
};

enum keyword keyword_from_str(str_t str);

struct lexer_token_vec lexer(str_t raw_file, struct token_vec *tokens);
int lexer_token_print(struct lexer_token* self);

int lexer_token_free(struct lexer_token* self);
int lexer_token_vec_free(struct lexer_token_vec* self);
int lexer_token_vec_push(struct lexer_token_vec* self, struct lexer_token* token);

#endif
