#include <iostream>
using namespace std;

template <class Type>
class linkQueue
{
private:
    struct node
    {
        Type data;

        node *next;

        node(const Type &x, node *n = NULL)
        {
            data = x;
            next = n;
        }

        node(): next(NULL){}
        ~node(){}
    };

    node *front, *rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};

template <class Type>
linkQueue<Type>::linkQueue()
{
    front = rear = NULL;
}

template <class Type>
linkQueue<Type>::~linkQueue()
{
    node *tmp;
    while (front != NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class Type>
bool linkQueue<Type>::isEmpty() const
{
    return front == NULL;
}

template <class Type>
Type linkQueue<Type>::getHead() const
{
    return front->data;
}

template <class Type>
void linkQueue<Type>::enQueue(const Type &x)
{
    if (rear == NULL) front = rear = new node(x);
    else rear = rear->next = new node(x);
}

template <class Type>
Type linkQueue<Type>::deQueue()
{
    node *tmp = front;
    Type value = front->data;
    front = front->next;
    if (front == NULL) rear = NULL; // empty
    delete tmp;
    return value;
}

////////////////////////////////////////////////////////////////

class adjListGraph
{
private:
    struct edgeNode
    {
        int end;
        int weight;
        edgeNode *next;

        edgeNode(int e, int w, edgeNode *n = NULL): end(e), weight(w), next(n) {}
    };
    
    struct verNode
    {
        int ver;
        edgeNode *head;
        verNode(edgeNode *h = NULL): head(h) {}

        bool operator<(const verNode &x) const {return ver < x.ver;}
        bool operator>(const verNode &x) const {return ver > x.ver;}
        bool operator==(const verNode &x) const {return ver == x.ver;}    
    };

    struct queueNode
    {
        int dist;
        int node;

        bool operator<(const queueNode &x) const {return dist < x.dist;}
        bool operator>(const queueNode &x) const {return dist > x.dist;}
        bool operator==(const queueNode &x) const {return dist == x.dist;}
    };

    verNode *vlist;
    int ver;
    int edge;

public:
    adjListGraph(int size);
    ~adjListGraph();

    bool insert(int s, int e, int w);
    bool remove(int s, int e);
    bool exist(int s, int e) const;
    void print_path(int start, int end, int prev[]) const;
    void minus_short_dis(int start, int end) const;
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

bool adjListGraph::insert(int s, int e, int w)
{
    vlist[s].head = new edgeNode(e, w, vlist[s].head);

    ++edge;
    return true;
}

void adjListGraph::print_path(int start, int end, int prev[]) const
{
    if (start == end)
    {
        cout << vlist[start].ver;
        return;
    }

    print_path(start, prev[end], prev);
    cout << ' ' << vlist[end].ver;
}

void adjListGraph::minus_short_dis(int start, int end) const
{
    int *distance = new int[ver + 1];
    int *prev = new int[ver + 1];
    int u, start_i;
    edgeNode *p;
    linkQueue<int> que;

    for (start_i = 1; start_i <= ver; ++start_i)
    {
        if (vlist[start_i].ver == start) break;
    }

    if (start_i == ver) 
    {
        cout << "Error! The start node doesn't exist." << endl;
        return;
    }

    for (int i = 1; i <= ver; ++i) distance[i] = 2147483647;

    distance[start_i] = 0;
    prev[start_i] = start_i;    
    que.enQueue(start_i);

    while (!que.isEmpty())
    {
        u = que.deQueue();
        for (p = vlist[u].head; p != NULL; p = p->next)
        {
            if (distance[p->end] > distance[u] + p->weight)
            {
                distance[p->end] = distance[u] + p->weight;
                prev[p->end] = u;
                que.enQueue(p->end);
            }
        }
    }

    cout << distance[end];
}

//////////////////////////////////////////////////////////////////////////////////

int main() 
{	
    int n, m, start, end;
    cin >> n >> m >> start >> end;

    adjListGraph alg(n);
    int a, b, p;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> p;
        alg.insert(a, b, p);
    }

    alg.minus_short_dis(start, end);
    return 0;
}