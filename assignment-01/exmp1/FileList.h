// fileList.h 
// linked list interface

typedef struct FileListNode *FileList;

// Create a new empty list
FileList createFileList (void);

// Create a new node to be added to the list
FileList newFileListNode (char *file, double tf, FileList next);

// Returns the number of elements in the list
int fileListLength (FileList list);

// Insert a new file into the right position in the list
// Sorted by alphabetical order
FileList insertFileList (FileList list, char *file, double tf);
