#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class seqQueue
    {
    private:
        Type *elem;
        int maxSize;
        int front, rear;

        void doubleSpace();

    public:
        seqQueue(int size = 10);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const Type &x);
        Type deQueue();
        Type getHead() const;
    };

#endif