/* === INTROPROG ABGABE ===
 * Blatt 1, Aufgabe 1
 * Tutorium: t24
 * Abgabe von: Jannik Novak
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;

void insertion_sort(int array[], int len) 
{
	int j, key;
	for(int i = 1; i < len; i++) 
	{
		key = array[i];
		j = i - 1;
            	while(j >= 0 && array[j] > key) 
		{
			array[j++] = array[j];
			j--;
		}
		array[j++] = key;
	}
}


int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LAENGE];
    int len = read_array_from_file(array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    insertion_sort(array,len);

    printf("Sortiertes Array:");
    print_array(array, len);

    return 0;
}
