#include <iostream>
#include <cstring>
using namespace std;
template <class elemType>
class seqList
{
    private:
        elemType *data;
        int currentLength;
        int maxSize;
        void doubleSpace();

    public:
        seqList(int initSize = 10);
        ~seqList(){delete [] data;}

        void append(const elemType x);
        void display() const;

        seqList<elemType> operator+(const seqList<elemType> &s) const;
};

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::append(const elemType x)
{
    if (currentLength == maxSize) doubleSpace();
    data[currentLength] = x;
    currentLength++;
}

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 0; i < currentLength; i++) data[i] = tmp[i];
    delete [] tmp;
}

template <class elemType>
void seqList<elemType>::display() const
{
    for (int i = 0; i < currentLength; i++) cout << data[i] << " ";
}

template <class elemType>
seqList<elemType> seqList<elemType>::operator+(const seqList<elemType> &s) const
{
    seqList<elemType> new_s(currentLength + s.currentLength);
    for (int i = 0; i < currentLength; i++) new_s.data[i] = data[i];
    for (int i = 0; i < s.currentLength; i++) new_s.data[i + currentLength] = s.data[i];
    new_s.currentLength = new_s.maxSize;

    return new_s;
}

int main()
{
    char input_type[6];
    cin >> input_type;

    if (strcmp(input_type, "int") == 0)
    {
        seqList<int> sl_A;
        seqList<int> sl_B;

        int m, n;
        cin >> m >> n;
        int x;

        for (int i = 0; i < m; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_A.append(x);
        }

        for (int i = 0; i < n; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_B.append(x);
        }

        (sl_A + sl_B).display();
        return 0;
    }

    if (strcmp(input_type, "double") == 0)
    {
        seqList<double> sl_A;
        seqList<double> sl_B;

        int m, n;
        cin >> m >> n;
        double x;

        for (int i = 0; i < m; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_A.append(x);
        }

        for (int i = 0; i < n; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_B.append(x);
        }

        (sl_A + sl_B).display();
        return 0;
    }

    if (strcmp(input_type, "char") == 0)
    {
        seqList<char> sl_A;
        seqList<char> sl_B;

        int m, n;
        cin >> m >> n;
        char x;

        for (int i = 0; i < m; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_A.append(x);
        }

        for (int i = 0; i < n; i++)
        {
            cin >> x;
            if (!cin.good()) return -1;
            sl_B.append(x);
        }

        (sl_A + sl_B).display();
        return 0;
    }

    return -1;
}
