#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
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
int GetTop_Stack(Stack* q);
void Push(Stack* q,int e);
int Pop(Stack* q);
void Traverse_Stack(Stack* q);
void Clear_Stack(Stack* q); 

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
int GetTop_Stack(Stack* q)
{
    SNode* a=q->top;
    return a->data;
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
	// 
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
	//运算符优先级表格 
char Precede(char T1,char T2)
{  
    int i,j;  
    char Operator[7][7]={            
        {'>','>','<','<','<','>','>'},  
        {'>','>','<','<','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'<','<','<','<','<','=','0'},  
        {'>','>','>','>','0','>','>'},  
        {'<','<','<','<','<','0','='}};  
    switch(T1)
	{  
        case '+': i=0; break;  
        case '-': i=1; break;  
        case '*': i=2; break;  
        case '/': i=3; break;  
        case '(': i=4; break;  
        case ')': i=5; break;  
        case '=': i=6; break;  
    }  
    switch(T2)
	{  
        case '+': j=0; break;  
        case '-': j=1; break;  
        case '*': j=2; break;  
        case '/': j=3; break;  
        case '(': j=4; break;  
        case ')': j=5; break;  
        case '=': j=6; break;  
    }  
    return Operator[i][j];  
}
	//判断是否为运算符 
int In(char c)
{
    switch(c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '=':
        return TRUE;
    default:
        return FALSE;
    }
}

int Operation(int a,char theta,int b)
{
    int c;
    switch(theta)
    {
	    case '+':
	        c = a + b;
	        break;
	    case '-':
	        c = a - b;
	        break;
	    case '*':
	        c = a * b;
	        break;
	    case '/':
	        c = a / b;
	        break;
    }
    return c;
}

int EvaluateExpression()
{
	char c;
	char theta;
	char z[10];
	char a,b,result,d,x;
	int i;
	Stack* OPTR;
	Stack* OPND;
	OPTR = (Stack*)malloc(sizeof(StackNode));
	OPND = (Stack*)malloc(sizeof(StackNode));
	Push(OPTR,(int)'#');
	c = getchar();
	x = GetTop_Stack(OPTR);
	while(c!='#'||(char)GetTop_Stack(OPTR)!='#')
	{
		if(!In(c))
		{
			switch(Precede((char)GetTop_Stack(OPTR),c))
			{
			case'<':
				Push(OPTR,(int)c);
				c = getchar();
				break;
			case'=':
				Pop(OPTR);
				c = getchar();
				break;
			case'>':
				theta = (char)Pop(OPTR);
				a = Pop(OPND);
				b = Pop(OPND);
				result = Operation(a,theta,b);
				Push(OPND,result);
				c = getchar();
				break;
			}
		}
		else if(c>='0'&&c<='9')
        {
            i = 0;
            do
            {
                z[i] = c;
                i++;
                c = getchar();
            }
			while(c>='0'&&c<='9');
            z[i] = 0;
            d = atoi(z);
            Push(OPND,d);
        }
        else
        {
            printf("非法字符！\n");
        }
        GetTop_Stack(OPTR);
    }
    result = GetTop_Stack(OPND);
    printf("%d",result);
}
	//主函数 
int main()
{
	EvaluateExpression();
}

