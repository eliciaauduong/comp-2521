#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

typedef struct GraphRep {
    int nV;
    int nE;
    char **vertex;
    int **edges;
} GraphRep;

typedef struct GraphRep *Graph;


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

// find the correct position of the vertex and returns the index or -1 if not found
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
    list[size] = strdup(v);
    return size;
}


void showGraph (Graph g, int mode)
{
	assert (g != NULL);
	if (g->nV == 0) {
		puts ("Graph is empty");
		return;
	}

	printf ("Graph has %zu vertices:\n", g->nV);
	if (mode == 1) {
		for (size_t i = 0; i < g->nV; i++) {
			for (size_t j = 0; j < g->nV; j++)
				printf ("%d ", g->edges[i][j]);
			putchar ('\n');
		}
	} else {
		for (size_t i = 0; i < g->nV; i++) {
			printf ("Vertex: %s\n", g->vertex[i]);
			printf ("connects to\n");
			for (size_t j = 0; j < g->nV; j++) {
				if (g->edges[i][j])
					printf ("   %s\n", g->vertex[j]);
			}
		}
	}
}
