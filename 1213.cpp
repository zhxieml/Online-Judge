#include <iostream>
using namespace std;

struct node
{
    node *left, *right, *parent;
    int data;

    node(int d = 0, node *l = NULL, node *r = NULL, node *p = NULL): data(d), left(l), right(r), parent(p){}
    ~node(){}
};

struct sNode
{
    node *oNode;
    int timePop;

    sNode(node *n = NULL): oNode(n), timePop(0){}
    ~sNode(){}
};

/////////////////////////////////////////////////////////////

class bTree
{
    friend bool isSamePre(const bTree &t1, const bTree &t2);
    friend bool isSameMid(const bTree &t1, const bTree &t2);

private:
    node *root;

public:
    bTree(node *r = NULL): root(r){}
    ~bTree();

private:
    void clear(node *&x);
};

void bTree::clear(node *&x)
{
    if (x == NULL) return;

    clear(x->left);
    clear(x->right);
    delete x;
    x = NULL;
}

bTree::~bTree()
{
    clear(root);
}

/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////

bool isSameNode(node *n1, node *n2)
{
    if (n1->data != n2->data) return false;

    if (n1->left)
    {
        if (!n2->left) return false;
        if (n1->left->data != n2->left->data) return false;
    }

    if (!n1->left)
    {
        if (n2->left) return false;
    }

    if (n1->right)
    {
        if (!n2->right) return false;
        if (n1->right->data != n2->right->data) return false;
    }

    if (!n1->right)
    {
        if (n2->right) return false;
    }

    return true;
}

bool isSameSNode(sNode sn1, sNode sn2)
{
    if (!isSameNode(sn1.oNode, sn2.oNode)) return false;

    if (sn1.timePop != sn2.timePop) return false;

    return true;
}

bool isSamePre(const bTree &t1, const bTree &t2)
{
    linkStack<node *> s1, s2;
    node *tmp1, *tmp2;
    s1.push(t1.root);
    s2.push(t2.root);

    while (!s1.isEmpty())
    {
        tmp1 = s1.pop();
        tmp2 = s2.pop();

        if (!isSameNode(tmp1, tmp2)) return false;

        if (tmp1->right)
        {
            s1.push(tmp1->right);
            s2.push(tmp2->right);
        }

        if (tmp1->left)
        {
            s1.push(tmp1->left);
            s2.push(tmp2->left);
        }
    }

    return true;
}

bool isSameMid(const bTree &t1, const bTree &t2)
{
    linkStack<sNode> s1, s2;
    sNode tmp1(t1.root), tmp2(t2.root);
    s1.push(tmp1);
    s2.push(tmp2);

    while (!s1.isEmpty())
    {
        tmp1 = s1.pop();
        tmp2 = s2.pop();

        if (!isSameSNode(tmp1, tmp2)) return false;

        tmp1.timePop++;
        tmp2.timePop++;

        if (tmp1.timePop == 2)
        {
            if (tmp1.oNode->right != NULL)
            {
                s1.push(sNode(tmp1.oNode->right));
                s2.push(sNode(tmp2.oNode->right));
            }
        }

        else
        {
            s1.push(tmp1);
            s2.push(tmp2);

            if (tmp1.oNode->left != NULL)
            {
                s1.push(sNode(tmp1.oNode->left));
                s2.push(sNode(tmp2.oNode->left));
            }
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////

int main()
{
    int n, m;
    int l, r, d;

    cin >> n;

    node **nodesN;
    nodesN = new node *[n + 10];
    for (int i = 0; i < n + 10; i++) nodesN[i] = new node;

    for (int i = 1; i <= n; i++)
    {
        cin >> l >> r >> d;

        nodesN[i]->data = d;

        if (l)
        {
            nodesN[i]->left = nodesN[l];
            nodesN[l]->parent = nodesN[i];
        }

        if (r)
        {
            nodesN[i]->right = nodesN[r];
            nodesN[r]->parent = nodesN[i];
        }
    }

    cin >> m;

    node **nodesM;
    nodesM = new node *[m + 10];
    for (int i = 0; i < m + 10; i++) nodesM[i] = new node;

    for (int i = 1; i <= m; i++)
    {
        cin >> l >> r >> d;

        nodesM[i]->data = d;

        if (l)
        {
            nodesM[i]->left = nodesM[l];
            nodesM[l]->parent = nodesM[i];
        }

        if (r)
        {
            nodesM[i]->right = nodesM[r];
            nodesM[r]->parent = nodesM[i];
        }
    }

    node *rootN = nodesN[1], *rootM = nodesM[1];

    while (rootN->parent) rootN = rootN->parent;
    while (rootM->parent) rootM = rootM->parent;

    bTree t1(rootN), t2(rootM);

    if (m != n)
    {
        cout << 'N';
        return 0;
    }


    if (isSamePre(t1, t2) && isSameMid(t1, t2)) cout << 'Y';
    else cout << 'N';
    return 0;
}





