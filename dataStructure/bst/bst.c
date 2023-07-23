
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))


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

/*
** function: createBSTNode
** requirements:
    an integer indicating the key of the node
    an initial value for the left pointer (L)
    an initial value for the right pointer (R)
    an initial value for the parent pointer (P)
    if L, R, or P is unknown, pass `NULL`
** results:
    creates a BST node with fields initialized
    returns a pointer of this instance
*/
BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P){
    BST_NODE *node = (BST_NODE *) malloc(sizeof(BST_NODE));
    node->height = 0;
    node->key = key;
    node->left = L;
    node->right = R;
    node->parent = P;
    return node;
}


/*
** function: createBST
** requirements:
    an integer indicating the maximum size of the BST
        i.e. the maximum number of elements that can be stored
** results:
    creates an empty BST with fields initialized
    returns a pointer of this instance
*/
BST* createBST(int max){
    BST *B = (BST *) malloc(sizeof(BST));
    B->maxSize = max;
    B->root =NULL;
    B->size =0;
    return B;
}

/*
** function: isEmpty
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is empty;
    otherwise, return 0
*/
int isEmpty(BST* B){
    if(B->root == NULL){
        return 1;
    }else{
        return 0;
    }
}

/*
** function: isFull
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is full;
    otherwise, return 0
*/
int isFull(BST* B){
    if(B->maxSize==B->size){
        return 1;
    }else{
        return 0;
    }
}

/*
** function: insert
** requirements:
    a non-null BST pointer
    a non-empty BST
    a non-null BST_NODE pointer
** results:
    inserts the given `node` to the BST `B`
    update the height of the affected nodes
** notes:
    a node's height can be derived from left and right subtrees
        i.e. node->height = max(L->height, R->height) + 1
    if there are no subtrees i.e L==R==NULL, then node->height = 0
*/
void heightAdjuster(BST_NODE *node){
    BST_NODE *ptr = node;
    int left,right,maxHeight;
    while(ptr!=NULL){
        if(ptr->left == NULL){
            left = -1;
        }else{
            left = ptr->left->height;
        }
        
        if(ptr->right == NULL){
            right = -1;
        }else{
            right = ptr->right->height;
        }
        maxHeight = max(left, right);
        ptr->height = maxHeight+1;
        ptr = ptr->parent;
    }
}

void recursionInsert(BST_NODE *node, BST_NODE *new){
    if(node->key>new->key){
        if(node->left==NULL){
            node->left = new;
            new->parent = node;
            heightAdjuster(new);
            return;
        }
        recursionInsert(node->left,new);
    }else{
        if(node->right==NULL){
            node->right = new;
            new->parent = node;
            heightAdjuster(new);
            return;
        }
        recursionInsert(node->right,new);
    }

}
void insert(BST* B, BST_NODE* node){
    if(isEmpty(B)){
        B->root = node;
    }else{
        recursionInsert(B->root,node);
        
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
BST_NODE* serachRecursion(BST_NODE *node, int key){
    if(node==NULL){
        return NULL;
    }
    if(node->key>key){
        serachRecursion(node->left,key);
    }else if(node->key == key){
        return node;
    }
    else{
        serachRecursion(node->right,key);
    }
}
BST_NODE* search(BST* B, int key){
    BST_NODE *ptr = B->root;
    BST_NODE *result = serachRecursion(ptr, key);
    if(result ==NULL){
        printf("\nNot found!\n");
    }else{
        printf("\nNode found: %p\n", result);
    }
    
}

/*
** function: preorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `pre-order traversal`
*/
void recursivePreorder (BST_NODE *node){
    if(node ==NULL) return;
    printf("%d ",node->key);
    recursivePreorder(node->left);
    recursivePreorder(node->right);

}
void preorderWalk(BST* B){
    recursivePreorder(B->root);
}

/*
** function: inorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `in-order traversal`
*/
void recursiveInorder (BST_NODE *node){
    if(node ==NULL) return;
    recursiveInorder(node->left); 
    printf("%d ",node->key);
    recursiveInorder(node->right);

}
void inorderWalk(BST* B){
    recursiveInorder(B->root);
}

/*
** function: postorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `post-order traversal`
*/
void postorderWalk(BST* B){
    
}


int main(){

	char command;
	int key, result;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				insert(B, createBSTNode(key, NULL, NULL, NULL));
				break;
			case '?':
				scanf("%d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
            case 'S':
                if(isEmpty(B)){
                    printf("\nTree is empty!\n");
                }else{
                    printf("Enter number to search: ");
                    scanf("%d", &key);
                    search(B, key);
                }
                break;
		
			case '<':
                if(B->root==NULL){
                    printf("\nTree is empty!\n");
                }else{
                    printf("Pre-order Traversal: ");
				    preorderWalk(B);
				    printf("\n");
                }
			
				break;
			case '>':
                if(B->root==NULL){
                    printf("\nTree is empty!\n");
                }else{
                    printf("Post-order Traversal: ");
                    postorderWalk(B);
                    printf("\n");  
                }
	
				break;
			case '/':
                if(B->root==NULL){
                    printf("\nTree is empty!\n");
                }else{
                    printf("In-order Traversal: ");
				    inorderWalk(B);
				    printf("\n");
                }
				
				break;
		
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}
