////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    TfIdfList.h                                                             //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 1 - Information Retrieval                         //
//    Linked list interface for storing a list of files and tdidf values      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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

// Check if a file is in a list
// Return 0 if not in list
// Return 1 if in list
int inTfIdf(TfIdfList list, char *file);

// For a given file already in the tfidf list
// Update the value of tfidf
TfIdfList updateTfIdfList(TfIdfList list, char *file, double tfidf);