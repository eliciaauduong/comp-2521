////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    searchPagerank.h                                                        //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Complete functions for part 2 - search engine                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef struct searchNode *searchList;

// create a linked list of page, number of search words and pagerank
// sorted in descending order of search terms
// then descending order of pagerank
searchList searchPagerank(void);

// from invertedIndex.txt
// print all lines with search words to a new file foundPages.txt
void findSearchPages(int numSearch, char **searchwords);

// find the pagerank of a given page using pagerankList.txt
double findPagerank(char *page);

// count the number of searchwords that a given page contains
int countSearch(char *page);
