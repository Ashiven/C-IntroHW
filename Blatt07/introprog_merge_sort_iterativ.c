/* === INTROPROG ABGABE ===
 * Blatt 7, Aufgabe 2
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
	int step = 1;
	int left;
	int middle = 0;
	int right = 0;
	while(step <= last) 
	{
		left = 0;
		while(left <= last - step) 
		{
			middle = left + step - 1;
			middle = ((middle < last) ? middle : last);
			right = left + 2 * step - 1;
			right = ((right < last) ? right : last);
			merge(array, left, middle, right);
			left = left + 2 * step;
		}
		step = step * 2;
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
