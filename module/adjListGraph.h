#ifndef ADJLISTGRAPH_H_INCLUDED
#define ADJLISTGRAPH_H_INCLUDED

    class adjListGraph
    {
    private:
        struct edgeNode
        {
            int end;
            edgeNode *next;
            edgeNode(int e, edgeNode *n = NULL): end(e), next(n) {}
        };
        
        struct verNode
        {
            int ver;
            edgeNode *head;
            verNode(edgeNode *h = NULL): head(h) {}
        };

        verNode *vlist;
        int ver;
        int edge;

        void dfs(int s, bool visited[], int l);

    public:
        adjListGraph(int size);
        ~adjListGraph();

        bool insert(int s, int e);
        bool remove(int s, int e);
        bool exist(int s, int e) const;
        void dfs(int s, int l);
    };

#endif