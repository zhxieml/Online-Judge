#ifndef ADJMATRIXGRAPH_H_INCLUDED
#define ADJMATRIXGRAPH_H_INCLUDED
    class adjMatrixGraph
    {
    private:
        int **edge; //存放邻接矩阵
        int *ver;  //存放结点值
        int noEdge; //邻接矩阵中的∞的表示值
        int Vers, Edges;

    public:  
        adjMatrixGraph(int vSize, const int d[], int noEdgeFlag);
        ~adjMatrixGraph();

        bool insert(int u, int v, int w);
        bool remove(int u, int v);
        bool exist(int u, int v) const;
        void floyd() const;
    };
#endif