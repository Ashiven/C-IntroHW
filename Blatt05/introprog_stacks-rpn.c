/* === INTROPROG ABGABE ===
 * Blatt 6, Aufgabe 2
 * Tutorium: txx
 * Gruppe: gxx
 * Gruppenmitglieder:
 *  - Max Mustermann
 *  - Rainer Testfall
 * ========================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

void stack_push(stack *astack, float value)
{
	stack_element *new_elem = (stack_element*)malloc(sizeof(stack_element));
	new_elem -> value = value;
	new_elem -> next = astack -> top;
	astack -> top = new_elem;
}

float stack_pop(stack *astack)
{
	float retflt;
	if(astack) 
	{
		stack_element *temp = astack -> top;
		retflt = temp -> value;
		astack -> top = temp -> next; 
		free(temp); 
	}
	else 
	{
		if(isnan(astack -> top -> value) == 1) 
		{
			retflt = 0; 
		}
	}
	return retflt;
}

void process(stack *astack, char *token)
{
	float tmpfloat1;
	float tmpfloat2;
	float tmpfloat3;
	if(is_number(token) == 1) 
	{
		tmpfloat1 = atof(token);
		stack_push(astack, tmpfloat1);
	}
	else if(astack -> top -> next == NULL) 
	{
    		printf("\n<Logik fehlt!>\n");
		return;
	}
	else if(is_add(token) == 1) 
	{
		tmpfloat1 = stack_pop(astack);
		tmpfloat2 = stack_pop(astack);
		tmpfloat3 = tmpfloat1 + tmpfloat2;
		stack_push(astack, tmpfloat3); 
	}
	else if(is_sub(token) == 1) 
	{
		tmpfloat1 = stack_pop(astack);
		tmpfloat2 = stack_pop(astack);
		tmpfloat3 = tmpfloat2 - tmpfloat1;
		stack_push(astack, tmpfloat3); 
	}
	else if(is_mult(token) == 1) 
	{
		tmpfloat1 = stack_pop(astack);
		tmpfloat2 = stack_pop(astack);
		tmpfloat3 = tmpfloat1 * tmpfloat2;
		stack_push(astack, tmpfloat3); 
	}
    	return;
}

void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}


stack* stack_erstellen() {
	stack *new_stack = (stack*)malloc(sizeof(stack));
	new_stack -> top = NULL;
	return new_stack;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}
