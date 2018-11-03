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




