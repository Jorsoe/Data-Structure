#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Stack_ADT.cpp"
#define MAX_VERTEX_NUM 20			//���ڵ����
#define NAME_LENGTH 5				//���ڵ���Ϣ����
#define ERROR 0
#define OK 1

int *ve;							//���緢��ʱ�� 

typedef int InfoType;
typedef char VertexType[NAME_LENGTH];

typedef struct ArcNode{
	int adjvex;							//�û���ָ��Ľڵ��λ��
	struct ArcNode *nextarc;			//ָ����һ������ָ��
	InfoType *info;						//�û������Ϣ��ָ�루Ȩֵָ�룩
}ArcNode;

typedef struct VNode{
	VertexType data;					//�ڵ���Ϣ
	ArcNode *firstarc;					//ָ���һ�������ڸö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum,arcnum;					//ͼ�ĵ�ǰ�ڵ����ͻ���
	int *indegree;						//ͼ�нڵ���������ָ��
}ALGraph;
//��ýڵ㣨Vex_A,Vex_B���±�
int Get_Locate_Vex(ALGraph Graph,char Vex[NAME_LENGTH])
{
    int i;
    for(i=0;i<Graph.vexnum;i++)
	{
        if(strcmp(Vex,Graph.vertices[i].data)==0)		//strcmp���ã��Ƚ�Vex��data����ȷ���0
        {
            return i;
		}
    }
    printf("û�иýڵ�!\n");
    return i;
}
//Ѱ�����нڵ�����
void FindVertexOfIndegree(ALGraph *Graph)
{
	for(int i=0;i<Graph->vexnum;i++)
	{
		Graph->indegree[i] = 0;
	}
	for(int j=0;j<Graph->vexnum;j++)
	{
		ArcNode *q = Graph->vertices[j].firstarc;
		while(q)
		{
			Graph->indegree[q->adjvex] ++;		//���ڽӵ���������ڶ�Ӧ��ֵ ��1
			q = q->nextarc;
		}
	}
}
//����������
void Create_Graph(ALGraph *Graph){
    int m,n,k;
    char Vex_A[NAME_LENGTH];       			//��β�ڵ����飨char�� ����Ϊ NAME_LENGTH
	char Vex_B[NAME_LENGTH];      			//��ͷ�ڵ����飨char�� ����Ϊ NAME_LENGTH
    ArcNode *Q;
    int value;								//�Ӽ���¼��Ȩֵ����ѭ���и���info

    printf("������ڵ����ͻ���(�ڵ���vexnum ����arcnum):\n");
    scanf("%d %d",&Graph->vexnum,&Graph->arcnum);
    fflush(stdin);

    printf("����������ڵ���Ϣ(�ڵ�����data):\n");
    for(m=0;m<Graph->vexnum;m++)
	{
        scanf("%s",Graph->vertices[m].data);        //���ڵ���Ϣ¼��
        fflush(stdin);
        Graph->vertices[m].firstarc = NULL;
    }
    Graph->indegree = (int*)malloc(Graph->vexnum * sizeof(int));     //����indegree���飬���ڴ����ȣ�����Ϊvexnum
    //�����ڽӱ�
    printf("������һ��%d�����Ļ�β�ڵ㡢��ͷ�ڵ��Ȩֵ(��β�ڵ�Vex_A ��ͷ�ڵ�Vex_B Ȩֵvalue):\n",Graph->arcnum);
    for(k=0;k<Graph->arcnum;k++)
	{
        scanf("%s %s %d",Vex_A,Vex_B,&value);
        fflush(stdin);

        m = Get_Locate_Vex(*Graph,Vex_A);                   //��ȡ����v1�±� ��β
        n = Get_Locate_Vex(*Graph,Vex_B);                   //��ȡ����v2�±� ��ͷ

        Q=(ArcNode*)malloc(sizeof(ArcNode));
        Q->adjvex = n;
        Q->info = (int*)malloc(sizeof(int));
        *(Q->info) = value;

        Q->nextarc = Graph->vertices[m].firstarc;
        Graph->vertices[m].firstarc = Q;          		  //ͷ���ָ��
    }
}
//��������
int Topological_Sort(ALGraph Graph,Stack stack ,Stack *T)
{
	ArcNode *p;								//��ʼ����ָ��
	int i,j,z,Adr;							//ij���ڿ���ѭ����Adr�ڽӽڵ��λ�ã����adjvex��
	int count = 0;							//countΪ�Ѿ�ɾ���Ľڵ����������жϸ�ͼ����û�л���
	int *indegree;
	FindVertexOfIndegree(&Graph);			//�Ը����ڵ������
	indegree = Graph.indegree;
	Init_Stack(&stack);						//��������Ƚڵ�ջstack
	Init_Stack(T);
	ve = (int*)malloc(Graph.vexnum*sizeof(int));	//��������ΪGraph.vexcum������
	for(i=0;i<Graph.vexnum;i++)
	{
		if(!indegree[i])					//���Ϊ0��ջ
		{
			Push_Stack(&stack,i);
		}
	}
	for(z=0;z<Graph.vexnum;z++)
	{
		ve[z] = 0;							//��ʼ��ve����
	}
	while(!Empty_Stack(&stack))
	{
		j = Pop_Stack(&stack);
		Push_Stack(T,j);
		printf("%s-> ",Graph.vertices[j].data);
		++count;							//����
		for(p = Graph.vertices[j].firstarc;p;p = p->nextarc)
		{
			Adr = p->adjvex;
			if(!(--indegree[Adr]))			//��i�Žڵ����ȼ�1���ж�����Ƿ�Ϊ0
			{
				Push_Stack(&stack,Adr);		//����ȼ�Ϊ0����ջ
			}
			if(ve[j]+*(p->info) > ve[Adr])
			{
				ve[Adr] = ve[j] + *(p->info);
			}
		}
	}
	if(count < Graph.vexnum)				//�жϸ�ͼ���޻�·
	{										//���л�·��ȫ���ڵ��޷��������
		printf("\n����������л�!\n"); 		//�������С�ڽڵ���
		return ERROR;
	}
	else									//��֮
	{										//�ڵ�ȫ�������������������
		printf("\n�����������!\n");
		return 	OK;
	}
}
//�ؼ�·��
int Critical_Path(ALGraph Graph,Stack stack)
{
    int i,j,k,ee,el,dut;
    char tag;
    int *vl;
    vl = (int*)malloc(Graph.vexnum * sizeof(int));
    ArcNode *p;

    for(i = 0; i < Graph.vexnum ; i++)
	{
        vl[i] = ve[Graph.vexnum-1];
       // printf("v1[i] = %d \n",vl[i]);
    }
    //����������
    while(!Empty_Stack(&stack))
	{
        j = Pop_Stack(&stack);                        //����ջ��Ԫ�� �������е����򵯳������±�
        for(p = Graph.vertices[j].firstarc ; p ; p = p->nextarc )
		{
            k = p->adjvex ;                           //��ȡ j�����µ� ���ڽӶ����±꣬����Ϊ�յ�ʱ��,ѭ�������
            dut = *(p->info);
            //printf("dut = = %d\t",dut);
            if(vl[k] - *(p->info) < vl[j])            //*(p->info) == dut(<j,k>)
            {
                vl[j] = vl[k] - dut;
			}
        }
    }
//    printf("j\tk\tdut\tee\tel\ttag\n");
    for(j = 0; j < Graph.vexnum ; j++)
	{
       for( p =Graph.vertices[j].firstarc ; p ; p = p->nextarc)
	   {
            k = p->adjvex;
            dut = *(p->info);
            ee = ve[j];                                 //e(i) = ve(j)
            el = vl[k] - dut;                    		//l(i) = vl(k) - dut(<j,k>)
            tag = (ee == el)? '*':' ';
//            printf("%d\t%d\t%d\t%d\t%d\t%c\n",j,k,*(p->info),ee,el,tag);
            if(tag == '*')
            {
                printf("%s -> %s \n",Graph.vertices[j].data,Graph.vertices[k].data);
			}
		}
    }
    printf("�ؼ�·�����ȣ�%d\n",ve[Graph.vexnum-1]);
    return OK;
}

int main()
{
	Stack stack ,T;
	ALGraph Graph;
	Create_Graph(&Graph);
	Topological_Sort(Graph,stack,&T);
	Critical_Path(Graph,T);
	return 0;
}

