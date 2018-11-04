#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class seqStack
    {
    private:
        Type *elem;
        int top_p;
        int maxSize;
        void doubleSpace();

    public:
        seqStack(int initSize = 10);
        ~seqStack();
        bool isEmpty() const;
        void push(const Type &x);
        Type pop();
        Type top() const;

    };

#endif














