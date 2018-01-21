#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "introprog_telefonbuch.h"

int min(int a, int b) {
    if (a < b) { return a; }
    return b;
}

void open_stdin(read_line_context *ctx) {
	ctx->line = NULL;
    ctx->linecapp = 0;
    ctx->filepointer = stdin;
}

void open_file(read_line_context *ctx, const char *filename) {
	ctx->line = NULL;
    ctx->linecapp = 0;
    ctx->filepointer = fopen(filename, "r");
    if (ctx->filepointer == NULL){
        perror(filename);
        exit(1);
    }
}

int read_line(read_line_context *ctx, char **operation, unsigned long* number, char **name) {

    char *delim = " ;";
    ssize_t len;
    
    char *operation_s = NULL;
    char *number_s = NULL; 
    char *name_s = NULL;

    if ((len = getline(&(ctx->line), &(ctx->linecapp), ctx->filepointer)) != -1)
    {
        /* remove tailing newline */
	    char *pos;
        if ((pos = strchr(ctx->line, '\n')) != NULL) {
            *pos = '\0';
        } else {
            pos = ctx->line+strlen(ctx->line);
        }
        
        /* parse strings */
        if(operation != NULL) {
            operation_s = strtok(ctx->line, delim);
            number_s = strtok(NULL, delim);
        } else {
            number_s = strtok(ctx->line, delim);
        }
        if (number_s != NULL) { 
            name_s = number_s + strlen(number_s) + 1;   
        }
        
        /* return parsed result */
        if(operation != NULL) {
            *operation = operation_s;
        }
        if(number_s != NULL) {
            *number = strtoul(number_s, NULL, 10);
        } else {
            *number = 0;
        }
        if(name_s != NULL && name_s < pos) {
            *name = name_s;
        } else {
            *name = "";
        }
        
        return 0;
        
    }
    return -1;       

}


void close_file(read_line_context *ctx) {

    fclose(ctx->filepointer);
    if (ctx->line != NULL) {
        free(ctx->line);
        ctx->line = NULL;
    }
    ctx->linecapp = 0;

}
                

void dot_print_null(int key, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void dot_print_aux(DOT_NODETYPE* node, FILE* stream)
{
    static int nullcount = 0;

    fprintf(stream, "    %lu [label=\"%s\\n(%lu)\"];\n", node->DOT_KEY, node->DOT_VALUE,  node->DOT_KEY);
    if (node->DOT_LCHILD)
    {
        fprintf(stream, "    %lu -> %lu [label=\"<\"];\n", node->DOT_KEY, node->DOT_LCHILD->DOT_KEY);
        dot_print_aux(node->DOT_LCHILD, stream);
    }
    else
       dot_print_null(node->DOT_KEY, nullcount++, stream);

    if (node->DOT_RCHILD)
    {
        fprintf(stream, "    %lu -> %lu [label=\">\"];\n", node->DOT_KEY, node->DOT_RCHILD->DOT_KEY);
        dot_print_aux(node->DOT_RCHILD, stream);
    }
    else
       dot_print_null(node->DOT_KEY, nullcount++, stream);

    if (node->DOT_PARENT)
    {
        if (node->DOT_PARENT->DOT_LCHILD != node && node->DOT_PARENT->DOT_RCHILD != node)
        {
           fprintf(stream, "    %lu -> %s;\n", node->DOT_KEY, "\"broken parent pointer\"");
        }
    }
}

/*
Diese Funktion gibt die übergebene baumstruktur als dot-file aus. Mit
    dot -O -Tpng filename
  können diese dot-files gezeichnet werden.

  (Benötigt graphviz)
*/
void print_to_dot(DOT_NODETYPE* tree, char* filename)
{
    FILE* fd = fopen(filename, "w");
    if (fd == NULL) {
        printf("dot output: could not open file %s", filename);
        return;
    }

    fprintf(fd, "digraph BST {\n");
    fprintf(fd, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(fd, "\n");
    else if (!tree->DOT_RCHILD && !tree->DOT_LCHILD)
        fprintf(fd, "    %lu;\n", tree->DOT_KEY);
    else
        dot_print_aux(tree, fd);

    fprintf(fd, "labelloc=\"t\"\n");
    //fprintf(fd, "\" %s\"\n", title);
    fprintf(fd, "}\n");
    fclose(fd);
}
