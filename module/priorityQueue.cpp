#include <iostream>
using namespace std;

template<class Type>
class priorityQueue
{
private:
    int currentLength;
    Type *elem;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};

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

}


