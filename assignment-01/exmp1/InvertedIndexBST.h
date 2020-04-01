////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    InvertedIndexBST.h                                                      //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    Adapted from source: COMP2521 Lab 03 BSTree.h                           //
//    COMP2521 - Assignment 1 - Information Retrieval                         //
//    Binary search tree interface for storing the inverted index             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef struct InvertedIndexNode *InvertedIndexBST;

// create an empty InvertedIndexBST
InvertedIndexBST newInvertedIndex (void);

// insert a new value into a InvertedIndexBST
InvertedIndexBST insertInvertedIndex (InvertedIndexBST b, char *word, char *filename, double tfidf);

// count #nodes in InvertedIndexBST
int nodesInvertedIndex (InvertedIndexBST b);

// check whether a value is in a InvertedIndexBST
InvertedIndexBST findInvertedIndex (InvertedIndexBST b, char *word);
