#include<iostream>
#include<string>
using namespace std;

class Female;
class Male
{
    Female *pWife;
public:
    string nm;
    Male(string _nm) { nm = _nm, m_buffer[m_sum++] = this; }
    Female *&getWife() { return pWife; }
    static Male *m_buffer[100];
    static int m_sum;
};

int Male::m_sum = 0;
Male *Male::m_buffer[100];

class Female
{
public:
    string nm;
    Female(string _nm){nm = _nm;}
    Male *getHusband();
};

Male *Female::getHusband()
{
    for (int i = 0; i < Male::m_sum; i++)
        if (Male::m_buffer[i]->getWife() == this)
            return Male::m_buffer[i];
    return 0;
}

int main()
{
    Male a("ymx"), b("msj");
    Female c("jiaran"), d("IU");
    a.getWife() = &c;
    b.getWife() = &d;
    cout << d.nm<< "'s husband is "<<d.getHusband()->nm << endl;
    cout << a.nm<< "'s wife is "<<a.getWife()->nm;
}
