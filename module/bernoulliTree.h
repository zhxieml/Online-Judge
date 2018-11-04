#ifndef BERNOULLITREE_H_INCLUDED
#define BERNOULLITREE_H_INCLUDED
    #include <iostream>
    #include <cmath>
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

    template <class Type>
    void Bernoulli<Type>::deleteTree(typename tree<Type>::node *x)
    {
        typename tree<Type>::node *son = x->son, *t;
        while (son != NULL)
        {
            t = son;
            son = son->bro;
            deleteTree(t);
        }

        delete(x);
    }

    template <class Type>
    Bernoulli<Type>::Bernoulli(int n)
    {
        scale = int(log(n) / log(2)) + 1;
        forest = new tree<Type>::node *[scale];
        for (int i = 0; i < scale; i++) forest[i] = NULL;
    }

    template <class Type>
    Bernoulli<Type>::~Bernoulli()
    {
        for (int i = 0; i < scale; i++)
        {
            if (forest[i] != NULL) deleteTree(forest[i]);
        }

        delete [] forest;
    }

    template <class Type>
    void Bernoulli<Type>::merge(Bernoulli &other)
    {
        tree<Type>::node **tmp = forest;
        tree<Type>::node *carry;
        int tmpSize = scale;
        int min = scale < other.scale ? scale : other.scale;
        int i;

        if (scale < other.scale)
        {
            scale = other.scale;
            if (other.forest[scale] != NULL) scale++;
        }

        else if (forest[scale] != NULL) scale++;

        forest = new tree<Type>::node *[scale];
        for (i = 0; i < scale; i++) forest[i] = NULL;

        carry = NULL;
        for (i = 0; i < min; i++)
        {
            if (carry == NULL)
            {
                if (tmp[i] == NULL) forest[i] = other.forest[i];

                else 
                {
                    if (other.forest[i] == NULL) forest[i] = tmp[i];
                    else carry = merge(other.forest[i], tmp[i]);
                }
            }

            else
            {
                if (tmp[i] != NULL && other.forest[i] != NULL)
                {
                    forest[i] = carry;
                    carry = merge(other.forest[i], tmp[i]);
                }

                else
                {
                    if (tmp[i] == NULL && other.forest[i] == NULL)
                    {
                        forest[i] = carry;
                        carry = NULL;
                    }

                    else 
                    {
                        if (tmp[i] == NULL) carry = merge(other.forest[i], carry);
                        
                        else carry = merge(tmp[i], carry);
                    }
                }
            }   
        }

        if (other.scale == min)
        {
            for (; i < tmpSize; i++)
            {
                if (carry == NULL) forest[i] = tmp[i];

                else
                {
                    if (tmp[i] == NULL)
                    {
                        forest[i] == carry;
                        carry = NULL;
                    }

                    else carry = merge(tmp[i], carry);
                }
            }
        }
    }

#endif