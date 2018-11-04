#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class linkStack
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
        node *top_p;
    public:
        linkStack();
        ~linkStack();
        bool isEmpty() const;
        void push(const Type &x);
        Type pop();
        Type top() const;
    };

#endif

