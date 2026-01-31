/*
 * mcc89 - src/main.c
 * ------------------
 * made by matyz
 * licensed under MPL 2.0
 */

#include <stdio.h>
#include <string.h>

int main(int argv, char **argc) {
        char *path = NULL;
        int i;
        for (i = 1; i < argv; i++) path = argc[i]; 
        if (!path) {
                printf("There was no argument provided!\n");
                return 1;
        } else {
                printf("%s\n", path);
        }
        return 0;
}
