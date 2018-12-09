#include <iostream>
#include "priorityQueue.h"
using namespace std;

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    elem = new Type[capacity];
    maxSize = capacity;
    currentLength = 0;
}

template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete [] elem;
}

template<class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentLength == 0;
}

template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return elem[1];
}

template<class Type>
void priorityQueue<Type>::doubleSpace()
{
    Type *tmp = elem;

    maxSize *= 2;
    elem = new Type[maxSize];
    for (int i = 0; i <= currentLength; i++) elem[i] = tmp[i];
    delete [] tmp;
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentLength == maxSize - 1) doubleSpace();

    int hole = ++currentLength;
    for (; hole > 1 && x < elem[hole / 2]; hole /= 2) elem[hole] = elem[hole / 2];
    elem[hole] = x;
}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp = elem[hole];

    for (; hole * 2 <= currentLength; hole = child)
    {
        child = hole * 2;

        if (child != currentLength && elem[child + 1] < elem[child]) child++;

        if (elem[child] < tmp) elem[hole] = elem[child];
        else break;
    }

    elem[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap()
{
    for (int i = currentLength / 2; i > 0; i--) percolateDown(i);
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size): maxSize(size + 10), currentLength(size)
{
    elem = new Type[maxSize];
    for (int i = 0; i < size; i++) elem[i + 1] = items[i];

    buildHeap();
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{ 
    Type minItem;
    minItem = elem[1];
    elem[1] = elem[currentLength--];
    
    percolateDown(1);
    return minItem;
} 
