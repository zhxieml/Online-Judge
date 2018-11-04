#include <iostream>
using namespace std;

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








