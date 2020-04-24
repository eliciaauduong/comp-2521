////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    graph.c                                                                 //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Graph ADT (Adjacency Matrix)                                            //
//    Adapted from COMP2521 Lab Week 08 								      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

// find the correct position of the vertex
// returns the index or -1 if not found
int vertexPosition (char *v, char** list, int size) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (strcmp(list[i], v) == 0) {
                return i;
            }
        }
    }
    return -1;
}

// add vertex to the list of vertices
int addVertex(char *v, char **list, int size) {
    list[size] = v;
    return size;
}

// add edge from source vertex to destination vertex
void addEdge(Graph g, char *src, char *dest) {
    int v = vertexPosition(src, g->vertex, g->nV);
    int w = vertexPosition(dest, g->vertex, g->nV);
    if (v < 0) {
        v = addVertex(src, g->vertex, g->nV);
        g->nV++;
    }
    if (w < 0) {
        w = addVertex(dest, g->vertex, g->nV);
        g->nV++;
    }
    if (g->edges[v][w] != 0 || v == w) {
        return;
    }
    g->edges[v][w] = 1;
    g->nE++;
}

// create and allocate memory for a new graph structure
Graph newGraph (int nV) {
    assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = 0, .nE = 0 };

    new->vertex = calloc (nV, sizeof (char *));
    assert(new->vertex != NULL);
	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);

        for (int w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}

	return new;
}

// free the memory for the graph
void dropGraph(Graph g) {
    assert (g != NULL);
    for (int v = 0; v < g->nV; v++)
		free (g->vertex[v]);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
    free (g->vertex);
	free (g->edges);
	free (g);
}
