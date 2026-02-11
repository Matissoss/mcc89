/*
 * mcc89 - src/main.c
 * made by matyz
 * licensed under MPL 2.0
 */

#include "../include/mcli.h"
#include <stdio.h>

#include "mcc89.h"

int main(int argv, char **argc) {
    /* ARGUMENT PARSING */
    struct argdef output = argdef_short('o', 1);
    struct argdef input = argdef_value();
    struct argdef help = argdef_full('h', "help", 0);
    struct argdef version = argdef_full('v', "version", 0);
    struct argdef* argtable[4];
    struct mcli_errbuf errbuf;
    /* INPUT FILE */
    FILE* input_file;
    unsigned long ifile_len;
    char* ifile_content;

    argtable[0] = &output;
    argtable[1] = &input;
    argtable[2] = &help;
    argtable[3] = &version;

    errbuf = parse_args(argtable, 4, argv, argc);

    if (errbuf.len) {
        mcli_errbuf_print(&errbuf, stderr);
        return 1;
    }
    mcli_errbuf_free(&errbuf);

    if (!input.value.str) {
        fprintf(stderr, "error: you didn't provide any input file for compilation\n");
        return 1;
    }

    input_file = fopen(input.value.str, "rb");
    if (!input_file) {
        fprintf(stderr, "error: file you provided as input (\"%s\") could not be opened for reading\n", input.value.str);
        return 1;
    }

    fseek(input_file, 0L, SEEK_END);
    ifile_len = ftell(input_file);
    rewind(input_file);
    ifile_content = (char*)malloc(ifile_len);
    if (!ifile_content) {
        fprintf(stderr, "error: couldn't allocate enough space to read the input file (\"%s\")\n", input.value.str);
        return 1;
    }
    ifile_content[ifile_len-1] = 0;
    if (fread(ifile_content, 1, ifile_len, input_file) != ifile_len) {
        fprintf(stderr, "error: could not read the whole input file (\"%s\")\n", input.value.str);
        return 1;
    }
    start_processing(ifile_content, ifile_len);

    return 0;
}
