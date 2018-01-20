/* === INTROPROG ABGABE ===
 * Blatt 9, Aufgabe 2
 * Tutorium: tXX
 * Gruppe: gXX
 * Gruppenmitglieder:
 *  - Erika Mustermann
 *  - Rainer Testfall
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

/* Reserviere Speicher für einen Heap
 *
 * Der Heap soll dabei Platz für capacity Elemente bieten.
 *
 * Um konsistent mit den Parametern für malloc zu sein, ist capacity
 * als size_t (entspricht unsigned long auf x86/64) deklariert.
 * Da es sauberer ist, sind auch alle Indizes in dieser Aufgabe als
 * size_t deklariert. Ob man size_t oder int als Index für ein Array
 * verwendet, macht in der Praxis (auf x86/64) nur bei Arrays
 * mit mehr als 2.147.483.647 Elementen einen Unterschied.
 */
heap* heap_create(size_t capacity) {
}

/* Stellt die Heap Bedingung an Index i wieder her
 *
 * Vorraussetzung: Der linke und rechte Unterbaum von i
 * erfüllen die Heap-Bedingung bereits.
 */
void heapify(heap* h, size_t i) {
}

/* Holt einen Wert aus dem Heap
 *
 * Wenn der Heap nicht leer ist, wird die größte Zahl zurückgegeben.
 * Wenn der Heap leer ist, wird -1 zurückgegeben.
 */
int heap_extract_max(heap* h) {
}

/* Fügt einen Wert in den Heap ein
 *
 * Wenn der Heap bereits voll ist, wird -1 zurückgegeben,
 */
int heap_insert(heap* h, int key) {
}

/* Gibt den Speicher von einem Heap wieder frei
 */
void heap_free(heap* h) {
}
