#include <iostream>
#include <iomanip>
using namespace std;
class seqQueue
{
private:
    int *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();

public:
    seqQueue(int size = 10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const int &x);
    int deQueue();
    int getHead() const;
};

struct ship
{
    int load;
    int num_0;
};

seqQueue::seqQueue(int size)
{
    elem = new int[size];
    maxSize = size;
    front = rear = 0;
}

seqQueue::~seqQueue()
{
    delete [] elem;
}

void seqQueue::doubleSpace()
{
    int *tmp = elem;
    elem = new int[maxSize * 2];
    for (int i = 1; i <= maxSize; i++) elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete [] tmp;
}

bool seqQueue::isEmpty() const
{
    return front == rear;
}

void seqQueue::enQueue(const int &x)
{
    if ((rear + 1) % maxSize == front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

int seqQueue::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

int seqQueue::getHead() const
{
    return elem[(front + 1) % maxSize];
}

int main()
{
    double totalWaitT_0 = 0, totalWaitT_1 = 0;
    int currentT = 0;
    int load = 0;
    int num;
    int num_0 = 0, num_1 = 0;
    int type, arriveT;
    seqQueue q_0(20000), q_1(20000);

    cin >> num;

    for (int i = 0; i < num; i++)
    {
        cin >> type >> arriveT;
        switch (type)
        {
            case 0:
                num_0++;
                q_0.enQueue(arriveT);
                break;

            case 1:
                num_1++;
                q_1.enQueue(arriveT);
                break;
        }
    }


    while (!q_0.isEmpty() || !q_1.isEmpty())
    {
        // We make sure that all the 0-type cars can be loaded first;
        while (load < 8 && !q_0.isEmpty() && q_0.getHead() <= currentT)
        {
            totalWaitT_0 += currentT - q_0.getHead();
            q_0.deQueue();
            load++;
        }

        // And then 1-type cars will be loaded;
        while (load < 10 && !q_1.isEmpty() && q_1.getHead() <= currentT)
        {
            totalWaitT_1 += currentT - q_1.getHead();
            q_1.deQueue();
            load++;
        }

        currentT += 10;
        load = 0;
    }


    cout << fixed << setprecision(3) << totalWaitT_0 / num_0 << ' ' << totalWaitT_1 / num_1;
    return 0;
}
