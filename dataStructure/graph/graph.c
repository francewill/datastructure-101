#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"


/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices){

}

/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int u, int v){

}

/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dfs() function to mark visited nodes
	- 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G){
    
}

/*
	DFS
	- implements a non-recursive DFS traversal
	- you may use the functions in the stack.h file 
*/
void dfs(GRAPH *G, int start){
    
}

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G){
    
}

/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G){
    
}


int main() {
	char command;
	int vertices, lines, u, v;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d", &u, &v);
				insertEdge(G, u-1, v-1); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				printf("\nDFS: ");
				dfs(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'Q':
				freeMatrix(G);
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}