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
GRAPH *createGraph(int vertices)
{
    GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH));
    G->num_vertices = vertices;
    G->matrix = (int **)malloc(sizeof(int *) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        G->matrix[i] = (int *)malloc(sizeof(int) * vertices);
    }
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
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
void insertEdge(GRAPH *G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;
}

/*
    CREATE VISITED
    - returns an integer array called visited - allocate and initialize your array properly
    - this will be used in the dfs() function to mark visited nodes
    - 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G)
{

    int *visited = (int *)malloc(sizeof(int) * G->num_vertices);
    for (int i = 0; i < G->num_vertices; i++)
    {
        visited[i] = 0;
    }
    return visited;
}

// Stack functions

/*
** printStack()
** requirements: none
** results:
    if list is empty, prints "*empty*"
    otherwise, prints the contents of a list
*/
void printStack(LIST *L)
{
    if (isEmpty(L))
    {
        printf("\nStack is empty\n");
    }
    else
    {
        for (NODE *temp = L->head; temp != NULL; temp = temp->next)
        {
            printf("%d ", temp->value);
        }
    }
}

/*
** createNode()
** requirements: an integer data
** results:
    creates an empty node with value `data`
    initializes fields of the structure
    returns the created node
*/
NODE *createNode(int data)
{
    NODE *temp = (NODE *)malloc(sizeof(NODE));
    temp->next = NULL;
    temp->value = data;
    return temp;
}

/*
** createStack()
** requirements: none
** results:
    creates an empty list
    initializes `head` field of the structure
    returns the created list
*/
LIST *createStack()
{
    LIST *S = (LIST *)malloc(sizeof(LIST));
    S->head = NULL;
    return S;
}

/*
** isEmpty()
** requirements: none
** results:
    returns 1 if the list is empty
    otherwise returns 0
*/
int isEmpty(LIST *L)
{
    if (L->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
** push()
** requirements: a list and a node to be inserted
** results:
    inserts `node` before the current `head` of the list
*/
void push(LIST *L, NODE *node)
{
    node->next = L->head;
    L->head = node;
}

/*
** pop()
** requirements: a list that must not be empty
** results:
    deletes the `head` node of the list
    returns the value of the deleted node
*/
int pop(LIST *L)
{
    if (isEmpty(L))
    {
        printf("\nStack is empty\n");
        return -1;
    }
    else
    {
        NODE *del = L->head;
        int val = del->value;
        L->head = del->next;
        free(del);
        return val;
    }
}

/*
    DFS
    - implements a non-recursive DFS traversal
    - you may use the functions in the stack.h file
*/
void dfs(GRAPH *G, int start)
{
    LIST *S = createStack();         // create a stack
    int *visited = createVisited(G); // create the visited array to track visited vertex
    push(S, createNode(start));  // push the start node

    do  // loop
    {
        int u = pop(S);  // pop the node in stack
        if (!visited[u])  // check node that is not visited
        {
            visited[u] = 1;  // mark them visited
            printf("%d ", u + 1);  // print it

            for (int v = G->num_vertices - 1; v >= 0; v--)  // loop reversely so we can prioritize smallest index value
            {
                if (G->matrix[u][v])  // find adjacent
                {
                    if (!visited[v])  // if not visited then push
                    {
                        push(S, createNode(v));
                    }
                }
            }
        }

    } while (!isEmpty(S));
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
}

int main()
{
    char command;
    int vertices, lines, u, v;

    scanf("%d", &vertices);
    GRAPH *G = createGraph(vertices);

    while (1)
    {
        scanf(" %c", &command);

        switch (command)
        {
        case '+':
            scanf(" %d %d", &u, &v);
            insertEdge(G, u - 1, v - 1); // there's a -1 since we use 0-indexing in the arrays
            printf("Successfully inserted edge %d %d\n", u, v);
            break;
        case '#':
            printf("\nDFS: ");
            dfs(G, 0); // 0 is the initial value since we use 0-indexing (it still represents vertex 1)
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