#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "searchPagerank.h"
#include "searchList.h"

static char *strip(char *word);
searchList searchPagerank(void);

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

void findSearchPages(int numSearch, char **searchwords) {
    FILE *invIndex = fopen("invertedIndex.txt", "r");
    FILE *found = fopen("foundPages.txt", "w");
    char line[1000];
    while (fgets(line, 1000, invIndex)) {
        char word[1000];
        sscanf(line, "%s", word);
        for (int i = 0; i < numSearch; i++) {
            if (strcmp(word, searchwords[i]) == 0) {
                fprintf(found,"%s", line);
            }
        }
    }   
    fclose(invIndex);
    fclose(found);
}

double findPagerank(char *page) {
    FILE *pr = fopen("pagerankList.txt", "r");
    char line[1000];
    
    while (fgets(line, 1000, pr) != NULL) {
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

searchList searchPagerank(void) {
    FILE *urls = fopen("foundPages.txt", "r");
    searchList sList = createSearchList();
    char word[1000];
    while (fscanf(urls, "%s", word) != EOF) {
        double pr = findPagerank(word);
        char *url = calloc(1000, sizeof(char));
        strcpy(url, word);
        int check = 0;
        if (pr != 0) {
            int count = countSearch(url);
            sList = addSearchNode(sList, url, count, pr); 
        }
    }
    return sList;
}

int countSearch(char *page) {
    FILE *search = fopen("foundPages.txt", "r");
    int count = 0;
    char word[1000];
    while (fscanf(search, "%s", word) != EOF) {
        if (strcmp(word, page) == 0) {
            count++;
        }
    }
    return count;
}

static char *strip(char *word) {
    int len = strlen(word);
    if (word[len + 1] == '\n') {
        word[len + 1] = '\0';
        len--;
    }
    return word;
}
// write a simple search engine that given search terms (words) as commandline arguments, find pages with one or more search terms and outputs (to stdout) top 30 pages in descending order of number of search terms found and then within each group, descending order of weighted pagerank