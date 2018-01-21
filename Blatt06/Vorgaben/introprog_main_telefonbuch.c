#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

void print_node(bst_node *node) {
    printf("Tel: %-9lu Name: %s\n", node->phone, node->name);
}

// Ausgabe für die Suche, damit das Interface selbst etwas kompakter ist.
void find_and_print(bstree* bst, int phone) {
    bst_node *node = find_node(bst, phone);
    if(node == NULL) {
        printf("Telefonnummer %d existiert nicht.\n", phone);
    } else {
        print_node(node);
    }
}



// Debug Ausgabe: Erstellt eine Bilddatei, die den ggw. Baum visualisiert.
void debug(bstree *bst) {
    printf("Erstelle zur Visualisierung die Datei 'baum.dot'...");
    print_to_dot(bst->root, "baum.dot");
    printf("Fertig.\n");
#if !defined(_WIN32) || !defined(_WIN64)
    printf("Konvertiere mithilfe von 'dot' die Datei in das 'png' Format...");
    int status = system("dot -Tpng baum.dot -o baum.png");
    if (status == 0) {
        printf("Fertig.\n"
               "Die Debug Ausgabe befindet sich in der Datei 'baum.png'\n");
    } else {
        printf("Fehler!\n"
               "Die Konvertierung ist fehlgeschlagen."
               "Möglicherweise ist 'dot' bzw. Graphviz nicht installiert!'\n");
    }
#else
    printf("Auf Windows Systemen muss die dot Datei per Hand kompiliert werden.\n"
           "Information zu Graphviz lassen sich unter folgender URL finden\n"
           "   http://www.graphviz.org/Download_windows.php\n");
#endif
}

// Parst die Eingabe aus der übergebenen Datei und führt die entsprechenden Operationen aus.
bstree* read_file(char* filename, bstree *bst)
{
    unsigned long phone;
    char* name;
    read_line_context ctx;
    open_file(&ctx, filename);
    while (read_line(&ctx, NULL, &phone, &name)==0) {
        bst_insert_node(bst, phone, name);
    }
    close_file(&ctx);
    return bst;
}

void help() {
    printf(" Fernsprech-Datensatz-System\n"
           " ===========================\n"
           "  Füge in das Telefonbuch ein:\t+ <Nummer> <Name>\n"
           "  Gebe das Telefonbuch aus:\tp\n"
           "  Finde den Namen zu:\t\t? <Nummer>\n"
           "  Debugausgabe des Baumes:\td\n"
           "  Beende das System:\t\tq\n\n"
           " Hinweis: Nummern haben maximal 9 Ziffern\n\n"
    );
}

// Kreiert eine Benutzeroberfläche
bstree* interface(bstree *bst) {
    help();
    char *operation;
    unsigned long phone;
    char *name;
    read_line_context in;
    open_stdin(&in);
    printf("> ");
    while (read_line(&in, &operation, &phone, &name) == 0) {
        if (operation != NULL) {
            if (operation[0] == '?' && phone > 0) {
                find_and_print(bst, phone);
            } else if (operation[0] == '+' && phone > 0 && strlen(name) > 0) {
                bst_insert_node(bst, phone, name);
            } else if (operation[0] == 'd') {
                debug(bst);
            } else if (operation[0] == 'p') {
                bst_in_order_walk(bst);
            } else if (operation[0] == 'q') {
                break;
            } else {
                printf("Inkorrekte Eingabe\n\n");
                help();
            }
        }
        printf("> ");
        phone = -1;
    }
    printf("Exiting...\n");
    close_file(&in);
    return bst;
}

int main(int argc, char** argv) {
    // Erzeuge leeren Suchbaum
    bstree bst;
    bst.root = NULL;
    bst.count = 0;

    if (argc != 2)
    {
        printf("Nutzung: %s <Dateiname>\n",argv[0]);
        return 1;
    }

    // Lese das Telefonbuch ein
    read_file(argv[1], &bst);

    // Gib die Benutzeroberfläche aus
    interface(&bst);

    // Gib den Speicher frei
    bst_free_tree(&bst);

    return 0;
}
