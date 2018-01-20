/* === INTROPROG ABGABE ===
 * Blatt 4, Aufgabe 2
 * Tutorium: txx
 * Abgabe von: Max Mustermann
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

#define MAX_STR 255

typedef struct _element {
	char title[MAX_STR]; 
	char author[MAX_STR];
	int year;
	long long int isbn;
	struct _element *next;
} element; 

typedef struct _list { 
    element *first;   
    int count;         
} list;

element *insert_sorted(element *first, element *new_elem) 
{
	element *prev, *current, *temp;
	temp = new_elem;
	if(!first) 
	{
		first = temp; 
	}
	else {
		current = first;
		prev = NULL;
		while(current && current -> isbn <= temp -> isbn) 
		{
			prev = current;
			current = current -> next; 
		}
		if(!current) 
		{
			prev -> next = temp; 
		}
		else 
		{
			if(prev) 
			{
			temp -> next = prev -> next;
			prev -> next = temp; 
			}
			else 
			{
			temp -> next = first;
			first = temp; 
			}
		}
	}
	return first;
}

element *construct_element(char *title, char* author, int year, long long int isbn) 
{
	element *neu = (element*) malloc(sizeof(element));
	strncpy(neu -> title , title, MAX_STR - 1);
	strncpy(neu -> author, author, MAX_STR - 1);
	neu -> title[MAX_STR - 1] = '\0';
	neu -> author[MAX_STR - 1] = '\0';
	neu -> year = year;
	neu -> isbn = isbn;
	neu -> next = NULL;
	return neu;
}

void free_list(list *alist) 
{
	element *element = alist -> first;
	struct _element *alt;
	while(element != NULL) 
	{
		alt = element;
		element = element -> next;
		free(alt);
	}
	free(element);
	free(alist);
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 * */
void read_list(char* filename, list *alist) {
    element* new_elem;
    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

/* Gib die Liste aus:
 * _Soll nicht angepasst werden_
 */
void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

/* Main Funktion
 * _Soll nicht angepasst werden_
 */
int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
