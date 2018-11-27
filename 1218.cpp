#include <iostream>
using namespace std;

template <class Type>
class binarySearchTree
{
private:
    struct node
    {
        Type data;
        node *left, *right;

        node(const Type &d, node *l, node *r): data(d), left(l), right(r){}
    };

    node *root;

    void insert(const Type &x, node *&p);
    void remove(const Type &x, node *&p);
    bool find(const Type &x, node *p) const;
    void clear(node *p);
    void display(node *p) const;

public:
    binarySearchTree(node *r = NULL): root(r){};
    ~binarySearchTree();
    bool find(const Type &x) const;
    void insert(const Type &x);
    void remove(const Type &x);
    void clear();
    void display() const;   // Display in order
};

template <class Type>
binarySearchTree<Type>::~binarySearchTree()
{
    clear(root);
}

template <class Type>
bool binarySearchTree<Type>::find(const Type &x) const
{
    return find(x, root);
}

template <class Type>
bool binarySearchTree<Type>::find(const Type &x, node *p) const
{
    if (!p) return false;

    if (x < p->data) return find(x, p->left);

    if (x > p->data) return find(x, p->right);

    return true;
}

template <class Type>
void binarySearchTree<Type>::insert(const Type &x)
{
    insert(x, root);
}

template <class Type>
void binarySearchTree<Type>::insert(const Type &x, node *&p)
{
    if (!p) p = new node(x, NULL, NULL);

    else
    {
        if (x < p->data) insert(x, p->left);

        else if (x > p->data) insert(x, p->right);
    }
}

template <class Type>
void binarySearchTree<Type>::remove(const Type &x)
{
    remove(x, root);
}

template <class Type>
void binarySearchTree<Type>::remove(const Type &x, node *&p)
{
    if (!p) return;

    if (x < p->data) remove(x, p->left);

    else
    {
        if (x > p->data) remove(x, p->right);

        else
        {
            if (p->left && p->right)
            {
                node *tmp = p->right;

                while (tmp->left) tmp = tmp->left;
                p->data = tmp->data;
                remove(p->data, p->right);
            }

            else 
            {
                node *tmp = p;
                p = (p->left) ? p->left:p->right;
                delete tmp;
            }
        }
    }
}

template <class Type>
void binarySearchTree<Type>::clear()
{
    clear(root);
}

template <class Type>
void binarySearchTree<Type>::clear(node *p)
{
    if (!p) return;

    if (p->left) clear(p->left);
    if (p->right) clear(p->right);

    delete p;
}

template <class Type>
void binarySearchTree<Type>::display() const
{
    display(root);
}

template <class Type>
void binarySearchTree<Type>::display(node *p) const
{
    if (!p) return;

    if (p->left) display(p->left);

    cout << p->data << ' ';

    if (p->right) display(p->right);
}

/////////////////////////////////////////////////////////

int main() 
{	
    binarySearchTree<int> *tree = new binarySearchTree<int>;
    binarySearchTree<int> *tmp = new binarySearchTree<int>;

    char op;
    int num, opNum, opElem;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        cin >> op >> opNum;

        switch (op)
        {
            case '+': 
                for (int j = 0; j < opNum; j++)
                {
                    cin >> opElem;

                    tree->insert(opElem);
                }

                tree->display();
                cout << endl;
                break;
            
            case '-':
                for (int j = 0; j < opNum; j++)
                {
                    cin >> opElem;

                    tree->remove(opElem);
                } 

                tree->display();
                cout << endl;
                break;

            case '*':
                for (int j = 0; j < opNum; j++)
                {
                    cin >> opElem;
                    
                    if (tree->find(opElem)) tmp->insert(opElem);
                }

                tmp->display();
                cout << endl;

                delete tree;
                tree = tmp;
                tmp = new binarySearchTree<int>;
                break;
        }
    }

    return 0;
}