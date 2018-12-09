#include <iostream>
#include "math.h"
using namespace std;

class disJointSet
{
private:
    int size;
    int *parent;
    int *path;

public:
    disJointSet(int s);
    ~disJointSet();
    int find(int x);
    void unionn(int r1, int r2);
    void display(int n) const;
    void link(int a, int b);
};

disJointSet::disJointSet(int s)
{
    size = s;
    parent = new int[size];
    path = new int[size];
    for (int i = 0; i < size; i++) parent[i] = path[i] = -1;
}

disJointSet::~disJointSet()
{
    delete [] parent;
}

int disJointSet::find(int x)
{
    int start = x;
    int tmp;

    while (parent[x] >= 0) x = parent[x];

    while (start != x)
    {
        tmp = parent[start];
        parent[start] = x;
        start = tmp;
    }

    return x;
}

// r1, r2 are two roots
void disJointSet::unionn(int r1, int r2)
{
    if (r1 == r2) return;

    if (parent[r1] > parent[r2])
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }

    else
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
}

void disJointSet::link(int a, int b)
{
    if (path[a] > b || path[a] == -1) path[a] = b;
}

void disJointSet::display(int n) const
{
    cout << n << ' ';

    while (path[n] > 0)
    {
        n = path[n];
        cout << n << ' ';
    }
}

///////////////////////////////////////////////////////////////////

int main() 
{	
    int N, A, B;
    cin >> N >> A >> B;
    int scale = N * (1 + N) / 2;

    int *level = new int[scale + 1];
    int index = 1;
    level[0] = 0;
    level[1] = 1;
    for (int i = 2; i <= scale; ++i) 
    {
        if (i >= index + level[i - 1]) 
        {
            level[i] = level[i - 1] + 1;
            index = i;
        }

        else level[i] = level[i - 1];
    }

    disJointSet djs(scale);
    int grid, wall;
    // int a, b;
    int to_link;

    // cout << djs.find(A) << djs.find(B);

    while (djs.find(A) != djs.find(B))
    {
        cin >> grid >> wall;

        // a = djs.find(grid);

        switch (wall)
        {
            case 0: 
                if (level[grid] == level[grid - 1]) to_link = grid - level[grid];
                break;

            case 1:
                if (grid != scale && level[grid] == level[grid + 1]) to_link = grid - level[grid] + 1;
                break;

            case 2:
                if (level[grid] != N) to_link = grid + level[grid];
                break;

            case 3:
                if (level[grid] != N) to_link = grid + level[grid] + 1;
        }

        djs.unionn(djs.find(grid), djs.find(to_link));

        if (A == grid)
        {
            djs.link(grid, to_link);
            continue;
        }

        if (A == to_link)
        {
            djs.link(to_link, grid);
            continue;
        }

        if (B == grid)
        {
            djs.link(to_link, grid);
            continue;
        }

        if (B == to_link)
        {
            djs.link(grid, to_link);
            continue;
        }

        djs.link(grid, to_link);
    }

    djs.display(A);

    // cout << int(pow(2, 3)) << endl;
    return 0;
}