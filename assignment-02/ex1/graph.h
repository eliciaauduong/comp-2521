////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    graph.h                                                                 //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 2 - Simple Search Engine                          //
//    Graph ADT (Adjacency Matrix)                                            //
//    Adapted from COMP2521 Lab Week 08 								      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef struct GraphRep {
    int nV;
    int nE;
    char **vertex;
    int **edges;
} GraphRep;

typedef struct GraphRep *Graph;

// find the correct position of the vertex
// returns the index or -1 if not found
int vertexPosition (char *v, char** list, int size);

// add vertex to the list of vertices
int addVertex(char *v, char **list, int size);

// add edge from source vertex to destination vertex
void addEdge(Graph g, char *src, char *dest);

// create and allocate memory for a new graph structure
Graph newGraph (int nV);

// free the memory for the graph
void dropGraph(Graph g);
