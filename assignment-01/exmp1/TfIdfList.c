////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    TfIdfList.c                                                             //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 1 - Information Retrieval                         //
//    Linked list implementation for storing a list of files and tdidf values //
//                                                                            //
/////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TfIdfList.h"
#include "invertedIndex.h"

// Create a new empty list
TfIdfList createTfIdfList (void) {
    return NULL;
}

// Create a new node to be added to the list
TfIdfList newTfIdfListNode (char *file, double tfidf, TfIdfList next) {
    TfIdfList new = malloc(sizeof(*new));
    new->filename = file;
    new->tfIdfSum = tfidf;
    new->next = next;
    return new;
}

// Returns the number of elements in the list
int tfIdflistLength (TfIdfList list) {
    if (list == NULL) {
        return 0;
    }

    int len = 0;
    while (list != NULL) {
        len++;
        list = list->next;
    }

    return len;
}

// Insert a new file into the right position in the list
// Sorted by alphabetical order
TfIdfList insertTfIdfList (TfIdfList list, char *file, double tfidf) {
    // empty list
    if (list == NULL) {
        return newTfIdfListNode(file, tfidf, NULL);
    }

    // start of list
    // if tfidf is larger than first node, add it to the front of the list
    if (tfidf > list->tfIdfSum) {
        return newTfIdfListNode(file, tfidf, list);
    }
    // if tfidf is the same as the first node in the list
    if (tfidf == list->tfIdfSum) {
        // compare file names and add in ascending order
        if (strcmp(file, list->filename) < 0) {
            return newTfIdfListNode(file, tfidf, list);
        } 
        else if (strcmp(file, list->filename) > 0) {
            TfIdfList new = newTfIdfListNode(file, tfidf, list->next);
            list->next = new;
            return list;
        }
    }

    // middle of list
    TfIdfList curr = list;
    while (curr->next != NULL) {
        // if tfidf is bigger than the next node, add in place
        if (tfidf > curr->next->tfIdfSum) {
            TfIdfList new = newTfIdfListNode(file, tfidf, curr->next);
            curr->next = new;
            return list;
        }

        // if tfidf is the same as the current node
        // compare filenames
        if (curr->tfIdfSum == tfidf) {
            // add in alphabetical order
            if (strcmp(file, curr->next->filename) < 0) {
                TfIdfList new = newTfIdfListNode(file, tfidf, curr->next);
                curr->next = new;
                return list;
            } 
            else if (strcmp(file, curr->next->filename) > 0) {
                while (curr->next->next->tfIdfSum == tfidf 
                    && strcmp(file, curr->next->filename) > 0) {
                    curr = curr->next;
                }
                TfIdfList new = newTfIdfListNode(file, tfidf, curr->next->next);
                curr->next->next = new;
                return list;
            }

        }
        curr = curr->next;
    }

    // end of list
    curr = list;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // if tfidf is smaller than the last node
    if (tfidf < curr->tfIdfSum) {
        TfIdfList new = newTfIdfListNode(file, tfidf, NULL);
        curr->next = new;
        return list;
    }
    
    // if tfidf is the same as the last node in the list
    if (tfidf == curr->tfIdfSum) {
        // compare file names and add in ascending order
        if (strcmp(file, curr->filename) < 0) {
            return newTfIdfListNode(file, tfidf, curr);
        } 
        else if (strcmp(file, curr->filename) > 0) {
            TfIdfList new = newTfIdfListNode(file, tfidf, NULL);
            curr->next = new;
            return list;
        }
    }
    return list;
}

// Check if a file is in a list
// Return 0 if not in list
// Return 1 if in list
int inTfIdf(TfIdfList list, char *file) {
    if (list == NULL) {
        return 0;
    }

    TfIdfList curr = list;
    while (curr != NULL) {
        if (strcmp(file, curr->filename) == 0) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

// For a given file already in the tfidf list
// Update the value of tfidf
TfIdfList updateTfIdfList(TfIdfList list, char *file, double tfidf) {
    TfIdfList curr = list;
    while (curr != NULL) {
        if (strcmp(file, curr->filename) == 0) {
            curr->tfIdfSum += tfidf;
        }
        curr = curr->next;
    }
    return list;
}
