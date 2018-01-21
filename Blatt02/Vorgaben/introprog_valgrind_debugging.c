#include<stdio.h>
#include<stdlib.h>

#include "input_valgrind_debug.h"

/*********************************************************************
*                           W A R N U N G
* 
* Dieser Code dient als Vorlage, wie man ein C Programm nicht schreiben
* sollte und dient nur zu Debug-Zwecken. 
**********************************************************************/

//alloziert ein Integer Array der Größe *size
int* allocate_array(int* size)
{
    int* result = (int*)malloc(sizeof(int) * (*size));
    return result;
}

/*********************************************************************
* Initialisiere das array: Am Index i wird die Zahl i+1 eingetragen
**********************************************************************/
void initialize_array(int array[], int size)
{
    for(int i = 0; i <= size; ++i)
    {
        array[i-1] = i;
    }
}

/*********************************************************************
* Berechnet die Summe der Elemente des Arrays, indem das Array von 
* hinten durchgegangen wird: Der Wert des Arrays an der Stelle i-1
* berechnet sich immer als Summe des Werts an der Stelle i-1 
* und des Werts an der Stelle i. Somit ist steht nach der Ausführung
* die Summe aller Zahlen in array[0].
**********************************************************************/
void compute_sum_and_place_in_first_elem(int array[], int* size)
{
    /*
    Mit diesem alten Code gab es Probleme; müsste aber auch korrekt sein

    int* ptr_to_elem = array + (*size);
    while(ptr_to_elem >= array)
    {
        (*(ptr_to_elem-1)) = (*(ptr_to_elem-1)) + (*(ptr_to_elem));
        ptr_to_elem--;
    }
    */

    for(int i = *size; i >= 0; --i)
    {
        array[i-1] = array[i-1] + array[i];
    }
    
    //Die Summe  steht jetzt in array[0]
}

/*********************************************************************
* Gibt den Speicher des Arrays sowie den Pointer N wieder frei.
**********************************************************************/
void free_memory(int array[], int* N)
{
    return; //in dieser Funktion gab es Fehler
    //Gib den Speicher für das array und für N wieder frei.
    free(array);
    free(N);    
}

/*********************************************************************
* Hat Gauß wirklich recht? Ist die Summe 1,2,...,N wirklich (N+1)*N/2?
* 
* Dieses Programm berechnet die Summe der Zahlen 1 bis N. N kann dem
* Programm als Parameter übergeben werden. Wird kein Wert übergeben, 
* wird der Wert N über die Kommandozeile abgefragt.
**********************************************************************/
int main(int argc, char* argv[])
{   
    int* N = malloc(sizeof(int));
    if(argc == 1)
    {
        //falls das Programm ohne Parameter aufgerufen wurde, 
        //lies den Wert N über die Kommandozeile ein
        while(read_number_from_stdin(N) != 1);  
    }
    else if(argc == 2)
    {
        if(read_number_from_string(argv[1], N) == 0)
        {
            printf("Kommandozeilen Parameter %s konnte nicht in eine Zahl konvertiert werden!\n", argv[1]);
            return -1;
        }
    }
    else
    {
        printf("Es wird maximal ein numerischer Parameter (optional) erwartet. Ausführung des Programms wird abgebrochen!\n");
        return -1;
    }   

    //Erstelle ein Array der Größe N
    int* array = allocate_array(N);

    //schreibe die Zahlen 1,2,...,N in das Array
    initialize_array(array, *N);
    //berechne die Summe des Arrays
    compute_sum_and_place_in_first_elem(array,N);
    int result = array[0];
    int result_gauss = ((*N+1)*(*N)/2);
    if(result == result_gauss)
    {
        printf("\nVielleicht hatte Gauß ja doch recht...\nDie Summe der %d natürlichen Zahlen ist %d und somit gleich (%d+1)*%d/2.\n\n", *N, result, *N,*N);
    }
    else
    {
        printf("\nGauß hatte unrecht!\nDie Summe der %d natürlichen Zahlen ist %d und somit UNGLEICH (%d+1)*%d/2\n\n", *N, result, *N,*N);
    }
    
    //gib den Speicher wieder frei
    free_memory(array, N);
}
