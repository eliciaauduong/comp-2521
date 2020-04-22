// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);

	// checks if a path is found or not
	int found = 0;
	int *visited = (int *)calloc(g->nV, sizeof(int));
	visited[dest] = dest;

	Queue flights = newQueue();
	// start from the destination and work backwards
	QueueJoin(flights, dest);

	// while there are still tripss to fly
	while (!QueueIsEmpty(flights)) {
		// get first item
		Vertex temp = QueueLeave(flights);
		// if first item is source
		// trip is complete
		if (temp == src) {
			found = 1;
			break;
		}
		// otherwise check all the other vertex in the graph
		for (int i = 0; i < g->nV; i++) {
			// check if the vertex has not been visited
			// check if there is no link between the first item and current item
			// check if the distance between the edges are less thnan maximum distance
			if ((visited[i] == 0) 
			&& (g->edges[temp][i] != 0) 
			&& (g->edges[temp][i] < max)) {
				// if the vertex meets above criteria, add to list of flights to check
				QueueJoin(flights, i);
				visited[i] = temp;
			}
		}
	}

	// if no path is found
	if (found == 0) {
		dropQueue(flights);
		free(visited);
		return 0;
	}

	// count all items in route starting from the source, moving to destination
	int location = src;
	int len = 0;
	path[len] = src;
	len++;
	while(location != dest) {
		location = visited[location];
		path[len] = location;
		len++;
	}

	dropQueue(flights);
	free(visited);
	return len;
}
