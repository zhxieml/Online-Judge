#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

template <class Type>
struct node
{
    Type data;
    node *son, *bro;

    node(Type d, node *s = NULL, node *b = NULL): data(d), son(s), bro(b){}
    ~node(){}
};

////////////////////////////////////////////////////////

template <class Type>
class Bernoulli
{
private:
    node<Type> **forest;
    int scale;

    node<Type> *merge(node<Type> *t1, node<Type> *t2);
    int findMin();
    void deleteTree(node<Type> *x);

public:
    Bernoulli(int n = 100);
    ~Bernoulli();

    void enQueue(Type x);
    Type deQueue();
    bool isEmpty();
    Type getHead();
    void merge(Bernoulli &other);
    void show() const;
};

template <class Type>
void Bernoulli<Type>::deleteTree(node<Type> *x)
{
    node<Type> *son = x->son, *t;
    while (son != NULL)
    {
        t = son;
        son = son->bro;
        deleteTree(t);
    }

    delete(x);
}

template <class Type>
Bernoulli<Type>::Bernoulli(int n)
{
    scale = int(log(n) / log(2)) + 1;
    forest = new node<Type> *[scale];
    for (int i = 0; i < scale; i++) forest[i] = NULL;
}

template <class Type>
Bernoulli<Type>::~Bernoulli()
{
    for (int i = 0; i < scale; i++)
    {
        if (forest[i] != NULL) deleteTree(forest[i]);
    }

    delete [] forest;
}

template <class Type>
void Bernoulli<Type>::merge(Bernoulli &other)
{
    node<Type> **tmp = forest;
    node<Type> *carry;
    int tmpSize = scale;
    int min = scale < other.scale ? scale : other.scale;
    int i;

    if (scale < other.scale)
    {
        scale = other.scale;
        if (other.forest[scale - 1] != NULL) scale++;
    }

    else if (forest[scale - 1] != NULL) scale++;

    forest = new node<Type> *[scale];
    for (i = 0; i < scale; i++) forest[i] = NULL;

    carry = NULL;
    for (i = 0; i < min; i++)
    {
        if (carry == NULL)
        {
            if (tmp[i] == NULL) forest[i] = other.forest[i];

            else 
            {
                if (other.forest[i] == NULL) forest[i] = tmp[i];
                else carry = merge(other.forest[i], tmp[i]);
            }
        }

        else
        {
            if (tmp[i] != NULL && other.forest[i] != NULL)
            {
                forest[i] = carry;
                carry = merge(other.forest[i], tmp[i]);
            }

            else
            {
                if (tmp[i] == NULL && other.forest[i] == NULL)
                {
                    forest[i] = carry;
                    carry = NULL;
                }

                else 
                {
                    if (tmp[i] == NULL) carry = merge(other.forest[i], carry);
                    
                    else carry = merge(tmp[i], carry);
                }
            }
        }   
    }

    if (other.scale == min)
    {
        for (; i < tmpSize; i++)
        {
            if (carry == NULL) forest[i] = tmp[i];

            else
            {
                if (tmp[i] == NULL)
                {
                    forest[i] = carry;
                    carry = NULL;
                }

                else carry = merge(tmp[i], carry);
            }
        }
    }

    else 
    {
        for (; i < other.scale; i++)
        {
            if (carry == NULL) forest[i] = other.forest[i];

            else
            {
                if (other.forest[i] == NULL)
                {
                    forest[i] = carry;
                    carry = NULL;
                }

                else carry = merge(other.forest[i], carry);
            }
        }
    }

    if (carry != NULL) forest[i] = carry;

    for (i = 0; i < other.scale; i++) other.forest[i] = NULL;
    delete [] tmp;
}

template <class Type>
node<Type> *Bernoulli<Type>::merge(node<Type> *t1, node<Type> *t2)
{
    node<Type> *min, *max;

    if (t1->data < t2->data)
    {
        min = t1;
        max = t2;
    }

    else 
    {
        min = t2;
        max = t1;
    }

    if (min->son == NULL) min->son = max;

    else 
    {
        node<Type> *t = min->son;
        while (t->bro != NULL) t = t->bro;
        t->bro = max;
    }

    return min;
}

template <class Type>
void Bernoulli<Type>::enQueue(Type x)
{
    Bernoulli<Type> tmp(1);
    tmp.forest[0] = new node<Type>(x);
    merge(tmp);
}

template <class Type>
int Bernoulli<Type>::findMin()
{
    int min, i;

    for (i = 0; i < scale && forest[i] == NULL; i++);
    min = i;

    for (; i < scale; i++)
    {
        if (forest[i] != NULL && forest[i]->data < forest[min]->data) min = i;
    }

    return min;
}

template <class Type>
Type Bernoulli<Type>::deQueue()
{
    Type value;
    int min = findMin();

    if (min == 0)
    {
        value = forest[0]->data;
        delete forest[0];
        forest[0] = NULL;
        return value;
    }

    node<Type> *t = forest[min];
    node<Type> *son, *brother;
    int newScale = int (pow(2, min) - 1);
    Bernoulli tmp(newScale);
    value = t->data;
    forest[min] = NULL;

    son = t->son;
    delete t;
    int i = 0;

    do
    {
        tmp.forest[i++] = son;
        brother = son->bro;
        son->bro = NULL;
    } 
    while ((son = brother) != NULL);

    merge(tmp);

    return value;
}

template <class Type>
bool Bernoulli<Type>::isEmpty()
{
    for (int i = 0; i < scale; i++)
    {
        if (forest[i] != NULL) return false;
    }

    return true;
}

template <class Type>
Type Bernoulli<Type>::getHead()
{
    int pos = findMin();
    return forest[pos]->data;
}

int main()
{
    int num;
    cin >> num;

    char op[10];
    int opNum;
    Bernoulli<int> que;

    for (int i = 0; i < num; i++)
    {
        cin >> op;

        if (strcmp(op, "insert") == 0)
        {
            cin >> opNum;
            que.enQueue(opNum);
        }

        if (strcmp(op, "delete") == 0)
        {
            que.deQueue();
        }

        if (strcmp(op, "min") == 0)
        {
            cout << que.getHead() << endl;
        }
    }

    return 0;
}