#include <iostream>
#include "adjListGraph.h"
using namespace std;

adjListGraph::adjListGraph(int size)
{
    ver = size;
    vlist = new verNode[ver + 1];
    edge = 0;

    for (int i = 1; i <= size; i++) vlist[i].ver = i;
}

adjListGraph::~adjListGraph()
{
    edgeNode *tmp;

    for (int i = 0; i < ver; ++i)
    {
        while ((tmp = vlist[i].head) != NULL)
        {
            vlist[i].head = tmp->next;
            delete tmp;
        }
    }

    delete [] vlist;
}

bool adjListGraph::insert(int s, int e)
{
    vlist[s].head = new edgeNode(e, vlist[s].head);

    ++edge;
    return true;
}

void adjListGraph::dfs(int s, bool visited[], int l)
{
    edgeNode *tmp = vlist[s].head;

    bool *new_visited = new bool[ver + 1];
    for (int i = 1; i <= ver; ++i) new_visited[i] = visited[i];    
    new_visited[s] = true;

    --l;

    while (tmp)
    {
        if (!new_visited[tmp->end]) 
        {
            if (l != 0) dfs(tmp->end, new_visited, l);

            else ++count;
        }

        tmp = tmp->next;
    }
}

void adjListGraph::dfs(int s, int l)
{
    bool *visited = new bool[ver + 1];

    dfs(s, visited, l);
}

void adj