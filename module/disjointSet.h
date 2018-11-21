#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED
    #include <iostream>
    using namespace std;

    class disjointSet
    {
    private:
        int size;
        int *parent;

    public:
        disjointSet(int s);
        ~disjointSet();
        int find(int x);
        void union(int r1, int r2);
    };
#endif