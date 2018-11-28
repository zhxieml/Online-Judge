#include <iostream>
using namespace std;

struct node
{
    int weight;
    int parent;

    // node(int w = 0, int p = 0): weight(w), parent(p) {}
};

//////////////////////////////////////////////////////////////////////////

int main() 
{	
    int num;
    cin >> num;

    const int MAX_INT = 2147483647;
    int min1, min2;
    int x, y;
    int length = 2 * num;
    // node *elem = new node[length + 10];
    node elem[50000];

    for (int i = num; i < length; ++i)
    { 
        cin >> elem[i].weight;
        elem[i].parent = 0;
    } 

    for (int i = num - 1; i > 0; --i)
    { 
        min1 = min2 = MAX_INT; 
        x = y = i + 1;

        for (int j = i + 1; j < length; ++j)
        {
		    if (elem[j].parent == 0)
            {
		       if (elem[j].weight < min1) 
                { 
                    min2 = min1; 
                    min1 = elem[j].weight; 
                    x = y;
                    y = j;
                }
                
                else if (elem[j].weight < min2)
                {
                    min2 = elem[j].weight; 
                    x = j; 
                }
            } 
        }

        elem[i].weight = min1 + min2;
        elem[i].parent = 0;
        elem[x].parent = i; 
        elem[y].parent = i;
    }

    long long result = 0;
    int tmp;
    int p;

    for (int i = num; i < length; i++)
    {
        tmp = 0;
        p = elem[i].parent; 

        while (p)
        {
            tmp++;
            p = elem[p].parent;
        }

        result += tmp * elem[i].weight;
    }

    cout << result;

    return 0;
}