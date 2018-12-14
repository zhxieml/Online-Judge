#include <iostream>
using namespace std;

void merge(int data[], int left, int mid, int right)
{
    int *tmp = new int[right - left + 1];
    int i = left, j = mid, k = 0;
    while (i < mid && j <= right)
    {
        if (data[i] < data[j]) tmp[k++] = data[i++];
        else tmp[k++] = data[j++];
    }
    while (i < mid) tmp[k++] = data[i++];
    while (j <= right) tmp[k++] = data[j++];
    for (i = 0, k = left; k <= right; ) data[k++] = tmp[i++];

    delete [] tmp;
}

void mergeSort(int data[], int left, int right)
{
    int mid = (left + right) / 2;
    if (left == right) return;
    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);
    merge(data, left, mid + 1, right);
}

void mergeSort(int data[], int size)
{
    mergeSort(data, 0, size - 1);
}