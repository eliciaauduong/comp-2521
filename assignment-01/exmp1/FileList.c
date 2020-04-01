////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    FileList.c                                                              //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 1 - Information Retrieval                         //
//    Linked list implementation for storing a list of files                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileList.h"
#include "invertedIndex.h"

// Create a new empty list
FileList createFileList (void) {
    return NULL;
}

// Create a new node to be added to the list
FileList newFileListNode (char *file, double tf, FileList next) {
    FileList new = malloc(sizeof(*new));
    new->filename = file;
    new->tf = tf;
    new->next = next;
    return new;
}

// Returns the number of elements in the list
int fileListLength (FileList list) {
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
FileList insertFileList (FileList list, char *file, double tf) {
    // empty list
    if (list == NULL) {
        return newFileListNode(file, tf, NULL);
    }

    // start of list
    if (strcmp(file, list->filename) == 0) {
        return list;
    }
    
    if (strcmp(file, list->filename) < 0) {
        FileList tmp = list;
        list = newFileListNode(file, tf, tmp);
        return list;
    }

    // middle of list
    FileList curr = list;
    while (curr->next != NULL) {
        if (strcmp(file, curr->next->filename) == 0) {
            return list;
        }
        
        if (strcmp(file, curr->next->filename) < 0) {
            FileList tmp = curr->next;
            curr->next = newFileListNode(file, tf, tmp);
            return list;
        }
        curr = curr->next;
    }

    // end of list
    if (strcmp(file, list->filename) == 0) {
        return list;
    } else {
        FileList curr = list;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newFileListNode(file, tf, NULL);
        return list;
    }

}