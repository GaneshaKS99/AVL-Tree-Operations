A Design and Analysis of algorithm project by
Vikas Kalagi PES1201701654          and
Ganesha K S PES1201701731
From Class 4B


There is a header file called “ header.h ”contains all the functions and structure
required to implement the AVL tree with integer and character matching option that is left to the user.

server.c is a file which contain all the functions required to insert,delete,search while doing the integer and string matching.
The output is printed in preorder form.
	int int_match (NODE * node, int key, char c [100]);
	int str_match (NODE * node, int key, char c [100]); 
	We use these functions as callback in insertion, deletion and search functions.

We are also using helping functions like,
int getBalance(struct Node *N) ;----- getting the balance factor
int height(NODE *N); 		----- height of the tree from the current node
int max(int a, int b) ;		----- Maximum value of a and b
NODE *leftRotate(NODE *x);	----- rotate left for balancing the given node x
NODE *rightRotate(NODE *y) ; 	----- rotate right for balancing the given node x

To execute the program we use the following command in the linux terminal
 gcc client.c server.c
 ./a.out 