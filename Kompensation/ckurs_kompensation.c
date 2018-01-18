/* ==== KOMPENSATION ABGABE ====
 * Kompensationsaufgabe
 * Abgabe von: Jannik Novak
 * =============================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_MATCH 200 
#define MAX_STRING 255 

typedef struct QElement { //final
	char string[MAX_STRING];
	struct QElement *next;
} Qelement;

typedef struct Queue { //final
	Qelement *first;
	Qelement *rear;
	int count;
} Queue;

Queue* init_queue() { //final
	Queue *new_queue = (Queue*)malloc(sizeof(Queue));
	if(new_queue == NULL) {
		printf("Overflow\n");
		return NULL; }
	new_queue -> first = NULL;
	new_queue -> rear = NULL;
	new_queue -> count = 0;
	return new_queue;
}

void queue_freigeben(Queue *queue) { //final
	if(queue -> first == NULL) {
		free(queue);
		printf("\tQueue ist leer!(queue_freigeben)\n");
		return; }
	Qelement *prev;
	Qelement *current = queue -> first;
	while(current) {
		prev = current;
		current = current -> next;
		free(prev); }
	free(queue); 
}

void enqueue(Queue *queue, char* string){ //final
	Qelement *new_elem = (Qelement*)malloc(sizeof(Qelement));
	if(new_elem == NULL) {
		printf("Overflow\n");
		return; }
	new_elem -> next = NULL;
	strncpy(new_elem -> string, string, MAX_STRING - 1);
	new_elem -> string[MAX_STRING - 1] = '\0';
	if(queue -> first == NULL) {
		queue -> first = new_elem; }
	else {
		queue -> rear -> next = new_elem; }
	queue -> rear = new_elem;
}

void dequeue (Queue *queue) { //final
	if(queue -> first == NULL) {
		printf("\tQueue ist leer!(dequeue)\n");
		return; }
	Qelement *temp = queue -> first;
	queue -> first = queue -> first -> next;
	free(temp);
}

void queue_ausgeben(Queue *queue) { //final
	Qelement *p;
	if(queue -> first == NULL) {
		printf("\tQueue ist leer!(queue_ausgeben)\n");
		return; }
	p = queue -> first;
	printf("\t");
	while(p) {
		printf("%s ", p -> string);
		p = p -> next; }
	printf("\n");
}

int match(Queue *suchphrase, Queue *queue) { 		//final
	if(suchphrase == NULL && queue == NULL) {
		return 0; }
	Qelement *search = suchphrase -> first;
	Qelement *word = queue -> first;
	while(search != NULL && word != NULL) {
		if(strcmp(search -> string, word -> string) != 0) {
			break; }
		search = search -> next;
		word = word -> next; 
	}
	if(search == NULL && word == NULL) {
		return 0; }
	else {
		return 1; }
}

int main(int argc, char** argv) {
    if (argc < 3)
    {
        printf("Nutzung: %s <Dateiname> <Wort1> <Wort2> ...\n", argv[0]);
        return 1;
    }
	Queue* suchphrase = init_queue();
	Queue* queue = init_queue();
	if(!suchphrase || !queue) {
		printf("\tFehler beim initialisieren der Queues!\n");
		return -1; }
	int hitcount = 0;	
	
	FILE *fp = fopen(argv[1], "r");
	char buffer[MAX_STRING];

	if(fp == NULL) {
		perror("Fehler beim öffnen der Datei!\n");
		return -2; }

	for(int i = 2; i < argc; ++i) {
		strncpy(buffer, argv[i], MAX_STRING - 1);
		buffer[MAX_STRING - 1] = '\0';
		enqueue(suchphrase, buffer);
		suchphrase -> count = suchphrase -> count + 1; }
	printf("\n\tElemente der Suchphrase:\n");
	queue_ausgeben(suchphrase);
	printf("\n");

	while(queue -> count != suchphrase -> count) {
		fscanf(fp, "%254s", buffer);
		enqueue(queue, buffer); 
		queue -> count = queue -> count + 1; }
	/*printf("\n\tElemente der Queue:\n");	
	queue_ausgeben(queue);
	
	int teststrcmp = strcmp(queue -> first -> string, suchphrase -> first -> string);
	printf("\n\tStrcmp return vor Suche(1. Element): %d\n\n", teststrcmp);

	int teststrcmp1 = strcmp(queue -> first -> next -> string, suchphrase -> first -> next -> string);
	printf("\tStrcmp return vor Suche(2. Element): %d\n\n", teststrcmp1);

	int teststrcmp2 = strcmp(queue -> first -> next -> next -> string, suchphrase -> first -> next -> next-> string);
	printf("\tStrcmp return vor Suche(3. Element): %d\n\n", teststrcmp2);

	int testmatch = match(suchphrase, queue);
	printf("\tMatch return vor Suche: %d\n\n", testmatch);*/

	while(!feof(fp)) {
		if(match(suchphrase, queue) == 0) {
			++hitcount;
			printf("\t%d. Treffer beginnend bei Wort Nr. %d\n", hitcount, queue -> count - suchphrase -> count + 1); } 
		if(hitcount == MAX_MATCH) {
			printf("\tmaximale Anzahl an Treffern erreicht!\n");
			break; }
		fscanf(fp, "%254s", buffer);
		enqueue(queue, buffer); 
		dequeue(queue);
		queue -> count = queue -> count + 1;
	}
	/*printf("\n\tElemente der Queue(nachdem Suche beendet):\n");
	queue_ausgeben(queue);*/

	printf("\n\t===> %d Treffer\n\n", hitcount);

	fclose(fp);
	queue_freigeben(queue);
	queue_freigeben(suchphrase);
	/*printf("\tSuchphrase(Count): %d, Queue(Count): %d\n",suchphrase -> count, queue -> count); */
	return 0;
}
