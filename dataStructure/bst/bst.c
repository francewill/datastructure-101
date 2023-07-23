
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
BST_NODE *createBSTNode(int key, BST_NODE *L, BST_NODE *R, BST_NODE *P)
{
    BST_NODE *node = (BST_NODE *)malloc(sizeof(BST_NODE));
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
BST *createBST(int max)
{
    BST *B = (BST *)malloc(sizeof(BST));
    B->maxSize = max;
    B->root = NULL;
    B->size = 0;
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

/*
** function: isFull
** requirements:
    a non-null BST pointer
** results:
    returns 1 if BST is full;
    otherwise, return 0
*/
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
        ptr = ptr->parent;            // traverse upwards
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
            return;              // then end the function
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

void insert(BST *B, BST_NODE *node)
{ // insert function
    if (isEmpty(B))
    { // this is for adding our root
        B->root = node;
    }
    else
    {
        recursionInsert(B->root, node);
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
BST_NODE *serachRecursion(BST_NODE *node, int key) // recursive function for search
{
    if (node == NULL) // if null means not found and just return null
    {
        return NULL;
    }
    if (node->key > key) // traverse downwards by evaluating left and right child
    {
        serachRecursion(node->left, key);
    }
    else if (node->key == key) // if found then return that noud
    {
        return node;
    }
    else
    {
        serachRecursion(node->right, key);
    }
}

BST_NODE *search(BST *B, int key)
{
    BST_NODE *ptr = B->root;
    BST_NODE *result = serachRecursion(ptr, key);
    if (result == NULL)
    {
        printf("\nSearch result: %p\n", result);
    }
    else
    {
        printf("\nNode found: %p\n", result);
    }
    return result;
}

/*
** function: preorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `pre-order traversal`
*/
void recursivePreorder(BST_NODE *node) // root left right traversal
{
    if (node == NULL)
        return;
    printf("%d ", node->key);
    recursivePreorder(node->left);
    recursivePreorder(node->right);
}
void preorderWalk(BST *B)
{
    recursivePreorder(B->root);
}

/*
** function: inorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `in-order traversal`
*/
void recursiveInorder(BST_NODE *node) // left root right traversal
{
    if (node == NULL)
        return;
    recursiveInorder(node->left);
    printf("%d ", node->key);
    recursiveInorder(node->right);
}
void inorderWalk(BST *B)
{
    recursiveInorder(B->root);
}

/*
** function: postorderWalk
** requirements:
    a non-null BST pointer
** results:
    displays a list of elements of the BST using `post-order traversal`
*/
void recursivePostorder(BST_NODE *node) // left right root traversal
{
    if (node == NULL)
        return;
    recursivePostorder(node->left);
    recursivePostorder(node->right);
    printf("%d ", node->key);
}
void postorderWalk(BST *B)
{
    recursivePostorder(B->root);
}

/*
** function: minimum
** requirements:
    a non-null BST_NODE pointer
** results:
    finds the leftmost node of the subtree rooted at node n and returns its node pointer if found,
        otherwise, return `NULL`
*/
BST_NODE *minimum(BST_NODE *n)
{
    while (n->left != NULL)
    {
        n = n->left;
    }
    return n;
}

/*
** function: maximum
** requirements:
    a non-null BST_NODE pointer
** results:
    finds the rightmost node of the subtree rooted at node n and returns its node pointer if found,
        otherwise, return `NULL`
*/
BST_NODE *maximum(BST_NODE *n)
{
    while (n->right != NULL)
    {
        n = n->right;
    }
    return n;
}
/*
** function: remove
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds `key` and delete's it node from the BST `B`
    if found, delete then, return key
    otherwise, return 0

*/
int delete(BST *B, int key)
{
}

/*
** function: predecessor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's predecessor, if it exists
    otherwis, return `NULL`
*/
BST_NODE *predecessor(BST_NODE *node)
{
    BST_NODE *ptr = node, *temp = node->left;
    // two cases to check
    if (temp == NULL)
    { // if temp does not have left child
        while (ptr->parent != NULL && ptr->parent->left == ptr)
        { // check if parent is null and parent left child is the current node
            ptr = ptr->parent;
        }
        if (ptr->parent != NULL)
        { // if not null then just return the parent (ancestor type)
            return ptr->parent;
        }
        return NULL; // means the node your chosen is the minimum of that tree
    }
    else
    { // if it has left child then go to the rightmost node
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }
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

/*
** function: clear
** requirements:
    a non-null BST pointer
** results:
    removes all data items in the BST
*/
void clear(BST *B)
{
}

int main()
{

    char command;
    int key, result;

    BST *B = createBST(100);
    BST_NODE *node;
    while (1)
    {
        scanf(" %c", &command);

        switch (command)
        {
        case '+':
            scanf("%d", &key);
            printf("Inserting key: %d\n", key);
            insert(B, createBSTNode(key, NULL, NULL, NULL));
            break;
        case '-':
            if (isEmpty(B))
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                scanf("%d", &key);
                if (search(B, key) != NULL)
                {
                    printf("Removing node with key: %d\n", key);
                    result = delete (B, key); // result is unused. print if u want
                }else{
                    printf("Not found!\n");
                }
            }
            break;
        case 'p':
            printf("Tree (rotated +90 degrees): \n");
            showTree(B);
            printf("\n");
            break;
        case 'E':
            printf("BST %s empty.\n", isEmpty(B) ? "is" : "is not");
            break;
        case 'F':
            printf("BST %s full.\n", isFull(B) ? "is" : "is not");
            break;
        case '?':
            if (isEmpty(B))
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                scanf("%d", &key);
                search(B, key);
            }
            break;

        case '<':
            if (B->root == NULL)
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                printf("Pre-order Traversal: ");
                preorderWalk(B);
                printf("\n");
            }

            break;
        case '>':
            if (B->root == NULL)
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                printf("Post-order Traversal: ");
                postorderWalk(B);
                printf("\n");
            }

            break;
        case '/':
            if (B->root == NULL)
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                printf("In-order Traversal: ");
                inorderWalk(B);
                printf("\n");
            }

            break;
        case 'm':
            if (B->root == NULL)
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                BST_NODE *min = minimum(B->root);
                printf("\nMinimum of the tree: %d\n", min->key);
            }
            break;
        case 'M':
            if (B->root == NULL)
            {
                printf("\nTree is empty!\n");
            }
            else
            {
                BST_NODE *min = maximum(B->root);
                printf("\nMaximum of the tree: %d\n", min->key);
            }
            break;

        case '[':
            scanf("%d", &key);
            node = search(B, key);
            if (!node)
            {
                printf("%d not found\n", key);
            }
            else
            {
                node = predecessor(node);
                if (node)
                    printf("Predecessor of %d is %d.\n", key, node->key);
                else
                    printf("No predecessor for %d\n", key);
            }
            break;
        case ']':
            scanf("%d", &key);
            node = search(B, key);
            if (!node)
            {
                printf("%d not found\n", key);
            }
            else
            {
                node = successor(node);
                if (node)
                    printf("Successor of %d is %d.\n", key, node->key);
                else
                    printf("No successor for %d\n", key);
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
