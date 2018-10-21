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
    seqQueue(int size = 10);
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
    delete [] tmp;
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

//class bTree
//{
//private:
//    struct Node
//    {
//        Node *left, *right, *parent;
//        int data, index;
//
//        Node(int d = 0, int i = 0, Node *l = NULL, Node *r = NULL, Node *p = NULL): left(l), right(r), parent(p), data(d), index(i){}
//        ~Node(){};
//    };
//
//    Node *root;
//
//public:
//    bTree(int l[], int r[], int w[], int n);
//    ~bTree();
//
//    void clear();
//    void levelTravel() const;
//
//private:
//    void clear(Node *&x);
//
//};
//
//bTree::bTree(int l[], int r[], int w[], int n)
//{
//    seqQueue<Node *> que;
////    Node *tmp;
//    Node **nodes;
//
//    nodes = new Node*[n + 1];
//
//    for (int i = 1; i <= n; i++) nodes[i] = new Node(w[i]);
//
//    for (int i = 1; i <= n; i++)
//    {
//        if (l[i] != 0)
//        {
//            nodes[i]->left = nodes[l[i]];
//            nodes[l[i]]->parent = nodes[i];
//        }
//
//        if (r[i] != 0)
//        {
//            nodes[i]->right = nodes[r[i]];
//            nodes[r[i]]->parent = nodes[i];
//        }
//    }
//
//    Node *root;
//    root = nodes[1];
////    que.enQueue(root);
////
////    while (!que.isEmpty())
////    {
////        tmp = que.deQueue();
////        if (l[tmp->index] != 0)
////        {
////            que.enQueue(tmp->left = new Node(w[tmp->index], l[tmp->index]));
////            tmp->left->parent = tmp;
////        }
////
////        if (r[tmp->index] != 0)
////        {
////            que.enQueue(tmp->right = new Node(w[tmp->index], r[tmp->index]));
////            tmp->left->parent = tmp;
////        }
////    }
//
//    while (root->parent) root = root->parent;
//}
//
//void bTree::clear(bTree::Node *&x)
//{
//    if (x == NULL) return;
//    clear(x->left);
//    clear(x->right);
//    delete x;
//    x = NULL;
//}
//
//void bTree::clear()
//{
//    clear(root);
//}
//
//bTree::~bTree()
//{
//    clear(root);
//}
//
//void bTree::levelTravel() const
//{
//    seqQueue<Node *> que;
//    Node *tmp;
//    que.enQueue(root);
//
//    while (!que.isEmpty())
//    {
//        tmp = que.deQueue();
//
//        cout << tmp->data << ' ';
//        if (tmp->left) que.enQueue(tmp->left);
//        if (tmp->right) que.enQueue(tmp->right);
//    }
//}

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

//    int *leftC = new int[num + 1], *rightC = new int[num + 1], *weight = new int[num + 1];

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

//    bTree tree(leftC, rightC, weight, num);
//
//    tree.levelTravel();

    return 0;
}
