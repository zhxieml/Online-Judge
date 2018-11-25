#include <iostream>
using namespace std;

template <class Key, class Other>
struct set
{
    Key key;
    Other other;
};

///////////////////////////////////////////////////////////////////////

template <class Key, class Other>
class closeHashTable
{
private:
    struct node
    {
        set<Key, Other> data;
        int state;  // 0--empty; 1--active; 2--deleted;

        node(){state = 0;}
    };

    node *elem;
    int size;   // Prime number check;
    int (*key)(const Key &x);
    static int defaultKey(const int &x){return x;}

public:
    closeHashTable(int length = 101, int (*f)(const Key &x) = defaultKey);
    ~closeHashTable(){delete [] elem;}
    set<Key, Other> *find(const Key &x) const;
    void insert(const set<Key, Other> &x);
    void remove(const Key &x); 
};

template <class Key, class Other>
closeHashTable<Key, Other>::closeHashTable(int length, int (*f)(const Key &x))
{
    size = length;
    elem = new node[size];
    key = f;
}

template <class Key, class Other>
void closeHashTable<Key, Other>::insert(const set<Key, Other> &x)
{
    int initPos, pos;
    initPos = pos = key(x.key) % size;

    do
    {
        if (elem[pos].state != 1)
        {
            elem[pos].data = x;
            elem[pos].state = 1;
            return;
        }

        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class Key, class Other>
void closeHashTable<Key, Other>::remove(const Key &x)
{
    int initPos, pos;
    initPos = pos = key(x) % size;

    do 
    {
        if (elem[pos].state == 0) return;

        if (elem[pos].state == 1 && elem[pos].data.key == x)
        {
            elem[pos].state == 2;
            return;
        }

        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class Key, class Other>
set<Key, Other> *closeHashTable<Key, Other>::find(const Key &x) const
{
    int initPos, pos;
    initPos = pos = key(x) % size;

    do
    {
        if (elem[pos].state == 0) return NULL;

        if (elem[pos].state == 1 && elem[pos].data.key == x) return (set<Key, Other> *)&elem[pos];

        pos = (pos + 1) % size; 
    } while (pos != initPos);
}

///////////////////////////////////////////////////////////////////////

int main() 
{	
    closeHashTable<int, int> test;
    
    return 0;
}