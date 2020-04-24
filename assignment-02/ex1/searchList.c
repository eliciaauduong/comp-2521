#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "searchList.h"

// Create a new empty list
searchList createSearchList(void) {
    return NULL;
}

// Allocate memory for a new node
searchList newSearchNode(char *page, int searchTerms, double pagerank, searchList next) {
    searchList new = malloc(sizeof(*new));
    new->page = page;
    new->searchTerms = searchTerms;
    new->pagerank = pagerank;
    new->next = next;
    return new;
}

// Add a node in the correct (ordered) position in a linked list
// sort by descending order of search terms
// then sort by descending order of weighted pagerank
searchList addSearchNode(searchList list, char *page, int searchTerms, double pagerank) {
    // empty list
    if (list == NULL) {
        return newSearchNode(page, searchTerms, pagerank, NULL);
    }

    // if page comes before the first node in the list
    if (searchTerms > list->searchTerms) {
        return newSearchNode(page, searchTerms, pagerank, list);
    }
    if (searchTerms == list->searchTerms) {
        if (pagerank > list->pagerank) {
            return newSearchNode(page, searchTerms, pagerank, list);
        }
        else if (pagerank < list->pagerank) {
            searchList new = newSearchNode(page, searchTerms, pagerank, list->next);
            list->next = new;
            return list;
        }
    }
    // middle of list
    searchList curr = list;
    while (curr->next != NULL) {
        // if page comes before the next node in the list
        if (searchTerms > curr->next->searchTerms) {
            searchList new = newSearchNode(page, searchTerms, pagerank, curr->next);
            curr->next = new;
            return list;
        }
        
        if (searchTerms == curr->searchTerms) {
            if (pagerank > curr->next->pagerank) {
                searchList new = newSearchNode(page, searchTerms, pagerank, curr->next);
                curr->next = new;           
                return list;
            } else if (pagerank < curr->next->pagerank) {
                while (curr->next->next != NULL 
                && curr->next->next->searchTerms == searchTerms
                && pagerank < curr->next->pagerank) {
                    curr = curr->next;
                }
                searchList new = newSearchNode(page, searchTerms, pagerank, curr->next->next);
                curr->next->next = new;
                return list;
            }
            
        }
        curr = curr->next;
    }

    // add to the end of the list
    curr = list;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    if (searchTerms < curr->searchTerms) {
        searchList new = newSearchNode(page, searchTerms, pagerank, NULL);
        curr->next = new;
        return list;
    }
    if (searchTerms == curr->searchTerms) {
        
        if (pagerank > curr->pagerank) {
            searchList new = newSearchNode(page, searchTerms, pagerank, curr);
            curr->next = new;
            return list;
        } else if (pagerank < curr->pagerank) {
            searchList new = newSearchNode(page, searchTerms, pagerank, NULL);
            curr->next = new;
            return list;
        }
    }

    return list;
}

// Return the size of a list
int searchListSize(searchList list) {
    searchList curr = list;
    int len = 0;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

// return the node of a search term if found
int findSearchNode(searchList list, char *page) {
    searchList curr = list;
    while (curr != NULL) {
        if (strcmp(page, curr->page) == 0) {
            return 1;
        }
    }
    return 0;
}