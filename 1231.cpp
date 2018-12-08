#include <iostream>
using namespace std;

struct node
{
    // int data;
    int parent, left, right;

    node(int p = 0, int l = 0, int r = 0): parent(p), left(l), right(r) {}
};

int find_LCA(int root, int x, int y, node *nodes)
{
    if (!root) return 0;
    if (root == x || root == y) return root;

    int left = find_LCA(nodes[root].left, x, y, nodes);
    int right = find_LCA(nodes[root].right, x, y, nodes);

    if (left && right) return root;

    if (left) return left;
    if (right) return right;

    return 0;
}

int main() 
{	
    int n, x, y;
    cin >> n >> x >> y;

    node *nodes = new node[n + 1];
    int left, right;

    for (int i = 1; i <= n; ++i)
    {
        cin >> left >> right;

        nodes[i].left = left;
        nodes[i].right = right;

        nodes[right].parent = nodes[left].parent = i;
    }

    int root = 1;

    while (nodes[root].parent) root = nodes[root].parent;

    cout << find_LCA(root, x, y, nodes);
    
    return 0;
}