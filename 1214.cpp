#include <iostream>
using namespace std;

struct node
{
    node *left, *right, *previous;
    int data;

    node(int d = 0, node *l = NULL, node *r = NULL, node *p = NULL): data(d), left(l), right(r), previous(p){}
    ~node(){}
};

//struct sNode
//{
//    node *oNode;
//    int timePop;
//
//    sNode(node *n = NULL): oNode(n), timePop(0){}
//    ~sNode(){}
//};

///////////////////////////////////////////////////////////////

template <class Type>
class linkStack
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
    node *top_p;
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const Type &x);
    Type pop();
    Type top() const;
};

template <class Type>
linkStack<Type>::linkStack()
{
    top_p = NULL;
}

template <class Type>
linkStack<Type>::~linkStack()
{
    node *tmp;
    while (top_p != NULL)
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

template <class Type>
bool linkStack<Type>::isEmpty() const
{
    return top_p == NULL;
}

template <class Type>
void linkStack<Type>::push(const Type &x)
{
    top_p = new node(x, top_p);
}

template <class Type>
Type linkStack<Type>::pop()
{
    node *tmp = top_p;
    Type x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}

template <class Type>
Type linkStack<Type>::top() const
{
    return top_p->data;
}

///////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////

//void preTraverse(node *root)
//{
//    linkStack<node *> s;
//    node *tmp;
//    s.push(root);
//
//    while (!s.isEmpty())
//    {
//        tmp = s.pop();
//        cout << tmp->data << ' ';
//
//        if (tmp->right) s.push(tmp->right);
//        if (tmp->left) s.push(tmp->left);
//    }
//
//    cout << endl;
//}
//
//void postTraverse(node *root)
//{
//    linkStack<sNode> s;
//    sNode tmp(root);
//    s.push(tmp);
//
//    while (!s.isEmpty())
//    {
//        tmp = s.pop();
//
//        if (++tmp.timePop == 3)
//        {
//            cout << tmp.oNode->data << ' ';
//            continue;
//        }
//
//        s.push(tmp);
//
//        if (tmp.timePop == 1)
//        {
//            if (tmp.oNode->left != NULL) s.push(sNode(tmp.oNode->left));
//        }
//
//        else
//        {
//            if (tmp.oNode->right != NULL) s.push(sNode(tmp.oNode->right));
//        }
//    }
//
//    cout << endl;
//}
//
//void levelTraverse(node *root)
//{
//    linkQueue<node *> que;
//    node *tmp;
//    que.enQueue(root);
//
//    while (!que.isEmpty())
//    {
//        tmp = que.deQueue();
//        cout << tmp->data << ' ';
//
//        if (tmp->left) que.enQueue(tmp->left);
//        if (tmp->right) que.enQueue(tmp->right);
//    }
//
//}

void preTraverse(node *root)
{
    if (root == NULL) return;

    cout << root->data << ' ';

    if (node *kid = root->left)
    {
        preTraverse(kid);

        while (kid->right)
        {
            kid = kid->right;
            preTraverse(kid);
        }
    }
}

void postTraverse(node *root)
{
    if (root == NULL) return;

    if (node *kid = root->left)
    {
        postTraverse(kid);

        while (kid->right)
        {
            kid = kid->right;
            postTraverse(kid);
        }
    }

    cout << root->data << ' ';
}

void levelTraverse(node *root)
{
    linkQueue<node *> que;
    node *tmp, *kid;
    que.enQueue(root);

    while (!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << tmp->data << ' ';

        if (tmp->left) que.enQueue(tmp->left);

        while (tmp->right)
        {
            tmp = tmp->right;
            cout << tmp->data << ' ';

            if (tmp->left) que.enQueue(tmp->left);
        }

    }


}

///////////////////////////////////////////////////////////////

int main()
{
    int num;
    cin >> num;

    node **nodes;
    nodes = new node *[num + 10];
    for (int i = 0; i < num + 10; i++) nodes[i] = new node;

    int l, r, d;

    for (int i = 1; i <= num; i++)
    {
        cin >> l >> r >> d;

        nodes[i]->data = d;

        if (l)
        {
            nodes[i]->left = nodes[l];
            nodes[l]->previous = nodes[i];
        }

        if (r)
        {
            nodes[i]->right = nodes[r];
            nodes[r]->previous = nodes[i];
        }
    }

    node *root = nodes[1];
    while (root->previous) root = root->previous;

    preTraverse(root);

    cout << endl;

    postTraverse(root);

    cout << endl;

    levelTraverse(root);
    return 0;
}














