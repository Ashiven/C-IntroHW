#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 255
#define DOT_NODETYPE bst_node
#define DOT_RCHILD right
#define DOT_LCHILD left
#define DOT_PARENT parent
#define DOT_KEY phone
#define DOT_VALUE name

/* typedefs, damit wir uns das "struct" sparen können.
 */
typedef struct bst_node bst_node;
typedef struct bstree  bstree;

/* Knoten im Binären Suchbaum, wobei ...
 * - left und right das linke bzw. rechte Kind spezifiziert.
 * - parent auf denjenigen Knoten verweist, dessen Kind dieser Knoten ist.
 * - phone die Telefonnummer des Suchbaumknotens angibt.
 * - name den entsprechenden Namen des Suchbaumknotens angibt.
 */
struct bst_node
{
    bst_node* left;
    bst_node* right;
    bst_node* parent;
    unsigned long phone;
    char *name;
};

/* Ein Binärer Suchbaum mit einem Wurzelknoten root und der Anzahl an
 * Elementen im Baum.
 */
struct bstree
{
    struct bst_node* root;
    int count;
};

/* Hilfsstrucktur für open_file / read_line / close_file
 */
typedef struct  {
    FILE *filepointer;
    char *line;
    size_t linecapp;
} read_line_context;

void bst_insert_node(bstree* bst, unsigned long phone, char *name);
bst_node* find_node(bstree* bst, unsigned long phone);
void bst_in_order_walk(bstree* bst);
void bst_free_tree(bstree* bst);
void open_file(read_line_context *ctx, const char *filename);
void open_stdin(read_line_context *ctx);
int read_line(read_line_context *ctx, char **operation, unsigned long* nummer, char **name);
void close_file(read_line_context *ctx);
void print_to_dot(DOT_NODETYPE* tree, char* filename);
void print_node(bst_node *node);
