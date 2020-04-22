

//linked list
struct urlNode {
    char *file;
    struct urlNode *next;
};
typedef struct urlNode *urlList;

// Create a new empty list
urlList createUrlList(void);

// Allocate memory for a new node
urlList newUrlNode(char *file, urlList next);

// Add a node in the correct (ordered) position in a linked list
urlList addUrlNode(urlList list, char *file);

// Return the size of a list
int urlListSize(urlList list);