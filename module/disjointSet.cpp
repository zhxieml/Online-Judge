#include <iostream>
#include "disJointSet.h"
using namespace std;

disJointSet::disJointSet(int s)
{
    size = s;
    parent = new int[size];
    for (int i = 0; i < size; i++) parent[i] = -1;
}

disJointSet::~disJointSet()
{
    delete [] parent;
}

// int disJointSet::find(int x)
// {
//     if (parent[x] < 0) return x;
//     return parent[x] = find(parent[x]);
// }

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