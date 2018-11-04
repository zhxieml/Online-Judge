#ifndef LINKQUQUE_H_INCLUDED
#define LINKQUQUE_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class linkQueue
    {
    private:
        struct node
        {
            Type data;

            node *next;

            node(const Type &x, node *n = NULL)
            {
                data = x;
                next = n;
            }

            node(): next(NULL){}
            ~node(){}
        };

        node *front, *rear;

    public:
        linkQueue();
        ~linkQueue();
        bool isEmpty() const;
        void enQueue(const Type &x);
        Type deQueue();
        Type getHead() const;
    };

#endif







