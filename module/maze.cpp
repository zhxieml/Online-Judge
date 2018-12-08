#include <iostream>
#include "time.h"
using namespace std;

class disJointSet
{
private:
    int size;
    int *parent;

public:
    disJointSet(int s);
    ~disJointSet();
    int find(int x);
    void unionn(int r1, int r2);
};

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

int disJointSet::find(int x)
{
    if (parent[x] < 0) return x;
    return parent[x] = find(parent[x]);
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

void createPuzzle(int size) //size为迷宫的规模
{ 
    int num1, num2;
    disJointSet ds(size*size); 
    srand(time(0));
    while (ds.find(0) != ds.find(size*size-1)) 
    {
        while (true) 
        { //选择两个相邻的不连通单元
            num1 = rand() * size * size / (RAND_MAX + 1);
            num2 = num1-size;  //检查上方的单元
            if (num2 >= 0) 
            {
                if (ds.find(num1) != ds.find(num2)) break;  
            }
            num2 = num1 - 1;    //检查左边的单元

	        if (num1 % size != 0)   
            {
                if (ds.find(num1) != ds.find(num2)) break;
            }
            num2 = num1 + size;    //检查下方的单元

            if (num2 < size * size)   
            {
                if (ds.find(num1) != ds.find(num2)) break;
            }
	        num2 = num1 + 1;  //检查右边的单元

            if (num2 % size != 0) 
            {
                if (ds.find(num1) != ds.find(num2)) break;
            }
	    }
        
        ds.unionn(ds.find(num1), ds.find(num2));
        cout << '<' << num1 << ',' << num2 << ">, ";
    }
} 