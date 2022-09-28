#include <iostream>
using namespace std;

class Female;
class Male
{
    Female *pWife;

public:
    Female *&getWife() { return pWife; }
};

class Female
{
    Male *pHusband;

public:
    Male *&getHusband() { return pHusband; }
};

int main()
{
    Female a, c;
    Male b, d;
    a.getHusband() = &b;
    b.getWife() = &a;
}
