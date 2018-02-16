// @author: Matthias Rost (mrost@inet.tu-berlin.de)
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>		
#include <stdio.h>		//Ein- / Ausgabe
#include <assert.h>		//Immer auf der richtigen Seite!
#include <math.h>		//Für die Berechnungen der Ausgabe
#include <string.h>
#include "avl.h"

/*
 *	Code für die Ausgabe eines Baums auf stdin
 */

int left(int i) {
	return 2*i+1;
}

int right(int i) {
	return 2*i+2;
}

// Kopiere Knoten rekursiv in ein Array
void fill_array(AVLNode* node, AVLNode** node_array, int current_position)
{
	node_array[current_position] = node;
	if(node->left != NULL)
	{
		fill_array(node->left, node_array, left(current_position));
	}
	if(node->right != NULL)
	{
		fill_array(node->right, node_array, right(current_position));
	}
	
}

// Findet das Maximum in einem Teilbaum
int find_max_value(AVLNode* node)
{
	while(node->right != NULL)
	{
		node = node->right;
	}
	return node->value;
}

// Gibt eine String-Represenation des übergebenen Baumes zurück (muss danach grefreeed werden!).
char* draw_AVL_tree(AVLTree* avlt)
{
	assert(avlt != NULL);
	
	if(avlt->root == NULL)
	{
		return(strdup("Baum ist leer!"));
	}
	
	int height = avlt->root->height;
	
	// maximale Anzahl an Blättern ist 2^height
	int max_leaves = (1 << height);
	
	// berechne die maximal benötigte Breite der Knoten
	int entry_width = (int)(ceil(log10(abs(find_max_value(avlt->root)))));
	if(entry_width % 2 == 0)
	{
		entry_width++;
	}
	
	// ein paar weitere Konstanten
	int entry_spacing = 1;
	int line_width = max_leaves * entry_width + (max_leaves-1) * entry_spacing;
	int max_node_count = max_leaves * 2;
	
	// lege ein 2d-Array von Chars für die Ausgabe an
	char** string_buffer = malloc(sizeof(char*) * ((height)*2));
	for(int y = 0; y <= (height-1)*2 +1; ++y)
	{
		string_buffer[y] = malloc(sizeof(char) * line_width + 2);
		for(int x = 0; x < line_width; ++x)
		{
			string_buffer[y][x] = ' ';
		}
		string_buffer[y][line_width] = '\n';
		string_buffer[y][line_width+1] = '\0';
	}
	
	// speichere alle Knoten des Graphs in einem Array
	AVLNode** node_array = malloc(max_node_count * sizeof(AVLNode*));
	for(int i = 0; i < max_node_count; ++i)
	{
		node_array[i] = NULL;
	}
	fill_array(avlt->root, node_array, 0);
	
	
	// berechne (mittels dynamischer Programmierung) die Positionen
	// jedes einzelnen Knoten
	int* position_pointer = malloc(max_node_count * sizeof(int));
	for(int level = height; level >= 0; level--)
	{

		int index_of_first_node_in_level = ((1 << level) - 1);
		if(level == height)
		{
			//der unterste, linkeste Knoten wird bündig links ausgegeben
			position_pointer[index_of_first_node_in_level] = 0;
		
			// alle anderen Knoten sind (entry_spacing+entry_width) weit entfernt
			for(int i = 1; i < (1 << level); ++i)
			{
				position_pointer[index_of_first_node_in_level + i] = position_pointer[index_of_first_node_in_level + i - 1] + entry_spacing + entry_width;
			}
		}
		else
		{
			// für Knoten in höheren Schichten nehmen wir das arithmetische Mittel der Kinderpositionen
			for(int i = 0; i < (1 << level); ++i)
			{
				position_pointer[index_of_first_node_in_level + i] = (position_pointer[left(index_of_first_node_in_level + i)] + position_pointer[right(index_of_first_node_in_level + i)]) / 2;
			}
		}
	}
	
	for(int y = (height-1) * 2; y >= 0; y -= 2)
	{
		int level = y / 2;
		int index_of_first_node_in_level = ((1 << level) - 1);
		
		// Schreibe die Knoten..
		for(int i = 0; i < (1 << level); ++i)
		{
			AVLNode* current_node = node_array[index_of_first_node_in_level + i];
			char* curr_pointer = string_buffer[y] + position_pointer[index_of_first_node_in_level + i];
			if(current_node != NULL)
			{
				// füge Leerzeichen hinzu falls notwendig..
				int trailing_spaces = (int)(floor( (entry_width - (ceil(log10(abs(current_node->value))))) / 2));
				if(trailing_spaces > 0)
				{
					curr_pointer += trailing_spaces;
				}
				int len = sprintf(curr_pointer, "%d", current_node->value);
				curr_pointer[len] = ' ';
			}
		}
		if(y < (height-1) * 2)
		{
			// Schreibe die Kanten
			for(int i = 0; i < (1 << level); ++i)
			{
				int position = index_of_first_node_in_level + i;
				if(node_array[left(position)] != NULL)
				{
					char* curr_pointer = string_buffer[y+1];
					for(int k = position_pointer[left(position)] + entry_width / 2; k <= position_pointer[position] + entry_width / 2 - 1; ++k)
					{
						curr_pointer[k] = '-';
					}
					curr_pointer[position_pointer[left(position)] + entry_width / 2] = '/';
					curr_pointer[position_pointer[position]+ entry_width / 2] = '|';
				}
				if(node_array[right(position)] != NULL)
				{
					char* curr_pointer = string_buffer[y+1];
					for(int k = position_pointer[right(position)] + entry_width / 2; k >= position_pointer[position] + entry_width / 2 + 1; --k)
					{
						curr_pointer[k] = '-';
					}
					curr_pointer[position_pointer[right(position)] + entry_width / 2] = '\\';
					curr_pointer[position_pointer[position]+ entry_width / 2] = '|';
				}
			}
		}				
		
	}
	
	// länge für rückgabestring bestimmen
	size_t ostrlen = 1;
	for(int y = 0; y <= (height) * 2-1; ++y)
	{
		ostrlen += strlen(string_buffer[y]);
	}
	char* ostr = calloc(ostrlen, sizeof(char));
	char* ostrp = ostr;
	
	// baut den String und gibt allen Speicher wieder frei
	for(int y = 0; y <= (height) * 2-1; ++y)
	{
		ostrp = stpncpy(ostrp, string_buffer[y], ostrlen-(ostrp-ostr) );
		free(string_buffer[y]);
	}
	free(string_buffer);
	free(position_pointer);
	free(node_array);
	return(ostr); 
}

// Gibt den übergebenen Baum auf stdout aus.
void print_AVL_tree(AVLTree* avlt)
{
	char* tr = draw_AVL_tree(avlt);
	printf("%s\n", tr);
	free(tr);
}

// Parst die Eingabe aus der übergebenen Datei und führt die entsprechenden Operationen 
// auf dem Baum avlt aus.
void execute_operations(AVLTree* avlt, FILE* input)
{
	char buffer[255];
	int abort = 0;
	while(!abort && (fgets(buffer, 255, input) != NULL))
	{
		char operation;
		int value;
		
		int result=sscanf(buffer,"%d",&value);		
		if(result != 1)
		{
			result = sscanf(buffer, "%c", &operation);
			if(result != 1)
			{
				printf("fgets/sscanf konnte die Eingabe nicht parsen...!\n");
			}
			else
			{
				if(operation == 'p')
				{
					print_AVL_tree(avlt);
				}
				else if(operation == 'w')
				{
					AVL_in_order_walk(avlt);
				}
				else if(operation == 'q')
				{
					abort = 1;
				}
				else if(operation == 'c')
				{
					printf("Im AVL-Baum sind %d Elemente enthalten.\n", avlt->numberOfNodes);
				}
				else
				{
					printf("Zeichen %c wird ignoriert\n", operation);
				}
			}
		}
		else
		{
			printf("Füge %d ein...\n", value);
			AVL_insert_value(avlt, value);
		}
	}
}













































