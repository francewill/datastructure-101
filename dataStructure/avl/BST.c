/* ********************************************************* *
 * BST.c                                                     *
 *                                                           *
 * Contains the function definitions of all functions        *
 *    declared in BST.h.                                     *
 *                                                           *
 * !!! DO NOT EDIT LINES 11-28 !!!                           *
 *                                                           *
 * ********************************************************* */
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE *node, int tabs)
{

	if (!node)
		return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for (int i = 0; i < tabs; i++)
		printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);
}

void showTree(BST *B)
{
	showTreeHelper(B->root, 0);
}

/***********************************************************************/
/* Copy your previous function definitions for the functions in BST.h. */
/* PASTE THEM BELOW THIS COMMENT.                                      */
/***********************************************************************/

// your implementation for the functions in BST.h below !!!

// returns the address of a newly-created node
// based on the paremeters given
BST_NODE *createBSTNode(int key, BST_NODE *L, BST_NODE *R, BST_NODE *P)
{
	BST_NODE *node = (BST_NODE *)malloc(sizeof(BST_NODE));
	node->key = key;
	node->left = L;
	node->right = R;
	node->parent = NULL;
	return node;
}

// returns the address of a newly-created tree
// with maximum size based on the formal parameter `max`
BST *createBST(int max)
{
	BST *B = (BST *)malloc(sizeof(BST));
	B->root = NULL;
	B->size = 0;
	B->maxSize = max;
	return B;
}

// returns 1 if empty, 0 otherwise
int isEmpty(BST *B)
{
	if (B->root == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// returns 1 if full, 0 otherwise
int isFull(BST *B)
{
	if (B->maxSize == B->size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*
** function: search
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds `key` from BST `B` and returns its node pointer if found,
        otherwise, return `NULL`
*/
BST_NODE *searchRecursion(BST_NODE *node, int key) // recursive function for search
{
    if (node == NULL) // if null means not found and just return null
    {
        return NULL;
    }
    if (node->key > key) // traverse downwards by evaluating left and right child
    {
        searchRecursion(node->left, key);
    }
    else if (node->key == key) // if found then return that noud
    {
        return node;
    }
    else
    {
        searchRecursion(node->right, key);
    }
}

BST_NODE *search(BST *B, int key)
{
    BST_NODE *ptr = B->root;
    BST_NODE *result = searchRecursion(ptr, key);
    if (result == NULL)
    {
        printf("\nSearch result: %p\n", result);
    }
    return result;
}


void heightAdjuster(BST_NODE *node)
{
	BST_NODE *ptr = node;
	int left, right, maxHeight;
	while (ptr != NULL)
	{ // loop until ptr is not null
		if (ptr->left == NULL)
		{ // null means -1
			left = -1;
		}
		else
		{
			left = ptr->left->height; // else their height will represent the left
		}

		if (ptr->right == NULL)
		{ // null means -1
			right = -1;
		}
		else
		{
			right = ptr->right->height; // else their height will represent the right
		}
		maxHeight = max(left, right); // get the maximum numbere between left and right
		ptr->height = maxHeight + 1;  // height = max height +1
		ptr = ptr->parent;			  // traverse upwards
	}
}

void recursionInsert(BST_NODE *node, BST_NODE *new)
{
	if (node->key > new->key)
	{ // traverse left and right until we reach the leaf node
		if (node->left == NULL)
		{ // if we reached the leaf node means we will insert the data
			node->left = new;
			new->parent = node;
			heightAdjuster(new); // adjust its height
			return;				 // then end the function
		}
		recursionInsert(node->left, new); // if not null then we will call the recursive function again and evaluate with the given condition
	}
	else
	{ // this is for the right child
		if (node->right == NULL)
		{
			node->right = new;
			new->parent = node;
			heightAdjuster(new);
			return;
		}
		recursionInsert(node->right, new);
	}
}
// inserts the node being pointed by `node`
// to the tree being pointed by `B`
void insert(BST *B, BST_NODE *node)
{
	if (isEmpty(B))
	{ // this is for adding our root
		B->root = node;
	}
	else
	{
		recursionInsert(B->root, node);
	}
	B->size++;
}

/*
** function: successor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's successor, if it exists
    otherwis, return `NULL`
*/
BST_NODE *successor(BST_NODE *node)
{
    BST_NODE *temp = node->right, *ptr = node;
    ;
    // two cases
    if (temp == NULL)
    { // if the node doesn't have right child
        while (ptr->parent != NULL && ptr->parent->right == ptr)
        {
            ptr = ptr->parent;
        }
        if (ptr->parent == NULL)
        { // it means that the node chosen is the highest number of that tree
            return NULL;
        }
        return ptr->parent; // ancestor type
    }
    else
    { // if node has right child then go to the leftmost node of temp
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
}

int deleteRecursive(BST *B, BST_NODE *del)
{
	int val;
	if (del == NULL) // not found if NULL
	{
		return -1;
	}
	else
	{
		if (del->right == NULL && del->left == NULL) // deleting a node with no child
		{
			if (del == B->root) // deleting root with no child
			{
				val = del->key;
				B->root = NULL;
				free(del);
				B->size--;
				return val;
			}
			if (del == del->parent->left) // deleting left node with no child
			{
				val = del->key;
				del->parent->left = NULL;
			}
			else // deleting right node with no child
			{
				val = del->key;
				del->parent->right = NULL;
			}
			heightAdjuster(del->parent);
			free(del);
			B->size--;
			return val;
		}
		else if (del->right != NULL || del->left != NULL)
		{
			if (del->right != NULL && del->left == NULL) // deleting node with right child
			{
				if (del == B->root) // deleting root with right child only
				{
					val = del->key;
					B->root = del->right;
					del->right->parent = NULL;
					heightAdjuster(del->right);
					free(del);
					B->size--;
					return val;
				}
				if (del->parent->right == del) // deleting right node with right child
				{
					val = del->key;
					del->parent->right = del->right;
					del->right->parent = del->parent;
					heightAdjuster(del->right);
					free(del);
					B->size--;
					return val;
				}
				else // deleting left node with right child
				{
					val = del->key;
					del->parent->left = del->right;
					del->right->parent = del->parent;
					heightAdjuster(del->right);
					free(del);
					return val;
				}
			}
			else if (del->right == NULL && del->left != NULL)
			{
				if (del == B->root) // deleting root with left child
				{
					val = del->key;
					B->root = del->left;
					del->left->parent = NULL;
					heightAdjuster(del->left);
					free(del);
					B->size--;
					return val;
				}
				if (del->parent->right == del) // deleting  right node with left child
				{
					val = del->key;
					del->parent->right = del->left;
					del->left->parent = del->parent;
					heightAdjuster(del->left);
					free(del);
					B->size--;
					return val;
				}
				else // deleting left node with left child
				{
					val = del->key;
					del->parent->left = del->left;
					del->left->parent = del->parent;
					heightAdjuster(del->left);
					free(del);
					return val;
				}
			}
			else // deleting node with two children
			{
				BST_NODE *suc = successor(del);
				del->key = suc->key;
				deleteRecursive(B, suc);
			}
		}
	}
}
// deletes the node containing the `key` from tree `B`
// if it exists
int delete(BST *B, int key)
{
	BST_NODE *del = search(B, key);
	int deletedVal = deleteRecursive(B, del);
	if (deletedVal == -1)
	{
		printf("\nNode not found!\n");
	}
	else
	{
		printf("\nSuccessfully deleted %d\n", key);
	}
}

// deletes all the nodes from tree `B`
void clear(BST *B)
{
    int val;
    if (isEmpty(B))
    {
        printf("\nTree is clean!\n");
    }
    else
    {
        while (B->root != NULL)
        {
            val = B->root->key;
            delete (B, val);
        }
    }
}


/********************************************************************/
/* If your implementation to the functions above requires another   */
/*    function you implemented during the BST requirements, please  */
/*    DECLARE THEM BELOW.                                           */
/********************************************************************/

// other function prototypes below !!!
