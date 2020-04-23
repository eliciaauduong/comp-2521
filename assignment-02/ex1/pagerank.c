#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "pagerank.h"
#include "readData.h"
#include "urlList.h"
#include "graph.h"
#include "pagerankList.h"

static double countLinks(Graph g, int link, int mode);
static double zeroCheck(double degree);
static double weightedIn(Graph g, int v, int u);
static double weightedOut(Graph g, int v, int u);

int main(int argc, char *argv[]) {
    // store command-line arguments to be used in calculatePagerank
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    urlList list = GetCollection("collection.txt");
    Graph urlGraph = getGraph(list);
    pagerankList prList = calculatePageRank(urlGraph, d, diffPR, maxIterations);
    printPagerankList(prList, "pagerankList.txt");
}

pagerankList calculatePageRank(Graph g, double d, double diffPR, int maxIterations) {
    // number of urls in the collection
    double nUrl = g->nV; 
    
    // iteration 0 pageranks for each vertex
    double *iPagerank = calloc(nUrl, sizeof(double));
    
    for (int i = 0; i < nUrl; i++) {
        iPagerank[i] = (1 / nUrl);
    }

    double *iPagerankNext = calloc(nUrl, sizeof(double));

    int iteration = 0;
    double diff = diffPR;

    while (iteration < maxIterations && diff >= diffPR) {
        
        for (int i = 0; i < nUrl; i++) {
            // M is a set containing nodes with outgoing links to pi
            double jPagerank = 0;
            for (int j = 0; j < nUrl; j++) {
                // sum of (pagerank * in * out) for every outlink to pi
                if (g->edges[j][i] != 0) {
                    jPagerank += (iPagerank[j] * weightedIn(g, j, i) * weightedOut(g, j, i));
                }
            }
            if (jPagerank == 0) {
                jPagerank = 1;
            }
            iPagerankNext[i] = (((1-d) / nUrl) + (d * jPagerank));
        }
        
        diff = 0;
        for (int i = 1; i < nUrl; i++) {
            diff += fabs(iPagerankNext[i] - iPagerank[i]);
        }
        // t+1 becomes t for the next iteration
        for (int i = 0; i < nUrl; i++) {
            iPagerank[i] = iPagerankNext[i];
        }
        iteration++;
    }

    pagerankList prList = createPagerankList();
    for (int i = 0; i < nUrl; i++) {
        prList = addPagerankNode(prList, g->vertex[i], countLinks(g, i, 1), iPagerank[i]);
    }
    
    return prList;
}

void printPagerankList(pagerankList pr, char *file) {
    FILE *prFile = fopen(file, "w");
    pagerankList curr = pr;
    while (curr != NULL) {
        fprintf(prFile, "%s, %d, %.7f\n", curr->file, curr->outlinks , curr->pagerank);
        curr = curr->next;
    }
    fclose(prFile);
}

// calculate the number of links connected to or from a given link
// mode 0 is inlink; mode 1 is outlink
static double countLinks(Graph g, int link, int mode) {
    // calculate inlink
    if (mode == 0) {
        int inlink = 0;
        for (int i = 0; i < g->nV; i++) {
            if (g->edges[i][link] != 0) {
                inlink++;
            }
        }
        return (double)inlink;
    }

    // calculate outlink
    if (mode == 1) {
        double outlink = 0;
        for (int i = 0; i < g->nV; i++) {
            if (g->edges[link][i] != 0) {
                outlink++;
            }
        }
        return outlink;
    }
}

// if a given degree is 0, change it to 0.5
static double zeroCheck(double degree) {
    if (degree == 0) {
        return 0.5;
    }
    return degree;
}

static double weightedIn(Graph g, int v, int u) {
    // wIn = (u inlinks) / (sum of all inlinks of reference pages of v)
    double uLink = zeroCheck(countLinks(g, u, 0));
    double vLink = 0;
   
    // for every vertex in the graph
    for (int i = 0; i < g->nV; i++) {
        // find all reference pages of v (all pages with links from v)
        if (g->edges[v][i] != 0) {
            // sum the inlinks of each reference page
            vLink += zeroCheck(countLinks(g, i, 0));
        }
    }
    return (uLink / vLink);
}

static double weightedOut(Graph g, int v, int u) {
    // wOut = (u outlinks) / (sum of all outlinks of reference pages of v)
    double uLink = zeroCheck(countLinks(g, u, 1));
    double vLink = 0;

    // for every vertex in the graph
    for (int i = 0; i < g->nV; i++) {
        // find all reference pages of v (all pages with links from v)
        if (g->edges[v][i] != 0) {
            // sum the outlinks of each refence page
            vLink += zeroCheck(countLinks(g, i, 1));
        }
    }

    return (uLink / vLink);
}