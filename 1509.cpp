#include <iostream>
using namespace std;

class date
{
    int year;
    int month;
    int day;
    int dayType;

    date(int y, int m, int d, int dt): year(y), month(m), day(d), dayType(dt){}
    ~date(){}

    void nextWeek();
};

void date::nextWeek()
{
    if (isLunar(year))
    {
        day =
    }
}

bool isLunar(int year)
{
    if (year % 400 == 0) return true;
    if (year % 4 ==0 & year % 100 != 0) return true;
    return false;
}

int monthLunar = [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
int monthNormal = [0, 30, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

int main()
{
    int a, b, c, y1, y2;
    cin >> a >> b >> c >> y1 >> y2;


    return 0;
}
