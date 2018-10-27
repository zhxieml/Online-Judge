//#include <iostream>
//using namespace std;
//
//template <class Type>
//class seqQueue
//{
//private:
//    Type *elem;
//    int maxSize;
//    int front, rear;
//    void doubleSpace();
//
//public:
//    seqQueue(int size = 100000);
//    ~seqQueue();
//    bool isEmpty() const;
//    void enQueue(const Type &x);
//    Type deQueue();
//    Type getHead() const;
//};
//
//template <class Type>
//seqQueue<Type>::seqQueue(int size)
//{
//    elem = new Type[size];
//    maxSize = size;
//    front = rear = 0;
//}
//
//template <class Type>
//seqQueue<Type>::~seqQueue()
//{
//    delete [] elem;
//}
//
//template <class Type>
//void seqQueue<Type>::doubleSpace()
//{
//    Type *tmp = elem;
//    elem = new Type[maxSize * 2];
//    for (int i = i; i < maxSize; i++) elem[i] = tmp[(front + i) % maxSize];
//    front = 0;
//    rear = maxSize - 1;
//    maxSize *= 2;
//    delete tmp;
//}
//
//template <class Type>
//bool seqQueue<Type>::isEmpty() const
//{
//    return front == rear;
//}
//
//template <class Type>
//void seqQueue<Type>::enQueue(const Type &x)
//{
//    if ((rear + 1) % maxSize == front) doubleSpace();
//    rear = (rear + 1) % maxSize;
//    elem[rear] = x;
//}
//
//template <class Type>
//Type seqQueue<Type>::deQueue()
//{
//    front = (front + 1) % maxSize;
//    return elem[front];
//}
//
//template <class Type>
//Type seqQueue<Type>::getHead() const
//{
//    return elem[(front + 1) % maxSize];
//}
//
///////////////////////////////////////////////////////////
//
//struct Node
//{
//    Node *left, *right, *parent;
//    int data;
//
//    Node(int D = 0, Node *L = NULL, Node *R = NULL, Node *P = NULL): data(D), left(L), right(R), parent(P){}
//    ~Node(){};
//};
//
///////////////////////////////////////////////////////////
//
//int main()
//{
//    int num;
//    cin >> num;
//
//    Node **nodes;
//    nodes = new Node *[num + 10];
//
//    int l, r;
//
//    for (int i = 1; i <= num; i++)
//    {
//        nodes[i]->data = i;
//
//        cin >> l >> r;
//
//        if (l)
//        {
//            nodes[i]->left = nodes[l];
//            nodes[l]->parent = nodes[i];
//        }
//
//        if (r)
//        {
//            nodes[i]->right = nodes[r];
//            nodes[r]->parent = nodes[i];
//        }
//    }
//
//    Node *root = nodes[1];
//
//    while (root->parent) root = root->parent;
//
//    seqQueue<Node *> que;
//    Node *tmp;
//
//    que.enQueue(root);
//
//    while ((tmp = que.deQueue()) != NULL)
//    {
//        que.enQueue(tmp->left);
//        que.enQueue(tmp->right);
//    }
//
//    while (!que.isEmpty())
//    {
//        tmp = que.deQueue();
//
//        if (tmp != NULL) return false;
//    }
//
//    return true;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
