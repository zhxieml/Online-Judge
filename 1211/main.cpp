#include <iostream>
using namespace std;

int lastIndex(double n)
{
    int count = 0, result = 1;
    while (n >= 2)
    {
        n /= 2;
        count++;
    }

    for (int i = 0; i < count; i++) result *= 2;

    return result * 2 - 1;
}

/////////////////////////////////////////////////////////////////////

template <class eT>
class seqQueue
{
private:
    eT *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();

public:
    seqQueue(int size = 10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const eT &x);
    eT deQueue();
    eT getHead() const;
};

template <class eT>
seqQueue<eT>::seqQueue(int size)
{
    elem = new eT[size];
    maxSize = size;
    front = rear = 0;
}

template <class eT>
seqQueue<eT>::~seqQueue()
{
    delete [] elem;
}

template <class eT>
void seqQueue<eT>::doubleSpace()
{
    eT *tmp = elem;
    elem = new eT[maxSize * 2];
    for (int i = i; i <= maxSize; i++) elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete tmp;
}

template <class eT>
bool seqQueue<eT>::isEmpty() const
{
    return front == rear;
}

template <class eT>
void seqQueue<eT>::enQueue(const eT &x)
{
    if ((rear + 1) % maxSize == front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class eT>
eT seqQueue<eT>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <class eT>
eT seqQueue<eT>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

/////////////////////////////////////////////////////////////////////

class bTree
{
private:
    struct Node
    {
        Node *left, *right;
        int data;

        Node(int D = 0, Node *L = NULL, Node *R = NULL): data(D), left(L), right(R){}
        ~Node(){}
    };

    Node *root;

public:
    bTree(int l[], int r[], int num);
    ~bTree();

    void clear();
    bool isCBT() const;
    void levelTravel() const;

private:
    void clear(Node *&x);

};

bTree::bTree(int l[], int r[], int num)
{
    seqQueue<Node *> que;
    Node *tmp;
    int x, ldata, rdata;
    root = new Node(num);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        if (l[tmp->data] != 0) que.enQueue(tmp->left = new Node(l[tmp->data]));
        if (r[tmp->data] != 0) que.enQueue(tmp->right = new Node(r[tmp->data]));
    }
}

void bTree::clear(bTree::Node *&x)
{
    if (x == NULL) return;
    clear(x->left);
    clear(x->right);
    delete x;
    x = NULL;
}

void bTree::clear()
{
    clear(root);
}

bTree::~bTree()
{
    clear(root);
}

//void bTree::create(int l[], int r[], int num)
//{
//    seqQueue<Node *> que;
//    Node *tmp;
//    int x, ldata, rdata;
//    root = new Node(num);
//    que.enQueue(root);
//
//    while(!que.isEmpty())
//    {
//        tmp = que.deQueue();
//        if (l[tmp->data] != 0) que.enQueue(tmp->left = new Node(l[tmp->data]));
//        if (r[tmp->data] != 0) que.enQueue(tmp->right = new Node(r[tmp->data]));
//    }
//}

void bTree::levelTravel() const
{
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
}

//bool bTree::isCBT() const
//{
//    seqQueue<Node *> que;
//    Node *tmp;
//    int count = 0;
//
//    que.enQueue(root);
//
//    while (!que.isEmpty())
//    {
//        tmp = que.deQueue();
//        count++;
//
//        if (tmp->left == NULL && tmp->right != NULL) return false;
//
//        if (tmp->left == NULL || tmp->right == NULL)
//        {
//            if (tmp->left) que.enQueue(tmp->left);
//            if (tmp->right) que.enQueue(tmp->right);
//
////            for (int i = count + 1; i <= lastIndex(count); i++)
////            {
////                tmp = que.deQueue();
////
////                if (tmp->left != NULL || tmp->right != NULL) return false;
//////
//////                if (tmp->left) que.enQueue(tmp->left);
//////                if (tmp->right) que.enQueue(tmp->right);
////            }
//
//            while (!que.isEmpty())
//            {
//                tmp = que.deQueue();
//                if (tmp->left != NULL || tmp->right != NULL) return false;
//            }
////            if (que.isEmpty()) return true;
////            return false;
//            return true;
//        }
//
//        que.enQueue(tmp->left);
//        que.enQueue(tmp->right);
//    }
//
//    return true;
//}

bool bTree::isCBT() const
{
    seqQueue<Node *> que;
    Node *tmp;

    que.enQueue(root);

    while ((tmp = que.deQueue()) != NULL)
    {
        que.enQueue(tmp->left);
        que.enQueue(tmp->right);
    }

    while (!que.isEmpty())
    {
        tmp = que.deQueue();

        if (tmp != NULL) return false;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////

int main()
{
    int num;
    cin >> num;

    int *leftC = new int[num + 1], *rightC = new int[num + 1];

    for (int i = 1; i <= num; i++) cin >> leftC[i] >> rightC[i];

    bTree bt(leftC, rightC, num);

    if (bt.isCBT()) cout << 'Y';
    else cout << 'N';

    delete [] leftC;
    delete [] rightC;
    return 0;
}
