#include"bit_operation.h"
using namespace std;
int main()
{
loop:
    char op;
    int a, b;
    printf("====================================\n");
    printf("请选择功能：\n");
    printf("A,与 B,或 C,非 D,异或 E,左移 F,右移\n");
    printf("1,加法 2,减法 3,乘法 4,退出\n");
    printf(">>");
    cin >> op;
    Bit_Operation Bit;
    switch(op)
    {
    case '1':
    {
        system("cls");
        printf("请输入第一个数>>");
        cin >> a;
        printf("请输入第二个数>>");
        cin >> b;
        cout << "结果为:" << add(a, b);
        break;
    }
    case '2':
    {
        system("cls");
        printf("请输入被减数>>");
        cin >> a;
        printf("请输入减数>>");
        cin >> b;
        cout << "结果为:" << sub(a, b);
        break;
    }
    case '3':
    {
        system("cls");
        printf("请输入第一个乘数>>");
        cin >> a;
        printf("请输入第二个乘数>>");
        cin >> b;
        cout << "结果为:" << multiply(a, b);
        break;
    }
    case '4':
    {
        return 0;
        break;
    }
    case 'A':
    {
        system("cls");
        printf("请输入第一个数>>");
        cin >> a;
        printf("请输入第二个数>>");
        cin >> b;
        cout << "与:" << Bit.Yu(a,b);
        break;
    }
    case 'B':
    {
        system("cls");
        printf("请输入第一个数>>");
        cin >> a;
        printf("请输入第二个数>>");
        cin >> b;
        cout << "或:" << Bit.Huo(a,b);
        break;
    }
    case 'C':
    {
        system("cls");
        printf("请输入数>>");
        cin >> a;
        cout << "非:" << Bit.Fan(a);
        break;
    }
    case 'D':
    {
        system("cls");
        printf("请输入第一个数>>");
        cin >> a;
        printf("请输入第二个数>>");
        cin >> b;
        cout << "异或:" << Bit.Yihuo(a,b);
        break;
    }
    case 'E':
    {
        system("cls");
        printf("请输入数>>");
        cin >> a;
        printf("请输入左移位数>>");
        cin >> b;
        cout << "结果为:" << Bit.Zy(a,b);
        break;
    }
    case 'F':
    {
        system("cls");
        printf("请输入数>>");
        cin >> a;
        printf("请输入右移位数>>");
        cin >> b;
        cout << "结果为:" << Bit.Yy(a,b);
        break;
    }
    default:
    {
        printf("无该服务\n");
        printf("按任意键继续……\n");
        getchar();
        getchar();
        system("cls");
        goto loop;
        break;
    }
    }
    printf("\n按任意键退出……\n");
    getchar();
    getchar();
    return 0;
}