#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Stack_ADT.cpp"
#define MAX_VERTEX_NUM 20			//最大节点个数
#define NAME_LENGTH 5				//最大节点信息长度
#define ERROR 0
#define OK 1

int *ve;							//最早发生时间 

typedef int InfoType;
typedef char VertexType[NAME_LENGTH];

typedef struct ArcNode{
	int adjvex;							//该弧所指向的节点的位置
	struct ArcNode *nextarc;			//指向下一条弧的指针
	InfoType *info;						//该弧相关信息的指针（权值指针）
}ArcNode;

typedef struct VNode{
	VertexType data;					//节点信息
	ArcNode *firstarc;					//指向第一条依附在该定点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum,arcnum;					//图的当前节点数和弧数
	int *indegree;						//图中节点的入度数组指针
}ALGraph;
//获得节点（Vex_A,Vex_B）下标
int Get_Locate_Vex(ALGraph Graph,char Vex[NAME_LENGTH])
{
    int i;
    for(i=0;i<Graph.vexnum;i++)
	{
        if(strcmp(Vex,Graph.vertices[i].data)==0)		//strcmp作用：比较Vex与data，相等返回0
        {
            return i;
		}
    }
    printf("没有该节点!\n");
    return i;
}
//寻找所有节点的入度
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
			Graph->indegree[q->adjvex] ++;		//给邻接点入度数组内对应的值 加1
			q = q->nextarc;
		}
	}
}
//创建有向网
void Create_Graph(ALGraph *Graph){
    int m,n,k;
    char Vex_A[NAME_LENGTH];       			//弧尾节点数组（char） 长度为 NAME_LENGTH
	char Vex_B[NAME_LENGTH];      			//弧头节点数组（char） 长度为 NAME_LENGTH
    ArcNode *Q;
    int value;								//从键盘录入权值，在循环中赋给info

    printf("请输入节点数和弧数(节点数vexnum 弧数arcnum):\n");
    scanf("%d %d",&Graph->vexnum,&Graph->arcnum);
    fflush(stdin);

    printf("请输入各个节点信息(节点名称data):\n");
    for(m=0;m<Graph->vexnum;m++)
	{
        scanf("%s",Graph->vertices[m].data);        //将节点信息录入
        fflush(stdin);
        Graph->vertices[m].firstarc = NULL;
    }
    Graph->indegree = (int*)malloc(Graph->vexnum * sizeof(int));     //建立indegree数组，用于存放入度，长度为vexnum
    //构建邻接表
    printf("请输入一共%d个弧的弧尾节点、弧头节点和权值(弧尾节点Vex_A 弧头节点Vex_B 权值value):\n",Graph->arcnum);
    for(k=0;k<Graph->arcnum;k++)
	{
        scanf("%s %s %d",Vex_A,Vex_B,&value);
        fflush(stdin);

        m = Get_Locate_Vex(*Graph,Vex_A);                   //获取顶点v1下标 弧尾
        n = Get_Locate_Vex(*Graph,Vex_B);                   //获取顶点v2下标 弧头

        Q=(ArcNode*)malloc(sizeof(ArcNode));
        Q->adjvex = n;
        Q->info = (int*)malloc(sizeof(int));
        *(Q->info) = value;

        Q->nextarc = Graph->vertices[m].firstarc;
        Graph->vertices[m].firstarc = Q;          		  //头结点指向弧
    }
}
//拓扑排序
int Topological_Sort(ALGraph Graph,Stack stack ,Stack *T)
{
	ArcNode *p;								//初始化弧指针
	int i,j,z,Adr;							//ij用于控制循环，Adr邻接节点的位置（存放adjvex）
	int count = 0;							//count为已经删除的节点数（用于判断该图中有没有环）
	int *indegree;
	FindVertexOfIndegree(&Graph);			//对各个节点求入度
	indegree = Graph.indegree;
	Init_Stack(&stack);						//建立零入度节点栈stack
	Init_Stack(T);
	ve = (int*)malloc(Graph.vexnum*sizeof(int));	//创建长度为Graph.vexcum的数组
	for(i=0;i<Graph.vexnum;i++)
	{
		if(!indegree[i])					//入度为0进栈
		{
			Push_Stack(&stack,i);
		}
	}
	for(z=0;z<Graph.vexnum;z++)
	{
		ve[z] = 0;							//初始化ve数组
	}
	while(!Empty_Stack(&stack))
	{
		j = Pop_Stack(&stack);
		Push_Stack(T,j);
		printf("%s-> ",Graph.vertices[j].data);
		++count;							//计数
		for(p = Graph.vertices[j].firstarc;p;p = p->nextarc)
		{
			Adr = p->adjvex;
			if(!(--indegree[Adr]))			//对i号节点的入度减1并判断入度是否为0
			{
				Push_Stack(&stack,Adr);		//若入度减为0，进栈
			}
			if(ve[j]+*(p->info) > ve[Adr])
			{
				ve[Adr] = ve[j] + *(p->info);
			}
		}
	}
	if(count < Graph.vexnum)				//判断该图有无回路
	{										//若有回路则全部节点无法遍历完成
		printf("\n这个有向网有环!\n"); 		//计数结果小于节点数
		return ERROR;
	}
	else									//反之
	{										//节点全部遍历，拓扑排序完成
		printf("\n拓扑排序完成!\n");
		return 	OK;
	}
}
//关键路径
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
    //逆拓扑排序
    while(!Empty_Stack(&stack))
	{
        j = Pop_Stack(&stack);                        //弹出栈顶元素 拓扑序列的逆序弹出顶点下标
        for(p = Graph.vertices[j].firstarc ; p ; p = p->nextarc )
		{
            k = p->adjvex ;                           //获取 j顶点下的 各邻接顶点下标，当有为空的时候,循环会结束
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
    printf("关键路径长度：%d\n",ve[Graph.vexnum-1]);
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

