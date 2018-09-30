#include <iostream>
#include <cstring>
using namespace std;

class sLinkList
{
    private:
        struct node
        {
            char data;
            node *next;

            node(const char &x, node *n = NULL) {data = x; next = n;}
            node(): next(NULL){}
            ~node(){}
        };

        node *head;
        int currentLength;

        node *move(int i) const;

    public:
        sLinkList();
        ~sLinkList(){clear(); delete head;}

        void clear();
        void display() const;
        bool insert(int i, char *x);
        bool remove(int i, int n);

//        sLinkList &operator=(const sLinkList &s);
};

sLinkList::node *sLinkList::move(int i) const
{
//    if (i > currentLength) return NULL;
//    if (currentLength == 0) return head;
    node *p = head;
    while (i-- >= 0) p = p->next;
    return p;
}

sLinkList::sLinkList()
{
    head = new node;
    head->next = NULL;
    currentLength = 0;
}

void sLinkList::clear()
{
    node *p = head->next, *q;
    head->next = NULL;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }

    currentLength = 0;
}

void sLinkList::display() const
{
    node *p = head->next;
    while (p != NULL)
    {
        cout << p->data;
        p = p->next;
    }
    cout << endl;
}

bool sLinkList::insert(int i, char *x)
{
    node *pos;

    if (i > currentLength || i < 0) return false;

    if (i == 0) pos = head;
    else pos = move(i - 1);

    for (int j = 0; j < strlen(x); j++)
    {
        pos->next = new node(x[j], pos->next);
        ++currentLength;
        pos = pos->next;
    }

    return true;
//    pos->next = new node(x, pos->next);
//    ++currentLength;
}

bool sLinkList::remove(int i, int n)
{
    if (currentLength < i + n - 1) return false;
    node *pos, *delp;

    pos = move(i - 1);
    for (int j = 0; j < n; j++)
    {
        delp = pos->next;
        pos->next = delp->next;
        delete delp;
        --currentLength;
    }

    return true;
}


int main()
{
    sLinkList lines[100];
    char line[2000];
    int count_line = 0;

    while (true)
    {
        cin.getline(line, 2000, '\n');
        if (strcmp(line, "******") == 0) break;

        lines[count_line].insert(0, line);
        count_line++;
    }


    while (true)
    {
        char order[5];
        cin >> order;
        int n1, n2;

        if (strcmp(order, "quit") == 0)
        {
            for (int i = 0; i < count_line; i++) lines[i].display();
            return 0;
        }

        if (strcmp(order, "list") == 0)
        {
            cin >> n1 >> n2;
            if (n1 > count_line || n2 > count_line || n1 <= 0 || n2 < n1)
            {
                cout << "Error!" << endl;
                continue;
            }

            for (int i = n1 - 1; i < n2; i++) lines[i].display();
        }

        if (strcmp(order, "ins") == 0)
        {
            char ins_str[100];
            cin >> n1 >> n2;
            cin.get();
            cin.getline(ins_str, 100, '\n');
            if (n1 > count_line || n1 < 0 || n2 < 0)
            {
                cout << "Error!" << endl;
                continue;
            }

            if (!lines[n1 - 1].insert(n2 - 1, ins_str)) cout << "Error!" << endl;
        }

        if (strcmp(order, "del") == 0)
        {
            int num;
            cin >> n1 >> n2 >> num;
            if (n1 > count_line || n1 < 0)
            {
                cout << "Error!" << endl;
                continue;
            }

            if (!lines[n1 - 1].remove(n2 - 1, num)) cout << "Error!" << endl;
        }

    }

    return 0;
}
