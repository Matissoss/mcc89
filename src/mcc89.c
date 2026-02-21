/* mcc89 - src/mcc89.h 
 * made by matyz
 * licensed under MPL 2.0
 */
#include "mcc89.h"
#include "tokenizer.h"
#include "lexer.h"

void start_processing(char *raw_file, unsigned long len) {    
    struct token_vec tokens;
    struct lexer_token_vec ltokens;
    int i;
    str_t raw_file_str;
    raw_file_str.ptr = raw_file;
    raw_file_str.len = len;
    printf("== TOKENIZER OUTPUT ==\n\n");
    tokens = tokenizer(raw_file, len);
    for (i = 0; i < tokens.len; i++) {
        token_print(&tokens.ptr[i]);
        if (i == tokens.len - 1) printf("\n");
        else printf(", ");
    }

    printf("\n== LEXER OUTPUT ==\n\n");

    ltokens = lexer(raw_file_str, &tokens);
    for (i = 0; i < ltokens.len; i++) {
        lexer_token_print(&ltokens.ptr[i]);
        if (i == tokens.len - 1) printf("\n");
        else printf(", ");
    }
    printf("\n");
    lexer_token_vec_free(&ltokens);
    token_vec_free(&tokens);
    return;
}
