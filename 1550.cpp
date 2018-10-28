#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    char input[50000];
    cin >> input;

    int ground[2000];
    int count = 0;

    for (int i = 0; input[i] != '\0' && count < n; i++)
    {
        if (input[i] <= '9' && input[i] >= '0')
        {
            ground[count] = input[i] - '0';
            count++;
        }
    }

    int level = 0;
    int pool = 0;
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (ground[i] > level)
        {
            level = ground[i];
            sum += pool;
            pool = 0;
        }

        else
        {
            pool += level - ground[i];
        }
    }

    level = pool = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (ground[i] >= level)
        {
            level = ground[i];
            sum += pool;
            pool = 0;
        }

        else
        {
            pool += level - ground[i];
        }
    }

    cout << sum;
    return 0;
}

























