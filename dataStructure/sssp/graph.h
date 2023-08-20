//Structure for the graph
typedef struct graph_tag {
	int **matrix; //holder of the adjacency matrix
	int num_vertices; //holds the vertex count
} GRAPH;

/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices);


/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int u, int v, int w);


/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dijkstra() function to mark visited nodes
	- 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G);


/*
	CREATE DISTANCE
	- returns an integer array called distance - allocate and initialize your array properly
	- this will be used in the dijkstra() function to keep track of the distance of the vertices
	- initialize to 99999 (maximum distance possible)
*/
int *createDistance(GRAPH *G);


/*
	CREATE PARENT
	- returns an integer array dijkstra parent - allocate and initialize your array properly
	- this will be used in the dijisktra() function to keep track of the parent of a visited vertex
	- initialize to -1 (no parent yet)
*/
int *createParent(GRAPH *G);


/*
	DIJKSTRA
	- implements dijkstra's algorithm to find the shortest path from a source to a target
	- computes for the distance of the path
	- you may create additional functions for the different operations needed in the dijkstra's algorithm
*/
void dijkstra(GRAPH *G, int source, int target);

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G);


/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G);
