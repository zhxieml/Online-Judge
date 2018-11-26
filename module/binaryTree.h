#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
    template <class Type> 
    class binaryTree 
    {
    private:
        struct node 
        {  
            Type data;
            node *left, *right;
            
            node(): left(NULL), right(NULL) {}
            node(Type item, node *l = NULL, node *r = NULL): data(item), left(l), right(r) {}
            ~node() {} 
        };

        node *root;

    public: 
        binaryTree():root(NULL) {}
        binaryTree(const Type &value) {root = new node(value);} 
        binaryTree(node *p) {root = p;}
        ~binaryTree() {clear();}

        Type getRoot() const {return root->data;}
        Type getLeft() const {return root->left->data;}
        Type getRight() const {return root->right->data;}
        void makeTree(const Type &x, binaryTree &lt, binaryTree &rt);
        void delLeft();
        void delRight();
        bool isEmpty() const {return root == NULL;}
        void clear();
        int size() const {return size(root);} 
        int height() const {return height(root);}
        void preTraveral() const;
        void postTraveral() const;
        void midTraveral() const;
        void createTree(Type flag);

    private:
        void clear(node *t);
        int height(node *t) const;
        int size(node *t) const;
        void preTraveral(node *t) const;
        void postTraveral(node *t) const;
        void midTraveral(node *t) const;
    }; 

#endif