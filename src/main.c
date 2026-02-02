/*
 * mcc89 - src/main.c
 * ------------------
 * made by matyz
 * licensed under MPL 2.0
 */

#include "../include/mcli.h"

#include <stdio.h>

int main(int argv, char **argc) {
    /* ARGUMENT PARSING */
    struct argdef output = argdef_short('o', 1);
    struct argdef input = argdef_value();
    struct argdef help = argdef_full('h', "help", 0);
    struct argdef version = argdef_full('v', "version", 0);
    struct argdef* argtable[4];
    struct mcli_errbuf errbuf;
    argtable[0] = &output;
    argtable[1] = &input;
    argtable[2] = &help;
    argtable[3] = &version;
    
    errbuf = parse_args(argtable, 4, argv, argc);

    if (errbuf.len) {
        mcli_errbuf_print(&errbuf, stderr);
        return 1;
    }

    if (input.value.str) printf("INPUT: %s\n", input.value.str);
    if (output.value.str) printf("OUTPUT: %s\n", output.value.str);
    if (help.value.found) printf("HELP: %u\n", help.value.found);
    if (version.value.found) printf("VERSION: %u\n", version.value.found);
    mcli_errbuf_free(&errbuf);
    return 0;
}
