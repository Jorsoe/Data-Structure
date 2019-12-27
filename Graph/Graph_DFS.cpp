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
*ͼ���ڽӾ����ADT
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

//��������
int LocateVex(MGraph g , char v[MAX_NAME]);
Status CreateDG(MGraph *g);
Status CreateDN(MGraph *g);
Status CreateUDG(MGraph *g);
Status CreateUDN(MGraph *g);

/**
*˳����е�ADT
*ʵ�� ���죬��ӣ����ԣ��Կգ�����
*��������Ϊѭ��ջ���
*/
typedef int ElemType;   //Ԫ���������ͣ����Ը��������Զ�������
typedef int Status ;    //����ĺ�����������

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



/**����ͼ**/
Status CreateGraph(MGraph *g){
    int k;
    
    printf("0.����ͼ 1.������ 2.����ͼ 3.������\n");
    scanf("%d",&k);
    g->kind=(GraphKind)k;

    switch(g->kind){
        case  DG: return CreateDG(g);     
        case  DN: return CreateDN(g);    
        case UDG: return CreateUDG(g);    
        case UDN: return CreateUDN(g);  
    }

}

/**����ͼ����
*/
Status CreateDG(MGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];
    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("���������������:\n");
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
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵�(���ݼ��ÿո����)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);
        i = LocateVex(*g,v1);              
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = 1;             
    }
    return OK;

}

/**����������**/
Status CreateDN(MGraph *g){
    char v1[MAX_NAME],v2[MAX_NAME];     //�ڽӾ����������v1 ������v2�����������˵㣩
    int w;          //wΪȨֵ
    int i,j,k;

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("���������������:\n");
    for(i=0;i<g->vexnum;i++){
        scanf("%s",g->vexs[i]);   //������������
        fflush(stdin);
    }
    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            g->arcs[i][j].adj=INFINITY; 
            g->arcs[i][j].info = NULL;   
        }
    }
    for(k=0;k<g->arcnum;k++){
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵㣬Ȩֵ��(���ݼ��ÿո����)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);
        i = LocateVex(*g,v1);              
        j = LocateVex(*g,v2);
        g->arcs[i][j].adj = w;              

    )
    return OK;
}

/**����ͼ����**/
Status CreateUDG(MGraph *g){
    int i,j,k;
    char v1[MAX_NAME],v2[MAX_NAME];  

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("���������������:\n");
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
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵�(���ݼ��ÿո����)\n",k+1);
        scanf("%s %s",v1,v2);
        fflush(stdin);
        i = LocateVex(*g,v1);        
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = 1;             
        g->arcs[j][i] = g->arcs[i][j];     
    }
    return OK;

}

/**����������
*/
Status CreateUDN(MGraph *g){
    char v1[MAX_NAME],v2[MAX_NAME];    
    int w;        
    int i,j,k;

    printf("�����붥����������\n");
    scanf("%d %d",&g->vexnum,&g->arcnum);
    fflush(stdin);
    printf("���������������:\n");
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
        printf("�������%d���ĵ�һ�˵㣬�ڶ��˵㣬Ȩֵ��(���ݼ��ÿո����)\n",k+1);
        scanf("%s %s %d",v1,v2,&w);
        fflush(stdin);
        i = LocateVex(*g,v1);           
        j = LocateVex(*g,v2);               
        g->arcs[i][j].adj = w;             
        g->arcs[j][i] = g->arcs[i][j];     
    }
    return OK;

}

/**��ȡ������±�**/
int LocateVex(MGraph g , char v[MAX_NAME]){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(strcmp(v,g.vexs[i])==0)
            return i;
    }
    printf("δ�ҵ�����!\n");
    return i;
}//LocateVex

/**��ӡ�ڽӾ���**/
void ListGraph(MGraph g){
    int i,j;
    printf("����ڽӾ���:\n");
    for(i=0;i<g.vexnum;i++){
        printf("%s----",g.vexs[i]);
        for(j=0;j<g.vexnum;j++){
            if((g.kind == DN || g.kind == UDN) && g.arcs[i][j].adj == INFINITY){
                printf("  ��"); 
                continue;
            }
            printf("%4d",g.arcs[i][j].adj);
        }
        printf("\n");
    }
}

/** ����v�ĵ�һ���ڽӶ������š�**/
int FirstAdjVex(MGraph g,VertexType v)
{
    int i;
	int u;          
	u = LocateVex(g,v);
	for(i=0;i<g.vexnum;i++){  //�������ж���
        if(g.arcs[u][i].adj != 0 && g.arcs[u][i].adj != INFINITY && !visited[i]) /
            return i;
	}
	return -1;

/**����v�������w����һ���ڽӽ�㡣**/
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

/**��ӡ����**/
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

/**DFSTraverse �����������**/
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

