#include <iostream>
using namespace std;

void percolateDown(int data[], int hole, int size)
{
    int child;
    int tmp = data[hole];

    for (; hole * 2 + 1 < size; hole = child)
    {
        child = hole * 2 + 1;

        if (child != size - 1 && data[child + 1] > data[child]) ++child;

        if (data[child] > tmp) data[hole] = data[child];
        else break;
    }

    data[hole] = tmp;
}

void headSort(int data[], int size)
{
    int i;
    int tmp;

    for (i = size / 2 - 1; i >= 0; --i) percolateDown(data, i, size);

    for (i = size - 1; i > 0; --i)
    {
        tmp = data[0];
        data[0] = data[i];
        data[i] = tmp;
        percolateDown(data, 0, i);
    }
}