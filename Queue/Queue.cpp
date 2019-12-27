#include<stdio.h>
#define MaxSize 50
#define TRUE 1
#define FALSE 0

//����ѭ�����нṹ��
typedef struct { 
	int data[MaxSize];
	int front,rear;
}Queue;

//��ʼ��
void Init_Queue(Queue &Q)
{
	Q.rear = Q.front = 0;
}
//�ж϶����Ƿ�Ϊ��
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
//��Ӳ���
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
		printf("%d\n",Q.data[Q.rear]); //������ʾ�������
		return true;
	}

}
//���Ӳ���
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
		printf("%d\n",x); //������ʾ��������
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
