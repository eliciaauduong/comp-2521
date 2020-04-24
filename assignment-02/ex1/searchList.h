//linked list
struct searchNode {
    char *page;
    int searchTerms;
    double pagerank;
    struct searchNode *next;
};
typedef struct searchNode *searchList;

// Create a new empty list
searchList createSearchList(void);

// Allocate memory for a new node
searchList newSearchNode(char *page, int searchTerms, double pagerank, searchList next);

// Add a node in the correct (ordered) position in a linked list
searchList addSearchNode(searchList list, char *page, int searchTerms, double pagerank);

// Return the size of a list
int searchListSize(searchList list);

// return the node of a search term if found
int findSearchNode(searchList list, char *page);