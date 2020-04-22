#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "readData.h"
#include "urlList.h"
#include "graph.h"

#define MAX_URL 1000

// create a set (list) of urls to process by reading data from a file
urlList GetCollection(char *file) {
    FILE *collection = fopen(file, "r");
    urlList list = createUrlList();

    char filename[MAX_URL];
    while (fscanf(collection, "%s", filename) != EOF) {
        char *files = (char *)calloc(MAX_URL, sizeof(char));
        strcpy(files, filename);
        list = addUrlNode(list, files);
    }

    fclose(collection);
    return list; 
}

// create empty graph
// for each url in urlList, read url file
// update graph by adding a node and outgoing links
Graph getGraph(urlList list) {
    // create empty graph
    int graphSize = urlListSize(list);
    Graph urlGraph = newGraph(graphSize);

    // for each url in urlList
    urlList curr = list;
    while (curr != NULL) {
        // change file name with .txt at the end
        char file[MAX_URL];
        strcpy(file, curr->file);
        strcat(file, ".txt");
        // open url file
        FILE *urlFile = fopen(file, "r");
        // read and ignore this line
        fscanf(urlFile, "#start Section-1");
        // scan in all the outgoing links
        char link[MAX_URL];
        while ((fscanf(urlFile, "%s", link) == 1) && (strcmp(link, "#end") != 0)) {
            
            char *urlLink = (char *)calloc(MAX_URL, sizeof(char));
            strcpy(urlLink, link);
            // update graph by adding node and outgoing links
            addEdge(urlGraph, curr->file, urlLink);
        }
        printf("\n");
        fclose(urlFile);
        curr = curr->next;
    }
    return urlGraph;
}