#include <iostream>
#include "binarySearchTree.h"
using namespace std;

template <class Type>
binarySearchTree<Type>::~binarySearchTree()
{
    clear(root);
}

template <class Type>
bool binarySearchTree<Type>::find(const Type &x) const
{
    return find(x, root);
}

template <class Type>
bool binarySearchTree<Type>::find(const Type &x, node *p) const
{
    if (!p) return false;

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
    if (!p) p = new node(x, NULL, NULL);

    else
    {
        if (x < p->data) insert(x, p->left);

        else if (x > p->data) insert(x, p->right);
    }
}

template <class Type>
void binarySearchTree<Type>::remove(const Type &x)
{
    remove(x, root);
}

template <class Type>
void binarySearchTree<Type>::remove(const Type &x, node *&p)
{
    if (!p) return;

    if (x < p->data) remove(x, p->left);

    else
    {
        if (x > p->data) remove(x, p->right);

        else
        {
            if (p->left && p->right)
            {
                node *tmp = p->right;

                while (tmp->left) tmp = tmp->left;
                p->data = tmp->data;
                remove(p->data, p->right);
            }

            else 
            {
                node *tmp = p;
                p = (p->left) ? p->left:p->right;
                delete tmp;
            }
        }
    }
}

template <class Type>
void binarySearchTree<Type>::clear()
{
    clear(root);
}

template <class Type>
void binarySearchTree<Type>::clear(node *p)
{
    if (!p) return;

    if (p->left) clear(p->left);
    if (p->right) clear(p->right);

    delete p;
}

template <class Type>
void binarySearchTree<Type>::display() const
{
    display(root);
}

template <class Type>
void binarySearchTree<Type>::display(node *p) const
{
    if (!p) return;

    if (p->left) display(p->left);

    cout << p->data << ' ';

    if (p->right) display(p->right);
}