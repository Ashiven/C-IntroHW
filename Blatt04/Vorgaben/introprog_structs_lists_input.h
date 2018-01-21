
typedef struct  {
    FILE *filepointer;
    const char *filename;
    char *line;
    size_t linecapp;
} read_line_context;

void open_file(read_line_context *ctx, const char *filename);
int read_line(read_line_context *ctx, char **name, char **author, int *year, long long int *isbn);
