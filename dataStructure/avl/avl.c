/* ********************************************************* *
 * template.c                                                *
 *                                                           *
 * Template C Source File for AVL Insert.                    *
 *                                                           *
 * !!! DO NOT EDIT THE CONTENTS OF THE MAIN FUNCTION !!!     *
 *                                                           *
 * ********************************************************* */
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

AVL_NODE *createAVLNode(int key)
{
	return createBSTNode(key, NULL, NULL, NULL);
}

AVL *createAVL(int max)
{
	return createBST(max);
}

/**** PUT YOUR FUNCTIONS HERE ******************************/

/*
** function: leftRotate
** requirements:
	a non-null AVL pointer and a non-null node pointer
** results:
	rotates the tree (or subtree) rooted at `node` to the left
*/
/*
** function: heightOf
** requirements:
	a non-null node pointer
** results:
	returns -1 if node is NULL
	otherwirse, return the height of node
*/

int heightOf(AVL_NODE *node)
{
	if (node == NULL)
	{
		return -1;
	}
	else
	{
		return node->height;
	}
}

void rightRotate(AVL *A, AVL_NODE *node)
{
	AVL_NODE *pivot = node->left; // pivot will always be the node left
	if (node == A->root)		  // right rotate with the root
	{
		if (node->right != NULL && node->left->right != NULL) // rotate if root right child is not null
		{
			printf("\nA\n");
			A->root = pivot;
			pivot->parent = NULL;
			pivot->right->parent = node; // the node will be the parent of the pivot right child
			node->left = pivot->right;	 // the left child of the node will point to the right child of the pivot
			pivot->right = node;
			node->parent = pivot;
			heightAdjuster(node);
		}
		else // rotate if root right child is null
		{
			A->root = pivot;
			pivot->parent = NULL;
			pivot->right = node;
			node->parent = pivot;
			node->left = NULL;
			heightAdjuster(node);
		}
	}
	else
	{
		if (node->right != NULL && node->left->right != NULL)
		{
			node->parent->left = pivot;
			pivot->parent = node->parent;
			node->left = pivot->right;
			pivot->right->parent = node;
			pivot->right = node;
			node->parent = pivot;
			heightAdjuster(node);
		}
		else
		{
			node->parent->left = pivot;
			pivot->parent = node->parent;
			pivot->right = node;
			node->parent = pivot;
			node->left = NULL;
			heightAdjuster(node);
		}
	}
}

/*
** function: rightRotate
** requirements:
	a non-null AVL pointer and a non-null node pointer
** results:
	rotates the tree (or subtree) rooted at `node` to the right
*/
void leftRotate(AVL *A, AVL_NODE *node)
{
	AVL_NODE *pivot = node->right;
	int left, right;
	left = heightOf(node->left);
	right = heightOf(node->right);
	if (abs(left - right) <= 1)
	{

		if (node->right->left == NULL)
		{
			node->right->parent = node->parent;
			node->parent->left = node->right;
			node->parent = node->right;
			node->right->left = node;
			node->right = NULL;
			heightAdjuster(node);
		}
		else
		{
			AVL_NODE *pivot2 = node->right;

			pivot2->parent = node->parent;
			node->parent->left = pivot2;
			node->right = pivot2->left;
			node->parent = pivot2;
			pivot2->left->parent = node;
			pivot2->left = node;
			// node->parent = node->right;
			// node->right = ptr;
			// ptr = node;
			// // node->right = NULL;
			// heightAdjuster(node);
		}
		return;
	}
	if (node == A->root) // rotating when critical node is root
	{
		if (node->left != NULL) // switching parent case
		{
			A->root = pivot;
			pivot->parent = NULL;
			pivot->left->parent = node; // the parent of the left child of the pivot will be the node
			node->right = pivot->left;	// the pivot left child will be the right child of the node
			pivot->left = node;
			node->parent = pivot;
			heightAdjuster(node);
		}
		else // basic right rotate
		{
			A->root = pivot;
			pivot->parent = NULL;
			pivot->left = node;
			node->parent = pivot;
			node->right = NULL;
			heightAdjuster(node);
		}
	}
	else // rotating a subtree (critical node is not the root)
	{
		if (node->left != NULL)
		{
			node->parent->right = pivot;
			pivot->parent = node->parent;
			node->right = pivot->left;
			pivot->left->parent = node;
			pivot->left = node;
			node->parent = pivot;
			heightAdjuster(node);
		}
		else
		{
			node->parent->right = pivot;
			pivot->parent = node->parent;
			pivot->left = node;
			node->parent = pivot;
			node->right = NULL;
			heightAdjuster(node);
		}
	}
}

/*
** function: AVLInsert
** requirements:
	a non-null AVL pointer and a non null node pointer
** results:
	inserts the given node, `node`, to the AVL tree described by `A`
*/

void AVLInsert(AVL *A, AVL_NODE *node)
{
	insert(A, node);
	AVL_NODE *temp = node;
	int left, right, ans;
	while (temp != NULL)
	{
		left = heightOf(temp->left);
		right = heightOf(temp->right);
		if (abs(left - right) <= 1)
		{
			temp = temp->parent;
			continue;
		}
		else
		{
			ans = left - right;
			if (ans > 0)
			{
				int l, r;
				if (temp->left->left == NULL)
				{
					printf("\nLeft right crit at %d\n", temp->key);
					AVL_NODE *pivot = temp->left;
					leftRotate(A, pivot);
					rightRotate(A, temp);
				}
				else
				{
					l = heightOf(temp->left->left);
					r = heightOf(temp->left->right);
					if (l > r)
					{
						printf("\nLeft left crit at %d\n", temp->key);
						rightRotate(A, temp);
					}
					else
					{
						printf("\nLeft right crit at %d\n", temp->key);
						AVL_NODE *pivot = temp->left;
						leftRotate(A, pivot);
						printf("\nHalo\n");
						rightRotate(A, temp);
					}
				}
				break;
			}
			else
			{
				if (temp->right->right == NULL)
				{
					printf("\nRight left crit at %d\n", temp->key);
				}
				else
				{
					printf("\nRight right\n");
					leftRotate(A, temp);
				}
				break;
			}
		}
		temp = temp->parent;
	}
}

/**** FUNCTIONS ABOVE **************************************/

int main()
{

	char command;
	int key, result;

	AVL *A = createAVL(100);
	AVL_NODE *node;
	while (1)
	{
		scanf(" %c", &command);

		switch (command)
		{
		case '+':
			scanf("%d", &key);
			printf("Inserting key: %d\n", key);
			AVLInsert(A, createAVLNode(key));
			break;
		case 'p':
			printf("Tree (rotated +90 degrees): \n");
			showTree(A);
			printf("\n");
			break;
		case 'C':
			printf("Removing all contents.\n");
			clear(A);
			break;
		case 'Q':
			clear(A);
			free(A);
			return 0;
		default:
			printf("Unknown command %c\n", command);
		}
	}
}
