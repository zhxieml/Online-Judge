#include <iostream>
using namespace std;

// 有向图
// 输入可能有重边
// 关于简单路径的起点终点是否能相同，这个有点争议。本题规定不能相同

int count = 0;
bool *visited;
// int length;

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

adjListGraph::adjListGraph(int size)
{
    ver = size;
    vlist = new verNode[ver + 1];
    edge = 0;

    for (int i = 1; i <= size; i++) vlist[i].ver = i;
}

adjListGraph::~adjListGraph()
{
    edgeNode *tmp;

    for (int i = 0; i < ver; ++i)
    {
        while ((tmp = vlist[i].head) != NULL)
        {
            vlist[i].head = tmp->next;
            delete tmp;
        }
    }

    delete [] vlist;
}

bool adjListGraph::insert(int s, int e)
{
    vlist[s].head = new edgeNode(e, vlist[s].head);

    ++edge;
    return true;
}

void adjListGraph::dfs(int s, bool visited[], int l)
{
    edgeNode *tmp = vlist[s].head;

    bool *new_visited = new bool[ver + 1];
    for (int i = 1; i <= ver; ++i) new_visited[i] = visited[i];    
    // delete [] visited; 
    // visited = new_visited;

    new_visited[s] = true;

    --l;

    // for (int i = 1; i <= ver; i++) cout << new_visited[i] << endl;

    // if (l == 0) 
    // {
    //     ++count;
    //     return;
    // }

    while (tmp)
    {
        if (!new_visited[tmp->end]) 
        {
            // cout << s << " -> " << tmp->end  << "(" << l << ")" << endl;
            if (l != 0) dfs(tmp->end, new_visited, l);
            // if (l == 0) ++count;

            else ++count;
        }

        tmp = tmp->next;
        // if (!tmp) ++count;
    }
}

void adjListGraph::dfs(int s, int l)
{
    // bool *visited = new bool[ver + 1];
    // for (int i = 1; i <= ver; i++) visited[i] = false;
    // bool *visited;

    dfs(s, visited, l);
}

/////////////////////////////////////////////////////////////////

int main() 
{	
    int n, m, start, l;
    cin >> n >> m >> start >> l;

    adjListGraph graph(n);
    int s, e;
    visited = new bool[n + 1];
    for (int i = 1; i <= n; i++) visited[i] = false;

    for (int i = 0; i < m; ++i)
    {
        cin >> s >> e;
        graph.insert(s, e);
    }

    graph.dfs(start, l);

    cout << count;

    return 0;
}