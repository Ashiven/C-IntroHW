#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include "introprog_structs_lists_input.h"
#include <string.h>

void open_file(read_line_context *ctx, const char *filename) {
    ctx->filename = filename;
	ctx->line = NULL;
    ctx->linecapp = 0;
    ctx->filepointer = fopen(ctx->filename, "r");
    if (ctx->filepointer == NULL){
        perror(ctx->filename);
        exit(1);
    }
}

int read_line(read_line_context *ctx, char **name, char **author, int *year, long long int *isbn) {
    if (ctx->filepointer == NULL){
        perror(ctx->filename);
        exit(1);
    }
    char *name_s;
    char *author_s;
    char *year_s;
    char *isbn_s;
    char *delim = ";";
    ssize_t len;

    if ((len = getline(&(ctx->line), &(ctx->linecapp), ctx->filepointer)) != -1)
    {
        /* remove tailing newline */
	    char *pos;
        if ((pos = strchr(ctx->line, '\n')) != NULL)
            *pos = '\0';
        
	/* read individual fields */
	name_s   = strtok(ctx->line, delim);
	author_s = strtok(NULL, delim);
	year_s   = strtok(NULL, delim);
	isbn_s   = strtok(NULL, delim);

	if(name_s != NULL && author_s != NULL && year_s != NULL  && isbn_s != NULL ) {
	    *name   = name_s;
            *author = author_s;
            *year   = atoi(year_s);
            *isbn   = atoll(isbn_s);
            return 0;
        }
        
    }
    fclose(ctx->filepointer);
    ctx->filepointer = NULL;
    ctx->linecapp = 0;
    if (ctx->line != NULL ) {
        free(ctx->line);
    }
    return -1;
}
