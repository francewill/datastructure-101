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

// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){

	if(!node) return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);

}

void showTree(BST* B){
	showTreeHelper(B->root, 0);
}

/***********************************************************************/
/* Copy your previous function definitions for the functions in BST.h. */
/* PASTE THEM BELOW THIS COMMENT.                                      */
/***********************************************************************/

//your implementation for the functions in BST.h below !!!


