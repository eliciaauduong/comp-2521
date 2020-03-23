// InvertedIndexBST.h
// binary search tree ADT interface
// adapted from source: COMP2521 lab 03 BSTree.h

typedef struct InvertedIndexNode *InvertedIndexBST;

// create an empty InvertedIndexBST
InvertedIndexBST newInvertedIndex (void);

// insert a new value into a InvertedIndexBST
InvertedIndexBST insertInvertedIndex (InvertedIndexBST b, char *word, char *filename, double tfidf);

// count #nodes in InvertedIndexBST
int nodesInvertedIndex (InvertedIndexBST b);

// check whether a value is in a InvertedIndexBST
int findInvertedIndex (InvertedIndexBST b, char *word);
