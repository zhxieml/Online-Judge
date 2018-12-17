#include <iostream>
using namespace std;

// 分块查找表，所有块块长相同
template <class Type>
class indexList
{
private:
    int blockSize;
    int listSize;
    Type *data;
    Type *index;

public:
    indexList(int bs, int ls, Type *d)；
    {
        blockSize = bs;
        listSize = ls;
        data = new Type[ls];
        index = new Type[(ls - 1) / blockSize + 1];
        for (int i = 0; i < ls; ++i) data[i] = d[i];
        for (int i = 0; i < (ls - 1) / bs; ++i) index[i] = data[(i + 1) * bs - 1];
        index[(ls - 1) / bs] = data[ls - 1];
    }
    ~indexList() {delete [] data; delete [] index;}

    int find(Type x) const;
};

template <class Type>
int indexList<Type>::find(Type x) const
{
    int i;
    int indexLength = listSize = = 0 ? 0 : (listSize - 1) / blockSize + 1;
    for (i = 0; i < indexLength; ++i)
    {
        if (x <= index[i]) break;
    }

    if (i == indexLength) return -1;

    int start, end;
    if (i == 0) start = 0;
    else start = i * blockSize;

    end = blockSize * (i + 1) - 1;
    end = (end < listSize ? end : listSize);

    for (i = start; i <= end; ++i)
    {
        if (x == data[i]) return i;
    }

    return -1;
}