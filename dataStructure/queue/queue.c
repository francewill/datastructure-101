#include<stdio.h>
#include<stdlib.h>
#include"queue.h"


/*
** printQueue()
** requirements: none
** results:
	if list is empty, prints "*empty*"
	otherwise, prints the contents of a list
*/
void printQueue(LIST *L);



/*
** createNode()
** requirements: an integer data
** results:
	creates an empty node with value `data`
	initializes fields of the structure
	returns the created node
*/
NODE* createNode(int data){
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new->value = data;
    return new;
}



/*
** createQueue()
** requirements: none
** results:
	creates an empty list
	initializes `head` and `tail` field of the structure
	returns the created list
*/
LIST* createQueue(){
    LIST *L =  (LIST *) malloc(sizeof(LIST));
    L->head = NULL;
    L->tail = NULL;
    return L;
}



/*
** isEmpty()
** requirements: none
** results:
	returns 1 if the list is empty
	otherwise return 0
*/
int isEmpty(LIST *L);



/*
** enqueue()
** requirements: a list and a node to be inserted
** results:
	inserts `node` at the `tail` of the list
*/
void enqueue(LIST *L, NODE* node);



/*
** dequeue()
** requirements: a list that must not be empty
** results:
	deletes the `head` node of the list
	returns the value of the deleted node
*/
int dequeue(LIST *L);


int main(){


}