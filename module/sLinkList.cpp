#include <iostream>
using namespace std;

template <class Type>
typename sLinkList<Type>::node *sLinkList<Type>::move(int i) const
{
    node *p = head;
    while (i-- >= 0) p = p->next;
    return p;
}

template <class Type>
sLinkList<Type>::sLinkList()
{
    head = new node;
    currentLength = 0;
}

template <class Type>
void sLinkList<Type>::clear()
{
    node *p = head->next, *q;
    head->next = NULL;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }

    currentLength = 0;
}

template <class Type>
void sLinkList<Type>::insert(int i, const Type &x)
{
    node *pos;

    pos = move(i - 1);
    pos->next = new node(x, pos->next);
    currentLength++;
}

template <class Type>
void sLinkList<Type>::remove(int i)
{
    node *pos, *delp;

    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    currentLength--;
}

template <class Type>
int sLinkList<Type>::search(const Type &x) const
{
    node *p = head->next;
    int i = 0;

    while (p != NULL && p->data != x)
    {
        p = p->next;
        i++;
    }
    if (p == NULL) return -1;
    else return i;
}

template <class Type>
Type sLinkList<Type>::visit(int i) const
{
    return move(i)->data;
}

template <class Type>
void sLinkList<Type>::traverse() const
{
    node *p = head->next;
    cout << endl;
    while (p != NULL)
    {
        cout << p->data << ' ';
        p = p->next;
    }

    cout << endl;
}








