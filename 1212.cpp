#include <iostream>

using namespace std;

template <class T>
class seqQueue
{
private:
    T *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();

public:
    seqQueue(int size = 1000000);
    ~seqQueue();

    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
    bool isEmpty() const;
};

template <class T>
seqQueue<T>::seqQueue(int size)
{
    elem = new T[size];
    maxSize = size;
    front = rear = 0;
}

template <class T>
seqQueue<T>::~seqQueue()
{
    delete [] elem;
}

template <class T>
void seqQueue<T>::doubleSpace()
{
    T *tmp = elem;
    elem = new T[2 * maxSize];
    for (int i = 1; i <= maxSize; i++) elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete tmp;
}

template <class T>
void seqQueue<T>::enQueue(const T &x)
{
    if ((rear + 1) % maxSize == front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <class T>
bool seqQueue<T>::isEmpty() const
{
    return front == rear;
}

template <class T>
T seqQueue<T>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

/////////////////////////////////////////////////////

struct Node
{
    Node *left, *right, *parent;
    int data;

    Node(int d = 0, Node *l = NULL, Node *r = NULL, Node *p = NULL): left(l), right(r), parent(p), data(d){}
    ~Node(){};
};

/////////////////////////////////////////////////////

int main()
{
    int num;
    cin >> num;

    Node *nodes;
    nodes = new Node[num + 1];

    int l, r;

    for (int i = 1; i <= num; i++)
    {
        cin >> l >> r >> nodes[i].data;

        if (l != 0)
        {
            nodes[i].left = &nodes[l];
            nodes[l].parent = &nodes[i];
        }

        if (r != 0)
        {
            nodes[i].right = &nodes[r];
            nodes[r].parent = &nodes[i];
        }
    }

    Node *root = &nodes[1];

    while (root->parent) root = root->parent;

    seqQueue<Node *> que;
    Node *tmp;
    que.enQueue(root);

    while (!que.isEmpty())
    {
        tmp = que.deQueue();

        cout << tmp->data << ' ';
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }

    return 0;
}
