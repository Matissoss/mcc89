/* mcc89 - src/lexer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#ifndef LEXER_H
#define LEXER_H

#include "str.h"
#include "tokenizer.h"

enum keyword {
    K_NONE,
	K_IF,
	K_WHILE,
	K_FOR,
	K_ELSE,
	K_RETURN
};

enum number_type {
	N_F64,
	N_F32,
	
	N_U64,
	N_U32,
	N_U16,
	N_U8,
	
	N_I64,
	N_I32,
	N_I16,
	I_I8
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
		enum keyword v_keyword;
		
		long is_some;
	} content;
};

enum keyword keyword_from_str(str_t str);

struct lexer_token_vec lexer(str_t raw_file, struct token_vec *tokens);

int lexer_token_free(struct lexer_token* self);
int lexer_token_vec_free(struct lexer_token_vec* self);
int lexer_token_vec_push(struct lexer_token_vec* self, struct lexer_token* token);

#endif
