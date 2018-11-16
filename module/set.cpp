#include <iostream>
#include "set.h"
using namespace std;

template <class Type>
set<Type>::set(int volume)
{
    currentSize = 0;
    maxSize = volume;
    elem = new Type[maxSize];
}

template <class Type>
set<Type>::set(const set<Type> &s)
{
    currentSize = s.currentSize;
    maxSize = s.maxSize;
    elem = new Type[maxSize];
    for (int i = 0; i < maxSize; i++) elem[i] = s.elem[i];
}

template <class Type>
set<Type>::~set()
{
    delete [] elem;
}

template <class Type>
void set<Type>::doubleSpace()
{
    Type *tmp = elem;

    maxSize *= 2;
    elem = new Type[maxSize];
    for (int i = 0; i < currentSize; i++) elem[i] = tmp[i];
    delete [] tmp;
}

template <class Type>
bool set<Type>::exist(Type x) const
{
    for (int i = 0; i < currentSize; i++)
    {
        if (elem[i] == x) return true;
    }

    return false;
}

template <class Type>
bool set<Type>::insert(Type x)
{
    if (exist(x)) return false;

    if (currentSize == maxSize) doubleSpace();
    elem[currentSize++] = x;
    return true;
}

template <class Type>
bool set<Type>::erase(Type x)
{
    bool flag = false;
    int i;
    for (i = 0; i < currentSize; i++)
    {
        if (elem[i] == x)
        {
            flag = true;
            break;
        }
    }

    if (flag) 
    {
        for (; i < currentSize - 1; i++) elem[i] = elem[i + 1];
    }

    return flag;
}

template <class Type>
void set<Type>::display()
{
    for (int i = 0; i < currentSize; i++) cout << elem[i] << ' ';
}

template <class Type>
set<Type> &set<Type>::operator=(const set<Type> &s)
{
    if (this == &s) return *this;

    currentSize = a.currentSize;
    maxSize = a.maxSize;
    delete [] elem;
    elem = new Type[maxSize];
    for (int i = 0; i < currentSize; i++) elem[i] = s.elem[i];
    return *this;
}

template <class Type>
set<Type> operator*(const set<Type> &s1, const set<Type> &s2)
{
    set<Type> s;

    for (int i = 0; i < s1.currentSize; i++)
    {
        if (s2.exist(s1.elem[i])) s.insert(s1.elem[i]);
    }

    return s;
}

template <class Type>
set<Type> operator+(const set<Type> &s1, const set<Type> &s2)
{
    set<Type> s(s2);

    for (int i = 0; i< s1.currentSize; i++) s.insert(s1.elem[i]);

    return s;
}

template <class Type>
set<Type> operator-(const set<Type> &s1, const set<Type> &s2)
{
    set<Type> s;

    for (int i = 0; i < s1.currentSize; i++)
    {
        if (!s2.exist(s1.elem[i])) s.insert(s1.elem[i]);
    }

    return s;
}
