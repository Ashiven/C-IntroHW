#include <stdio.h>
#include <stdlib.h>
#include "introprog_input_stacks-rpn.h"
#include <string.h>

#define noop

int taschenrechner_input(char zeile[]) {
    char line[MAX_STR];
    char *pos;
    int length;

    printf("\nWas willst du rechnen?>\t");
    if (fgets(line, MAX_STR, stdin)!=NULL)
    {
        if ((pos = strchr(line, '\n')) != NULL)
            *pos = '\0';
        if (line[0] == 'q') { 
            printf("\nExiting...\n");
            return -1;
        }
        length = strlen(line);
        strncpy(zeile, line, length);
        zeile[length] = '\0';
        return 0;
    }
    return -1;
}
 
void intro() {
    // Quelle: http://climate.thephpleague.com/terminal-objects/draw/
    // Climate untersteht der MIT Lizenz
    printf(
    "     ( )          \n"
    "      H           \n"
    "      H           \n"
    "     _H_          \n"
    "  .-'-.-'-.       \n"
    " /         \\       Willkommen beim allmächtigen RPN Taschenrechner\n"
    "|           |      ===============================================\n"
    "|   .-------'._   \n"
    "|  / /  '.' '. \\     Ein par Beispiele:\n"
    "|  \\ \\ @   @ / // \n"
    "|   '---------'     Richtig: -3 5 +\n"
    "|    _______|       Richtig: 11 5 - 2.0 *\n"
    "|  .'-+-+-+|        Falsch:   3 + 2\n"
    "|  '.-+-+-+|        Falsch:   + 3 2\n"
    "|    \"\"\"\"\"\" |\n"
    "'-.__   __.-'       Bei Eingabe von 'q' beendet sich das Programm\n"
    "     \"\"\"");
}
int is_number(char *token) {
    int len = strlen(token);
    int i = 0;
    int period = 0;
    if (token[i] == '-' && len > 1) {
        i++;
    }
    for (; i<len; i++) {
        if (token[i] == '.' && period == 0) {
            period = 1;
        } else if (token[i] >= '0' && token[i] <= '9') {
            noop;
        } else {
            return 0;
        }
    }
    return 1;
}
int is_add(char *token) {
    if (token[0] == '+' && strlen(token) == 1) {
        return 1;
    }
    return 0;
}
int is_sub(char *token) {
    if (token[0] == '-' && strlen(token) == 1) {
        return 1;
    }
    return 0;
}
int is_mult(char *token) {
    if (token[0] == '*' && strlen(token) == 1) {
        return 1;
    }
    return 0;
}
