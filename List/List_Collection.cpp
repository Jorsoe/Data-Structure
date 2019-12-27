#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	struct LNode *next;
}LinkNode,*LinkList;

LinkList build(LinkList L,int n)
{
	LinkList p;
	int i;
	printf("请输入集合元素");
	L = (LNode*)malloc(sizeof(LNode));
	p = L;
	scanf("%d",&p->data);
	for(i=1;i<n;i++)
	{
		p->next = (LinkNode*)malloc(sizeof(LNode));
		p = p->next;
        scanf("%d",&p->data);
	}
	p->next = NULL;
	return L;
}

LinkList Intersection(LinkList L1,LinkList L2)
{
	LinkList Set;
	LinkList z;
	LinkList s;
	s = L2;
	Set = (LinkNode*)malloc(sizeof(LNode));
	z = Set;
	while(L1!=NULL)
	{ 
		L2 = s;
		while(L2!=NULL)
		{
			if(L1->data==L2->data)
			{
				z->data = L1->data;
				z->next = (LinkNode*)malloc(sizeof(LNode));
				z = z->next;				
			}
			L2 = L2->next;
		}
		L1 = L1->next; 
	}
	z->next = NULL;
	return Set;
}

LinkList Union(LinkList L1,LinkList L2)
{
	LinkList Set;
	LinkList p,q,z;
	Set = (LinkNode*)malloc(sizeof(LNode));
	p = L1;
	q = L2;
	z = Set;
	while(q!=NULL)
	{
		L1 = p;
		while(p!=NULL)
		{
			if(q->data > p->data)
			{
				z->next = p->next;
				p->next = z;
			}
			p = p->next;
		}
		q = q->next;
	}
	return L1;
}

void print(LinkList L)
{
	LinkList p;
	p = L;
	while(p)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	LinkList La,Lb,Lc,Ld;
	int na,nb;
	La = (LNode*)malloc(sizeof(LNode));
    Lb = (LNode*)malloc(sizeof(LNode));
	printf("请输入集合A元素个数");
	scanf("%d",&na);
	La = build(La,na);
	printf("请输入集合B元素个数");
	scanf("%d",&nb);
    Lb = build(Lb,nb);

	print(La);
	print(Lb);
	
	printf("两集合的交集为："); 
	Lc = Intersection(La,Lb);
	print(Lc);
	printf("两集合的并集为：");
	Ld = Union(La,Lb);
	print(Ld);
}

