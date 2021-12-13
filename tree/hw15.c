#include <stdio.h>
#include <stdlib.h>
#include<string.h> 
// Data structure to store a binary tree node
struct Node
{
    int key;
    struct Node *left, *right;
};
 
// Function to create a new binary tree node having a given key
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
 
    return node;
}
 
// Recursive function to perform inorder traversal on a given binary tree
void inorderTraversal(struct Node* root)
{
    if (root == NULL) {
        return;
    }
 
    inorderTraversal(root->left);
    printf("%d ", root->key);
    inorderTraversal(root->right);
}
 
// Recursive function to perform preorder traversal on a given binary tree
void preorderTraversal(struct Node* root)
{
    if (root == NULL) {
        return;
    }
 
    printf("%d ", root->key);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct Node* root)
{
    if (root == NULL) {
        return;
    }
 
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->key);
}
 
// Recursive function to construct a binary tree from a given
// inorder and preorder sequence
struct Node* IPconstruct(int inorder[], int start, int end,
                int preorder[], int *pIndex)
{
    // base case
    if (start > end) {
        return NULL;
    }
 
    // The next element in `preorder[]` will be the root node of
    // subtree formed by sequence represented by `inorder[start, end]`
    struct Node* node = newNode(preorder[(*pIndex)++]);
 
    // search the root node index in sequence `inorder[]` to determine the
    // left and right subtree boundary
    int i;
    for (i = start; i <= end; i++)
    {
        if (inorder[i] == node->key) {
            break;
        }
    }
 
    // recursively construct the left subtree
    node->left = IPconstruct(inorder, start, i - 1, preorder, pIndex);
 
    // recursively construct the right subtree
    node->right = IPconstruct(inorder, i + 1, end, preorder, pIndex);
 
    // return current node
    return node;
}
struct Node* PPconstruct(int inorder[], int start, int end,
                int postorder[], int *pIndex)
{
    // base case
    if (start > end) {
        return NULL;
    }
 
    // The next element in `preorder[]` will be the root node of
    // subtree formed by sequence represented by `inorder[start, end]`
    struct Node* node = newNode(postorder[(*pIndex)--]);
 
    // search the root node index in sequence `inorder[]` to determine the
    // left and right subtree boundary
    int i;
    for (i = start; i <= end; i++)
    {
        if (inorder[i] == node->key) {
            break;
        }
    }
 
 
    // recursively construct the right subtree
    node->right = PPconstruct(inorder, i + 1, end, postorder, pIndex);
    // recursively construct the left subtree
    node->left = PPconstruct(inorder, start, i - 1, postorder, pIndex);
 
    // return current node
    return node;
}
 
// Construct a binary tree from inorder and preorder traversals.
// This function assumes that the input is valid, i.e., given
// inorder and preorder sequence forms a binary tree.
struct Node* IPconstructTree(int inorder[], int preorder[], int n)
{
    // `pIndex` stores the index of the next unprocessed node in a preorder sequence;
    // root node is present at index 0 in a preorder sequence
    int pIndex = 0;
 
    return IPconstruct(inorder, 0, n - 1, preorder, &pIndex);
}
struct Node* PPconstructTree(int inorder[], int postorder[], int n)
{
	int pIndex = n-1;

	return PPconstruct(inorder, 0, n-1, postorder, &pIndex);
}
 
int main()
{
	long numOfSet;
	const char *preinorder = "preorder-inorder";
	const char *postinorder = "postorder-inorder";
	char orderType[17];
	int numOfNode;
	scanf("%ld",&numOfSet);
	for(long i=0;i<numOfSet;i++){
		scanf("%s",orderType);
		if(strcmp(orderType, preinorder)==0){ //0 means equal
			scanf("%d",&numOfNode);
			int inorder[numOfNode];
			int preorder[numOfNode];
			for(int i=0;i<numOfNode;i++) scanf("%d",&preorder[i]);
			for(int i=0;i<numOfNode;i++) scanf("%d",&inorder[i]);
			int n = sizeof(inorder)/sizeof(inorder[0]);
			struct Node* root = IPconstructTree(inorder, preorder, n);
			// traverse the constructed tree
			printf("\n"); 
			postorderTraversal(root);
			printf("\n");
		}else{
			scanf("%d",&numOfNode);
			int inorder[numOfNode];
			int postorder[numOfNode];
			for(int i=0;i<numOfNode;i++) scanf("%d",&postorder[i]);
			for(int i=0;i<numOfNode;i++) scanf("%d",&inorder[i]);
			int n = sizeof(inorder)/sizeof(inorder[0]);
			struct Node* root = PPconstructTree(inorder, postorder, n);
			// traverse the constructed tree
			printf("\n"); 
			preorderTraversal(root);
			printf("\n");
		}

	}
 
    return 0;
}
			//int inorder[] = { 5, 4, 3, 2, 1 };
			// int preorder[] = { 5, 2, 4, 3, 1 };
			//int postorder[] = {3,4,1,2,5};

