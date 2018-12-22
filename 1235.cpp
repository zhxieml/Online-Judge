#include <iostream>
using namespace std;

template<class Type>
class priorityQueue
{
private:
    int currentLength;
    Type *elem;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    elem = new Type[capacity];
    maxSize = capacity;
    currentLength = 0;
}

template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete [] elem;
}

template<class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentLength == 0;
}

template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return elem[1];
}

template<class Type>
void priorityQueue<Type>::doubleSpace()
{
    Type *tmp = elem;

    maxSize *= 2;
    elem = new Type[maxSize];
    for (int i = 0; i <= currentLength; i++) elem[i] = tmp[i];
    delete [] tmp;
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentLength == maxSize - 1) doubleSpace();

    int hole = ++currentLength;
    for (; hole > 1 && x < elem[hole / 2]; hole /= 2) elem[hole] = elem[hole / 2];
    elem[hole] = x;
}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp = elem[hole];

    for (; hole * 2 <= currentLength; hole = child)
    {
        child = hole * 2;

        if (child != currentLength && elem[child + 1] < elem[child]) child++;

        if (elem[child] < tmp) elem[hole] = elem[child];
        else break;
    }

    elem[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap()
{
    for (int i = currentLength / 2; i > 0; i--) percolateDown(i);
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size): maxSize(size + 10), currentLength(size)
{
    elem = new Type[maxSize];
    for (int i = 0; i < size; i++) elem[i + 1] = items[i];

    buildHeap();
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{ 
    Type minItem;
    minItem = elem[1];
    elem[1] = elem[currentLength--];
    
    percolateDown(1);
    return minItem;
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
    void dijkstra(int start, int end) const;
    void print_path(int start, int end, int prev[]) const;
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

void adjListGraph::dijkstra(int start, int end) const
{
    long long *distance = new long long[ver + 1];
    int *prev = new int[ver + 1];
    bool *known = new bool[ver + 1];
    int *cost = new int[ver + 1];
    int start_i;
    edgeNode *p;
    priorityQueue<queueNode> que;
    queueNode min, succ;

    for (int i = 1; i <= ver; ++i)
    {
        known[i] = false;
        distance[i] = 2147483647;
        cost[i] = 0;
    }

    for (start_i = 1; start_i <= ver; ++start_i)
    {
        if (vlist[start_i].ver == start) break;
    }

    if (start_i == ver) 
    {
        cout << "Error! The start node doesn't exist." << endl;
        return;
    }

    distance[start_i] = 0;
    prev[start_i] = start_i;
    min.dist = 0;
    min.node = start_i;
    que.enQueue(min);

    while (!que.isEmpty())
    {
        min = que.deQueue();
        if (known[min.node]) continue;

        known[min.node] = true;
        for (p = vlist[min.node].head; p != NULL; p = p->next)
        {
            if (!known[p->end] && (distance[p->end] > min.dist + p->weight || distance[p->end] == min.dist + p->weight && cost[p->end] > cost[min.node] + 1))
            {
                cost[p->end] = cost[min.node] + 1;
                succ.dist = distance[p->end] = min.dist + p->weight;
                prev[p->end] = min.node;
                succ.node = p->end;
                que.enQueue(succ);
            }
        }
    }

    cout << distance[end] << endl;

    print_path(start, end, prev);
}

////////////////////////////////////////////////////////////////

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

    alg.dijkstra(start, end);

    return 0;
}