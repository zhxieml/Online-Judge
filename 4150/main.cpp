#include <iostream>
using namespace std;

template <class Type>
class seqQueue
{
private:
    Type *elem;
    int maxSize;
    int front, rear;
    int total;
    void doubleSpace();

public:
    seqQueue(int size = 100000);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
    bool isFull() const;
    Type getTotal() const;
};

template <class Type>
seqQueue<Type>::seqQueue(int size)
{
    elem = new Type[size];
    maxSize = size;
    front = rear = 0;
    total = 0;
}

template <class Type>
seqQueue<Type>::~seqQueue()
{
    delete [] elem;
}

template <class Type>
bool seqQueue<Type>::isEmpty() const
{
    return front == rear;
}

template <class Type>
void seqQueue<Type>::enQueue(const Type &x)
{
//    if ((rear + 1) % maxSize == front)
//    {
//        cout << "Full" << endl;
//        doubleSpace();
//    }
    rear = (rear + 1) % maxSize;
    elem[rear] = x;

    total += x;
}

template <class Type>
Type seqQueue<Type>::deQueue()
{
    front = (front + 1) % maxSize;
    total -= elem[front];
    return elem[front];
}

template <class Type>
bool seqQueue<Type>::isFull() const
{
    return (rear + 1) % maxSize == front;
}

template <class Type>
Type seqQueue<Type>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

template <class Type>
Type seqQueue<Type>::getTotal() const
{
    return total;
}

//////////////////////////////////////////////////////

int main()
{
    int n, m;
    cin >> n >> m;

    seqQueue<int> que(n + 1);
    int count = 0;
    int num;

    int numList[10000];

    for (int i = 0; i < m; i++) cin >> numList[i];

    for (int i = 0; i < m; i++)
    {
//        cout << numList[i] << endl;
        if (que.isFull()) que.deQueue();
        que.enQueue(numList[i]);
        if (count < n) count++;

        cout << que.getTotal() / count << endl;
    }


    return 0;
}
