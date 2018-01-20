/* === INTROPROG ABGABE ===
 * Blatt 7, Aufgabe 1
 * Tutorium: txx
 * Gruppe: gxx
 * Gruppenmitglieder:
 *  - Max Mustermann
 *  - Rainer Testfall
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"


void merge(int* array, int first, int middle, int last)
{
	int *mrgarray = (int*)malloc((last - first + 2) * sizeof(int));
	int k = first;
	int m = middle + 1;
	int i = 1;
	int j = 1;
	while(k <= middle && m <= last) 
	{
		if(array[k] <= array[m]) 
		{
			*(mrgarray + i) = array[k];
			k++; 
		}
		else {
			*(mrgarray + i) = array[m];
			m++; 
		}
		i++; 
	}
	while(k <= middle) 
	{
		*(mrgarray + i) = array[k];
		k++;
		i++; 
	}

	while(m <= last) 
	{
		*(mrgarray + i) = array[m];
		m++;
		i++; 
	}
	while( j < i) 
	{
		array[first + j - 1] = *(mrgarray + j);
		j++; 
	}
	free(mrgarray);
}

void merge_sort(int* array, int first, int last)
{
	int q;
	if(first < last) 
	{
		q = (first + last)/2;
		merge_sort(array, first, q);
		merge_sort(array, q + 1, last);
		merge(array, first, q, last); 
	}
}

int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];

    int size = atof(argv[1]);
    int *array = (int*)malloc(size * sizeof(int));
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    merge_sort(array, 0, len - 1);

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);
    return 0;
}
