#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include"header.h"

int main() 
{ 
NODE *root=NULL; 
int option;
int (*fun_pointer)(NODE * node, int key,char c[100]);

int servar;
int srn;
char name[10];

printf("how do you want to arrange the avl tree if by string then type 1 else by int then type 0 : ");
scanf("%d",&option);
if(option)
{
fun_pointer=int_match;
}
else{
fun_pointer=str_match;
}
do
{
printf("1.inert\n2.deletion\n3.display\n4.serarch\n");
scanf("%d",&option);
switch(option){
case 1:printf("enter the srn and name to insert :");
		scanf("%d %s",&srn,name);
		root = insert(root, srn,name,fun_pointer); 
		break;
case 2:printf("enter the srn and name to delete :");
		scanf("%d %s",&srn,name);
		root = deleteNode(root, srn,name,fun_pointer); 
		break;
case 3:preOrder(root);printf("\n");
	break;
case 4:
		printf("to search according to srn(1) or string(0) : ");
		scanf("%d",&servar);
		if(servar)
		{	
			printf("enter the srn : ");
			scanf("%d",&srn);
			search(root,srn," ",int_match);
		}
		else
		{
			printf("enter the nme : ");
			scanf("%s",name);
			search(root,0,name,str_match);
		}
		break;

default : return 0;


}
}
while(1);
} 
