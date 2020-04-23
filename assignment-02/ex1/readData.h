typedef struct urlNode *urlList;
typedef struct GraphRep *Graph;

// create a set (list) of urls to process by reading data from a file
urlList GetCollection(char *file);

// create empty graph
// for each url in urlList, read url file
// update graph by adding a node and outgoing links
Graph getGraph(urlList list);