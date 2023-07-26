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

AVL_NODE * createAVLNode(int key){
    return createBSTNode(key, NULL, NULL, NULL);
}

AVL * createAVL(int max){
    return createBST(max);
}

/**** PUT YOUR FUNCTIONS HERE ******************************/






/**** FUNCTIONS ABOVE **************************************/

int main(){

	char command;
	int key, result;

	AVL *A = createAVL(100);
	AVL_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
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
