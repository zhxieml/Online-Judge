#include <iostream>
#include "binarySearchTree.h"
using namespace std;

template <class Type>
bool binarySearchTree<Type>::find(const Type &x) const
{
    return find(x, root);
}

template <class Type>
bool binarySearchTree<Type>::find(const Type &x, node *p) const
{
    if (p == NULL) return false;

    if (x < p->data) return find(x, p->left);

    if (x > p->data) return find(x, p->right);

    return true;
}

template <class Type>
void binarySearchTree<Type>::insert(const Type &x)
{
    insert(x, root);
}

template <class Type>
void binarySearchTree<Type>::insert(const Type &x, node *&p)
{
    if (p == NULL) p = new node 
}