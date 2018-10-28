#include <iostream>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    int people[100000];

    for (int i = 0; i < n; i++) people[i] = i + 1;

    int call = 0;

    int index;

    for (int i = 0; i < k; i++)
    {
        call = (call + m - 1) % n;
        index = people[call];

        for (int j = call; j < n - 1; j++) people[j] = people[j + 1];

        n--;
    }

    cout << index;
    return 0;
}
