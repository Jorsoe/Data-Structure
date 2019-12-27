#include<stdio.h>
#define MaxSize 50
#define TRUE 1
#define FALSE 0

//定义循环队列结构体
typedef struct { 
	int data[MaxSize];
	int front,rear;
}Queue;

//初始化
void Init_Queue(Queue &Q)
{
	Q.rear = Q.front = 0;
}
//判断队列是否为空
int IsEmpty(Queue &Q)
{
	if(Q.rear == Q.front)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;		
	}
}
//入队操作
int Enter_Queue(Queue &Q,int x)
{
	if((Q.rear+1)%MaxSize == Q.front)
	{
		return false;
	}
	else
	{
		Q.rear = (Q.rear+1)%MaxSize;
		Q.data[Q.rear] = x;
		printf("%d\n",Q.data[Q.rear]); //用于显示入队数据
		return true;
	}

}
//出队操作
int Delete_Queue(Queue &Q,int x)
{
	if(Q.rear == Q.front)
	{
		return false;
	}
	else
	{
		Q.front = (Q.front+1)%MaxSize;
		x = Q.data[Q.front];
		printf("%d\n",x); //用于显示出队数据
		return true;
	}
	
}

int main()
{
	Queue q;
	int m,x;
	Init_Queue(q);
	Enter_Queue(q,5);
	Enter_Queue(q,23);
	Enter_Queue(q,31);
	Enter_Queue(q,36);
	Delete_Queue(q,x);
	m = IsEmpty(q);
	printf("%d\n",m);
}
