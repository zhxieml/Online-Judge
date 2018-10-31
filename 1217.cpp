#include <iostream>
using namespace std;

bool find(int e[], int length, int x)
{
    for (int i = 0; i < length; i++)
    {
        if (e[i] == x) return true;
    }

    return false;
}

int main()
{
    int n, m, tmp;

    cin >> n;

    int *elem = new int[n];

    for (int i = 0; i < n; i++) cin >> elem[i];

    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> tmp;

        if (find(elem, n, tmp)) cout << 'Y' << endl;
        else cout << 'N' << endl;
    }

    return 0;
}