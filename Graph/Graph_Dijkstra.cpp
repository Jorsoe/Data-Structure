#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MaxSize 5
#define OK 1
#define ERROR 0

void find(int pineer[MaxSize], int i, int AdjacentMatrix[MaxSize][MaxSize])
{
    while(pineer[i]!=-1)
    {
        printf("(%d, %d)%d ", pineer[i], i, AdjacentMatrix[pineer[i]][i]);
        i=pineer[i];
    }
}

void Dijkstra(int vertex, int source, int PathLength[], int AdjacentMatrix[MaxSize][MaxSize],int pioneer[MaxSize])
{
    int signs[vertex];
    for(int i=0; i<vertex; i++)
    {
        PathLength[i]=AdjacentMatrix[source][i];
        signs[i]=FALSE;
        if(PathLength[i]==Infinity)
        {
            pioneer[i]=-1;
        }
        else
        {
            pioneer[i]=source;
        }
    }
    PathLength[source]=0;
    signs[source]=TRUE;
    for(int i=0; i<vertex; i++)
    {
        int temp=Infinity;
        int t=source;
        for(int j=0; j<vertex; j++)
        {
            if((!signs[j]) && (PathLength[j]<temp))
            {
                t=j;
                temp=PathLength[j];
            }
        }
        if(t==source) break;
            signs[t]=TRUE;
        for(int j=0; j<vertex; j++)
        {
            if((!signs[j]) && (AdjacentMatrix[t][j]!=Infinity))
            {
                if(PathLength[j]>(PathLength[t]+AdjacentMatrix[t][j]))
                {

                    PathLength[j]=PathLength[t]+AdjacentMatrix[t][j];
                    pioneer[j]=t;
                }
            }
        }
    }
}

int main(void)
{
    int AdjacentMatrix[MaxSize][MaxSize]={
        Infinity,8,32,Infinity,Infinity,
        12,Infinity,16,15,Infinity,
        Infinity,29,Infinity,Infinity,13,
        Infinity,21,Infinity,Infinity,7,
        Infinity,Infinity,27,19,Infinity
    };
    int vertex=MaxSize;
    int source=3;
    int PathLength[MaxSize];
    int pioneer[MaxSize];
    for(int i=0; i<MaxSize; i++)
    {
        pioneer[i]=Infinity;
    }
    printf("输入原点：");
    scanf("%d", &source);
    printf("\n最短路径：\n");
    Dijkstra(vertex, source, PathLength, AdjacentMatrix, pioneer);
    for(int i=0; i<vertex; i++)
    {
        if(i==source) continue;
        printf("\n原点%d到顶点%d : %d ", source, i, PathLength[i]);
        find(pioneer, i, AdjacentMatrix);
        printf("\n");
    }
   return 0;
}

