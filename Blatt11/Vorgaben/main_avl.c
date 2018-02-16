#include <stdio.h>
#include "avl.h"

int main(int argc, char** args)
{
	if (argc < 1 || argc > 2)
	{
		printf("Nutzung: %s [Dateiname]\n",args[0]);
		return 1;
	}
	
	FILE* input = NULL;
	if(argc == 1)
	{
		input = stdin;
	}
	else
	{
		input=fopen(args[1],"r");
		if(input == NULL)
		{
			return 1;
		}	
	}
	
	// erzeuge leeren Suchbaum
	AVLTree avlt;
	avlt.root = NULL;
	avlt.numberOfNodes = 0;
	
	// führe operationen auf dem Baum aus
	execute_operations(&avlt, input);
	
	// gib den Speicher frei
	AVL_remove_all_elements(&avlt);
	
	if(argc == 2)
	{
		fclose(input);
	}
	return 0;
}
