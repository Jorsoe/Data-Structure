#include<stdio.h>
#include<stdlib.h>
//节点定义
typedef struct node{
	int data;
	struct node *next;
}Node,*pNode;
//栈定义
typedef struct stack{
	pNode top;
	pNode bottom;
}Stack,*pStack;
//建立空栈
void Init_Stack(pStack a)
{
	a->top=(pNode)malloc(sizeof(Node));
	if(a->top==NULL)
	{
		printf("内存分配失败！");
	}
	else{
		a->bottom=a->top;
		a->top->next=NULL;
	}
}
//入栈
void Push_Stack(pStack a,int val)
{
	pNode p=(pNode)malloc(sizeof(Node));
	p->data=val;
	p->next=a->top;
	a->top=p;
}
//判断是否栈空
int Empty_Stack(pStack a)
{
	if(a->top==a->bottom){
		return 1;
	}
	else{
		return 0;
	}
 }
//出栈
int Pop_Stack(pStack a)
{
	int temp;
	if(Empty_Stack(a)){
		printf("栈为空，出栈失败");
		return -1;
	}
	else{
		pNode p;
		p=a->top;
		temp=p->data;
		a->top=p->next;
		free(p);
		return temp;
	}
}
//遍历栈
void Travers_Stack(pStack a)
{
	pNode p;
	p=a->top;
	while(p!=a->bottom){
		printf("%d ",p->data);
		p=p->next;
	}
}
//获得栈顶元素
int GetTop_Stack(pStack a)
{
	int value;
	value=a->top->data;
	return value;
}


