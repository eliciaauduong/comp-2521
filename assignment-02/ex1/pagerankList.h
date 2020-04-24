////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    pagerankList.h                                                          //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Linked list ADT to store pages, outlinks and pageranks                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//linked list
struct pagerankNode {
    char *file;
    int outlinks;
    double pagerank;
    struct pagerankNode *next;
};
typedef struct pagerankNode *pagerankList;

// create a new empty list
pagerankList createPagerankList(void);

// allocate memory for a new node
pagerankList newPagerankNode(char *file, int outlink, double pr, pagerankList next);

// add a node in the correct (ordered) position in a linked list
pagerankList addPagerankNode(pagerankList list, char *file, int outlink, double pr);

// return the size of a list
int pagerankListSize(pagerankList list);
