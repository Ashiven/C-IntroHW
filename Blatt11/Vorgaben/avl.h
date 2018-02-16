// Knoten im AVL Suchbaum, wobei ...
// - left und right auf das linke bzw. rechte Kind zeigt.
// - parent auf denjenigen Knoten verweist, dessen Kind dieser Knoten ist.
// - value der ganzzahlige Wert des Knotens ist.
// - height bezeichnet Höhe des Teilbaums; dieser Wert sollte immer aktuell gehalten werden!
struct AVLNode
{
	struct AVLNode* left;		
	struct AVLNode* right;	
	struct AVLNode* parent;
	int value;
	int height;
};

// Ein Binärer Suchbaum mit einem Wurzelknoten root und der Anzahl an
// Elementen im Baum (diese Wert muss aktuell gehalten werden!)
struct AVLTree
{
	struct AVLNode* root;
	int numberOfNodes;
};

// typedefs, damit man sich das "struct" sparen kann.
typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;

// Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus.
void AVL_in_order_walk(AVLTree* avlt);

// Diese Funktion führt eine Linksrotation auf dem angegebenen Knoten aus.
// Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal) angepast werden.
void AVL_rotate_left(AVLTree* avlt, AVLNode* x);

// Diese Funktion führt eine Rechtsrotation auf dem angegebenen Knoten aus.
// Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal) angepast werden.
void AVL_rotate_right(AVLTree* avlt, AVLNode* y);

//Balanciert den Teilbaum unterhalb von node.
void AVL_balance(AVLTree* avlt, AVLNode* node);

// Fügt der Wert value in den Baum ein.
// Die Implementierung muss sicherstellen, dass der Baum nach dem Einfügen
// immer noch balanciert ist!
void AVL_insert_value(AVLTree* avlt, int value);

// Löscht den gesamten Baum AVL und gibt den Speicher aller Knoten frei.
void AVL_remove_all_elements(AVLTree* avlt);

// Gibt eine String-Represenation des übergebenen Baumes zurück (muss danach grefreeed werden!).
char* draw_AVL_tree(AVLTree* avlt);

// Gibt den übergebenen Baum auf stdout aus.
void print_AVL_tree(AVLTree* avlt);

// Parst die Eingabe aus der übergebenen Datei und führt die entsprechenden Operationen 
// auf dem Baum avlt aus.
void execute_operations(AVLTree* avlt, FILE* input);














































