////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    searchList.h                                                            //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Linked list ADT to store pages, number of search terms and pageranks    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//linked list
struct searchNode {
    char *page;
    int searchTerms;
    double pagerank;
    struct searchNode *next;
};
typedef struct searchNode *searchList;

// create a new empty list
searchList createSearchList(void);

// allocate memory for a new node
searchList newSearchNode(char *page, int searchTerms, double pagerank, searchList next);

// add a node in the correct (ordered) position in a linked list
searchList addSearchNode(searchList list, char *page, int searchTerms, double pagerank);

// return the size of a list
int searchListSize(searchList list);
