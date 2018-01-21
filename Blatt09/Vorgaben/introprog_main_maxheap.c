#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "introprog_heap.h"

#define MAX_HEAP_SIZE 400
#define MAX_LINE_SIZE 100

void banner() {
    // The following ASCII artwork is property of Josua G. Stark
    // Find more of his art at http://www.oocities.org/spunk1111/
    printf("              .------,\n");
    printf("               =\\      \\\n");
    printf("  .---.         =\\      \\\n");
    printf("  | C~ \\         =\\      \\\n");
    printf("  |     `----------'------'----------,\n");
    printf(" .'     LI.-.LI LI LI LI LI LI LI.-.LI`-.\n");
    printf(" \\ _/.____|_|______.------,______|_|_____)\n");
    printf("                  /      /\n");
    printf("                =/      /\n");
    printf("               =/      /\n");
    printf("              =/      /\n");
    printf("       jgs    /_____,'\n\n");
    printf("\n");
    printf("\tBoarding-Administration\n");
    printf("\t#######################\n");
    printf("\tVerfügbare Eingaben:\n");
    printf("\t <Zahl>\tVerfügbare Sitzreihe eintragen.\n");
    printf("\t n\tNächste zu belegende Sitzreihe erhalten.\n");
    printf("\t q\tProgramm beenden.\n\n");
}

/* Lese die Eingabe von STDIN. Lese jeweils nur eine Zeile ein.
 * Gebe folgende Werte zurück
 *
 * Eine positive Zahl, wenn eine solche eingegeben wurde (z.b. "10").
 * -1 Bei der Eingabe von 'n'
 * -2 Bei der Eingabe von 'q'
 * -3 Wenn die Eingabe sich nicht eindeutig zuordnen ließ.
 *
 */
int read_user_input() {
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE-1, stdin);
    if ( strlen(line) < 2 ) {
        return -3;
    } else if (line[0] == 'n' && line[1] == '\n' && line[2] == 0) {
        return -1;
    } else if (line[0] == 'q' && line[1] == '\n' && line[2] == 0) {
        return -2;
    } else { 
        for (int i=0; i < strlen(line)-1; i++) {
            if (!isdigit(line[i])) {
                return -3;
            }
        }
        return atoi(line);
    }
}

/* Programm zum Führen einer Warteliste
 *
 * Das Programm nimmt Befehle zeilenweise auf der Standardeingabe entgegen:
 * "q": Beende das Programm.
 * "n": Der nächste Passagier soll einsteigen. Das Programm gibt als Antwort die
 *      vorzugebenede Sitzreihe aus.
 * positive Ganzzahl: Ein Passagier mit dieser Sitzreihennummer wurde registriert.
 */
int main(int argc, char** argv)
{
    heap* warteliste = heap_create(MAX_HEAP_SIZE);
    int eingabe;
    int zahl;
    banner();
    while (1) {
        printf("> ");
        eingabe = read_user_input();
        if (eingabe == -3) { // Falsche Eingabe
            printf("Fehler: Eingabe nicht erkannt!\n");
        } else if (eingabe == -2) { // 'q'
            break; // Exit
        } else if (eingabe == -1) { // 'n'
            zahl = heap_extract_max(warteliste);
            if (zahl >= 0) {
                printf("%i\n", zahl);
            } else {
                printf("Leer!\n");
            }
        } else { // Zahl eingelesen
            if(heap_insert(warteliste, eingabe)==-1) {
                printf("Fehler: Heap ist voll, Eingabe nicht gespeichert\n");
            }
        }
    }
    heap_free(warteliste);
    return 0;
}
