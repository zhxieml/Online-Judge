#ifndef CLOSEHASHTABLE_H_INCLUDED
#define CLOSEHASHTABLE_H_INCLUDED
    #include "set.h"
    
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

#endif