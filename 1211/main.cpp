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
    node *root;

public:
    bTree(node *r = NULL): root(r){}
    ~bTree();

    void clear();
    bool isCBT() const;

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

////////////////////////////////////////////////////////

int main()
{
    int num;
    cin >> num;

    node **nodes;
    nodes = new node *[num + 10];

    for (int i = 0; i < num + 10; i++) nodes[i] = new node;

    int l, r;

    for (int i = 1; i <= num; i++)
    {
        nodes[i]->data = i;
        cin >> l >> r;

        if (l)
        {
            nodes[i]->left = nodes[l];
            nodes[l]->parent = nodes[i];
        }

        if (r)
        {
            nodes[i]->right = nodes[r];
            nodes[r]->parent = nodes[i];
        }
    }

    node *root = nodes[1];

    while (root->parent) root = root->parent;

    bTree tree(root);

    if (tree.isCBT()) cout << 'Y';
    else cout << 'N';
}





