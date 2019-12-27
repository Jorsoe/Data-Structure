#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>             
#define INFINITY    INT_MAX     
#define Max_VERTEX_NUM 20       
#define MAX_NAME 5              
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
/**
*邻接表
*/

typedef enum{DG , DN , UDG , UDN}GraphKind;     
typedef char VertexType[MAX_NAME];              
typedef int InfoType;                          
typedef int Status;
int visited[Max_VERTEX_NUM];	
void(*VisitFunc)(char *v);		

typedef struct arcNode{        
    int adjvex;                 
    struct arcNode *nextarc;    
    InfoType *info;           
}ArcNode;

typedef struct vnode{          
    VertexType data;            
    ArcNode *firstarc;          
}VNode , AdjList[Max_VERTEX_NUM];

typedef struct algraph{
    AdjList vertices;           
    int vexnum,arcnum;          
    int kind;                   
}ALGraph;

int LocateVex(ALGraph g , char v[MAX_NAME]);
Status CreateDG(ALGraph *g);
Status CreateDN(ALGraph *g);
Status CreateUDG(ALGraph *g);
Status CreateUDN(ALGraph *g);
void DFS(ALGraph g , int v);

/**创建邻接表
*   g 为邻接表指针
*/

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


Status CreateGraph(ALGraph *g){
    printf("0.有向图 1.有向网 2.无向图 3.无向网\n");
    scanf("%d",&g->kind);

    switch(g->kind){
        case  DG: return CreateDG(g);    
        case  DN: return CreateDN(g);    
        case UDG: return CreateUDG(g);   
        case UDN: return CreateUDN(g);   
        default: return ERROR;
    }

}

/**有向图构建
*/
Status CreateDG(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                 

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);        
        fflush(stdin);
        g->vertices[i].firstarc = NULL;        
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点(数据间用空格隔开)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);

        i = LocateVex(*g,v1);                   
        j = LocateVex(*g,v2);                   

        p=(ArcNode*)malloc(sizeof(ArcNode));    
        p->adjvex = j;                        

        p->info = NULL;                        

        p->nextarc = g->vertices[i].firstarc;   
        g->vertices[i].firstarc = p;            
    }//for(k)
    return OK;
}//CreateDG

/**有向网构建
*/
Status CreateDN(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];             //邻接矩阵的行向量v1 列向量v2（弧的两个端点）
    ArcNode *p;                                 //弧指针 作为每个表结点
    int w;                                      //w为权值

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);       
        fflush(stdin);
        g->vertices[i].firstarc = NULL;        
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点，权值：(数据间用空格隔开)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);
        i = LocateVex(*g,v1);                  
        j = LocateVex(*g,v2);                   
        p=(ArcNode*)malloc(sizeof(ArcNode));   
        p->adjvex = j;                         
        p->info = (int*)malloc(sizeof(int));   
        *(p->info) = w;
        p->nextarc = g->vertices[i].firstarc;   
        g->vertices[i].firstarc = p;           
    }
    return OK;
}

/**无向图构建
*/
Status CreateUDG(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                
    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);       
        fflush(stdin);
        g->vertices[i].firstarc = NULL;         
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点(数据间用空格隔开)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);
        i = LocateVex(*g,v1);                   
        j = LocateVex(*g,v2);                   
        p=(ArcNode*)malloc(sizeof(ArcNode));    
        p->adjvex = j;                         
        p->info = NULL;                         
        p->nextarc = g->vertices[i].firstarc;   
        g->vertices[i].firstarc = p;           
        p=(ArcNode*)malloc(sizeof(ArcNode));    
        p->adjvex = i;                          
        p->info = NULL;                         
        p->nextarc = g->vertices[j].firstarc;   
        g->vertices[j].firstarc = p;            

    }
    return OK;
}

/**无向网构建
*/
Status CreateUDN(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                 
    int w;                                      

    printf("请输入顶点数，弧数\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("请输入各顶点名称:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);        
        fflush(stdin);
        g->vertices[i].firstarc = NULL;         
    }
    for(k=0;k<g->arcnum;k++){
        printf("请输入第%d弧的第一端点，第二端点，权值：(数据间用空格隔开)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);

        i = LocateVex(*g,v1);                   
        j = LocateVex(*g,v2);                   
        p=(ArcNode*)malloc(sizeof(ArcNode));    
        p->adjvex = j;                         
        p->info = (int*)malloc(sizeof(int));    
        *(p->info) = w;

        p->nextarc = g->vertices[i].firstarc;   
        g->vertices[i].firstarc = p;            
        p=(ArcNode*)malloc(sizeof(ArcNode));    
        p->adjvex = j;                          
        p->info = (int*)malloc(sizeof(int));    
        *(p->info) = w;
        p->nextarc = g->vertices[i].firstarc;   
        g->vertices[i].firstarc = p;           
    }
    return OK;
}

/**获取顶点的下标*/
int LocateVex(ALGraph g , char v[MAX_NAME]){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(strcmp(v,g.vertices[i].data)==0)
            return i;
    }
    printf("未找到顶点!\n");
    return i;
}//LocateVex

/** 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1。**/
int FirstAdjVex(ALGraph g,VertexType v)
{
	ArcNode *p;
	int v1;

	v1 = LocateVex(g,v);
	p = g.vertices[v1].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}
/**返回v（相对于w）下一个邻接结点。*/
int NextAdjVex(ALGraph g , VertexType v,VertexType w ){
    ArcNode *p;
    int v1,w1;          

    v1 = LocateVex(g,v);
    w1 = LocateVex(g,w);

    p = g.vertices[v1].firstarc;    
    while(!p&&p->adjvex != w1)      
        p=p->nextarc;              

    if(!p || !p->nextarc)           
        return -1;
    else                            
        return p->nextarc->adjvex;  
}


/**打印顶点*/
void print(char *a){
    printf("%s",a);
}//print


/**BFS 广度优先搜索遍历
思想是将所有头结点的邻接顶点输出*/
void BFSTraverse(ALGraph g , void(*Visit)(char *a)){
    int v ,w;                      
    SqQueue q;                      
    int u;                          
    for(v=0;v<g.vexnum;v++)
        visited[v] = FALSE;
    InitQueue(&q);                  
    for(v=0;v<g.vexnum;v++){
        if(!visited[v]){              
            visited[v] = TRUE;         
            Visit(g.vertices[v].data);  
            EnQueue(&q , v);            

            while(!isEmpityQueue(q)){   
                for(w = FirstAdjVex(g , g.vertices[u].data) ; w>=0; w = NextAdjVex(g,g.vertices[u].data , g.vertices[w].data) ){ //w依次从u 往后找邻接表顶点
                    if(!visited[w]){    
                        visited[w] = TRUE;
                        Visit(g.vertices[w].data);
                        EnQueue(&q , w);
                    }
                }
            }
        }
    }
}


int main()
{
	AlGraph g;
	CreateGraph(&g);
	BFSTraverse(g,print);
    return 0;
}

