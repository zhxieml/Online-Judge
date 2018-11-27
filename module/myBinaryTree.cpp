#include <iostream>
using namespace std;

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

////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////

struct node
{
    int data;

    node *left, *right, *parent;

    node(int d = 0, node *l = NULL, node *r = NULL, node *p = NULL): data(d), left(l), right(r), parent(p){}
    ~node(){};
};

////////////////////////////////////////////////////////

class bTree
{
private:
    struct stNode
    {
        node *oriNode;
        int timePop;

        stNode(node *N = NULL): oriNode(N), timePop(0) {}
    };

    node *root;

public:
    bTree(node *r = NULL): root(r){}
    ~bTree();

    void clear();
    bool isCBT() const;
    void preTraveral() const;
    void postTraveral() const;
    void midTraveral() const;

private:
    void clear(node *&x);
};

bTree::~bTree()
{
    clear(root);
}

void bTree::clear(node *&x)
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

bool bTree::isCBT() const
{
    linkQueue<node *> que;
    node *tmp;

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

void bTree::preTraveral() const
{
    linkStack<node *> s;
    node *tmp;
    s.push(root);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        cout << tmp->data << ' ';
        if (tmp->right != NULL) s.push(tmp->right);
        if (tmp->left != NULL) s.push(tmp->left);
    }
}

void bTree::midTraveral() const
{
    linkStack<stNode> s;
    stNode tmp(root);
    s.push(tmp);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        if (++tmp.timePop == 2)
        {
            cout << tmp.oriNode->data << ' ';
            if (tmp.oriNode->right != NULL) s.push(stNode(tmp.oriNode->right));
        }

        else
        {
            s.push(tmp);
            
            if (tmp.oriNode->left != NULL) s.push(stNode(tmp.oriNode->left));
        }
    }
}

void bTree::postTraveral() const
{
    linkStack<stNode> s;  
    stNode tmp(root);
    s.push(tmp);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        if (++tmp.timePop == 3)
        {
            cout << tmp.oriNode->data << ' ';
            continue;
        }

        s.push(tmp);

        if (tmp.timePop == 1)
        {
            if (tmp.oriNode->left != NULL) s.push(stNode(tmp.oriNode->left));
        }

        else
        {
            if (tmp.oriNode->right != NULL) s.push(stNode(tmp.oriNode->right));
        }
    }
}