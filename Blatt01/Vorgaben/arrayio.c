/*
 * Diese Datei soll nicht verändert werden.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "arrayio.h"

int read_array_from_file(int array[], size_t size, char *filename) {
    FILE *file_pointer = fopen(filename, "r");

    if (file_pointer == NULL){
        perror(filename);
        exit(1);
    }
    int i = 0;

    while(i < size && fscanf(file_pointer, "%d", &array[i]) != EOF){
        i++;
    }
    fclose(file_pointer);
    return i;
}


// Gibt das Array nach dem gewünschten Format aus.
void print_array(int array[], int len) {
    for (int i = 0; i < len ; i++) {
        printf(" %d", array[i]);
    }
    printf("\n");
}
