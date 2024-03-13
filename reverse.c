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
void checkFile(char *file1, char *file2) {
    struct stat file1_stat, file2_stat;
    // Obtener información del primer archivo
    if (stat(file1, &file1_stat) == -1) {
        perror("Error obteniendo la info del primer archivo");
        exit(EXIT_FAILURE);
    }
    // Obtener información del segundo archivo
    if (stat(file2, &file2_stat) == -1) {
        perror("Error obteniendo la info del segundo archivo");
        exit(EXIT_FAILURE);
    }
    // Comparar
    if (file1_stat.st_dev == file2_stat.st_dev && file1_stat.st_ino == file2_stat.st_ino) {
        fprintf(stderr, "Los archivos deben ser diferentes\n");
        exit(EXIT_FAILURE);
    } 
}
void reverseLines(char lines[][MAX_LINE_LENGTH],int numLines) {
    // Imprimir lineas al revés 
    for (int x = numLines - 1; x >= 0; x--) {
        printf("%s", lines[x]);
    }
}
void readAndPrintLines() {
    char text[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int lineCount = 0;

    // Leer líneas desde la entrada estándar
    while (fgets(text[lineCount], MAX_LINE_LENGTH, stdin) != NULL) {
        lineCount++;
    }

    // Imprimir las líneas en orden inverso
    printReversedLines(text, lineCount);
}
void readLinesFromFileAndPrint(FILE *file) {
    char line[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int numLines = 0;

    // Leer líneas del archivo
    while (fgets(line[numLines], MAX_LINE_LENGTH, file) != NULL) {
        numLines++;
    }

    // Imprimir líneas en orden inverso
    for (int i = numLines - 1; i >= 0; i--) {
        printf("%s", line[i]);
    }

    fclose(file);
}