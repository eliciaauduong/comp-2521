// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/
int *visited;
int pathCheck(Graph g, int src, int dest);
double calculatePR(Graph g, int v);

void rankPopularity(Graph g, int src, double *mnV) {
    visited = (int *)calloc(g->nV, sizeof(int));
    for (int v = 0; v < g->nV; v++){
        visited[v] = -1;
    }
    visited[src] = src;
	for (int i = 0; i < g->nV; i++) {
        if (pathCheck(g, src, i) != 0) {
            printf("%d\n", i);
            mnV[i] = calculatePR(g, i);
        }
    }
	free(visited);
}

double calculatePR(Graph g, int v) {
    double inlinks = 0;
    double outlinks = 0;
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[i][v] != 0) {
            inlinks++;
        }
        if (g->edges[v][i] != 0) {
            outlinks++;
        }
    }
    if (outlinks == 0) {
        outlinks = 0.5;
    }
    return (inlinks / outlinks);

}

int pathCheck(Graph g, int src, int dest) {
    for (int i = 0; i < g->nV; i++) {
        if (adjacent(g, src,i) && visited[i] == -1) {
            visited[i] = src;
            if (i == dest) {
                return 1;
            } 
            else if (pathCheck(g, i, dest) == 1) {
                return 1;
            }
        }
    }
    return 0; 
}