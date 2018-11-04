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

    template <class Type>
    seqList<Type>::seqList(int initSize)
    {
        data = new Type[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    template <class Type>
    seqList<Type>::~seqList()
    {
        delete [] data;
    }

    template <class Type>
    void seqList<Type>::clear()
    {
        currentLength = 0;
    }

    template <class Type>
    int seqList<Type>::length() const
    {
        return currentLength;
    }

    template <class Type>
    Type seqList<Type>::visit(int i) const
    {
        return data[i];
    }

    template <class Type>
    void seqList<Type>::traverse() const
    {
        for (int i = 0; i < currentLength; i++) cout << data[i] << ' ';
    }

    template <class Type>
    int seqList<Type>::search(const Type &x) const
    {
        int i = 0;
        for (; i < currentLength && data[i] != x; i++);
        if (i == currentLength) return -1;
        else return i;
    }

    template <class Type>
    void seqList<Type>::doubleSpace()
    {
        Type *tmp = data;

        maxSize *= 2;
        data = new Type[maxSize];
        for (int i = 0; i < currentLength; i++) data[i] = tmp[i];
        delete [] tmp;
    }

    template <class Type>
    void seqList<Type>::insert(int i, const Type &x)
    {
        if (currentLength == maxSize) doubleSpace();
        for (int j = currentLength; j > i; j--) data[j] = data[j - 1];
        data[i] = x;
        currentLength++;
    }

    template <class Type>
    void seqList<Type>::remove(int i)
    {
        for (int j = i; j < currentLength - 1; j++) data[j] = data[j + 1];
        currentLength--;
    }

#endif






