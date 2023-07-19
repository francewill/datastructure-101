#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isBalanced.h"

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
        printf("\nStack is empty!\n");
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
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->value = data;
    return node;
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
    LIST *L = NULL;
    L = (LIST *)malloc(sizeof(LIST));
    L->head = NULL;
    return L;
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
        printf("\nStack is empty!\n");
    }
    else
    {
        int val;
        NODE *temp = L->head;
        L->head = L->head->next;
        val = temp->value;
        free(temp);
        return val;
    }
}

/*
** isBalanced()
** requirements: a string `expr`
** results:
    checks the balance of parentheses using stack operations
    returns 1 if the parentheses are balanced
    otherwise returns 0
*/
int isBalanced(char *expr)
{
    LIST *L = createStack();
    int val;

    for (int i = 0; i < strlen(expr); i++)
    {
        if ((int)expr[i] == 40)
        {
            push(L, createNode((int)expr[i]));
        }
        else if ((int)expr[i] == 41)
        {
            if (isEmpty(L))
            {
                return 0;
            }
            else
            {
                val = pop(L);
            }
        }
    }
    if (isEmpty(L))
    {
        return 1;
    }
}

int main()
{
    // LIST *L= createStack();
    // push(L,createNode(1));
    // push(L,createNode(2));
    // push(L,createNode(3));
    // push(L,createNode(4));
    // push(L,createNode(5));
    // printStack(L);
    char userInput[50];
    while (1)
    {

        printf("\nEnter expression: ");
        scanf("%s", userInput);

        if (isBalanced(userInput))
        {
            printf("\nThe parenthesis are balance.\n");
        }
        else
        {
            printf("\nThe parenthesis are not balance.\n");
        }
      }

    return 0;
}