#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int monkeys[10000];

    for (int i = 0; i < n; i++) monkeys[i] = i + 1;

    int index = 0;

    int op, n1, n2;

    for (int i = 0; i < m; i++)
    {
        cin >> op;

        if (op == 0)
        {
            cin >> n1;

            index = (index + n1 - 1) % n;

            for (int j = index + 1; j < n; j++) monkeys[j - 1] = monkeys[j];
            n--;
        }

        else
        {
            cin >> n1 >> n2;

            index = (index+ n1) % n;
            for (int j = n; j > index; j--) monkeys[j] = monkeys[j - 1];

            monkeys[index] = n2;

            n++;
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++) sum += monkeys[i];

    cout << sum;
}

















