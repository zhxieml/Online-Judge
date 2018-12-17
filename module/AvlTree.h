#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
    template <class Type>
    class AvlTree
    {
    private:
        struct AvlNode
        {  
            Type data;
            AvlNode *left;
            AvlNode *right;
            int height;
        
            AvlNode(const Type &element, AvlNode *lt, AvlNode *rt, int h = 0): data(element), left(lt), right(rt), height(h) {}
        };

        AvlNode *root;

        void insert(const Type &x, AvlNode *&t);
        bool remove(const Type &x, AvlNode *&t);
        void makeEmpty(AvlNode *&t);
        int height(AvlNode *t) const {return t == NULL ? -1 : t->height;}
        void LL(AvlNode *&t);
        void LR(AvlNode *&t);
        void RL(AvlNode *&t);
        void RR(AvlNode *&t);
        int max(int a, int b) {return (a>b)?a:b;}

    public:
        AvlTree(AvlNode *t = NULL) {root = t;}
        ~AvlTree() {makeEmpty(root);}

        bool find(const Type &x) const;
        void insert(const Type &x) {insert(x, root);}
        void remove(const Type &x) {remove(x, root);}
    }; 
#endif