#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
	//�ڵ㶨�� 
typedef struct Node{
	int data;		//������ 
	struct Node* next;		//ָ���� 
}SNode;
	//ջ���� 
typedef struct StackNode{
	SNode* top;		//ջ��ָ�� 
	SNode* base;	//ջ��ָ�� 
}Stack;

	//�������� 
void init_Stack(Stack* q);
int Empty_Stack(Stack* q);
void GetTop_Stack(Stack* q);
void Push(Stack* q,int e);
int Pop(Stack* q);
void Traverse_Stack(Stack* q);
void Clear_Stack(Stack* q); 
void Conversion();

	//��ʼ��ջ 
void init_Stack(Stack* q)
{
	q->base = (SNode*)malloc(sizeof(Node));
	q->top = q->base;
	q->top->next = NULL;
	printf("��ջ�������!\n");
}
	// �ж��Ƿ�ջ��ջ�� 
int Empty_Stack(Stack* q)
{
	if (q->top==q->base)
	{
		return ERROR;
	}
	else
	{
		return OK;
	}
}
	//���ջ��Ԫ�� 
void GetTop_Stack(Stack* q)
{
    SNode* a=q->top;
    printf("%d\n",a->data);
}
	//��ջ 
void Push(Stack* q,int e)
{
	SNode* s = (SNode*)malloc(sizeof(Node)); 
	s->data = e;
	s->next = q->top;
	q->top = s;
}
	//��ջ 
int Pop(Stack* q)
{
	int e;
	SNode* p;
	if (!Empty_Stack(q))
	{
		printf("��ջ!\n");
	}
	else
	{
		e = q->top->data;
		p = q->top;
		q->top = p->next;
		free(p);
		return e;
	}
}
	//��ӡջ�����ֵ 
void Traverse_Stack(Stack* q)
{
	SNode* Bl;
	Bl = q->top;
	printf("ջ�е�Ԫ���ǣ�"); 
	while(Bl!=q->base)
	{
		printf("%d ",Bl->data);
		Bl = Bl->next; 
	}
}

void Clear_Stack(Stack* q)
{
	if(!Empty_Stack)
	{
		return; 
	}
	else
	{
		SNode *s = NULL;
		while(q->top!=q->base)
		{
			s = q->top;
			q->top = q->top->next;
			free(s);
		}
	}
}
	//����ת�� 
void Conversion()
{
	int N,s; 
	Stack* q;
	q = (Stack*)malloc(sizeof(StackNode));
	init_Stack(q);
	printf("������ʮ��������");
	scanf("%d",&N);
	printf("����������ת�ɵĽ��ƣ�");
	scanf("%d",&s);
	while(N)
	{
		Push(q,N%s);
		N = N/s;
	}
	while(Empty_Stack(q))
	{
		printf("%d",Pop(q));
	}
}
	//������ 
int main()
{
	Conversion();
}

