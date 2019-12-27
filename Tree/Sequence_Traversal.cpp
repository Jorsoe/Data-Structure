#include <stdio.h> 
#include <stdlib.h>
#define MAX 100
 
typedef struct BiTNode{    //���Ľڵ� 
	char data; 
	struct BiTNode *lchild,*rchild; 
}BiTNode,*BiTree; 
 
typedef struct{      //���д洢���ڵ� 
	int front, rear;
	BiTNode * data[MAX];
} Queue;

void init_Queue (Queue *q)   //��ʼ������
{
	q->rear=0;
	q->front=0;
}
int Empty_Queue(Queue *q)   //�ж϶����Ƿ�Ϊ�� 
{
	if(q->rear==q->front)
	{
		return 1;	
	}
	else
	{
		return 0;
	}
}
 
BiTNode *Delete_Queue(Queue *q)    //��βɾ��һ��Ԫ�� 
{
	return q->data[(q->front)++];
}
 
void Input_Queue(Queue *q,BiTNode *p)   //��ͷһ��Ԫ�� 
{
	if (q->rear==MAX)
    {
		printf("��������!"); 
    }
    else
    {
    	q->data[(q->rear)++]=p;	
	}
}

BiTree CreateBiTree(BiTree T)
{ 
	char ch; 
	ch=getchar(); 
	if(ch=='#') 
	T=NULL; 
	else
	{ 
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) 
		{
			printf("Error!"); 
		}
		else
		{
			T->data=ch; 
			T->lchild=CreateBiTree(T->lchild);
			T->rchild=CreateBiTree(T->rchild);
		} 
	} 
	return T; 
} 

void Sequence_traversal(BiTree T,Queue *q)     //������� 
{
	BiTNode *p;
	p = T;
	if(p!=NULL)
	{
		Input_Queue(q,p);	
	} 
	while(!Empty_Queue(q))
	{
		p = Delete_Queue(q);
		printf("%c",p->data);
		if(p->lchild!=NULL)
		{
			Input_Queue(q,p->lchild);	
		}
		if(p->rchild!=NULL)
		{
			Input_Queue(q,p->rchild);
		}
	}
}
int main()
{ 
	BiTree Tree; 
	Queue queue;
	init_Queue(&queue);
	printf("�������������У�#Ϊ�գ���"); 
	Tree = CreateBiTree(Tree);
	printf("����������Ϊ��"); 
	Sequence_traversal(Tree,&queue);
	printf("\n");
}

