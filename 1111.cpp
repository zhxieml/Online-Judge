#include <iostream>
#include <cstring>
using namespace std;

char result[1010] = {0};
int maxIndex = 0;

int orderToTree(char pre[], char mid[], int index)
{
    int length = strlen(pre);

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

        orderToTree(leftPre, leftMid, index);
    }

    if (length - rootIndex > 1 && rootIndex >= 1)
    {
        index++;
        maxIndex = index > maxIndex ? index : maxIndex;

        result[index - 1] = pre[rootIndex + 1];

        orderToTree(rightPre, rightMid, index);
    }

    if (length - rootIndex > 1 && rootIndex < 1)
    {
        index = index * 2 + 1;
        maxIndex = index > maxIndex ? index : maxIndex;

        result[index - 1] = pre[rootIndex + 1];

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

    result[0] = pre[0];

    int index = orderToTree(pre, mid, 1);

    for (int i = 0; i < index; i++)
    {
        if (result[i] == 0) cout << "NULL ";
        else cout << result[i] << ' ';
    }

    return 0;
}


