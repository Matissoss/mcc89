/* mcc89 - src/tokenizer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum current_type {
    CT_NONE,
    /* a-z, A-Z, 0-9 */
    CT_ALNUM,
    /* Whitespace ' ' */
    CT_WS,
    /* like '=', '.', '-', '>' */
    CT_OTHER
};

static struct token operator(char* strslice, unsigned long len) {
    struct token token;
    str_t s;
    s.ptr = strslice;
    s.len = len;
    token.type = TOKEN_OPERATOR;
    token.content.v_operator = operator_from_str(s);
    return token;
}

struct token_vec tokenizer(char* file, unsigned long len) {
    struct token_vec token_vec = {0};
    struct token token = {0};
    unsigned long i, j, strs = 0;
    enum current_type current_type = CT_NONE;
    for (i = 0; i < len; i++) {
        if (file[i] == '\n') {
            if (i == strs) {
                token.type = TOKEN_ENDL;
                token_vec_push(&token_vec, token);
            } else {
                if (current_type == CT_ALNUM) {
                    token.type = TOKEN_STRING;
                    token.content.v_string.ptr = file + strs;
                    token.content.v_string.len = i - strs;
                    token_vec_push(&token_vec, token);
                    strs = i + 1;
                } else if (current_type == CT_OTHER) {
                    for (j = strs; j < i; j++) {
                        token = operator(file + j, i - j);
                        if (token.content.v_operator == OP_NONE) {
                            switch (file[j]) {
                                case '{':
                                    token.type = TOKEN_BRACE_OPEN;
                                    break;
                                case '}':
                                    token.type = TOKEN_BRACE_CLOSE;
                                    break;
                                case '[':
                                    token.type = TOKEN_SQUARE_OPEN;
                                    break;
                                case ']':
                                    token.type = TOKEN_SQUARE_CLOSE;
                                    break;
                                case '(':
                                    token.type = TOKEN_PARAM_OPEN;
                                    break;
                                case ')':
                                    token.type = TOKEN_PARAM_CLOSE;
                                    break;
                                case '"':
                                    token.type = TOKEN_STRING_QUOTE;
                                    break;
                                case '\'':
                                    token.type = TOKEN_CHAR_QUOTE;
                                    break;
                                case ',':
                                    token.type = TOKEN_COMMA;
                                    break;
                                case ';':
                                    token.type = TOKEN_SEMICOLON;
                                    break;
                            }
                            if (token.type != TOKEN_OPERATOR) token_vec_push(&token_vec, token);
                        } else {
                            token_vec_push(&token_vec, token);
                        }
                    }
                    strs = i + 1;
                } else if (current_type == CT_WS) {
                    token.type = TOKEN_WHITESPACE;
                    token.content.v_whitespace = i - strs;
                    token_vec_push(&token_vec, token);
                    strs = i + 1;
                }
                token.type = TOKEN_ENDL;
                token_vec_push(&token_vec, token);
                current_type = CT_NONE;
            }
        } else if (isalnum(file[i])) {
            if (i == strs) {
                current_type = CT_ALNUM;
                continue;
            }
            if (current_type == CT_WS) {
                token.type = TOKEN_WHITESPACE;
                token.content.v_whitespace = i - strs;
                token_vec_push(&token_vec, token);
                strs = i;
            } else if (current_type == CT_OTHER) {
                for (j = strs; j < i; j++) {
                    token = operator(file + j, i - j);
                    if (token.content.v_operator == OP_NONE) {
                        switch (file[j]) {
                            case '{':
                                token.type = TOKEN_BRACE_OPEN;
                                break;
                            case '}':
                                token.type = TOKEN_BRACE_CLOSE;
                                break;
                            case '[':
                                token.type = TOKEN_SQUARE_OPEN;
                                break;
                            case ']':
                                token.type = TOKEN_SQUARE_CLOSE;
                                break;
                            case '(':
                                token.type = TOKEN_PARAM_OPEN;
                                break;
                            case ')':
                                token.type = TOKEN_PARAM_CLOSE;
                                break;
                            case '"':
                                token.type = TOKEN_STRING_QUOTE;
                                break;
                            case '\'':
                                token.type = TOKEN_CHAR_QUOTE;
                                break;
                            case ',':
                                token.type = TOKEN_COMMA;
                                break;
                            case ';':
                                token.type = TOKEN_SEMICOLON;
                                break;
                        }
                        if (token.type != TOKEN_OPERATOR) token_vec_push(&token_vec, token);
                    } else {
                        token_vec_push(&token_vec, token);
                    }
                }
                strs = i;
            }
            current_type = CT_ALNUM;
        } else if (isspace(file[i])) {
            if (strs == i) {
                current_type = CT_WS;
                continue;
            }

            if (current_type == CT_ALNUM) {
                token.type = TOKEN_STRING;
                token.content.v_string.ptr = file + strs;
                token.content.v_string.len = i - strs;
                token_vec_push(&token_vec, token);
                strs = i;
            } else if (current_type == CT_OTHER) {
                for (j = strs; j < i; j++) {
                    token = operator(file + j, i - j);
                    if (token.content.v_operator == OP_NONE) {
                        switch (file[j]) {
                            case '{':
                                token.type = TOKEN_BRACE_OPEN;
                                break;
                            case '}':
                                token.type = TOKEN_BRACE_CLOSE;
                                break;
                            case '[':
                                token.type = TOKEN_SQUARE_OPEN;
                                break;
                            case ']':
                                token.type = TOKEN_SQUARE_CLOSE;
                                break;
                            case '(':
                                token.type = TOKEN_PARAM_OPEN;
                                break;
                            case ')':
                                token.type = TOKEN_PARAM_CLOSE;
                                break;
                            case '"':
                                token.type = TOKEN_STRING_QUOTE;
                                break;
                            case '\'':
                                token.type = TOKEN_CHAR_QUOTE;
                                break;
                            case ',':
                                token.type = TOKEN_COMMA;
                                break;
                            case ';':
                                token.type = TOKEN_SEMICOLON;
                                break;
                        }
                        if (token.type != TOKEN_OPERATOR) token_vec_push(&token_vec, token);
                    } else {
                        token_vec_push(&token_vec, token);
                    }
                }
                strs = i;
            }
            current_type = CT_WS;
        } else {
            if (strs == i) {
                current_type = CT_OTHER;
                continue;
            }
            if (current_type == CT_ALNUM) {
                token.type = TOKEN_STRING;
                token.content.v_string.ptr = file + strs;
                token.content.v_string.len = i - strs;
                token_vec_push(&token_vec, token);
                strs = i;
            } else if (current_type == CT_WS) {
                token.type = TOKEN_WHITESPACE;
                token.content.v_whitespace = i - strs;
                token_vec_push(&token_vec, token);
                strs = i;
            }
            current_type = CT_OTHER;
        }
    }
    return token_vec;
}

unsigned long token_as_str_len(struct token *token) {
    if (!token) {
        return 0;
    }
    switch (token->type) {
        case TOKEN_STRING_QUOTE:
        case TOKEN_CHAR_QUOTE:
        case TOKEN_SEMICOLON:
        case TOKEN_COMMA:
        case TOKEN_PARAM_OPEN:
        case TOKEN_PARAM_CLOSE:
        case TOKEN_BRACE_OPEN:
        case TOKEN_BRACE_CLOSE:
        case TOKEN_SQUARE_OPEN:
        case TOKEN_ENDL:
        case TOKEN_SQUARE_CLOSE:
            return 1;
        case TOKEN_STRING:
            return token->content.v_string.len;
        case TOKEN_WHITESPACE:
            return token->content.v_whitespace;
        case TOKEN_OPERATOR:
            return operator_as_str_len(token->content.v_operator);
    }
    return 0;
}

void token_print(struct token* token) {
    if (!token) return;
    switch (token->type) {
        case TOKEN_STRING:
            printf("String(\"");
            str_t_print(&token->content.v_string);
            printf("\")");
            break;
        case TOKEN_WHITESPACE:
            printf("Whitespace(%ld)", token->content.v_whitespace);
            break;
        case TOKEN_PARAM_OPEN:
            printf("ParamOpen");
            break;
        case TOKEN_PARAM_CLOSE:
            printf("ParamClose");
            break;
        case TOKEN_SQUARE_OPEN:
            printf("SquareOpen");
            break;
        case TOKEN_SQUARE_CLOSE:
            printf("SquareClose");
            break;
        case TOKEN_BRACE_OPEN:
            printf("BraceOpen");
            break;
        case TOKEN_BRACE_CLOSE:
            printf("BraceClose");
            break;
        case TOKEN_STRING_QUOTE:
            printf("StringQuote");
            break;
        case TOKEN_CHAR_QUOTE:
            printf("CharQuote");
            break;
        case TOKEN_COMMA:
            printf("Comma");
            break;
        case TOKEN_SEMICOLON:
            printf("Semicolon");
            break;
        case TOKEN_ENDL:
            printf("Endline");
            break;
        case TOKEN_OPERATOR:
            printf("Operator(");
            operator_print(&token->content.v_operator);
            printf(")");
            break;
    }
}

/* token_vec impls */
int token_vec_reserve(struct token_vec* self, unsigned long to_reserve) {
    if (self) {
        self->capacity += to_reserve;
        self->ptr = realloc(self->ptr, self->capacity * sizeof(struct token));
        return self->ptr != NULL ? 0 : 1;
    } else {
        return 1;
    }
}

struct token token_vec_pop(struct token_vec* self) {
    struct token ret = {0};
    if (self && self->len != 0) {
        ret = self->ptr[self->len - 1];
        self->len--;
    }
    return ret;
}
int token_vec_push(struct token_vec* self, struct token token) {
    if (self) {
        if (self->len >= self->capacity) {
            self->capacity++;
            self->ptr = realloc(self->ptr, self->capacity * sizeof(struct token));
            if (!self->ptr) {
                return 1;
            }
        }
        memcpy((void*)&self->ptr[self->len], (void*)&token, sizeof(struct token));
        self->len++;
        return 0;
    } else {
        return 1;
    }
}

void token_vec_free(struct token_vec* self) {
    if (self && self->ptr) {
        free(self->ptr);
    }
}
