#include <iostream>
#include "adjMatrixGraph.h"
using namespace std;

adjMatrixGraph::adjMatrixGraph(int vSize,  const int d[], int noEdgeFlag)
{ 
    int i, j;
    Vers = vSize;   
    Edges = 0;  
    noEdge = noEdgeFlag;

    //存放结点的数组的初始化
    ver = new int[vSize];
    for (i=0; i<vSize;++ i) ver[i] = d[i];  
    //邻接矩阵的初始化
    edge = new int*[vSize];
    for (i = 0; i < vSize; ++ i) {
        edge[i] = new int[vSize];
        for (j = 0; j < vSize; ++j) edge[i][j] = noEdge;
        edge[i][i] = 0;
    }
}

adjMatrixGraph::~adjMatrixGraph()
{
	  delete [] ver;
	  for (int i = 0; i < Vers; ++i) delete edge[i];
	  delete [] edge;
}

bool adjMatrixGraph::insert(int u, int v, int w)
{ 
    if (u < 0 || u > Vers - 1 || v < 0 || v > Vers -1) return false;
    if (edge[u][v] != noEdge) return false;
    edge[u][v] = w;
    ++Edges;
    return true;
 } 

bool adjMatrixGraph::remove(int u, int v)
{ 
    if (u < 0 || u > Vers -1 || v < 0 || v > Vers -1) return false;
    if (edge[u][v] == noEdge) return false;
    edge[u][v] = noEdge;
    --Edges;
    return true;
 } 

bool adjMatrixGraph::exist(int u, int v) const
{ 
    if (u < 0 || u > Vers -1 || v < 0 || v > Vers -1)return false;
    if (edge[u][v] == noEdge) return false; 
    else  return true;
} 

void adjMatrixGraph::floyd() const
{ 
    int **d = new int*[Vers]; 
    int **prev = new int*[Vers]; 
    int i, j, k;

    //初始化
    for (i = 0; i < Vers; ++i)
    {
        d[i] = new int[Vers]; 
        prev[i] = new int[Vers]; 
        for (j = 0; j < Vers; ++j) 
        { 
            d[i][j] = edge[i][j];
            prev[i][j] = (edge[i][j] != noEdge) ? i : -1;
        }
    } 
//迭代过程
    for (k = 0; k < Vers; ++k)
    {
	      for (i = 0; i < Vers; ++i)
        {
            for (j = 0; j < Vers; ++j) 
            {
                if (d[i][k] + d[k][j] < d[i][j]) 
                {
                    d[i][j] = d[i][k] + d[k][j];
                    prev[i][j] = prev[k][j];   
                }
            }
        }
    }

  //输出过程
    cout << "最短路径长度：" << endl;
    for (i = 0; i < Vers; ++i) 
    {
        cout << endl;
        for (j = 0; j < Vers; ++j) cout << d[i][j] << '\t';  
    }
  
    cout << "最短路径：" << endl;
    for (i = 0; i < Vers; ++i) 
    {
        cout << endl;
        for (j = 0; j < Vers; ++j) cout << prev[i][j] << '\t';  
    }
}