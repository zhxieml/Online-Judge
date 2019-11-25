#include <iostream>
#include <cstring>
using namespace std;

// 写出两个函数的声明
char *&funA(char **&p);
char *funB(char *b, char **p);

int main() {
    char a[100], b[100];
    
    for (int i = 0; i < 3; ++i) {
        char **p;
        
        cin >> a;
        funA(p) = a;

        cout << funB(b, p);
    }
    
    return 0;
}

// 写出两个函数的定义
char *&funA(char **&p) {
    p = new char *;

    return *p;
}

char *funB(char *b, char **p) {
    char *tmp = *p;
    int i;

    for (i = 0; tmp[i] != '\0'; ++i) {
        if (tmp[i] >= 'a' && tmp[i] <= 'z') 
            b[i] = tmp[i] - 32;

        else 
            b[i] = tmp[i];
    }

    b[i] = '\n';
    b[i + 1] = '\0';

    delete p;

    return b;
}