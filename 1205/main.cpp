#include <iostream>

using namespace std;

int A(int m, int n);

int A(int m ,int n)
{
    if (m == 0) return n + 1;
    if (n == 0) return A(m - 1, 1);
    return A(m - 1, A(m, n - 1));
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << A(m, n) << endl;
    return 0;
}
