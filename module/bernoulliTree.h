#ifndef BERNOULLITREE_H_INCLUDED
#define BERNOULLITREE_H_INCLUDED
    #include <iostream>
    #include "tree.h"
    using namespace std;

    template <class Type>
    class Bernoulli
    {
    private:
        typename tree<Type>::node **forest;
        int scale;

        typename tree<Type>::node *merge(typename tree<Type>::node *t1, typename tree<Type>::node *t2);
        int findMin();
        void deleteTree(typename tree<Type>::node *x);

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