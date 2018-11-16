#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class binarySearchTree
    {
    private:
        struct node
        {
            Type data;
            node *left, *right;

            node(const Type &d, node *l, node *r): data(d), left(l), right(r){}
        };

        node *root;

        void insert(const Type &x, node *&p);
        void remove(const Type &x, node *&p);
        bool find(const Type &x, node *p) const;
        void clear(node *&x);

    public:
        binarySearchTree(node *r);
        ~binarySearchTree();
        bool find(const Type &x);
        void insert(const Type &x);
        void remove(const Type &x);
        void display() const;   // Display in order
    };

#endif