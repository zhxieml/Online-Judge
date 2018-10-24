#include <iostream>
using namespace std;

//struct node
//{
//    int data;
//
//    node *next;
//
//    node(int x, node *n = NULL)
//    {
//        data = x;
//        next = n;
//    }
//
//    node(): next(NULL){}
//    ~node(){}
//};
//
///////////////////////////////////////////////////
//
//int main()
//{
//    int n, m;
//    cin >> n >> m;
//
//    node *head = new node(1);
//    node *tmp = head;
//
//    for (int i = 1; i < n; i++)
//    {
//        tmp->next = new node(i + 1);
//        tmp = tmp->next;
//    }
//
//    tmp->next = head;
//
//    int op[100011], index[100011], number[100011];
//
//    for (int i = 0; i < m; i++)
//    {
//        cin >> op[i];
//        if (op[i] == 0)
//        {
//            cin >> index[i];
//            number[i] = 0;
//        }
//        else cin >> index[i] >> number[i];
//    }
//
//    ////////////////////////////////////////////////////////////
////
////    for (int i = 0; i < 100; i++)
////    {
////        cout << tmp->data << endl;
////        tmp = tmp->next;
////    }
//
//    int count = 0;
//    node *p = tmp;
//
//    int call = 0;
//
//    while (count < m && n > 0)
//    {
//        if ((call % 5 + 1) == index[count])
//        {
//            if (op[count] == 0)
//            {
//                node *del = p->next;
//                p->next = del->next;
//                delete del;
//                p = p->next;
//                call = 1;
//                n--;
//            }
//
//            if (op[count] == 1)
//            {
//                node *add = new node(number[count]);
//                tmp = p->next;
//                add->next = tmp->next;
//                tmp->next = add;
//                p = p->next;
//                call = 1;
//                n++;
//            }
////            switch (op[count])
////            {
////                case 0:
////
////                    break;
////                case 1:
////
////                    break;
////            }
//            count++;
//        }
//
//        else
//        {
//            p = p->next;
//            call = call % 5 + 1;
//        }
//
////        cout << call << " " << p->data << endl;
//    }
//
//
//    int sum = 0;
//    for (int i = 0; i < n; i++)
//    {
//        sum += p->data;
//        p = p->next;
//    }
//
//    cout << sum;
//    return 0;
//}

int main()
{
    int n, m;
    cin >> n >> m;

    int monkeys[10000];

    for (int i = 0; i < n; i++) monkeys[i] = i + 1;

    int index = 0;

    int op, n1, n2;

    for (int i = 0; i < m; i++)
    {
        cin >> op;

        if (op == 0)
        {
            cin >> n1;

            index = (index + n1 - 1) % n;

            for (int j = index + 1; j < n; j++) monkeys[j - 1] = monkeys[j];
            n--;
        }

        else
        {
            cin >> n1 >> n2;

            index = (index+ n1) & n;
            for (int j = n; j > index; j--) monkeys[j] = monkeys[j - 1];

            monkeys[index] = n2;

            n++;
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++) sum += monkeys[i];

    cout << sum;
}

















