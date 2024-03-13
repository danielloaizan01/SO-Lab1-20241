#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1000

void tooManyArguments() {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
}

void openFile(char *file_name, FILE **file) {
    *file = fopen(file_name, "r");
    // Input file does not exist (Test 2) and Cannot open file (Test 3)
    if (*file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", file_name);
        exit(1);
    }
}

