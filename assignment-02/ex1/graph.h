typedef struct GraphRep {
    int nV;
    int nE;
    char **vertex;
    int **edges;
} GraphRep;

typedef struct GraphRep *Graph;

int vertexPosition (char *v, char** list, int size);
int addVertex(char *v, char **list, int size);
void addEdge(Graph g, char *src, char *dest);

Graph newGraph (int nV);
void dropGraph(Graph g);
void showGraph (Graph g, int mode);