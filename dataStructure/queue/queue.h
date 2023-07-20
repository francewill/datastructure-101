/* DO NOT EDIT THIS FILE */

/* LIST ADT */

typedef struct node_tag{
	int value;
	struct node_tag* next;
}NODE;


typedef struct list_tag{
	NODE* head;
	NODE* tail;
}LIST;



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
NODE* createNode(int data);



/*
** createQueue()
** requirements: none
** results:
	creates an empty list
	initializes `head` and `tail` field of the structure
	returns the created list
*/
LIST* createQueue();



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
