#include <iostream>
using namespace std;

struct node
{
    node *son, *bro, *prev;
    int data;

    node(int d = 0, node *s = NULL, node *b = NULL, node *p = NULL): data(d), son(s), bro(b), prev(p){}
    ~node(){}
};

////////////////////////////////////////////////////////////////

int main() 
{	
    int num;
    cin >> num;

    int tmp, s, b;
    node **nodes = new node *[num + 1];
    for (int i = 0; i < num + 1; i++) nodes[i] = new node;

    for (int i = 0; i < num; i++)
    {
        cin >> tmp >> s >> b;

        if (s)  
        {
            nodes[tmp]->son = nodes[s];
            nodes[s]->prev = nodes[tmp];
        }

        if (b)
        {
            nodes[tmp]->bro = nodes[b];
            nodes[b]->prev = nodes[tmp];
        }
    }

    return 0;
}