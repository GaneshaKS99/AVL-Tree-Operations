// An AVL tree node 
typedef struct Node 
{ 	char a[100];
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
} NODE; 

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(NODE *N); 
int max(int a, int b) ;
NODE *leftRotate(NODE *x);
NODE *rightRotate(NODE *y) ;
// Get Balance factor of node N 
int getBalance(NODE *N) ;
NODE * deleteNode(NODE * root, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100]) ) ;
NODE * insert(NODE * node, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100]));
int int_match(NODE * node, int key,char c[100]);
int str_match(NODE * node, int key,char c[100]);
void preOrder(NODE *root) ;
NODE * newNode(int key,char c[100]) ;
void search(NODE * root, int key,char c[100],int (*fun_pointer)(NODE * node, int key,char c[100]));
