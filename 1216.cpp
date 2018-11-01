#include <iostream>
#include <cstring>
using namespace std;

const int INT_MAX = 2147483647;

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
    int find(int x) const;
    void decrease(int i, int v);
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

template<class Type>
int priorityQueue<Type>::find(int x) const
{
    int minIndex = 0;
    elem[0] = INT_MAX;

    for (int i = 1; i <= currentLength; i++)
    {
        if (elem[i] > x && elem[i] < elem[minIndex]) minIndex = i;
    }

    return minIndex;
}

template<class Type>
void priorityQueue<Type>::decrease(int i, int v)
{
    int x = elem[i] - v;
    
    for (; i > 1 && x < elem[i / 2]; i /= 2) elem[i] = elem[i / 2];

    elem[i] = x;
}

/////////////////////////////////////////////////////////////////

int main()
{
    int num;
    cin >> num;

    char op[10];
    int op1, op2;

    priorityQueue<int> que;

    for (int i = 0; i < num; i++)
    {
        cin >> op;

        if (strcmp(op, "insert") == 0) 
        {
            cin >> op1;
            que.enQueue(op1);
        }

        if (strcmp(op, "find") == 0)
        {
            cin >> op1;
            cout << que.find(op1) << endl;
        }

        if (strcmp(op, "decrease") == 0)
        {
            cin >> op1 >> op2;
            que.decrease(op1, op2);
        }
    }

    return 0;
}

