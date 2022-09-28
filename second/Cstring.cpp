#include "CString.h"
using namespace std;
int main()
{
    CString m("software");
    CString n(m), o;
    o = m;
    cout << n[4] << endl;
    cout << n.len() << endl;
    o = m + n;
    o = m(2, 8);
    cout << o << endl;
}