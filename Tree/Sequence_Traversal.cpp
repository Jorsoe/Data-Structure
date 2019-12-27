#include <stdio.h> 
#include <stdlib.h>
#define MAX 100
 
typedef struct BiTNode{    //树的节点 
	char data; 
	struct BiTNode *lchild,*rchild; 
}BiTNode,*BiTree; 
 
typedef struct{      //队列存储树节点 
	int front, rear;
	BiTNode * data[MAX];
} Queue;

void init_Queue (Queue *q)   //初始化队列
{
	q->rear=0;
	q->front=0;
}
int Empty_Queue(Queue *q)   //判断队列是否为空 
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
 
BiTNode *Delete_Queue(Queue *q)    //队尾删除一个元素 
{
	return q->data[(q->front)++];
}
 
void Input_Queue(Queue *q,BiTNode *p)   //队头一个元素 
{
	if (q->rear==MAX)
    {
		printf("队列已满!"); 
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

void Sequence_traversal(BiTree T,Queue *q)     //层序遍历 
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
	printf("请输入先序序列（#为空）："); 
	Tree = CreateBiTree(Tree);
	printf("层序遍历结果为："); 
	Sequence_traversal(Tree,&queue);
	printf("\n");
}

