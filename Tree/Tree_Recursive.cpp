#include<stdio.h>
#include<stdlib.h>

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

void Front_Output(Bitree t)                 //����������������
{
	if(t!=NULL)
	{
		printf("%c ",t->data);
		Front_Output(t->lchild);
		Front_Output(t->rchild);
	}
}

void In_Output(Bitree t)                 //����������������
{
	if(t!=NULL)
	{
		In_Output(t->lchild);
		printf("%c ",t->data);
		In_Output(t->rchild);
	}
}

void Base_Output(Bitree t)                 //����������������
{
	if(t!=NULL)
	{
		Base_Output(t->lchild);
		Base_Output(t->rchild);
		printf("%c ",t->data);
	}
}

int main()
{
	Bitree root;
	root = (Tree*)malloc(sizeof(Node));
	printf("�������������Ϊ��������ֵ:");
	CreateBiTree(&root);
	printf("������������������:");
	Front_Output(root);
	printf("\n");
	printf("������������������:");
	In_Output(root);
	printf("\n");
	printf("�Ժ���������������:");
	Base_Output(root);
	printf("\n");
}

