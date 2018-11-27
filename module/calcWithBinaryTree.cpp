#include <iostream>
using namespace std;

class calc
{
private:
    enum Type{DATA, ADD, SUB, MULTI, DIV, OPAREN, CPAREN, EOL};

    struct node
    {
        Type type;
        int data;
        node *left, *right;
        
        node(Type t, int d = 0, node *l = NULL, node *r = NULL): type(t), data(d), left(l), right(r) {}
    };

    node *root;

    node *create(char *&s);
    Type getToken(char *&s, int &value);
    int result(node *p);

public:
    calc(char *s) {root = create(s);}
    int result();
};

int calc::result(calc::node *p)
{
    int n1, n2;

    if (p->type == DATA) return p->data;

    n1 = result(p->left);
    n2 = result(p->right);

    switch (p->type)
    {
        case ADD:
            p->data = n1 + n2;
            break;
        
        case SUB:
            p->data = n1 - n2;
            break;

        case MULTI:
            p->data = n1 * n2;
            break;
        
        case DIV:
            p->data = n1 / n2;
            break;
    }

    return p->data;
}

int calc::result()
{
    if (!root) return 0;

    return result(root);
}

calc::node *calc::create(char *&s)
{
    calc::node *p, *root = NULL;
    Type returnType;
    int value;

    while (*s)
    {
        returnType = calc::getToken(s, value);

        switch (returnType)
        {
            case DATA: case OPAREN:
                if (returnType == DATA) p = new calc::node(DATA, value);
                else p = create(s);
                
                if (root)
                {
                    if (!root->right) root->right = p;
                    else root->right->right = p;
                }

                break;
            
            case CPAREN: case EOL:
                return root;

            case ADD: case SUB:
                if (!root) root = new node(returnType, 0, p);
                else root = new node(returnType, 0, root);
                
                break;

            case MULTI: case DIV:
                if (!root) root = new node(returnType, 0, p);
                else 
                {
                    if (root->type == MULTI || root->type == DIV) root = new node(returnType, 0, root);
                    else root->right = new node(returnType, 0, root->right);
                }
        }
    }
}

calc::Type calc::getToken(char *&s, int &data)
{
    char type;

    while (*s == ' ') s++;

    if (*s >= '0' && *s <= '9')
    {
        data = 0;
        while (*s >= '0' && *s <= '9')
        {
            data = data * 10 + *s -'0';
            s++;
        }

        return DATA;
    }

    if (*s == '\0') return EOL;

    type = *s;
    s++;

    switch (type)
    {
        case '+':
            return ADD;

        case '-':
            return SUB;

        case '*':
            return MULTI;

        case '/':
            return DIV;

        case '(':
            return OPAREN;
        
        case ')':
            return CPAREN;

        default:
            return EOL;
    }
}