#include <iostream>
using namespace std;

template <class Type>
int divide(Type data[], int low, int high)
{
    Type st = data[low];

    do
    {
        while (low < high && data[high] >= st) high--;
        if (low < high)
        {
            data[low] = data[high];
            low++;
        }

        while (low < high && data[low] <= st) low++;
        if (low < high)
        {
            data[high] = data[low];
            high--;
        }
    } while (low != high);

    data[low] = st;
    return low;
}

template <class Type>
void quickSort(Type data[], int low, int high)
{
    int mid;
    
    if (low >= high) return;

    mid = divide(data, low, high);
    quickSort(data, low, mid - 1);
    quickSort(data, mid + 1, high);
}

template <class Type>
void quickSort(Type data[], int size)
{
    quickSort(data, 0, size - 1);
}