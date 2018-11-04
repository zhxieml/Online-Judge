#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
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

#endif