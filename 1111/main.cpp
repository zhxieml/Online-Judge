#include <iostream>
#include <cstring>
using namespace std;

char result[1010] = {0};
int maxIndex = 0;

//struct node
//{
//    char data;
//    int index;
//    node *left, *right, *parent;
//
//    node(char d = ' ', int i = 0, node *l = NULL, node *r = NULL, node *p = NULL): data(d), index(i), left(l), right(r), parent(p){}
//    ~node(){}
//};
//
//////////////////////////////////////////////////////////////
//
//template <class Type>
//class linkQueue
//{
//private:
//    struct node
//    {
//        Type data;
//
//        node *next;
//
//        node(const Type &x, node *n = NULL)
//        {
//            data = x;
//            next = n;
//        }
//
//        node(): next(NULL){}
//        ~node(){}
//    };
//
//    node *front, *rear;
//
//public:
//    linkQueue();
//    ~linkQueue();
//    bool isEmpty() const;
//    void enQueue(const Type &x);
//    Type deQueue();
//    Type getHead() const;
//};
//
//template <class Type>
//linkQueue<Type>::linkQueue()
//{
//    front = rear = NULL;
//}
//
//template <class Type>
//linkQueue<Type>::~linkQueue()
//{
//    node *tmp;
//    while (front != NULL)
//    {
//        tmp = front;
//        front = front->next;
//        delete tmp;
//    }
//}
//
//template <class Type>
//bool linkQueue<Type>::isEmpty() const
//{
//    return front == NULL;
//}
//
//template <class Type>
//Type linkQueue<Type>::getHead() const
//{
//    return front->data;
//}
//
//template <class Type>
//void linkQueue<Type>::enQueue(const Type &x)
//{
//    if (rear == NULL) front = rear = new node(x);
//    else rear = rear->next = new node(x);
//}
//
//template <class Type>
//Type linkQueue<Type>::deQueue()
//{
//    node *tmp = front;
//    Type value = front->data;
//    front = front->next;
//    if (front == NULL) rear = NULL; // empty
//    delete tmp;
//    return value;
//}

////////////////////////////////////////////////////////////

int orderToTree(char pre[], char mid[], int index)
{
    int length = strlen(pre);
//    cout << "length:" << length << endl;
//    cout << "index:" << index << endl;

    if (length == 0 || length == 1) return 1;

    char leftPre[100], leftMid[100], rightPre[100], rightMid[100];
    int rootIndex;

    for (int i = 0; i < length; i++)
    {
        if (mid[i] == pre[0])
        {
            rootIndex = i;
            break;
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (i < rootIndex)
        {
            leftMid[i] = mid[i];
            leftPre[i] = pre[i + 1];
        }

        if (i > rootIndex)
        {
            rightMid[i - rootIndex - 1] = mid[i];
            rightPre[i - rootIndex - 1] = pre[i];
        }
    }

    leftMid[rootIndex] = leftPre[rootIndex] = rightMid[length - rootIndex - 1] = rightPre[length - rootIndex - 1] = '\0';

    if (rootIndex >= 1)
    {
        index *= 2;
        maxIndex = index > maxIndex ? index : maxIndex;
        result[index - 1] = pre[1];
//        root->left = new node(pre[1], index);
        orderToTree(leftPre, leftMid, index);
    }

    if (length - rootIndex > 1 && rootIndex >= 1)
    {
        index++;
        maxIndex = index > maxIndex ? index : maxIndex;
        result[index - 1] = pre[rootIndex + 1];
//        root->right = new node(pre[rootIndex + 1], index);
        orderToTree(rightPre, rightMid, index);
    }

    if (length - rootIndex > 1 && rootIndex < 1)
    {
        index = index * 2 + 1;
        maxIndex = index > maxIndex ? index : maxIndex;
        result[index - 1] = pre[rootIndex + 1];
//        root->right = new node(pre[rootIndex + 1], index);
        orderToTree(rightPre, rightMid, index);
    }

    result[maxIndex] = '\0';

    return maxIndex;
}

////////////////////////////////////////////////////////////

int main()
{
    char pre[100], mid[100];
    cin >> pre >> mid;

//    node *root = new node(pre[0], 1);
    result[0] = pre[0];

    int index = orderToTree(pre, mid, 1);

    for (int i = 0; i < index; i++)
    {
        if (result[i] == 0) cout << "NULL ";
        else cout << result[i] << ' ';
    }

//    linkQueue<node *> que;
//    node *tmp;
//
//    que.enQueue(root);
//
//    while (!que.isEmpty())
//    {
//        tmp = que.deQueue();
//        if (tmp->data == ' ') cout << "NULL ";
//        else cout << tmp->data << ' ';
//
//        if (tmp->left) que.enQueue(tmp->left);
//        else if (tmp->index * 2 <= maxIndex) que.enQueue(new node(' ', tmp->index * 2));
//        if (tmp->right) que.enQueue(tmp->right);
//        else if (tmp->index * 2 + 1 <= maxIndex) que.enQueue(new node(' ', tmp->index * 2 + 1));
//    }
    return 0;
}


