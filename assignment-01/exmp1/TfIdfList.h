// TfIdfList.h 
// linked list interface

typedef struct TfIdfNode *TfIdfList;

// Create a new empty list
TfIdfList createTfIdfList (void);

// Create a new node to be added to the list
TfIdfList newTfIdfListNode (char *file, double tf, TfIdfList next);

// Returns the number of elements in the list
int tfIdflistLength (TfIdfList list);

// Insert a new file into the right position in the list
// Sorted by alphabetical order
TfIdfList insertTfIdfList (TfIdfList list, char *file, double tfidf);