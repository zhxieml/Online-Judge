#include <iostream>
using namespace std;

int main() 
{	
    int num;
    cin >> num;

    int *count = new int[num]{0};
    int *check = new int[num + 1]{0};
    count[0] = 1;
    check[1] = 1;

    int tmp;
    // bool flag = true;

    for (int i = 1; i < num; i++)
    {
        cin >> tmp;

        if (count[tmp] * 2 <= num && check[count[tmp] * 2] == 0) 
        {
            count[i] = count[tmp] * 2;
            check[count[tmp] * 2] = 1;
        }

        else if (count[tmp] * 2 + 1 <= num && check[count[tmp] * 2 + 1] == 0) 
        {
            count[i] = count[tmp] * 2 + 1;
            check[count[tmp] * 2 + 1] = 1;
        }

        else 
        {
            cout << "false";
            return 0;
        }
    }

    for (int i = num; i >= 1; i--)
    {
        if (check[i] == 0)
        {
            cout << "false";
            return 0;
        }
    }

    cout << "true";

    return 0;
}