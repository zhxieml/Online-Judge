#ifndef DLINKLIST_H_INCLUDED
#define DLINKLIST_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class dLinkList
    {
    private:
        struct node
        {
            Type data;
            node *prev, *next;

            node(const Type &x, node *p = NULL, node *n = NULL) {data = x; next = n; prev = p;}
            node():next(NULL), prev(NULL){}
            ~node(){}
        };

        node *head, *tail;
        int currentLength;

        node *move(int i) const;

    public:
        dLinkList();
        ~dLinkList() {clear(); delete head; delete tail;}

        void clear();
        int length() const {return currentLength;}
        void insert(int i, const Type &x);
        void remove(int i);
        int search(const Type &x) const;
        Type visit(int i) const;
        void traverse() const;
    };

#endif









