#include<stdio.h> 
#include<stdlib.h>

typedef struct List{
	char data;
	struct List *next;
}List;

List *p,*q,*head;
int m = sizeof(List);

void create()
{
	int i = 0;
	head = (List*)malloc(m);
	p = head;
	for( i=0 ; i<25 ; i++)
	{
	    p->data = 'a'+i;
		p->next = (List*)malloc(m);
		p = p->next;
	}
	p->data = 'a'+i;
	p->next = NULL;
}

void display()
{
	p = head;
	while(p->next != NULL)
	{
		printf("%c",p->data);
		p = p->next;
	}
	printf("%c\n",p->data);
}

void insert()
{
	int a,j;
	char b;
	printf("请输入插入字母的位置：");
	scanf("%d",&a);
	fflush(stdin);
	printf("请输入要插入的字母：");
	scanf("%c",&b);
	fflush(stdin);
	p = head;
	for(j=0 ; j<a-1 ; j++)
	{
		p = p->next;
	}
	q = (List*)malloc(m);
	q->data = b;
	q->next = p->next;
	p->next = q;
	display();
}

void Listdelete()
{
	List *s,*k;
	char del;
	int g=0; 
	printf("请输入要删除的字母：");
	scanf("%c",&del);
	s = head;
	k = head;
	while(s->next != NULL)
	{	
		if(s->data == del)
		{
			for(int h=0 ; h<g-1 ; h++)
			{
				k = k->next;
			}
			k->next = s->next;
			free(s);
			break;
		}
		s = s->next; 
		g++;		
	}
	display();
}

void search()
{
	int sea;
	printf("请输入要查找的字母：");
	scanf("%d",&sea);
	fflush(stdin);
	p = head;
	for(int i=0 ; i<sea-1 ;i++)
	{
		p = p->next;
	}
	printf("该字母的位置在第\n",p->data);
}

void modify()
{
	int mod;
	char le; 
	printf("请输入要改正的字母位置：");
	scanf("%d",&mod);
	fflush(stdin);
	printf("请输入改正后的字母");
	scanf("%c",&le);
	p = head;
	for(int i=0 ; i<mod-1 ;i++)
	{
		p = p->next;
	}
	p->data = le;
	display();
}

int main()
{
	create();
	display();
	insert();
	Listdelete();
	search();
	modify();
}

