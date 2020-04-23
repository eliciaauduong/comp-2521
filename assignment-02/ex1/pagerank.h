typedef struct GraphRep *Graph;
typedef struct pagerankNode *pagerankList;

pagerankList calculatePageRank(Graph g, double d, double diffPR, int maxIterations);	

void printPagerankList(pagerankList pr, char *file);