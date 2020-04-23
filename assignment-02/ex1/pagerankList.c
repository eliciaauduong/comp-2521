#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pagerankList.h"

// Create a new empty list
pagerankList createPagerankList(void) {
    return NULL;
}

// Allocate memory for a new node
pagerankList newPagerankNode(char *file, int outlink, double pr, pagerankList next) {
    pagerankList new = malloc(sizeof(*new));
    new->file = file;
    new->outlinks = outlink;
    new->pagerank = pr;
    new->next = next;
    return new;
}

// Add a node in the correct (ordered) position in a linked list
pagerankList addPagerankNode(pagerankList list, char *file, int outlink, double pr) {
    // empty list
    if (list == NULL) {
        return newPagerankNode(file, outlink, pr, NULL);
    }
    
    // if file comes before the first node in the list
    if (pr > list->pagerank) {
        pagerankList tmp = list;
        list = newPagerankNode(file, outlink, pr, tmp);
        return list;
    }

    // middle of list
    pagerankList curr = list;
    while (curr->next != NULL) {
        // if file comes before the next node in the list
        if (pr > curr->next->pagerank) {
            pagerankList tmp = curr->next;
            curr->next = newPagerankNode(file, outlink, pr, tmp);
            return list;
        }
        curr = curr->next;
    }
    
    // add to the end of the list
    curr = list;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newPagerankNode(file, outlink, pr, NULL);
    return list;
}

// Return the size of a list
int pagerankListSize(pagerankList list) {
    pagerankList curr = list;
    int len = 0;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}