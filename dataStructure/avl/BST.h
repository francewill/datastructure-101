/* ********************************************************* *
 * BST.h                                                     *
 *                                                           *
 * Contains the function prototypes of all functions created *
 *    in BST.c.                                              *
 *                                                           *
 * !!! DO NOT EDIT LINES 11-60 !!!                           *
 * !!! Make sure that file ends with #endif                  *
 *                                                           *
 * ********************************************************* */
#ifndef _BST_H_
#define _BST_H_

typedef struct bst_node{
    struct bst_node* left;  //left pointer
    struct bst_node* right; //right pointer
    struct bst_node* parent;//parent pointer
    int key;    //value of the node
    int height; //height of the node
} BST_NODE;

typedef struct bst{
    BST_NODE* root; //root pointer
    int maxSize;    //number of maximum nodes in the tree
    int size;   //current size of the tree
}BST;

//returns the address of a newly-created node
//based on the paremeters given
BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P);

//returns the address of a newly-created tree
//with maximum size based on the formal parameter `max`
BST* createBST(int max);

//returns 1 if empty, 0 otherwise
int isEmpty(BST* B);

//returns 1 if full, 0 otherwise
int isFull(BST* B);

//inserts the node being pointed by `node`
//to the tree being pointed by `B`
void insert(BST* B, BST_NODE* node);

//displays the elements of tree `B` in tree mode
void showTree(BST* B);

//deletes the node containing the `key` from tree `B`
//if it exists
int delete(BST* B, int key);

//deletes all the nodes from tree `B`
void clear(BST* B);

/********************************************************************/
/* If your implementation to the functions above requires another   */
/*    function you implemented during the BST requirements, please  */
/*    DECLARE THEM BELOW.                                           */
/********************************************************************/

//other function prototypes below !!!

#endif