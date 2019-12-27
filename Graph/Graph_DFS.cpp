#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>             		
#define INFINITY    INT_MAX     
#define Max_VERTEX_NUM 20       
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX_NAME 5               

/**
*图的邻接矩阵的ADT
*/

typedef enum{DG , DN , UDG , UDN}GraphKind;     
typedef char VertexType[MAX_NAME];   
typedef int InfoType;
typedef int Status;
int visited[Max_VERTEX_NUM];	
void(*VisitFunc)(char *v);	

typedef struct arcCell{  
    int       adj ;         
    InfoType *info;        
}ArcCell, AdjMatrix[Max_VERTEX_NUM][Max_VERTEX_NUM];

typedef struct mgraph{
    VertexType vexs[Max_VERTEX_NUM];        
    AdjMatrix  arcs;                       
    int        vexnum , arcnum;            
    GraphKind  kind;                        
}MGraph;

//函数声明
int LocateVex(MGraph g , char v[MAX_NAME]);
Status CreateDG(MGraph *g);
Status CreateDN(MGraph *g);
Status CreateUDG(MGraph *g);
Status CreateUDN(MGraph *g);

/**
*顺序队列的ADT
*实现 构造，入队，出对，对空，队满
*将队列做为循环栈最好
*/
typedef int ElemType;   //元素数据类型，可以根据需求自定义类型
typedef int Status ;    //定义的函数数据类型

typedef struct queue{
    ElemType *qBase;    //队列数组
    ElemType front;    //队头指针
    ElemType rear;     //队尾指针
    int queueSize;      //队列的大小，就是元素个数，或者空间大小
}SqQueue;

/**队列的构建
* q 为队列指针
*/
Status InitQueue(SqQueue *q){
    q->qBase = (ElemType*)malloc(QUEUE_INIT_SIZE * sizeof(ElemType));
    if(!q->qBase)
        exit(ERROR);    //分配空间失败
    q->front = 0;   //开始队头指向数组开头
    q->rear = 0;    //开始队尾指向数组开头
    return OK;
}

/**销毁队列
* q 为队列指针
*/
void destroyQueue(SqQueue * q)
{
    free(q);  //释放队列数组指针指向的内存
    q = NULL;    //队列数组指针重新指向NULL,避免成为野指针
}

/**判断队满
*/
Status isFullQueue(SqQueue q){
    if((q.rear+1)%q.queueSize == q.front) return TRUE;//队满

    return FALSE;
}

/**判断队空*/
Status isEmpityQueue(SqQueue q){
    if(q.front == q.rear) return TRUE; //队空
    return FALSE;
}

/**入队 插入元素
*   q为队列指针 e为插入的元素
*/
Status EnQueue(SqQueue *q , ElemType e ){
    //判断是否队满
    if(isFullQueue(*q)) {
        printf("队满\n");
        return ERROR; //队满
    }
    q->qBase[q->rear] = e;                        //插入元素
    q->rear = (q->rear + 1) % q->queueSize;       //队尾后移 保证了循环
    return OK;
}

/**获取队头元素
* q为队列指针 e为要接收的元素的变量地址
*/
Status GetHead(SqQueue q , ElemType *e){
    //判断是否为队空
    if(isEmpityQueue(q)){
        printf("队列为空\n");
        return ERROR;
    }
    *e = q.qBase[q.front];
    return OK;
}

/**出队
*   q为队列指针 e为要接收的元素的变量地址
* 删除队头元素
*/
Status DeQueue(SqQueue *q , ElemType *e){
    //判断是否为队空
    if(isEmpityQueue(*q)){
        printf("队列为空\n");
        return ERROR;
    }
    *e = q->qBase[q->front];
    q->front = (q->front + 1) % q->queueSize;//移到下一个位置
    return OK;
}

/**队列长度
* q 为队列
*/
Status QueueLength(SqQueue q){
    return q.queueSize;
}



/**构建图**/
Status CreateGraph(MGraph *g){
    int k;
    
    printf("0.有向图 1.有向网 2.无向图 3.无向网\n");
    scanf("%d",&k);
    g->kind=(GraphKind)k;

    switch(g->kind){
        case  DG: return CreateDG(g);     
        case  DN: return CreateDN(g);    
        case UDG: return CreateUDG(g);    
        case UDN: return CreateUDN(g);  
    }

}

/**有向图构建
*/
Status CreateDG(MGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];
    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vexs[i]);   
        fflush(stdin);
    }
    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            g->arcs[i][j].adj=0;            
            g->arcs[i][j].info = NULL;     
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点(数据间用空格隔开)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);
        i = LocateVex(*g,v1);              
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = 1;             
    }
    return OK;

}

/**有向网构建**/
Status CreateDN(MGraph *g){
    char v1[MAX_NAME],v2[MAX_NAME];     //邻接矩阵的行向量v1 列向量v2（弧的两个端点）
    int w;          //w为权值
    int i,j,k;

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vexs[i]);   //构建顶点向量
        fflush(stdin);
    }
    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            g->arcs[i][j].adj=INFINITY; 
            g->arcs[i][j].info = NULL;   
        }
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点，权值：(数据间用空格隔开)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);
        i = LocateVex(*g,v1);              
        j = LocateVex(*g,v2);
        g->arcs[i][j].adj = w;              

    )
    return OK;
}

/**无向图构建**/
Status CreateUDG(MGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];  

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vexs[i]); 
        fflush(stdin);
    }
    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            g->arcs[i][j].adj=0;   
            g->arcs[i][j].info = NULL;     
        })
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点(数据间用空格隔开)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);
        i = LocateVex(*g,v1);        
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = 1;             
        g->arcs[j][i] = g->arcs[i][j];     
    }
    return OK;

}

/**无向网构建
*/
Status CreateUDN(MGraph *g){
    char v1[MAX_NAME],v2[MAX_NAME];    
    int w;        
    int i,j,k;

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vexs[i]);  
        fflush(stdin);
    }

    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            g->arcs[i][j].adj=INFINITY;  
            g->arcs[i][j].info = NULL;     
        }
    }

    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点，权值：(数据间用空格隔开)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);
        i = LocateVex(*g,v1);           
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = w;             
        g->arcs[j][i] = g->arcs[i][j];     
    }
    return OK;

}

/**获取顶点的下标**/
int LocateVex(MGraph g , char v[MAX_NAME]){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(strcmp(v,g.vexs[i])==0)
            return i;
    }
    printf("未找到顶点!\n");
    return i;
}//LocateVex

/**打印邻接矩阵**/
void ListGraph(MGraph g){
    int i,j;
    printf("输出邻接矩阵:\n");
    for(i=0;i<g.vexnum;i++){
        printf("%s----",g.vexs[i]);
        for(j=0;j<g.vexnum;j++){
            if((g.kind == DN || g.kind == UDN) && g.arcs[i][j].adj == INFINITY){
                printf("  ∞"); 
                continue;
            }
            printf("%4d",g.arcs[i][j].adj);
        }
        printf("\n");
    }
}

/** 返回v的第一个邻接顶点的序号。**/
int FirstAdjVex(MGraph g,VertexType v)
{
    int i;
	int u;          
	u = LocateVex(g,v);
	for(i=0;i<g.vexnum;i++){  //遍历所有顶点
        if(g.arcs[u][i].adj != 0 && g.arcs[u][i].adj != INFINITY && !visited[i]) /
            return i;
	}
	return -1;

/**返回v（相对于w）下一个邻接结点。**/
int NextAdjVex(MGraph g , VertexType v,VertexType w ){
    int v1,w1;          
    v1 = LocateVex(g,v);
    w1 = LocateVex(g,w);

    for(i = w1; i< g.vexnum ; i++){
        if(g.arcs[v1][i].adj !=0 && g.arcs[v1][i].adj != INFINITY && !visited[i])
            return i;
    }
    return -1;
}

/**打印顶点**/
void print(char *a){
    printf("%s",a);
}

void DFS(MGraph g , int v){
    int w;                          
    visited[v] = TRUE;            
    VisitFunc(g.vexs[v]);           
    for(w = FirstAdjVex(g,g.vexs[v]) ; w>=0 ; w = NextAdjVex(g , g.vexs[v] ,g.vexs[w]))
        if(!visited[w])
            DFS(g,v);
}

/**DFSTraverse 深度优先搜索**/
void DFSTraverse(MGraph g , void(*Visit)(char *a)){
    int v;                          
    VisitFunc = Visit;              
    for(v=0;v<g.vexnum;v++)
        visited[v] = FALSE;         
    for(v=0;v<g.vexnum;v++)
        if(!visited[v])             
            DFS(g,v);
}

int main()
{
    MGraph g;
    CreateGraph(&g);
    ListGraph(g);
    return 0;
}

