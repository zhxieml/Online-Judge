#include <iostream>
using namespace std;

template <class Type>
seqStack<Type>::seqStack(int initSize)
{
    elem = new Type[initSize];
    maxSize = initSize;
    top_p = -1;
}

template <class Type>
seqStack<Type>::~seqStack()
{
    delete [] elem;
}

template <class Type>
bool seqStack<Type>::isEmpty() const
{
    return top_p == -1;
}

template <class Type>
void seqStack<Type>::push(const Type &x)
{
    if (top_p == maxSize - 1) doubleSpace();
    elem[++top_p] = x;
}

template <class Type>
Type seqStack<Type>::pop()
{
    return elem[top_p--];
}

template <class Type>
Type seqStack<Type>::top() const
{
    return elem[top_p];
}

template <class Type>
void seqStack<Type>::doubleSpace()
{
    Type *tmp = elem;

    elem = new Type[2 * maxSize];

    for (int i = 0; i < maxSize; i++) elem[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
}








