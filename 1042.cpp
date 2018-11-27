#include <iostream>
using namespace std;

struct node
{
    int data;
    node *son, *bro, *prev;

    node(int d = 0, node *s = NULL, node *b = NULL, node *p = NULL): data(d), son(s), bro(b), prev(p){}
    ~node(){}
};

////////////////////////////////////////////////////////////////

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

void preTraverse(node *root)
{
    if (root == NULL) return;

    cout << root->data << ' ';

    if (node *kid = root->son)
    {
        preTraverse(kid);

        while (kid->bro)
        {
            kid = kid->bro;
            preTraverse(kid);
        }
    }
}

void postTraverse(node *root)
{
    if (root == NULL) return;

    if (node *kid = root->son)
    {
        postTraverse(kid);

        while (kid->bro)
        {
            kid = kid->bro;
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

        if (tmp->son) que.enQueue(tmp->son);

        while (tmp->bro)
        {
            tmp = tmp->bro;
            cout << tmp->data << ' ';

            if (tmp->son) que.enQueue(tmp->son);
        }

    }
}

////////////////////////////////////////////////////////////////

int main() 
{	
    int num;
    cin >> num;

    int tmp, s, b;
    node **nodes = new node *[num + 1];
    for (int i = 1; i < num + 1; i++) nodes[i] = new node(i);

    for (int i = 0; i < num; i++)
    {
        cin >> tmp >> s >> b;

        if (s)  
        {
            nodes[tmp]->son = nodes[s];
            nodes[s]->prev = nodes[tmp];
        }

        if (b)
        {
            nodes[tmp]->bro = nodes[b];
            nodes[b]->prev = nodes[tmp];
        }
    }

    node *root = nodes[1];
    while (root->prev) root = root->prev;

    preTraverse(root);

    cout << endl;

    postTraverse(root);

    cout << endl;

    levelTraverse(root);

    return 0;
}