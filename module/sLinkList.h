#ifndef SLINKLIST_H_INCLUDED
#define SLINKLIST_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class sLinkList
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

        node *head;
        int currentLength;

        node *move(int i) const;

    public:
        sLinkList();
        ~sLinkList(){clear(); delete head;}

        void clear();
        int length() const {return currentLength;}
        void insert(int i, const Type &x);
        void remove(int i);
        int search(const Type &x) const;
        Type visit(int i) const;
        void traverse() const;
    };

#endif









