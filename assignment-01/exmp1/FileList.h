// fileList.h 
// linked list interface

typedef struct FileListNode *FileList;

// Create a new empty list
FileList createList (void);

// Create a new node to be added to the list
FileList newListNode (char *file, double tf, FileList next);

// Returns the number of elements in the list
int listLength (FileList list);

// Insert a new file into the right position in the list
// Sorted by alphabetical order
FileList insertList (FileList list, char *file, double tf);
