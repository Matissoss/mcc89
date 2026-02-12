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
    token.type = TOKEN_OPERATOR;
    token.content.v_operator = OP_NONE;
    if (len == 1) {
        switch (strslice[0]) {
            case '=':
                token.content.v_operator = OP_ASSIGN;
                break;
            case '<':
                token.content.v_operator = OP_LT;
                break;
            case '>':
                token.content.v_operator = OP_GT;
                break;
            case '^':
                token.content.v_operator = OP_XOR;
                break;
            case '+':
                token.content.v_operator = OP_ADD;
                break;
            case '-':
                token.content.v_operator = OP_SUB;
                break;
            case '*':
                token.content.v_operator = OP_MUL;
                break;
            case '/':
                token.content.v_operator = OP_DIV;
                break;
            case '%':
                token.content.v_operator = OP_MOD;
                break;
            case '&':
                token.content.v_operator = OP_AND;
                break;
            case '|':
                token.content.v_operator = OP_OR;
                break;
            case '!':
                token.content.v_operator = OP_NEG;
                break;
            case '.':
                token.content.v_operator = OP_DOT;
                break;
            case '?':
                token.content.v_operator = OP_QM;
                break;
            case ':':
                token.content.v_operator = OP_COLON;
                break;
            default:
                token.content.v_operator = OP_NONE;
                break;
        }
    } else if (len == 2) {
        switch (strslice[0]) {
            case '=':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_EQ;
                } else {
                    token.content.v_operator = OP_NONE;
                } 
                break;
            case '<':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_LTE;
                } else if (strslice[1] == '<') {
                    token.content.v_operator = OP_LSH;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '>':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_GTE;
                } else if (strslice[1] == '>') {
                    token.content.v_operator = OP_RSH;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '^':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_XORASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '+':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_ADDASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '-':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_SUBASSIGN;
                } else if (strslice[1] == '>') {
                    token.content.v_operator = OP_ARROW;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '*':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_MULASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '/':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_DIVASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '%':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_MODASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '&':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_ANDASSIGN;
                } else if (strslice[1] == '&') {
                    token.content.v_operator = OP_CMP_AND;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '|':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_ORASSIGN;
                } else if (strslice[1] == '&') {
                    token.content.v_operator = OP_CMP_OR;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '!':
                if (strslice[1] == '=') {
                    token.content.v_operator = OP_NEGASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            default:
                token.content.v_operator = OP_NONE;
                break;
        }
    } else if (len == 3) {
        if (strslice[0] == '<' && strslice[1] == '<' && strslice[2] == '=') {
            token.content.v_operator = OP_LSHASSIGN;
        } else if (strslice[0] == '>' && strslice[1] == '>' && strslice[2] == '=') {
            token.content.v_operator = OP_RSHASSIGN;
        } else {
            token.content.v_operator = OP_NONE;
        }
    } else {
        token.content.v_operator = OP_NONE;
    }
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

void operator_print(enum operator* operator) {
    if (!operator) return;
    switch (*operator) {
        case OP_NONE: break;
        case OP_ARROW: printf("->"); break;
        case OP_ASSIGN: printf("="); break;
        case OP_ADD: printf("+"); break;
        case OP_SUB: printf("-"); break;
        case OP_MUL: printf("*"); break;
        case OP_DIV: printf("/"); break;
        case OP_MOD: printf("%%"); break;
        case OP_AND: printf("&"); break;
        case OP_OR : printf("|"); break;
        case OP_XOR: printf("^"); break;
        case OP_NEG: printf("!"); break;
        case OP_LSH: printf("<<"); break;
        case OP_RSH: printf(">>"); break;
        case OP_ADDASSIGN: printf("+="); break;
        case OP_SUBASSIGN: printf("-="); break;
        case OP_MULASSIGN: printf("*="); break;
        case OP_DIVASSIGN: printf("/="); break;
        case OP_MODASSIGN: printf("%%="); break;
        case OP_ANDASSIGN: printf("&="); break;
        case OP_ORASSIGN: printf("|="); break;
        case OP_XORASSIGN: printf("^="); break;
        case OP_LSHASSIGN: printf("<<="); break;
        case OP_RSHASSIGN: printf(">>="); break;
        
        case OP_LT: printf("<"); break;
        case OP_GT: printf(">"); break;
        case OP_EQ: printf("=="); break;
        case OP_NEGASSIGN: printf("!="); break;
        case OP_GTE: printf(">="); break;
        case OP_LTE: printf("<="); break;
        case OP_CMP_AND: printf("&&"); break;
        case OP_CMP_OR: printf("||"); break;
        case OP_DOT: printf("."); break;
        case OP_QM: printf("?"); break;
        case OP_COLON: printf(","); break;
    }
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
