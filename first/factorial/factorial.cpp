#include"factorial.h"
using namespace std;
extern const int maxn;
int main()
{
    int n;
    printf("    求n的阶乘\n");
    printf("请输入n>>");
    cin >> n;
    int a[maxn], b[maxn], c[maxn], plus[10];
    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));
    memset(c, -1, sizeof(c));
    memset(plus, -1, sizeof(plus));
    a[0] = 1;
    plus[0] = 1;
    for(int i = 0; i <= n - 1; i++)
    {
        add(plus, b);
        multiply(a , b , c);
        val(a, c);
        memset(c, -1, sizeof(c));
    }
    cout << "结果为\n";
    print(a);
    return 0;
}