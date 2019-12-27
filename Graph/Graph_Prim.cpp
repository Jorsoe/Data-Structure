#include <stdio.h>
#include <stdlib.h>

/**prim算法*/
typedef enum{DG , DN , UDG , UDN}GraphKind;    
typedef char VertexType[MAX_NAME];     
typedef int InfoType;      
typedef int Status;

typedef struct arcCell{   
    int adj ;        
                           
    InfoType *info;    
}ArcCell, AdjMatrix[Max_VERTEX_NUM][Max_VERTEX_NUM];

typedef struct mgraph{
    VertexType vexs[Max_VERTEX_NUM];       
    AdjMatrix  arcs;                      
    int        vexnum , arcnum;          
    GraphKind  kind;                    
}MGraph;

/**无向网构建
*/
Status CreateUDN(MGraph *g){
    char v1[MAX_NAME],v2[MAX_NAME];     
    int w;      
    int i,j,k;

    g->kind = 3;
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

/**获取顶点的下标*/
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
                printf("  ∞"); //如果输出的是有权图 且为无穷 则输出无穷
                continue;
            }
            printf("%4d",g.arcs[i][j].adj);
        }//for(j)
        printf("\n");
    }//for(i)
}
void Prim(MGraph g , VertexType u){
    int min;                        
    int i,j,k;                            
    int lowcost[Max_VERTEX_NUM];            
    int closest[Max_VERTEX_NUM];           
    int a = LocateVex(g,u);              
    for(i=0;i<g.vexnum;i++){
        lowcost[i] = g.arcs[a][i].adj;       
        closest[i] = a;                  
    }
    for(i = 1; i < g.vexnum; i++){       
        min = INFINITY ;
        k=a;
        for(j = 0 ; j< g.vexnum;j++ ){
            if(j == a)  continue;                             
            if(lowcost[j]<min && lowcost[j] != 0){      
                min = lowcost[j];
                k = j;
            } 
        }
        printf("%s->%s \n",g.vexs[closest[k]],g.vexs[k]); 
        lowcost[k] = 0;                                 
        for(j=0;j<g.vexnum;j++){
            if(lowcost[j]!=0 && g.arcs[k][j].adj < lowcost[j]){ 
                lowcost[j] = g.arcs[k][j].adj;                  
                closest[j] = k;                                 
            }
        }
    }
}

int main()
{
    MGraph g;
    CreateUDN(&g);
    ListGraph(g);
    Prim(g,"v1");
    return 0;
}

