#ifndef BERNOULLITREE_H_INCLUDED
#define BERNOULLITREE_H_INCLUDED
    #include <iostream>
    #include "tree.h"
    using namespace std;

    template <class Type>
    class Bernoulli
    {
    private:
        node<Type> **forest;
        int scale;

        node<Type> *merge(node<Type> *t1, node<Type> *t2);
        int findMin();
        void deleteTree(node<Type> *x);

    public:
        Bernoulli(int n = 100);
        ~Bernoulli();

        void enQueue(Type x);
        Type deQueue();
        bool isEmpty();
        Type getHead() const;
        void merge(Bernoulli &other);
    };

#endif