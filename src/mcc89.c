/* mcc89 - src/mcc89.h 
 * made by matyz
 * licensed under MPL 2.0
 */
#include "mcc89.h"
#include "tokenizer.h"

void start_processing(char *raw_file, unsigned long len) {    
    struct token_vec tokens;

    tokens = tokenizer(raw_file, len);
    (void)tokens;
    return;
}
