
typedef struct heap heap;

/* Dieses struct definiert einen Heap
 *
 * capacity: Die maximale Anzahl Elemente,
 * die im Heap gespeichert werden koennen.
 * Diese wird an heap_create uebergeben und
 * der Speicher dafuer dynamisch alloziert.
 *
 * size: Die aktuelle Anzahl der Elemente.
 * Diese wird beim Hinzufuegen und Entfernen
 * von Elementen jedes Mal angepasst und
 * darf capacity nicht ueberschreiten.
 */
struct heap {
    int* elements;
    size_t size;
    size_t capacity;
};

heap* heap_create(size_t capacity);
void heapify(heap* h, size_t i);
int heap_extract_max(heap* h);
int heap_insert(heap* h, int key);
void heap_free(heap* h);
