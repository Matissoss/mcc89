/* mcc89 - src/mcc89.h 
 * made by matyz
 * licensed under MPL 2.0
 */
#include "mcc89.h"
#include "tokenizer.h"
#include "lexer.h"

void start_processing(char *raw_file, unsigned long len) {    
    struct token_vec tokens;
    int i;
    tokens = tokenizer(raw_file, len);
    for (i = 0; i < tokens.len; i++) {
        token_print(&tokens.ptr[i]);
        if (i == tokens.len - 1) printf("\n");
        else printf(", ");
    }
    token_vec_free(&tokens);
    return;
}
