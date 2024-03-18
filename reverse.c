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

void hardlinkTest(char *argv[]) {
    struct stat stat_in, stat_out;

    // Obtener información del archivo de entrada
    if (stat(argv[1], &stat_in) == -1) {
        fprintf(stderr, "Error trying to get inputfile info'\n");
        exit(1);
    }

    // Obtener información del archivo de salida
    if (stat(argv[2], &stat_out) == -1) {
        fprintf(stderr, "Error trying to get outputfile info'\n");
        exit(1);
    }

    // Comparar números de dispositivo e inodo
    if (stat_in.st_dev == stat_out.st_dev && stat_in.st_ino == stat_out.st_ino) {
        fprintf(stderr, "reverse: input and output file must differ\n");        
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
    reverseLines(text, lineCount);
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

void reverseAndWriteToFile(FILE **input, FILE **output) {
    char text[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int lineCount = 0;

    // Leer líneas del archivo de entrada
    while (fgets(text[lineCount], MAX_LINE_LENGTH, *input) != NULL) {
        lineCount++;
    }

    // Escribir líneas al archivo de salida en orden inverso
    for (int i = lineCount - 1; i >= 0; i--) {
        fputs(text[i], *output);
    }

    fclose(*input);
    fclose(*output);
}

int main(int argc, char *argv[]) {
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    switch (argc) {
        case 1:
            // No se proporcionaron argumentos de línea de comandos (Test 2)
            readAndPrintLines();
            break;
        case 2:
            // Se proporcionó solo un argumento de línea de comandos (Test 3)
            openFile(argv[1], &inputFile);
            readLinesFromFileAndPrint(inputFile);
            break;
        case 3:
            // El archivo de entrada tiene el mismo nombre que el archivo de salida (Test 4)
            if (strcmp(argv[1], argv[2]) == 0) {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(EXIT_FAILURE);
            } else {
                openFile(argv[1], &inputFile);
                openFile(argv[2], &outputFile);

		// Se proporcionaron dos argumentos de línea de comandos (Test 5)
		hardlinkTest(argv);

                // Verificar si el archivo de entrada y el archivo de salida son el mismo archivo (Test 6)
                checkFile(argv[1], argv[2]);

                // Revertir el archivo y escribirlo (Test 7)
                reverseAndWriteToFile(&inputFile, &outputFile);
            }
            break;
        default:
            // Demasiados argumentos de línea de comandos (Test 1)
            tooManyArguments();            
    }

    return 0;
}