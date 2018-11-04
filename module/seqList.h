#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED
    #include <iostream>
    using namespace std;

    template <class Type>
    class seqList
    {
    private:
        Type *data;
        int currentLength;
        int maxSize;
        void doubleSpace();

    public:
        seqList(int initSize = 10);
        ~seqList();

        void clear();
        int length() const;
        void insert(int i, const Type &x);
        void remove(int i);
        int search(const Type &x) const;
        Type visit(int i) const;
        void traverse() const;
    };

#endif






