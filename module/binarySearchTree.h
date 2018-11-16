#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
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
        void clear(node *p);
        void display(node *p) const;

    public:
        binarySearchTree(node *r = NULL): root(r){};
        ~binarySearchTree();
        bool find(const Type &x) const;
        void insert(const Type &x);
        void remove(const Type &x);
        void clear();
        void display() const;   // Display in order
    };

#endif