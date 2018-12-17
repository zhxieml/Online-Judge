#include <iostream>
using namespace std;

int count;

int divide(int data[], int low, int high)
{
    int st = data[low];

    do
    {
        while (low < high && data[high] >= st) --high;
        if (low < high)
        {
            ++count;

            data[low] = data[high];
            ++low;
        }

        while (low < high && data[low] <= st) ++low;
        if (low < high)
        {
            ++count;

            data[high] = data[low];
            --high;
        }
    } while (low != high);

    ++count;

    data[low] = st;

    return low;
}

void quickSort(int data[], int low, int high)
{
    int mid;
    
    if (low >= high) return;

    mid = divide(data, low, high);
    quickSort(data, low, mid - 1);
    quickSort(data, mid + 1, high);
}

void quickSort(int data[], int size)
{
    quickSort(data, 0, size - 1);
}

///////////////////////////////////////////////////////////////

void merge(int data[], int left, int mid, int right)
{
    int *tmp = new int[right - left + 1];
    int i = left, j = mid, k = 0;
    while (i < mid && j <= right)
    {        
        ++count;

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
    if (left == right) return;

    int mid = (left + right) / 2;
    if ((right - left + 1) % 2 != 0) --mid;
    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);
    merge(data, left, mid + 1, right);
}

void mergeSort(int data[], int size)
{
    mergeSort(data, 0, size - 1);
}

///////////////////////////////////////////////////////////////

void percolateDown(int data[], int hole, int size)
{
    int child;
    int tmp = data[hole];

    for (; hole * 2 + 1 < size; hole = child)
    {
        child = hole * 2 + 1;

        ++count;
        if (child != size - 1) ++count;

        if (child != size - 1 && data[child + 1] < data[child]) ++child;
        
        if (data[child] < tmp) data[hole] = data[child];
        else break;
    }

    data[hole] = tmp;
}

void heapSort(int size)
{
    int *data = new int[size + 10];
    int hole, tmp;

    for (int i = 0; i < size; ++i)
    {
        cin >> data[i];
        hole = i;

        for (; hole != 0; hole = (hole - 1) / 2)
        {
            ++count;

            if (data[hole] < data[(hole - 1) / 2])
            {
                tmp = data[(hole - 1) / 2];
                data[(hole - 1) / 2] = data[hole];
                data[hole] = tmp;
            }

            else break;
        }
    }

    for (int i = size - 1; i > 0; --i)
    {
        // ++count;

        tmp = data[0];
        data[0] = data[i];
        data[i] = tmp;
        percolateDown(data, 0, i);
    }
}

///////////////////////////////////////////////////////////////

int main() 
{	
    int n, t;
    cin >> n >> t;

    int *data;

    switch (t)
    {
        case 1:
            heapSort(n);
            break;
        
        case 2:
            data = new int[n + 10];
            for (int i = 0; i < n; ++i) cin >> data[i];

            mergeSort(data, n);
            break;
        
        case 3:
            data = new int[n + 10];
            for (int i = 0; i < n; ++i) cin >> data[i];

            quickSort(data, n);
    }

    cout << count;

    return 0;
}