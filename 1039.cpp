#include <iostream>
using namespace std;

int bTree[100000]{0};

void postTraveral(int i)
{
    if (!bTree[i]) return;

    postTraveral(i * 2);
    postTraveral(i * 2 + 1);
    cout << bTree[i] << ' ';
}

int main() 
{	
    int num;
    cin >> num;

    int node, left, right;
    int *index = new int[num + 1];
    index[1] = bTree[1] = 1;

    for (int i = 1; i <= num; i++)
    {
        cin >> node >> left >> right;

        if (left != -1)
        {
            index[left] = index[node] * 2;
            bTree[index[node] * 2] = left;
        }

        if (right != -1)
        {
            index[right] = index[node] * 2 + 1;
            bTree[index[node] * 2 + 1] = right;
        }
    }

    for (int i = 1; i <= num; i++) cout << index[i] << ' ';

    cout << endl;

    postTraveral(1);
    return 0;
}