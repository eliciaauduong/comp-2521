////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    pagerank.h                                                              //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Complete functions for part 1 - weighted page ranks                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef struct GraphRep *Graph;
typedef struct pagerankNode *pagerankList;

// implement the given weighted page rank algorithm
pagerankList calculatePageRank(Graph g, double d, double diffPR, int maxIterations);	

// print the pages and associated page ranks to a file pagerankList.txt
void printPagerankList(pagerankList pr, char *file);
