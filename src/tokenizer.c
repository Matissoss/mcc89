/* mcc89 - src/tokenizer.h
 * made by matyz
 * licensed under MPL 2.0
 */
#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum current_type {
    CT_NONE,
    /* a, Z, 0, 9 */
    CT_ALNUM,
    /* like ' ' */
    CT_WS,
    /* like '=', '.', '-', '>' */
    CT_OTHER
};

static struct token operator(char* file, unsigned long len) {
    struct token token = {0};
    token.type = TOKEN_OPERATOR;
    if (len == 1) {
        switch (file[0]) {
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
        switch (file[0]) {
            case '=':
                if (file[1] == '=') {
                    token.content.v_operator = OP_EQ;
                } else {
                    token.content.v_operator = OP_NONE;
                } 
                break;
            case '<':
                if (file[1] == '=') {
                    token.content.v_operator = OP_LTE;
                } else if (file[1] == '<') {
                    token.content.v_operator = OP_LSH;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '>':
                if (file[1] == '=') {
                    token.content.v_operator = OP_GTE;
                } else if (file[1] == '>') {
                    token.content.v_operator = OP_RSH;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '^':
                if (file[1] == '=') {
                    token.content.v_operator = OP_XORASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '+':
                if (file[1] == '=') {
                    token.content.v_operator = OP_ADDASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '-':
                if (file[1] == '=') {
                    token.content.v_operator = OP_SUBASSIGN;
                } else if (file[1] == '>') {
                    token.content.v_operator = OP_ARROW;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '*':
                if (file[1] == '=') {
                    token.content.v_operator = OP_MULASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '/':
                if (file[1] == '=') {
                    token.content.v_operator = OP_DIVASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '%':
                if (file[1] == '=') {
                    token.content.v_operator = OP_MODASSIGN;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '&':
                if (file[1] == '=') {
                    token.content.v_operator = OP_ANDASSIGN;
                } else if (file[1] == '&') {
                    token.content.v_operator = OP_CMP_AND;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '|':
                if (file[1] == '=') {
                    token.content.v_operator = OP_ORASSIGN;
                } else if (file[1] == '&') {
                    token.content.v_operator = OP_CMP_OR;
                } else {
                    token.content.v_operator = OP_NONE;
                }
                break;
            case '!':
                if (file[1] == '=') {
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
        if (file[0] == '<' && file[1] == '<' && file[2] == '=') {
            token.content.v_operator = OP_LSHASSIGN;
        } else if (file[0] == '>' && file[1] == '>' && file[2] == '=') {
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
    struct token to_push = {0};
    int i;
    unsigned long strs = 0, stre = 0;
    enum current_type current_type = CT_NONE;
    for (i = 0; i < len; i++) {
        if (file[i] == '\n') {
            if (strs != stre) {
                switch (current_type) {
                    case CT_ALNUM:
                        if (stre != strs) {
                            to_push.type = TOKEN_STRING;
                            to_push.content.v_string.ptr = file + strs;
                            to_push.content.v_string.len = stre - strs;
                            token_vec_push(&token_vec, to_push);
                        }
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    case CT_WS:
                        to_push.type = TOKEN_WHITESPACE;
                        to_push.content.v_whitespace = stre - strs;
                        token_vec_push(&token_vec, to_push);
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    case CT_OTHER:
                        to_push = operator(file, strs - stre);
                        if (to_push.content.v_operator == OP_NONE) {
                            if (file[strs] == '"') {
                                to_push.type = TOKEN_STRING_QUOTE;
                            } else if (file[strs] == '\'') {
                                to_push.type = TOKEN_CHAR_QUOTE;
                            } else if (file[strs] == '(') {
                                to_push.type = TOKEN_PARAM_OPEN;
                            } else if (file[strs] == ')') {
                                to_push.type = TOKEN_PARAM_CLOSE;
                            } else if (file[strs] == '[') {
                                to_push.type = TOKEN_SQUARE_OPEN;
                            } else if (file[strs] == ']') {
                                to_push.type = TOKEN_SQUARE_CLOSE;
                            } else if (file[strs] == '{') {
                                to_push.type = TOKEN_BRACE_OPEN;
                            } else if (file[strs] == '}') {
                                to_push.type = TOKEN_BRACE_CLOSE;
                            }
                        }
                        token_vec_push(&token_vec, to_push);
                        stre = i;
                        strs = i;
                        break;
                    default:
                        stre++;
                        break;
                }
                current_type = CT_NONE;
            }

        } else if (isalnum(file[i])) {
            if (current_type == CT_ALNUM) {
                stre++;
            } else {
                switch (current_type) {
                    case CT_OTHER:
                        to_push = operator(file, strs - stre);
                        if (to_push.content.v_operator == OP_NONE) {
                            if (file[strs] == '"') {
                                to_push.type = TOKEN_STRING_QUOTE;
                            } else if (file[strs] == '\'') {
                                to_push.type = TOKEN_CHAR_QUOTE;
                            } else if (file[strs] == '(') {
                                to_push.type = TOKEN_PARAM_OPEN;
                            } else if (file[strs] == ')') {
                                to_push.type = TOKEN_PARAM_CLOSE;
                            } else if (file[strs] == '[') {
                                to_push.type = TOKEN_SQUARE_OPEN;
                            } else if (file[strs] == ']') {
                                to_push.type = TOKEN_SQUARE_CLOSE;
                            } else if (file[strs] == '{') {
                                to_push.type = TOKEN_BRACE_OPEN;
                            } else if (file[strs] == '}') {
                                to_push.type = TOKEN_BRACE_CLOSE;
                            }
                        }
                        token_vec_push(&token_vec, to_push);
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    case CT_WS:
                        to_push.type = TOKEN_WHITESPACE;
                        to_push.content.v_whitespace = stre - strs;
                        token_vec_push(&token_vec, to_push);
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    default:
                        stre++;
                        break;
                }
                current_type = CT_ALNUM;
            }
        } else if (isspace(file[i])) {
            if (current_type == CT_WS) {
                stre++;
            } else {
                switch (current_type) {
                    case CT_OTHER:
                        to_push = operator(file, strs - stre);
                        if (to_push.content.v_operator == OP_NONE) {
                            if (file[strs] == '"') {
                                to_push.type = TOKEN_STRING_QUOTE;
                            } else if (file[strs] == '\'') {
                                to_push.type = TOKEN_CHAR_QUOTE;
                            } else if (file[strs] == '(') {
                                to_push.type = TOKEN_PARAM_OPEN;
                            } else if (file[strs] == ')') {
                                to_push.type = TOKEN_PARAM_CLOSE;
                            } else if (file[strs] == '[') {
                                to_push.type = TOKEN_SQUARE_OPEN;
                            } else if (file[strs] == ']') {
                                to_push.type = TOKEN_SQUARE_CLOSE;
                            } else if (file[strs] == '{') {
                                to_push.type = TOKEN_BRACE_OPEN;
                            } else if (file[strs] == '}') {
                                to_push.type = TOKEN_BRACE_CLOSE;
                            }
                        }
                        token_vec_push(&token_vec, to_push);
                        stre = i;
                        strs = i;
                        break;
                    case CT_ALNUM:
                        if (stre != strs) {
                            to_push.type = TOKEN_STRING;
                            to_push.content.v_string.ptr = file + strs;
                            to_push.content.v_string.len = stre - strs;
                            token_vec_push(&token_vec, to_push);
                        }
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    default:
                        stre++;
                        break;
                }
                current_type = CT_WS;
            }
        } else {
            if (current_type == CT_OTHER) {
                stre++;
            } else {
                switch (current_type) {
                    case CT_ALNUM:
                        if (stre != strs) {
                            to_push.type = TOKEN_STRING;
                            to_push.content.v_string.ptr = file + strs;
                            to_push.content.v_string.len = stre - strs;
                            token_vec_push(&token_vec, to_push);
                        }
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    case CT_WS:
                        to_push.type = TOKEN_WHITESPACE;
                        to_push.content.v_whitespace = stre - strs;
                        token_vec_push(&token_vec, to_push);
                        stre = i + 1;
                        strs = i + 1;
                        break;
                    default:
                        stre++;
                        break;
                }
                current_type = CT_OTHER;
            }
        }
    }
    return token_vec;
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
            self->capacity <<= 1;
            self->ptr = realloc(self->ptr, self->capacity * sizeof(struct token));
            if (!self->ptr) {
                return 1;
            }
        }
        memcpy((void*)&token, (void*)&self->ptr[self->len++], sizeof(struct token));
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
