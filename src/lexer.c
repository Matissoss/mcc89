/* mcc89 - src/lexer.h
 * made by matyz
 * licensed under MPL 2.0
 */

#include "lexer.h"
#include "number.h"
#include "str.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>

enum lstate {
    LS_NONE,
    LS_STRING,
    LS_CHAR
};

int lexer_token_print(struct lexer_token *self) {
    unsigned long i;
    if (!self) return 1;
    switch (self->type) {
        case LT_LABEL:
            printf("Label(");
            str_t_print(&self->content.v_string);
            printf(")");
            break;
        case LT_NUMBER:
            printf("Number(");
            number_print(self->content.v_number);
            printf(")");
            break;
        case LT_KEYWORD:
            printf("Keyword()");
            break;
        case LT_STRING:
            printf("String(");
            str_t_print(&self->content.v_string);
            printf(")");
            break;
        case LT_CHAR:
            printf("Char('%c')", self->content.v_char);
            break;
        case LT_OPERATOR:
            operator_print(&self->content.v_operator);
            break;
        case LT_COMMA:
            printf("Comma");
            break;
        case LT_EXPRESSION:
            printf("Expression(\n");
            for (i = 0; i < self->content.v_collection.len; i++) {
                lexer_token_print(&self->content.v_collection.ptr[i]);
                if (i == self->content.v_collection.len - 1) printf(", ");
            }
            printf("\n)");
            break;
        case LT_PARAM_CLOSURE:
            printf("ParamClosure(\n");
            for (i = 0; i < self->content.v_collection.len; i++) {
                lexer_token_print(&self->content.v_collection.ptr[i]);
                if (i == self->content.v_collection.len - 1) printf(", ");
            }
            printf("\n)");
            break;
        case LT_BRACKET_CLOSURE:
            printf("BracketClosure(\n");
            for (i = 0; i < self->content.v_collection.len; i++) {
                lexer_token_print(&self->content.v_collection.ptr[i]);
                if (i == self->content.v_collection.len - 1) printf(", ");
            }
            printf("\n)");
            break;
        case LT_SQUARE_CLOSURE:
            printf("SquareClosure(\n");
            for (i = 0; i < self->content.v_collection.len; i++) {
                lexer_token_print(&self->content.v_collection.ptr[i]);
                if (i == self->content.v_collection.len - 1) printf(", ");
            }
            printf("\n)");
            break;
    }
    return 0;
}

enum keyword keyword_from_str(str_t str) {
    switch (str.len) {
        case 2:
            if (str.ptr[0] == 'i' && str.ptr[1] == 'f') {
                return K_IF;
            } else return K_NONE;
            break;
        case 3:
            if (str.ptr[0] == 'f' && str.ptr[1] == 'o' && str.ptr[2] == 'r') {
                return K_FOR;
            } else return K_NONE;
            break;
        case 4:
            if (str.ptr[0] == 'e' && str.ptr[1] == 'l' && str.ptr[2] == 's' && str.ptr[3] == 'e') {
                return K_ELSE;
            } else return K_NONE;
            break;
        case 5:
            if (!strncmp(str.ptr, "while", 5)) {
                return K_WHILE;
            } else return K_NONE;
            break;
        case 6:
            if (!strncmp(str.ptr, "return", 6)) {
                return K_RETURN;
            } else return K_NONE;
            break;
        default: return K_NONE;
    }
}

struct lexer_token_vec lexer(str_t raw_file, struct token_vec *tokens) {
    /* for slicing */
    enum lstate state = LS_NONE;
    /* is '\\' char used */
    unsigned char is_escape = 0;
    struct token* ctoken = NULL;
    struct lexer_token lexer_token = {0};

    unsigned long sstart = 0, send = 0, i = 0;
    /* raw file offsets for "string"s and 'c'hars 
     * rf_offset is for current offset in the file
     */
    unsigned long rf_offset = 0, rf_slice_len = 0;
    struct lexer_token_vec ltoken_vec = {0};

    for (send = 0; send < tokens->len; send++) {
        ctoken = &tokens->ptr[send];
        switch (ctoken->type) {
            /* TODO */
            case TOKEN_BACKSLASH:
                is_escape = 1;
                break;
            case TOKEN_STRING:
                if (state == LS_NONE) {
                    lexer_token.type = LT_LABEL;
                    lexer_token.content.v_label.ptr = raw_file.ptr + rf_offset;
                    lexer_token.content.v_label.len = ctoken->content.v_string.len;
                    lexer_token_vec_push(&ltoken_vec, &lexer_token);
                }
                break;
            case TOKEN_STRING_QUOTE:
                if (is_escape == 1) {
                    is_escape = 0;
                    break;
                }
                if (state == LS_STRING) {
                    lexer_token.type = LT_STRING;
                    rf_slice_len = 1;
                    for (i = sstart + 1; i < send; i++) {
                        rf_slice_len += token_as_str_len(&tokens->ptr[i]);
                    }
                    lexer_token.type = LT_STRING;
                    lexer_token.content.v_string.ptr = raw_file.ptr 
                        + rf_offset 
                        - rf_slice_len 
                        + 1;
                    lexer_token.content.v_string.len = rf_slice_len - 1;
                    lexer_token_vec_push(&ltoken_vec, &lexer_token);
                    state = LS_NONE;
                } else if (state == LS_NONE) {
                    state = LS_STRING;
                    sstart = send;
                }
                break;
            default: break;
        }
        rf_offset += token_as_str_len(ctoken);
    }
    return ltoken_vec;
}

int lexer_token_vec_push(struct lexer_token_vec *self, struct lexer_token *token) {
    if (!self) {
        return 1;
    }
    if (self->len >= self->capacity) {
        self->capacity++;
        if (!(self->ptr = realloc(self->ptr, self->capacity * sizeof(struct lexer_token)))) return 1;
    }
    memcpy(&self->ptr[self->len++], token, sizeof(struct lexer_token));
    return 0;
}


int lexer_token_free(struct lexer_token* self) {
    if (!self) {
        return 1;
    }
    switch (self->type) {
        case LT_SQUARE_CLOSURE:
        case LT_EXPRESSION:
        case LT_PARAM_CLOSURE:
        case LT_BRACKET_CLOSURE:
            return lexer_token_vec_free(&self->content.v_collection);
        default: break;
    }
    return 0;
}

int lexer_token_vec_free(struct lexer_token_vec *self) {
    unsigned long i;
    if (!self){
        return 1;
    }
    for (i = 0; i < self->len; i++) {
        if (lexer_token_free(&self->ptr[i]) == 1) return 1;
    }
    return 0;
}
