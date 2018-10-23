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

template <class Type>
dLinkList<Type>::dLinkList()
{
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

template <class Type>
typename dLinkList<Type>::node *dLinkList<Type>::move(int i) const
{
    node *p = head;
    while (i-- >= 0) p = p->next;
    return p;
}

template <class Type>
void dLinkList<Type>::insert(int i, const Type &x)
{
    node *pos, *tmp;
    pos = move(i);
    tmp = new node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    currentLength++;
}

template <class Type>
void dLinkList<Type>::remove(int i)
{
    node *pos;

    pos = move(i);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    currentLength--;
}

template <class Type>
void dLinkList<Type>::clear()
{
    node *p = head->next, *q;
    head->next = tail;
    tail->prev = head;
    while (p != tail)
    {
        q = p->next;
        delete p;
        p = q;
    }

    currentLength = 0;
}

template <class Type>
int dLinkList<Type>::search(const Type &x) const
{
    node *p = head->next;
    int i;

    for (i = 0; p != tail && p->data != x; i++) p = p->next;
    if (p == tail) return -1;
    else return i;
}

template <class Type>
Type dLinkList<Type>::visit(int i) const
{
    return move(i)->data;
}

template <class Type>
void dLinkList<Type>::traverse() const
{
    node *p = head->next;
    cout << endl;
    while (p != tail)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}












