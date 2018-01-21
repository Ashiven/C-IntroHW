//Liest eine ganze Zahl von der Kommandozeile in die Speicheradresse auf die value zeigt.
//Die Funktion gibt 1 zurück, falls ein Wert eingelesen werden konnte und 0 sonst.
int read_number_from_stdin(int* value);

//Liest eine ganze Zahl aus einem String aus und speichert den Wert -- falls möglich -- an der
//Speicheradresse, auf die value zeigt.
//Die Funktion gibt 1 zurück, falls ein Wert eingelesen werden konnte und 0 sonst.
int read_number_from_string(char* string, int* value);
