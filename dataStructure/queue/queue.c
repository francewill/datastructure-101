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
void printQueue(LIST *L){
    if(isEmpty(L)){
        printf("\nList is empty!\n");
    }else{
        NODE *temp;
        printf("\nLIST = ");
        for(temp = L->head;temp!=NULL; temp = temp->next){
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
NODE* createNode(int data){
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new->value = data;
    new->next = NULL;
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
int isEmpty(LIST *L){
    if(L->head ==NULL){
        return 1;
    }else{
        return 0;
    }
}



/*
** enqueue()
** requirements: a list and a node to be inserted
** results:
	inserts `node` at the `tail` of the list
*/
void enqueue(LIST *L, NODE* node){
    if(L->head==NULL&& L->tail==NULL){
        L->head = node;
        L->tail = node;
    }else{
        NODE *temp = L->tail;
        L->tail = node;
        temp->next = node;
    }
}



/*
** dequeue()
** requirements: a list that must not be empty
** results:
	deletes the `head` node of the list
	returns the value of the deleted node
*/
int dequeue(LIST *L){
    int val;
    if(isEmpty(L)){
        printf("\nList is empty!\n");
        return -1;
    }else{
        NODE *temp = L->head;
        L->head = L->head->next;
        val = temp->value;
        free(temp);
        return val;
    }
}


int main(){
    LIST *L = createQueue();
    enqueue(L,createNode(1));
    enqueue(L,createNode(2));
    enqueue(L,createNode(3));
    enqueue(L,createNode(4));
    enqueue(L,createNode(5));
    dequeue(L);
    dequeue(L);
    dequeue(L);
    enqueue(L,createNode(10));  
    dequeue(L);
  
 
    printQueue(L);
    return 0;

}