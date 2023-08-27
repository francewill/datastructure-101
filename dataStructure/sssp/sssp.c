#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices)
{
	GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH)); // intialize graph
	G->num_vertices = vertices;
	G->matrix = (int **)malloc(sizeof(int *) * vertices);
	for (int i = 0; i < G->num_vertices; i++)  
	{
		G->matrix[i] = (int *)malloc(sizeof(int) * vertices);
	}
	for (int i = 0; i < G->num_vertices; i++)  // populate graph with zeroes
	{
		for (int j = 0; j < G->num_vertices; j++)
		{
			G->matrix[i][j] = 0;
		}
	}
	return G;
}

/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int u, int v, int w)
{
	G->matrix[u][v] = w;
}

/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dijkstra() function to mark visited nodes
	- 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G)
{
	int *visited = (int *)malloc(sizeof(int) * G->num_vertices);
	for (int i = 0; i < G->num_vertices; i++)  // populate visited array 
	{
		visited[i] = 0;
	}
	return visited;
}

/*
	CREATE DISTANCE
	- returns an integer array called distance - allocate and initialize your array properly
	- this will be used in the dijkstra() function to keep track of the distance of the vertices
	- initialize to 99999 (maximum distance possible)
*/
int *createDistance(GRAPH *G)
{
	int *distance = (int *)malloc(sizeof(int) * G->num_vertices);
	for (int i = 0; i < G->num_vertices; i++)  // populate distance array 
	{
		distance[i] = 99999;
	}
	return distance;
}

/*
	CREATE PARENT
	- returns an integer array dijkstra parent - allocate and initialize your array properly
	- this will be used in the dijisktra() function to keep track of the parent of a visited vertex
	- initialize to -1 (no parent yet)
*/
int *createParent(GRAPH *G)
{
	int *parent = (int *)malloc(sizeof(int) * G->num_vertices);
	for (int i = 0; i < G->num_vertices; i++)  // populate parent array
	{
		parent[i] = -1;
	}
	return parent;
}

/*
	DIJKSTRA
	- implements dijkstra's algorithm to find the shortest path from a source to a target
	- computes for the distance of the path
	- you may create additional functions for the different operations needed in the dijkstra's algorithm
*/
void dijkstra(GRAPH *G, int source, int target) // REVIEW THIS ONE
{
	int *visited = createVisited(G); // create arrays
	int *parent = createParent(G);
	int *distance = createDistance(G);

	int u = source;
	distance[u] = 0;

	for (int i = 0; i < G->num_vertices; i++)
	{
		for (int j = 0; j < G->num_vertices; j++)
		{ // check for the lowest distance
			if (!visited[j])
			{

				if (distance[u] > distance[j])
				{
					u = j;
				}
			}
		}

		visited[u] = 1;  // visit the node with lowest distance

		for (int v = 0; v < G->num_vertices; v++)  // check unvisited neighbors
		{
			if (G->matrix[u][v])
			{
				if (!visited[v])
				{

					if (distance[v] > (G->matrix[u][v] + distance[u]))
					{
						distance[v] = G->matrix[u][v] + distance[u];  // add the distance
						parent[v] = u;
					}
				}
			}
		}
		for (int i = 0; i < G->num_vertices; i++)  // find unvisited node (this step is needed to track the next lowest unvisited node)
		{
			if (!visited[i])
			{
				u = i;
			}
		}
	}
	int *path = (int *)malloc(sizeof(int) * G->num_vertices);  // create the path
	int node, count = 0, dist;

	path[count] = target;
	node = parent[target];	count++;
	path[count] = node;


	while (node != -1)  // adding the remaining paths
	{
		count++;
		node = parent[path[count - 1]];
		path[count] = node;
	}

	dist = distance[target];  // get the distance

	if (dist == 99999)  // prompts
	{
		printf("\nPath from %d to %d is impossible.",source+1,target+1);
	}
	else
	{
		printf("\nYour path from %d to %d: ", source + 1, target + 1);
		for (int i = count - 1; i >= 0; i--)  // print backwards for readability
		{
			printf("%d ", path[i] + 1);
		}
		printf("\nTotal distance: %d", distance[target]);
	}

	// Check the arrays if you want
	
	// printf("\nVisited: ");
	// for (int i = 0; i < G->num_vertices; i++)
	// {
	// 	printf("%d ", visited[i]);
	// }

	// printf("\nDistance: ");
	// for (int i = 0; i < G->num_vertices; i++)
	// {
	// 	printf("%d ", distance[i]);
	// }

	// printf("\nParent: ");
	// for (int i = 0; i < G->num_vertices; i++)
	// {
	// 	printf("%d ", parent[i]);
	// }
}

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G)
{
	for (int i = 0; i < G->num_vertices; i++)
	{
		for (int j = 0; j < G->num_vertices; j++)
		{
			printf("%d     ", G->matrix[i][j]);
		}
		printf("\n");
	}
}

/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G)
{
	for (int i = 0; i < G->num_vertices; i++)
	{
		free(G->matrix[i]);
	}
	free(G->matrix);
}

int main()
{
	char command;
	int vertices, lines, u, v, w, source, target;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while (1)
	{
		scanf(" %c", &command);

		switch (command)
		{
		case '+':
			scanf(" %d %d %d", &u, &v, &w);
			insertEdge(G, u - 1, v - 1, w); // there's a -1 since we use 0-indexing in the arrays
			printf("Successfully inserted edge %d %d\n", u, v);
			break;
		case '#':
			scanf(" %d %d", &source, &target);
			dijkstra(G, source - 1, target - 1);
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