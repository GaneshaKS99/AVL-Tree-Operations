// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>

#include"header.h"

// A utility function to get the height of the tree 
int height(NODE *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
NODE * newNode(int key,char c[100]) 
{ 
	NODE * node = (NODE *) malloc(sizeof(struct Node)); 
	node->key = key; 
	strcpy(node->a,c);
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
NODE *rightRotate(NODE *y) 
{ 
	NODE *x = y->left; 
	NODE *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
NODE *leftRotate(NODE *x) 
{ 
	NODE *y = x->right; 
	NODE *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(NODE *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 
int str_match(NODE * node, int key,char c[100])
{
	return strcmp(node->a,c);
}
int int_match(NODE * node, int key,char c[100])
{	
	if(node->key==key)return 0;
	return node->key>key?1:-1;
}
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
NODE * insert(NODE * node, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100])) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
		return(newNode(key,c)); 
	int value=fun_pointer(node,key,c);
	//printf("%d %s",value,c);
	if (value>0) 
		node->left = insert(node->left, key,c,fun_pointer); 
	else if (value<0) 
		node->right = insert(node->right, key,c,fun_pointer); 
	else // Equal keys are not allowed in BST 
		return node; 

	//2. Update height of this ancestor node 
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 &&  fun_pointer(node->left,key,c)>0) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && fun_pointer(node->right,key,c)<0) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && fun_pointer(node->left,key,c)<0) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && fun_pointer(node->right,key,c)>0) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 



NODE * minValueNode(NODE * node) 
{ 
	NODE * current = node; 

	/* loop down to find the leftmost leaf */
	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 

// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
NODE * deleteNode(NODE * root, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100]) ) 
{ 
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL) 
		return root; 
int value=fun_pointer(root,key,c);
	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if ( value>0) 
		root->left = deleteNode(root->left, key,c,fun_pointer); 

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if( value <0 ) 
		root->right = deleteNode(root->right, key,c,fun_pointer); 

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{ 
		// node with only one child or no child 
		if( (root->left == NULL) || (root->right == NULL) ) 
		{ 
			struct Node *temp = root->left ? root->left : 
											root->right; 

			// No child case 
			if (temp == NULL) 
			{ 
				temp = root; 
				root = NULL; 
			} 
			else // One child case 
			*root = *temp; // Copy the contents of 
							// the non-empty child 
			free(temp); 
		} 
		else
		{ 
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			NODE * temp = minValueNode(root->right); 

			// Copy the inorder successor's data to this node 
			root->key = temp->key; 
			strcpy(root->a,temp->a);
			// Delete the inorder successor 
			root->right = deleteNode(root->right, temp->key,c,fun_pointer); 
		} 
	} 

	// If the tree had only one node then return 
	if (root == NULL) 
	return root; 

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->height = 1 + max(height(root->left), 
						height(root->right)); 

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root); 

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0) 
		return rightRotate(root); 

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0) 
	{ 
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0) 
		return leftRotate(root); 

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0) 
	{ 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 



// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(NODE *root) 
{ 
	if(root != NULL) 
	{ 
		printf("%d ", root->key); printf("%s \n",root->a);
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 
void search(NODE * root, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100]))
{	 struct Node *temp=root;
	int value;
	while(temp!=NULL)
	{	value=fun_pointer(temp,key,c);
		if(value>0)
		{
			temp=temp->left;
		}
		else if(value<0)
		{
			temp=temp->right;
		}
		else
		{
			printf("%d %s\n",temp->key,temp->a);
			return;
		}
		
	}
	printf("not fount....\n");
}
