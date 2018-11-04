#include <iostream>
#include <cmath>
#include "bernoulliTree.h"
using namespace std;

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

    else 
    {
        for (; i < other.scale; i++)
        {
            if (carry == NULL) forest[i] = other.forest[i];

            else
            {
                if (other.forest[i] == NULL)
                {
                    forest[i] = carry;
                    carry = NULL;
                }

                else carry = merge(other.forest[i], carry);
            }
        }
    }

    if (carry != NULL) forest[i] = carry;

    for (i = 0; i < other.scale; i++) other.forest[i] = NULL;
    delete [] tmp;
}

template <class Type>
typename tree<Type>::node *Bernoulli<Type>::merge(typename tree<Type>::node *t1, typename tree<Type>::node *t2)
{
    tree<Type>::node *min, *max;

    if (t1->data < t2->data)
    {
        min = t1;
        max = t2;
    }

    else 
    {
        min = t2;
        max = t1;
    }

    if (min->son == NULL) min->son = max;

    else 
    {
        tree<Type>::node *t = min->son;
        while (t->bro != NULL) t = t->bro;
        t->bro = max;
    }

    return min;
}
