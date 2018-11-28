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

////////////////////////////////////////////////////////////////////////

int main() 
{	
    int num;
    cin >> num;

    int in, out;
    priorityQueue<int> queIn, queOut;

    for (int i = 0; i < num; i++)
    {
        cin >> in >> out;

        queIn.enQueue(in);
        queOut.enQueue(out);
    }

    int tmp;
    int currentTime = 0;
    int currentNum = 0;
    int count1 = 0;
    int max1 = 0;
    int max2 = 0;

    while (!queIn.isEmpty() || !queOut.isEmpty())
    {   
        if (queIn.getHead() <= queOut.getHead() && !queIn.isEmpty())
        {
            tmp = queIn.deQueue();

            if (currentNum == 0)
            {
                if (tmp - currentTime > max2 && currentTime != 0) max2 = tmp - currentTime;
            }

            else count1 += tmp - currentTime;

            currentNum++;
            currentTime = tmp;
        }

        else
        {
            tmp = queOut.deQueue();

            count1 += tmp - currentTime;

            if (currentNum == 1) 
            {
                if (count1 > max1) max1 = count1;

                count1 = 0;
            }

            currentNum--;
            currentTime = tmp;
        }
    }

    cout << max1 << ' ' << max2;

    return 0;
}