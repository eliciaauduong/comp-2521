////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    searchPagerank.c                                                        //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Complete functions for part 2 - search engine                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "searchPagerank.h"
#include "searchList.h"

#define MAX 1000

int main(int argc, char *argv[]) {
    
    // search terms as commandline arguments
    char **searchwords = calloc(argc, sizeof(char *));
    int numSearch = 0;
    for (int i = 0; i < (argc - 1); i++) {
        searchwords[i] = argv[i + 1];
        numSearch++;
    }
    // find pages with one or more search terms
    findSearchPages(numSearch, searchwords);
    searchList sList = searchPagerank();

    // output the top 30 pages 
    // descending order of number of search terms
    // then descending order of weighted pagerank
    searchList curr = sList;
    int count = 0;
    while (curr != NULL && count < 30) {
        if (curr->next != NULL) {
            if (strcmp(curr->page, curr->next->page) == 0) {
                curr = curr->next;
            }
        }
        printf("%s\n", curr->page);
        curr = curr->next;
        count++;
    }
}

// create a linked list of page, number of search words and pagerank
// sorted in descending order of search terms
// then descending order of pagerank
searchList searchPagerank(void) {
    FILE *urls = fopen("foundPages.txt", "r");
    searchList sList = createSearchList();
    char word[MAX];
    while (fscanf(urls, "%s", word) != EOF) {
        double pr = findPagerank(word);
        char *url = calloc(MAX, sizeof(char));
        strcpy(url, word);
        if (pr != 0) {
            int count = countSearch(url);
            sList = addSearchNode(sList, url, count, pr); 
        }
    }
    return sList;
}

// from invertedIndex.txt
// print all lines with search words to a new file foundPages.txt
void findSearchPages(int numSearch, char **searchwords) {
    FILE *invIndex = fopen("invertedIndex.txt", "r");
    FILE *found = fopen("foundPages.txt", "w");

    // scan each line of invertedIndex.txt
    char line[MAX];
    while (fgets(line, MAX, invIndex)) {
        char word[MAX];
        sscanf(line, "%s", word);
        // if the line contains a searchword
        for (int i = 0; i < numSearch; i++) {
            if (strcmp(word, searchwords[i]) == 0) {
                // print to foundPages.txt
                fprintf(found,"%s", line);
            }
        }
    }   

    fclose(invIndex);
    fclose(found);
}

// find the pagerank of a given page using pagerankList.txt
double findPagerank(char *page) {
    FILE *pr = fopen("pagerankList.txt", "r");
    char line[MAX];
    
    while (fgets(line, MAX, pr) != NULL) {
        int cnt = 0;
        char **prLine = calloc(3, sizeof(char *));
        char *token;
        token = strtok(line, ", ");
        while (token != NULL) {
            prLine[cnt] = token;
            token = strtok(NULL, ", ");
            cnt++;
        }
        if (strcmp(page, prLine[0]) == 0) {
            return atof(prLine[2]);
        }
    }
    fclose(pr);
    return 0;
}

// count the number of searchwords that a given page contains
int countSearch(char *page) {
    FILE *search = fopen("foundPages.txt", "r");
    int count = 0;
    char word[MAX];
    while (fscanf(search, "%s", word) != EOF) {
        if (strcmp(word, page) == 0) {
            count++;
        }
    }
    return count;
}
