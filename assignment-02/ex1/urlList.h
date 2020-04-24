////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    urlList.h                                                               //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    List ADT to store a list of urls                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// linked list
struct urlNode {
    char *file;
    struct urlNode *next;
};
typedef struct urlNode *urlList;

// create a new empty list
urlList createUrlList(void);

// allocate memory for a new node
urlList newUrlNode(char *file, urlList next);

// add a node in the correct (ordered) position in a linked list
urlList addUrlNode(urlList list, char *file);

// return the size of a list
int urlListSize(urlList list);
