

//linked list
struct pagerankNode {
    char *file;
    int outlinks;
    double pagerank;
    struct pagerankNode *next;
};
typedef struct pagerankNode *pagerankList;

// Create a new empty list
pagerankList createPagerankList(void);

// Allocate memory for a new node
pagerankList newPagerankNode(char *file, int outlink, double pr, pagerankList next);

// Add a node in the correct (ordered) position in a linked list
pagerankList addPagerankNode(pagerankList list, char *file, int outlink, double pr);

// Return the size of a list
int pagerankListSize(pagerankList list);