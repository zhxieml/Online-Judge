#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED
    #include <iostream>
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
#endif