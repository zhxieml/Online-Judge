#include <iostream>
#include <cstring>
using namespace std;

// 写出两个函数的声明

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
char *funA(char **p) {
    return *p;
}

char *funB(char *b, char **p) {
    
}