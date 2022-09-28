#include"factorial_a.h"
using namespace std;
extern const int maxn;
int main()
{
    int n;
    printf("    求n的阶乘\n");
    printf("请输入n>>");
    cin >> n;
    int a[maxn];
    memset(a, -1, sizeof(a));
    a[0] = 1;
    for(int b = 1; b <= n; b++)
    {
        multiply(a , b);
    }
    cout << "结果为\n";
    print(a);
    return 0;
}