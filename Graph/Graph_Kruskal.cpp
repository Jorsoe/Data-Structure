#include<stdio.h>
#include<stdlib.h>
/**kruskal算法*/
void Kruskal(ALGraph g){
    int i,j;
    int vend[g.vexnum];    
    ArcNode rets[g.arcnum];    
    ArcNode *edge;             
    int p1,p2;                 
    int m,n;                   
    int index = 0;
    for ( i = 0; i < g.vexnum; i++ )
        vend[i] = i;
    edge = g.edges;
    Sort_edges(edge,g.arcnum); 
    for(i=0;i<g.arcnum;j++){
        p1 = edge[i].adjvex;
        p2 = edge[i].nextarc->adjvex;
        m = vend[p1];
        n = vend[p2];
        if(m!=n){
            vend[m]=n;
            rets[index++] = edge[i];
        }
    }
    printf("成果\n");
    for(i=0;i<index;i++){
        printf("%s--%s\n",g.vertices[rets[i].adjvex].data , g.vertices[rets[i].nextarc->adjvex].data);
    }
}

/**排序 从小到大**/
void Sort_edges(ArcNode *edges , int num){
    int i , j;
    ArcNode temp;
    for(i=0;i< num-1;i++){
        for(j=0;j<num-i-1;j++){
            if(*(edges[j].info) >  *(edges[j+1].info)){
                temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }

        }
    }

}
int main()
{
    ALGraph g;
    CreateUDN(&g);
    Kruskal(g);
    return 0;
}
