#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "urlList.h"

// Create a new empty list
urlList createUrlList(void) {
    return NULL;
}

// Allocate memory for a new node
urlList newUrlNode(char *file, urlList next) {
    urlList new = malloc(sizeof(*new));
    new->file = file;
    new->next = next;
    return new;
}

// Add a node in the correct (ordered) position in a linked list
urlList addUrlNode(urlList list, char *file) {
    // empty list
    if (list == NULL) {
        return newUrlNode(file, NULL);
    }
    
    // if file comes before the first node in the list
    if (strcmp(file, list->file) < 0) {
        urlList tmp = list;
        list = newUrlNode(file, tmp);
        return list;
    }

    // middle of list
    urlList curr = list;
    while (curr->next != NULL) {
        // if file comes before the next node in the list
        if (strcmp(file, curr->next->file) < 0) {
            urlList tmp = curr->next;
            curr->next = newUrlNode(file, tmp);
            return list;
        }
        curr = curr->next;
    }
    
    // add to the end of the list
    curr = list;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newUrlNode(file, NULL);
    return list;
}

// Return the size of a list
int urlListSize(urlList list) {
    urlList curr = list;
    int len = 0;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}