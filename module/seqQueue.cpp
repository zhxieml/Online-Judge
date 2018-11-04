#include <iostream>
using namespace std;

template <class Type>
seqQueue<Type>::seqQueue(int size)
{
    elem = new Type[size];
    maxSize = size;
    front = rear = 0;
}

template <class Type>
seqQueue<Type>::~seqQueue()
{
    delete [] elem;
}

template <class Type>
void seqQueue<Type>::doubleSpace()
{
    Type *tmp = elem;
    elem = new Type[maxSize * 2];
    for (int i = i; i < maxSize; i++) elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

template <class Type>
bool seqQueue<Type>::isEmpty() const
{
    return front == rear;
}

template <class Type>
void seqQueue<Type>::enQueue(const Type &x)
{
    if ((rear + 1) % maxSize == front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class Type>
Type seqQueue<Type>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <class Type>
Type seqQueue<Type>::getHead() const
{
    return elem[(front + 1) % maxSize];
}
