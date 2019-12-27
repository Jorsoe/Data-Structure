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
*�ڽӱ�
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

/**�����ڽӱ�
*   g Ϊ�ڽӱ�ָ��
*/

typedef struct queue{
    ElemType *qBase;    //��������
    ElemType front;    //��ͷָ��
    ElemType rear;     //��βָ��
    int queueSize;      //���еĴ�С������Ԫ�ظ��������߿ռ��С
}SqQueue;

/**���еĹ���
* q Ϊ����ָ��
*/
Status InitQueue(SqQueue *q){
    q->qBase = (ElemType*)malloc(QUEUE_INIT_SIZE * sizeof(ElemType));
    if(!q->qBase)
        exit(ERROR);    //����ռ�ʧ��
    q->front = 0;   //��ʼ��ͷָ�����鿪ͷ
    q->rear = 0;    //��ʼ��βָ�����鿪ͷ
    return OK;
}

/**���ٶ���
* q Ϊ����ָ��
*/
void destroyQueue(SqQueue * q)
{
    free(q);  //�ͷŶ�������ָ��ָ����ڴ�
    q = NULL;    //��������ָ������ָ��NULL,�����ΪҰָ��
}

/**�ж϶���
*/
Status isFullQueue(SqQueue q){
    if((q.rear+1)%q.queueSize == q.front) return TRUE;//����

    return FALSE;
}

/**�ж϶ӿ�*/
Status isEmpityQueue(SqQueue q){
    if(q.front == q.rear) return TRUE; //�ӿ�
    return FALSE;
}

/**��� ����Ԫ��
*   qΪ����ָ�� eΪ�����Ԫ��
*/
Status EnQueue(SqQueue *q , ElemType e ){
    //�ж��Ƿ����
    if(isFullQueue(*q)) {
        printf("����\n");
        return ERROR; //����
    }
    q->qBase[q->rear] = e;                        //����Ԫ��
    q->rear = (q->rear + 1) % q->queueSize;       //��β���� ��֤��ѭ��
    return OK;
}

/**��ȡ��ͷԪ��
* qΪ����ָ�� eΪҪ���յ�Ԫ�صı�����ַ
*/
Status GetHead(SqQueue q , ElemType *e){
    //�ж��Ƿ�Ϊ�ӿ�
    if(isEmpityQueue(q)){
        printf("����Ϊ��\n");
        return ERROR;
    }
    *e = q.qBase[q.front];
    return OK;
}

/**����
*   qΪ����ָ�� eΪҪ���յ�Ԫ�صı�����ַ
* ɾ����ͷԪ��
*/
Status DeQueue(SqQueue *q , ElemType *e){
    //�ж��Ƿ�Ϊ�ӿ�
    if(isEmpityQueue(*q)){
        printf("����Ϊ��\n");
        return ERROR;
    }
    *e = q->qBase[q->front];
    q->front = (q->front + 1) % q->queueSize;//�Ƶ���һ��λ��
    return OK;
}

/**���г���
* q Ϊ����
*/
Status QueueLength(SqQueue q){
    return q.queueSize;
}


Status CreateGraph(ALGraph *g){
    printf("0.����ͼ 1.������ 2.����ͼ 3.������\n");
    scanf("%d",&g->kind);

    switch(g->kind){
        case  DG: return CreateDG(g);    
        case  DN: return CreateDN(g);    
        case UDG: return CreateUDG(g);   
        case UDN: return CreateUDN(g);   
        default: return ERROR;
    }

}

/**����ͼ����
*/
Status CreateDG(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                 

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("���������������:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);        
        fflush(stdin);
        g->vertices[i].firstarc = NULL;        
    }
    for(k=0;k<g->arcnum;k++){
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵�(���ݼ��ÿո����)\n",k+1);
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

/**����������
*/
Status CreateDN(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];             //�ڽӾ����������v1 ������v2�����������˵㣩
    ArcNode *p;                                 //��ָ�� ��Ϊÿ������
    int w;                                      //wΪȨֵ

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("���������������:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);       
        fflush(stdin);
        g->vertices[i].firstarc = NULL;        
    }
    for(k=0;k<g->arcnum;k++){
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵㣬Ȩֵ��(���ݼ��ÿո����)\n",k+1);
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

/**����ͼ����
*/
Status CreateUDG(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                
    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("���������������:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);       
        fflush(stdin);
        g->vertices[i].firstarc = NULL;         
    }
    for(k=0;k<g->arcnum;k++){
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵�(���ݼ��ÿո����)\n",k+1);
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

/**����������
*/
Status CreateUDN(ALGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];            
    ArcNode *p;                                 
    int w;                                      

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);

    printf("���������������:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vertices[i].data);        
        fflush(stdin);
        g->vertices[i].firstarc = NULL;         
    }
    for(k=0;k<g->arcnum;k++){
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵㣬Ȩֵ��(���ݼ��ÿո����)\n",k+1);
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

/**��ȡ������±�*/
int LocateVex(ALGraph g , char v[MAX_NAME]){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(strcmp(v,g.vertices[i].data)==0)
            return i;
    }
    printf("δ�ҵ�����!\n");
    return i;
}//LocateVex

/** ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1��**/
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
/**����v�������w����һ���ڽӽ�㡣*/
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


/**��ӡ����*/
void print(char *a){
    printf("%s",a);
}//print


/**BFS ���������������
˼���ǽ�����ͷ�����ڽӶ������*/
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
                for(w = FirstAdjVex(g , g.vertices[u].data) ; w>=0; w = NextAdjVex(g,g.vertices[u].data , g.vertices[w].data) ){ //w���δ�u �������ڽӱ���
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

