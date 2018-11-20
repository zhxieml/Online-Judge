#include <iostream>
#include <cstring>
using namespace std;

class binarySearchTree
{
private:
    struct node
    {
        int data;
        node *left, *right;

        node(int d, node *l, node *r): data(d), left(l), right(r){}
    };

    node *root;

    void insert(int x, node *&p);
    void remove(int x, node *&p);
    void remove_less_than(int x, node *&p);
    void remove_greater_than(int x, node *&p);
    void remove_interval(int a, int b, node *&p);
    bool find(int x, node *p) const;
    void find_ith(int &x, int &result, node *p) const;
    void clear(node *p);
    void display(node *p) const;

public:
    binarySearchTree(node *r = NULL): root(r){};
    ~binarySearchTree();

    bool find(int x) const;
    int find_ith(int x) const;
    void insert(int x);
    void remove(int x);
    void remove_less_than(int x);
    void remove_greater_than(int x);
    void remove_interval(int a, int b);
    void clear();
    void display() const;   // Display in order
};

binarySearchTree::~binarySearchTree()
{
    clear(root);
}

bool binarySearchTree::find(int x) const
{
    return find(x, root);
}

bool binarySearchTree::find(int x, node *p) const
{
    if (!p) return false;

    if (x < p->data) return find(x, p->left);

    if (x > p->data) return find(x, p->right);

    return true;
}

int binarySearchTree::find_ith(int x) const
{
    int result = -1;
    find_ith(x, result, root);
    return result;
}

void binarySearchTree::find_ith(int &x, int &result, node *p) const
{
    if (!p || !x) return;
    find_ith(x, result, p->left);
    
    x--;
    if (x == 0) 
    {
        result = p->data;
        return;
    }

    find_ith(x, result, p->right);
}

void binarySearchTree::insert(int x)
{
    insert(x, root);
}

void binarySearchTree::insert(int x, node *&p)
{
    if (!p) p = new node(x, NULL, NULL);

    else
    {
        if (x < p->data) insert(x, p->left);

        else if (x >= p->data) insert(x, p->right);
    }
}

void binarySearchTree::remove(int x)
{
    remove(x, root);
}

void binarySearchTree::remove(int x, node *&p)
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

void binarySearchTree::remove_less_than(int x)
{
    remove_less_than(x, root);
}

void binarySearchTree::remove_less_than(int x, node *&p)
{
    if (!p) return;

    if (x > p->data && !p->right && !p->left)
    {
        delete p;
        p = NULL;
    } 

    else
    {
        if (p->left) remove_less_than(x, p->left);
        if (p->right) remove_less_than(x, p->right);

        if (x > p->data)
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

void binarySearchTree::remove_greater_than(int x)
{
    remove_greater_than(x, root);
}

void binarySearchTree::remove_greater_than(int x, node *&p)
{
    if (!p) return;

    if (x < p->data && !p->right && !p->left)
    {
        delete p;
        p = NULL;
    } 

    else
    {
        if (p->left) remove_greater_than(x, p->left);
        if (p->right) remove_greater_than(x, p->right);

        if (x < p->data)
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

void binarySearchTree::remove_interval(int a, int b)
{
    remove_interval(a, b, root);
}

void binarySearchTree::remove_interval(int a, int b, node *&p)
{
    if (!p) return;

    if (a < p->data && b > p->data && !p->right && !p->left)
    {
        delete p;
        p = NULL;
    } 

    else
    {
        if (p->left) remove_interval(a, b, p->left);
        if (p->right) remove_interval(a, b, p->right);

        if (a < p->data && b > p->data)
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

void binarySearchTree::clear()
{
    clear(root);
}

void binarySearchTree::clear(node *p)
{
    if (!p) return;

    if (p->left) clear(p->left);
    if (p->right) clear(p->right);

    delete p;
}

void binarySearchTree::display() const
{
    display(root);
}

void binarySearchTree::display(node *p) const
{
    if (!p) return;

    if (p->left) display(p->left);

    cout << p->data << ' ';

    if (p->right) display(p->right);
}

/////////////////////////////////////////////////////////////////

int main() 
{	
    int num;
    cin >> num;

    binarySearchTree tree;
    char op[25];
    int opNum1, opNum2;

    for (int i = 0; i < num; i++)
    {
        cin >> op;

        if (strcmp(op, "insert") == 0)
        {
            cin >> opNum1;
            tree.insert(opNum1);
            
            // tree.display();
            // cout << endl;
        }

        if (strcmp(op, "delete") == 0)
        {
            cin >> opNum1;
            tree.remove(opNum1);

            // tree.display();
            // cout << endl;
        }

        if (strcmp(op, "delete_less_than") == 0)
        {
            cin >> opNum1;
            tree.remove_less_than(opNum1);

            // tree.display();
            // cout << endl;
        }

        if (strcmp(op, "delete_greater_than") == 0)
        {
            cin >> opNum1;
            tree.remove_greater_than(opNum1);

            // tree.display();
            // cout << endl;
        }

        if (strcmp(op, "delete_interval") == 0)
        {
            cin >> opNum1 >> opNum2;
            tree.remove_interval(opNum1, opNum2);

            // tree.display();
            // cout << endl;
        }

        if (strcmp(op, "find") == 0)
        {
            cin >> opNum1;
            if (tree.find(opNum1)) cout << 'Y' << endl;
            else cout << 'N' << endl;
        }

        if (strcmp(op, "find_ith") == 0)
        {
            cin >> opNum1;
            int result = tree.find_ith(opNum1);

            if (result == -1) cout << 'N';
            else cout << result;

            cout << endl; 
        }
    }

    return 0;
}