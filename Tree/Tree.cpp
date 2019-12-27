#include<stdio.h>
#include<stdlib.h>
#define MAXNODE 100 

typedef struct Node
{
	char data;
	struct Node *lchild;
	struct Node *rchild;
}Tree,*Bitree;

void CreateBiTree(Bitree *Tree)
{
	char s;
	scanf("%c",&s);
	if(s=='#')
		*Tree = NULL;
	else
	{
		*Tree = (Bitree)malloc(sizeof(Node));
		(*Tree)->data = s;
		(*Tree)->lchild = NULL;
		(*Tree)->rchild = NULL;
		CreateBiTree(&(*Tree)->lchild);
		CreateBiTree(&(*Tree)->rchild);
	}
}

void visit(char e)
{
	printf("%c",e);
}

void Front_Output(Bitree T)
{
	Bitree Stack[MAXNODE],p;
	int top;
	if(T == NULL)
	{
		return;
	}
	else
	{
		top = 0;
		p = T;
	}
	while(p!=NULL)
	{
		visit(p->data);
		if(top<MAXNODE-1)
		{
			Stack[top] = p;
			top++;
		}
		else
		{
			printf("溢出！");
		}
		p = p->lchild;
	}
	if(top<=0)
	{
		return;
	}
	else
	{
		top--;
		p = Stack[top];
		p = p->rchild; 
	} 
}

void In_Output(Bitree T)
{
	Bitree Stack[MAXNODE],p;
	int top;
	if(T == NULL)
	{
		return;
	}
	else
	{
		top = 0;
		p = T;
	}
	while(p!=NULL)
	{
		if(top<MAXNODE-1)
		{
			Stack[top] = p;
			top++;
		}
		else
		{
			printf("溢出！");
		}
		p = p->lchild;
	}
	if(top<=0)
	{
		return;
	}
	else
	{
		top--;
		p = Stack[top];
		visit(p->data);
		p = p->rchild; 
	} 
}

int main()
{
	Bitree root;
	root = (Tree*)malloc(sizeof(Node));
	printf("以先序遍历依次为二叉树赋值:");
	CreateBiTree(&root);
	printf("以先序遍历输出二叉树:");
	Front_Output(root);
	printf("\n");
	printf("以中序遍历输出二叉树:");
	In_Output(root);
	printf("\n");

}

