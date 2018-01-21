#include<stdio.h>

//Hinweis: Die Implementierungen dieser Funktionen ist korrekt.

int read_number_from_stdin(int* value)
{
	printf("Gib bitte eine ganze Zahl ein: ");
	int return_value = scanf("%d", value);
	if(return_value == 0)
	{
		while (fgetc(stdin) != '\n');
	}
	if(return_value == EOF)
	{
		return_value = 0;
	}
	return return_value;
}

int read_number_from_string(char* string, int* value)
{
	printf("Lese übergebenen Parameter ein...\n");
	int return_value = sscanf(string, "%d", value);
	if(return_value == 0 || return_value == EOF)
	{
		printf("\t... Parameter konnte nicht in Zahl übersetzt werden!\n");
		return_value = 0;
	}
	else
	{
		printf("\t... Es wurde die Zahl %d eingelesen.\n", *value);
	}
	return return_value;
}
