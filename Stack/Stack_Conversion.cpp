#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
	//节点定义 
typedef struct Node{
	int data;		//数据域 
	struct Node* next;		//指针域 
}SNode;
	//栈定义 
typedef struct StackNode{
	SNode* top;		//栈顶指针 
	SNode* base;	//栈底指针 
}Stack;

	//函数声明 
void init_Stack(Stack* q);
int Empty_Stack(Stack* q);
void GetTop_Stack(Stack* q);
void Push(Stack* q,int e);
int Pop(Stack* q);
void Traverse_Stack(Stack* q);
void Clear_Stack(Stack* q); 
void Conversion();

	//初始化栈 
void init_Stack(Stack* q)
{
	q->base = (SNode*)malloc(sizeof(Node));
	q->top = q->base;
	q->top->next = NULL;
	printf("空栈创建完成!\n");
}
	// 判断是否栈空栈满 
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
	//获得栈顶元素 
void GetTop_Stack(Stack* q)
{
    SNode* a=q->top;
    printf("%d\n",a->data);
}
	//进栈 
void Push(Stack* q,int e)
{
	SNode* s = (SNode*)malloc(sizeof(Node)); 
	s->data = e;
	s->next = q->top;
	q->top = s;
}
	//出栈 
int Pop(Stack* q)
{
	int e;
	SNode* p;
	if (!Empty_Stack(q))
	{
		printf("空栈!\n");
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
	//打印栈里面的值 
void Traverse_Stack(Stack* q)
{
	SNode* Bl;
	Bl = q->top;
	printf("栈中的元素是："); 
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
	//数制转换 
void Conversion()
{
	int N,s; 
	Stack* q;
	q = (Stack*)malloc(sizeof(StackNode));
	init_Stack(q);
	printf("请输入十进制数：");
	scanf("%d",&N);
	printf("请输入你想转成的进制：");
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
	//主函数 
int main()
{
	Conversion();
}

