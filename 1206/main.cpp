#include <iostream>
#include <cstring>
using namespace std;

class seqStack
{
private:
    int *elem;
    int top_p;
    int maxSize;
    void doublespace();

public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const int &x);
    int pop();
    int top() const;
};

seqStack::seqStack(int initSize)
{
    elem = new int[initSize];
    maxSize = initSize;
    top_p = -1;
}

seqStack::~seqStack()
{
    delete [] elem;
}

void seqStack::doublespace()
{
    int *tmp = elem;

    elem = new int[maxSize * 2];
    for (int i = 0; i < maxSize; i++) elem[i] = tmp[i];

    maxSize *= 2;
    delete [] tmp;
}

bool seqStack::isEmpty() const
{
    return top_p == -1;
}

void seqStack::push(const int &x)
{
    if (top_p == maxSize - 1) doublespace();
    elem[++top_p] = x;
}

int seqStack::pop()
{
    return elem[top_p--];
}

int seqStack::top() const
{
    if (top_p == -1) return -1;    /////////////////////////////////////////////
    return elem[top_p];
}

int main()
{
    seqStack my_stack = seqStack();
    char word[200];

    bool tag = true;

    // int 1 for "begin";
    // int 2, 3 for "if", "then";
    while (cin >> word)
    {
        if (strcmp(word, "begin") == 0)
        {
            if (my_stack.top() == 2)
            {
                cout << "Error!";
                tag = false;
                break;
            }

            else
            {
                my_stack.push(1);
                continue;
            }
        }

        if (strcmp(word, "if") == 0)
        {
            if (my_stack.top() == 2)
            {
                cout << "Error!";
                tag = false;
                break;
            }

            else
            {
                my_stack.push(2);
                continue;
            }
        }

        if (strcmp(word, "then") == 0)
        {
            if (my_stack.top() == 2)
            {
                my_stack.pop();
                my_stack.push(3);
                continue;
            }

            else
            {
                cout << "Error!";
                tag = false;
                break;
            }
        }

        if (strcmp(word, "else") == 0)
        {
            if (my_stack.top() == 3)
            {
                my_stack.pop();
                continue;
            }

            else
            {
                cout << "Error!";
                tag = false;
                break;
            }
        }

        if (strcmp(word, "end") == 0)
        {
            while (my_stack.top() == 3) my_stack.pop();

            if (my_stack.top() == 1) my_stack.pop();

            else
            {
                cout << "Error!";
                tag = false;
                break;
            }
        }
    }

    while (my_stack.top() == 3) my_stack.pop();

    if (tag)
    {
        if (my_stack.isEmpty())
        {
            cout << "Match!";
            return 0;
        }

        else
        {
            cout << "Error!";
            return -1;
        }
    }

}
